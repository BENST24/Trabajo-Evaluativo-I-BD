#ifndef USERGAMEASSOCIATION_H
#define USERGAMEASSOCIATION_H

#include "Database.h"
#include "User.h"
#include "Game.h"
#include "UserMapper.h"
#include "GameMapper.h"
#include <vector>
#include <utility>

class UserGameAssociation {
public:
    UserGameAssociation(Database& db);

    bool associate(int userId, int gameId);
    std::vector<std::pair<User, Game>> findAllAssociations(UserMapper& userMapper, GameMapper& gameMapper);
    std::vector<std::pair<User, Game>> findUserAssociations(int userId, GameMapper& gameMapper);
    std::vector<std::pair<Game, User>> findGameAssociations(int gameId, UserMapper& userMapper);

private:
    Database& db;
};

#endif // USERGAMEASSOCIATION_H
