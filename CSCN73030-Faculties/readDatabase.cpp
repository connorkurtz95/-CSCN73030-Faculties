#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <algorithm> // find_if
#include <iterator>  // istreambuf_iterator

// Lightweight ad-hoc parser targeted to the mock-database.json structure.
// This variant avoids <optional> for older toolchains by using sentinel values:
// - integer id fields use -1 to indicate "null" / absent where needed.

// Data types
struct Profile { std::string username; std::string password; };
struct LogEntry { int id = -1; std::string date; };
struct Report { int id = -1; std::string report_text; int log_id = -1; int part_id = -1; int machine_id = -1; bool needs_repair = false; };
struct Part { int id = -1; std::string name; int machine_id = -1; };
struct Machine { int id = -1; std::string name; };

struct FullReport {
    int id = -1;
    std::string report_text;
    int log_id = -1;
    int part_id = -1;      // -1 means none
    int machine_id = -1;   // -1 means none
    bool needs_repair = false;
    std::string date;                    // from logs (empty if missing)
    std::string part_name;               // empty if missing
    std::string machine_name;            // empty if missing
};

// Utility: read whole file to string
static std::string readFile(const std::string &path) {
    std::ifstream in(path);
    if (!in.is_open()) return {};
    std::string s((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
    return s;
}

// Trim helpers
static void ltrim(std::string &s) { s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char c){ return !std::isspace(c); })); }
static void rtrim(std::string &s) { s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char c){ return !std::isspace(c); }).base(), s.end()); }
static void trim(std::string &s) { ltrim(s); rtrim(s); }

// Find the JSON array content for a top-level key: returns substring between the opening '[' and the matching ']'.
static std::string findArrayContent(const std::string &s, const std::string &key) {
    std::string needle = "\"" + key + "\"";
    auto pos = s.find(needle);
    if (pos == std::string::npos) return {};
    pos = s.find('[', pos);
    if (pos == std::string::npos) return {};
    size_t start = pos + 1;
    int depth = 1;
    size_t i = start;
    for (; i < s.size(); ++i) {
        char c = s[i];
        if (c == '[') ++depth;
        else if (c == ']') {
            --depth;
            if (depth == 0) break;
        }
        else if (c == '"') { // skip strings
            ++i;
            while (i < s.size()) {
                if (s[i] == '\\') { i += 2; continue; }
                if (s[i] == '"') break;
                ++i;
            }
        }
    }
    if (i >= s.size()) return {};
    return s.substr(start, i - start);
}

// Helper: find position of colon after "key"
static bool findColonAfterKey(const std::string &obj, const std::string &key, size_t &colonPos) {
    std::string needle = "\"" + key + "\"";
    auto pos = obj.find(needle);
    if (pos == std::string::npos) return false;
    pos = obj.find(':', pos + needle.size());
    if (pos == std::string::npos) return false;
    colonPos = pos;
    return true;
}

// Extract key's string value from an object text (assumes "key": "value")
static bool extractString(const std::string &obj, const std::string &key, std::string &out) {
    size_t colon;
    if (!findColonAfterKey(obj, key, colon)) return false;
    // find first quote after colon
    auto q = obj.find('"', colon+1);
    if (q == std::string::npos) return false;
    ++q;
    out.clear();
    for (size_t i = q; i < obj.size(); ++i) {
        char c = obj[i];
        if (c == '\\') { // basic escape handling
            if (i + 1 < obj.size()) { out.push_back(obj[i+1]); ++i; continue; }
        }
        if (c == '"') break;
        out.push_back(c);
    }
    trim(out);
    return true;
}

