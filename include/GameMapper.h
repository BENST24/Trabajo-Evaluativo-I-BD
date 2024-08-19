#ifndef GAMEMAPPER_H
#define GAMEMAPPER_H

#include "Database.h"
#include "Game.h"
#include <vector>

class GameMapper {
public:
    GameMapper(Database& db);

    bool insert(std::string title, std::string genre);
    bool remove(int id);
    bool update(int id, std::string title, std::string genre);
    std::vector<Game> findAll();
    std::vector<Game> findByTitle(const std::string& title);
    std::vector<Game> findByID(int id);

private:
    Database& db;
};

#endif // GAMEMAPPER_H
