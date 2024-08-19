#ifndef MENU_H
#define MENU_H

#include "Database.h"
#include "UserMapper.h"
#include "GameMapper.h"
#include "UserGameAssociation.h"
#include <iostream>
#include <string>

class Menu {
public:
    Menu(Database& db);

    void show();
    void handleInput();

private:
    Database& db;
    UserMapper userMapper;
    GameMapper gameMapper;
    UserGameAssociation userGameAssociation;

    void addUser();
    void removeUser();
    void updateUser();
    void searchByUser();
    void listUsers();
    void addGame();
    void removeGame();
    void updateGame();
    void searchByGame();
    void listGames();
    void associateUserGame();
    void listAssociations();
    void searchUserAssociation();
    void searchGameAssociation();
};

#endif // MENU_H
