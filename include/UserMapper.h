#ifndef USERMAPPER_H
#define USERMAPPER_H

#include "Database.h"
#include "User.h"
#include <vector>

class UserMapper {
public:
    UserMapper(Database& db);

    bool insert(std::string name, std::string email);
    bool remove(int id);
    bool update(const User& user);
    std::vector<User> findAll();
    std::vector<User> findByName(const std::string& name);
    std::vector<User> findByID(int id);

private:
    Database& db;
};

#endif // USERMAPPER_H
