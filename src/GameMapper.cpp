#include "GameMapper.h"

GameMapper::GameMapper(Database& db) : db(db) {}

bool GameMapper::insert(std::string title, std::string genre) {
    Game game(0, title, genre);
    std::string sql = "INSERT INTO Games (title, genre) VALUES ('" + game.title + "', '" + game.genre + "');";
    return db.executeSQL(sql);
}

bool GameMapper::remove(int id) {
    std::string sql = "DELETE FROM Games WHERE id = " + std::to_string(id) + ";";
    return db.executeSQL(sql);
}

bool GameMapper::update(int id, std::string title, std::string genre) {
    Game game(id, title, genre);
    std::string sql = "UPDATE Games SET title = '" + game.title + "', genre = '" + game.genre + "' WHERE id = " + std::to_string(game.id) + ";";
    return db.executeSQL(sql);
}

std::vector<Game> GameMapper::findAll() {
    std::string sql = "SELECT id, title, genre FROM Games;";
    sqlite3_stmt* stmt;
    std::vector<Game> games;

    if (sqlite3_prepare_v2(db.getDB(), sql.c_str(), -1, &stmt, 0) != SQLITE_OK) {
        std::cerr << "Failed to execute query: " << sqlite3_errmsg(db.getDB()) << std::endl;
        return games;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        std::string title(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
        std::string genre(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
        games.emplace_back(id, title, genre);
    }
    sqlite3_finalize(stmt);
    return games;
}

std::vector<Game> GameMapper::findByTitle(const std::string& title) {
    std::string sql = "SELECT id, title, genre FROM Games WHERE title LIKE '%" + title + "%';";
    sqlite3_stmt* stmt;
    std::vector<Game> games;

    if (sqlite3_prepare_v2(db.getDB(), sql.c_str(), -1, &stmt, 0) != SQLITE_OK) {
        std::cerr << "Failed to execute query: " << sqlite3_errmsg(db.getDB()) << std::endl;
        return games;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        std::string title(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
        std::string genre(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
        games.emplace_back(id, title, genre);
    }
    sqlite3_finalize(stmt);
    return games;
}

std::vector<Game> GameMapper::findByID(int id) {
    std::string sql = "SELECT id, name, email FROM Game WHERE id = " + std::to_string(id) + ";";
    sqlite3_stmt* stmt;
    std::vector<Game> games;

    if (sqlite3_prepare_v2(db.getDB(), sql.c_str(), -1, &stmt, 0) != SQLITE_OK) {
        std::cerr << "Failed to execute query: " << sqlite3_errmsg(db.getDB()) << std::endl;
        return games;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int fetchedID = sqlite3_column_int(stmt, 0);
        std::string title(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
        std::string genre(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
        games.emplace_back(fetchedID, title, genre);
    }
    sqlite3_finalize(stmt);
    return games;
}