// Extract integer or null: returns true if key present; outVal set to -1 for null, otherwise parsed value.
static bool extractIntOrNull(const std::string &obj, const std::string &key, int &outVal) {
    size_t colon;
    if (!findColonAfterKey(obj, key, colon)) return false;
    size_t i = colon + 1;
    while (i < obj.size() && std::isspace((unsigned char)obj[i])) ++i;
    if (i >= obj.size()) return false;
    if (obj.compare(i, 4, "null") == 0) { outVal = -1; return true; }
    bool neg = false;
    if (obj[i] == '-') { neg = true; ++i; }
    int v = 0;
    bool any = false;
    while (i < obj.size() && std::isdigit((unsigned char)obj[i])) {
        any = true;
        v = v * 10 + (obj[i] - '0');
        ++i;
    }
    if (!any) return false;
    outVal = neg ? -v : v;
    return true;
}

// Extract integer (mandatory): returns true on success and writes outVal.
static bool extractInt(const std::string &obj, const std::string &key, int &outVal) {
    int tmp = 0;
    if (!extractIntOrNull(obj, key, tmp)) return false;
    if (tmp == -1) return false; // treat null as failure for mandatory ints
    outVal = tmp;
    return true;
}

// Extract bool: returns true on success.
static bool extractBool(const std::string &obj, const std::string &key, bool &outVal) {
    size_t colon;
    if (!findColonAfterKey(obj, key, colon)) return false;
    size_t i = colon + 1;
    while (i < obj.size() && std::isspace((unsigned char)obj[i])) ++i;
    if (i >= obj.size()) return false;
    if (obj.compare(i, 4, "true") == 0) { outVal = true; return true; }
    if (obj.compare(i, 5, "false") == 0) { outVal = false; return true; }
    return false;
}

// Iterate objects inside arrayContent (which contains comma-separated {...} objects).
static std::vector<std::string> splitObjects(const std::string &arrayContent) {
    std::vector<std::string> out;
    size_t i = 0;
    while (i < arrayContent.size()) {
        while (i < arrayContent.size() && std::isspace((unsigned char)arrayContent[i])) ++i;
        if (i >= arrayContent.size()) break;
        if (arrayContent[i] != '{') { ++i; continue; }
        int depth = 0;
        size_t start = i;
        for (; i < arrayContent.size(); ++i) {
            char c = arrayContent[i];
            if (c == '{') ++depth;
            else if (c == '}') {
                --depth;
                if (depth == 0) { ++i; break; }
            }
            else if (c == '"') {
                // skip string
                ++i;
                while (i < arrayContent.size()) {
                    if (arrayContent[i] == '\\') { i += 2; continue; }
                    if (arrayContent[i] == '"') break;
                    ++i;
                }
            }
        }
        if (i > start) {
            std::string obj = arrayContent.substr(start, i - start);
            trim(obj);
            out.push_back(std::move(obj));
        }
    }
    return out;
}

// Parsers for each top-level array
static std::vector<Profile> parseProfiles(const std::string &text) {
    std::vector<Profile> out;
    auto content = findArrayContent(text, "profiles");
    if (content.empty()) return out;
    for (auto &obj : splitObjects(content)) {
        Profile p;
        extractString(obj, "username", p.username);
        extractString(obj, "password", p.password);
        out.push_back(std::move(p));
    }
    return out;
}

static std::vector<LogEntry> parseLogs(const std::string &text) {
    std::vector<LogEntry> out;
    auto content = findArrayContent(text, "logs");
    if (content.empty()) return out;
    for (auto &obj : splitObjects(content)) {
        LogEntry l{};
        extractInt(obj, "id", l.id);
        extractString(obj, "date", l.date);
        out.push_back(std::move(l));
    }
    return out;
}

static std::vector<Report> parseReports(const std::string &text) {
    std::vector<Report> out;
    auto content = findArrayContent(text, "reports");
    if (content.empty()) return out;
    for (auto &obj : splitObjects(content)) {
        Report r{};
        extractInt(obj, "id", r.id);
        extractString(obj, "report_text", r.report_text);
        extractInt(obj, "log_id", r.log_id);
        // part_id and machine_id may be null
        int tmp = 0;
        if (extractIntOrNull(obj, "part_id", tmp)) r.part_id = tmp; else r.part_id = -1;
        if (extractIntOrNull(obj, "machine_id", tmp)) r.machine_id = tmp; else r.machine_id = -1;
        bool b = false;
        extractBool(obj, "needs_repair", b);
        r.needs_repair = b;
        out.push_back(std::move(r));
    }
    return out;
}

