#include <fstream>
#include <iostream>
#include <string>
#include "nlohmann/json.hpp"

using json = nlohmann::json;

// Helper: load the whole database file once (cached)
static json loadDatabase()
{
    static bool loaded = false;
    static json db = json::object();

    if (loaded) return db;
    loaded = true;

    const std::string path = "mock-database.json";
    std::ifstream in(path);
    if (!in.is_open()) {
        std::cerr << "readDatabase: failed to open " << path << '\n';
        return db;
    }

    try {
        in >> db;
    } catch (const std::exception &ex) {
        std::cerr << "readDatabase: JSON parse error: " << ex.what() << '\n';
        db = json::object();
    }
    return db;
}

// Public functions used by other cpp files.
// Each returns the corresponding array from the database (or empty array on error).

json getProfiles()
{
    json db = loadDatabase();
    if (db.contains("profiles") && db["profiles"].is_array()) return db["profiles"];
    return json::array();
}

json getLogs()
{
    json db = loadDatabase();
    if (db.contains("logs") && db["logs"].is_array()) return db["logs"];
    return json::array();
}

json getReports()
{
    json db = loadDatabase();
    if (db.contains("reports") && db["reports"].is_array()) return db["reports"];
    return json::array();
}

json getParts()
{
    json db = loadDatabase();
    if (db.contains("parts") && db["parts"].is_array()) return db["parts"];
    return json::array();
}

json getMachines()
{
    json db = loadDatabase();
    if (db.contains("machines") && db["machines"].is_array()) return db["machines"];
    return json::array();
}