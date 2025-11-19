#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <regex>
#include <algorithm>
#include <cctype>

struct Entry {
    std::string date;
    std::string reportText;
    std::string connectedName;
};

static std::string readFile(const std::string& path) {
    std::ifstream ifs(path);
    if (!ifs) return {};
    std::ostringstream ss;
    ss << ifs.rdbuf();
    return ss.str();
}

static std::string trim(const std::string& s) {
    size_t a = 0;
    while (a < s.size() && std::isspace(static_cast<unsigned char>(s[a]))) ++a;
    size_t b = s.size();
    while (b > a && std::isspace(static_cast<unsigned char>(s[b - 1]))) --b;
    return s.substr(a, b - a);
}

static std::regex makeTagRegex(const std::string& tag) {
    // capture any content (including newlines) inside the tag; non-greedy
    return std::regex("<\\s*" + tag + "\\s*>\\s*(.*?)\\s*<\\s*/\\s*" + tag + "\\s*>",
                      std::regex::icase | std::regex::dotall);
}

static std::vector<std::string> extractAll(const std::string& src, const std::string& tag) {
    std::vector<std::string> out;
    std::regex re = makeTagRegex(tag);
    std::sregex_iterator it(src.begin(), src.end(), re);
    std::sregex_iterator end;
    for (; it != end; ++it) {
        out.push_back((*it)[1].str());
    }
    return out;
}

static std::string extractFirst(const std::string& src, const std::string& tag) {
    std::regex re = makeTagRegex(tag);
    std::smatch m;
    if (std::regex_search(src, m, re)) return m[1].str();
    return {};
}

int main() {
    const std::string filename = "mock-database.xml";
    std::string xml = readFile(filename);
    if (xml.empty()) {
        std::cerr << "Failed to read " << filename << "\n";
        return 1;
    }

    // Build lookup maps for logs, parts, machines
    std::map<std::string, std::string> logsById;
    for (const auto& logBlock : extractAll(xml, "log")) {
        std::string id = trim(extractFirst(logBlock, "id"));
        std::string date = trim(extractFirst(logBlock, "date"));
        if (!id.empty()) logsById[id] = date;
    }

    std::map<std::string, std::string> partsById;
    for (const auto& partBlock : extractAll(xml, "part")) {
        std::string id = trim(extractFirst(partBlock, "id"));
        std::string name = trim(extractFirst(partBlock, "name"));
        if (!id.empty()) partsById[id] = name;
    }

    std::map<std::string, std::string> machinesById;
    for (const auto& mBlock : extractAll(xml, "machine")) {
        std::string id = trim(extractFirst(mBlock, "id"));
        std::string name = trim(extractFirst(mBlock, "name"));
        if (!id.empty()) machinesById[id] = name;
    }

    // Collect report entries
    std::vector<Entry> entries;
    for (const auto& repBlock : extractAll(xml, "report")) {
        std::string reportText = trim(extractFirst(repBlock, "report_text"));
        std::string logId = trim(extractFirst(repBlock, "log_id"));
        std::string partId = trim(extractFirst(repBlock, "part_id"));
        std::string machineId = trim(extractFirst(repBlock, "machine_id"));

        std::string date = "Unknown Date";
        if (!logId.empty() && logsById.count(logId)) date = logsById[logId];

        std::string connected = "Unknown";
        if (!partId.empty() && partsById.count(partId)) connected = partsById[partId];
        else if (!machineId.empty() && machinesById.count(machineId)) connected = machinesById[machineId];

        entries.push_back({date, reportText, connected});
    }

    // Sort by date lexicographically (ISO yyyy-mm-dd). Unknown Date goes last.
    std::sort(entries.begin(), entries.end(), [](const Entry& a, const Entry& b) {
        bool aUnknown = (a.date == "Unknown Date");
        bool bUnknown = (b.date == "Unknown Date");
        if (aUnknown != bUnknown) return !aUnknown;
        return a.date < b.date;
    });

    // Print results
    for (const auto& e : entries) {
        std::cout << "Date: " << e.date
                  << " | Report: " << e.reportText
                  << " | Connected: " << e.connectedName << "\n";
    }

    return 0;
}