static std::vector<Part> parseParts(const std::string &text) {
    std::vector<Part> out;
    auto content = findArrayContent(text, "parts");
    if (content.empty()) return out;
    for (auto &obj : splitObjects(content)) {
        Part p{};
        extractInt(obj, "id", p.id);
        extractString(obj, "name", p.name);
        int tmp = 0;
        if (extractIntOrNull(obj, "machine_id", tmp)) p.machine_id = tmp; else p.machine_id = -1;
        out.push_back(std::move(p));
    }
    return out;
}

static std::vector<Machine> parseMachines(const std::string &text) {
    std::vector<Machine> out;
    auto content = findArrayContent(text, "machines");
    if (content.empty()) return out;
    for (auto &obj : splitObjects(content)) {
        Machine m{};
        extractInt(obj, "id", m.id);
        extractString(obj, "name", m.name);
        out.push_back(std::move(m));
    }
    return out;
}

// Public API functions (return C++ lists)
std::vector<Profile> getProfiles() {
    auto txt = readFile("mock-database.json");
    return parseProfiles(txt);
}
std::vector<LogEntry> getLogs() {
    auto txt = readFile("mock-database.json");
    return parseLogs(txt);
}
std::vector<Report> getReports() {
    auto txt = readFile("mock-database.json");
    return parseReports(txt);
}
std::vector<Part> getParts() {
    auto txt = readFile("mock-database.json");
    return parseParts(txt);
}
std::vector<Machine> getMachines() {
    auto txt = readFile("mock-database.json");
    return parseMachines(txt);
}

// Build full reports and print them before returning
std::vector<FullReport> getFullReports() {
    auto txt = readFile("mock-database.json");
    auto reports = parseReports(txt);
    auto logs = parseLogs(txt);
    auto parts = parseParts(txt);
    auto machines = parseMachines(txt);

    // helper lookups (linear search - fine for small test data)
    auto findLogDate = [&](int id)->std::string {
        for (auto &l : logs) if (l.id == id) return l.date;
        return std::string();
    };
    auto findPartName = [&](int id)->std::string {
        for (auto &p : parts) if (p.id == id) return p.name;
        return std::string();
    };
    auto findMachineName = [&](int id)->std::string {
        for (auto &m : machines) if (m.id == id) return m.name;
        return std::string();
    };

    std::vector<FullReport> out;
    for (auto &r : reports) {
        FullReport fr;
        fr.id = r.id;
        fr.report_text = r.report_text;
        fr.log_id = r.log_id;
        fr.part_id = r.part_id;
        fr.machine_id = r.machine_id;
        fr.needs_repair = r.needs_repair;
        fr.date = findLogDate(r.log_id);
        if (r.part_id != -1) fr.part_name = findPartName(r.part_id);
        if (r.machine_id != -1) fr.machine_name = findMachineName(r.machine_id);
        out.push_back(std::move(fr));
    }

    // Print results (simple readable format)
    for (const auto &fr : out) {
        std::cout << "Report id=" << fr.id << ", text=\"" << fr.report_text << "\", date=\"" << fr.date << "\"";
        if (fr.part_id != -1) std::cout << ", part_id=" << fr.part_id << ", part_name=\"" << fr.part_name << "\"";
        if (fr.machine_id != -1) std::cout << ", machine_id=" << fr.machine_id << ", machine_name=\"" << fr.machine_name << "\"";
        std::cout << ", needs_repair=" << (fr.needs_repair ? "true" : "false") << "\n";
    }

    return out;
}