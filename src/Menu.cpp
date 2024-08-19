#include "Menu.h"

void clearConsole()
{
    #ifdef __unix__
        system("clear");
    #elif __APPLE__
        system("clear");
    #elif defined(_WIN32) || defined(WIN32)
        system("cls");
    #endif // defined
}

void pauseConsole()
{
    std::cin.ignore();
    std::cin.get();
}

Menu::Menu(Database& db)
    : db(db), userMapper(db), gameMapper(db), userGameAssociation(db) {}

void Menu::show() {
    clearConsole();
    std::cout << "\t\t\tMenu de Sistema\n" << std::endl;
    std::cout << "1. Alta Usuario" << std::endl;
    std::cout << "2. Baja Usuario" << std::endl;
    std::cout << "3. Modificar Usuario" << std::endl;
    std::cout << "4. Buscar Usuario" << std::endl;
    std::cout << "5. Listar Usuarios" << std::endl;
    std::cout << "6. Alta Juego" << std::endl;
    std::cout << "7. Baja Juego" << std::endl;
    std::cout << "8. Modificar Juego" << std::endl;
    std::cout << "9. Buscar Juego" << std::endl;
    std::cout << "10. Listar Juegos" << std::endl;
    std::cout << "11. Asociar Usuario y Juego" << std::endl;
    std::cout << "12. Buscar juegos asociados a Usuario" << std::endl;
    std::cout << "13. Buscar usuarios asociados a Juego" << std::endl;
    std::cout << "14. Listar Asociaciones" << std::endl;
    std::cout << "15. Salir" << std::endl;
}

void Menu::handleInput() {
    int choice;
    bool running = true;
    while (running) {
        show();
        std::cout << "Seleccione una opción: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                addUser();
                break;
            case 2:
                removeUser();
                break;
            case 3:
                updateUser();
                break;
            case 4:
                searchByUser();
                break;
            case 5:
                listUsers();
                break;
            case 6:
                addGame();
                break;
            case 7:
                removeGame();
                break;
            case 8:
                updateGame();
                break;
            case 9:
                searchByGame();
                break;
            case 10:
                listGames();
                break;
            case 11:
                associateUserGame();
                break;
            case 12:
                searchUserAssociation();
                break;
            case 13:
                searchGameAssociation();
                break;
            case 14:
                listAssociations();
                break;
            case 15:
                running = false;
                break;
            default:
                std::cout << "Opción inválida, intente de nuevo." << std::endl;
                break;
        }
    }
}

void Menu::addUser() {

    while (true)
    {
        std::string name, email;
        clearConsole();
        std::cout << "\t\tAlta de Usuario\n\n";
        std::cout << "Ingrese nombre: ";
        std::cin.ignore();
        std::getline(std::cin, name);
        std::vector<User> users = userMapper.findByName(name);
        if(users.empty())
        {
            std::cout << "Ingrese email: ";
            std::getline(std::cin, email);

            if (userMapper.insert(name, email)) {
                std::cout << "Usuario agregado exitosamente.\n" << std::endl;
            } else {
                std::cout << "Error al agregar usuario." << std::endl;
            }
            pauseConsole();
            break;
        }else
        {
            std::cout << "El nombre de usuario no esta disponible\n\n";
            char choice;
            std::cout << "¿Desea intentar con otro nombre? (s/n): ";
            std::cin >> choice;
            if (choice == 'n' || choice == 'N') {
                break; // Salir del bucle si el usuario no quiere continuar
            } else {
                continue; // Volver al inicio del bucle
            }
        }
    }
}

void Menu::removeUser() {

    int id, option;
    std::string name, email;
    do
    {
        clearConsole();
        std::cout << "\t\tBaja de Usuario\n\n";
        std::cout << "Ingrese ID del usuario a eliminar: ";
        std::cin >> id;

        std::vector<User> users = userMapper.findByID(id);
        for (const User& user : users) 
        {
            std::cout << "ID: " << user.id << ", Nombre: " << user.name << ", Email: " << user.email << std::endl;
        }
        std::cout << "\nEs el usuario que quiere Eliminar?\n";
        std::cout << "0. 'NO'\n";
        std::cout << "1. 'SI'\n";
        std::cout << "2. Salir\n";
        std::cin >>option;
        if(option < 0 || option > 2)
        {
            std::cout << "Opcion invalida\n\n";
            option = 0;
        }

        if (option == 1)
        {
            if (userMapper.remove(id)) 
            {
            std::cout << "Usuario eliminado exitosamente.\n\n" << std::endl;
            } else 
            {
                std::cout << "Error al eliminar usuario." << std::endl;
            }
        }
        pauseConsole();
        
    } while (option == 0);
}

void Menu::updateUser() {
    int id, option;
    std::string name, email;
    do
    {
        clearConsole();
        std::cout << "\t\tModificacion de Usuario\n\n";
        std::cout << "Ingrese ID del usuario a modificar: \n";
        std::cin >> id;
        std::vector<User> users = userMapper.findByID(id);
        for (const User& user : users) {
            std::cout << "ID: " << user.id << ", Nombre: " << user.name << ", Email: " << user.email << std::endl;
        }
        std::cout << "Es el usuario que quiere modificar?\n";
        std::cout << "0. 'NO'\n";
        std::cout << "1. 'SI'\n";
        std::cout << "2. Salir\n";
        std::cin >>option;
        if(option < 0 || option > 2)
        {
            std::cout << "Opcion invalida\n";
            pauseConsole();
            option = 0;
        }

        if(option == 1)
        {   
            while (true)
            {
                std::cout << "Ingrese nuevo nombre: ";
                std::cin.ignore();
                std::getline(std::cin, name);
                std::vector<User> users = userMapper.findByName(name);
                if(users.empty())
                {
                    std::cout << "Ingrese nuevo email: ";
                    std::getline(std::cin, email);

                    User user(id, name, email);
                    if (userMapper.update(user)) {
                        std::cout << "Usuario modificado exitosamente." << std::endl;
                    } else {
                        std::cout << "Error al modificar usuario." << std::endl;
                    }
                    pauseConsole();
                    break;
                }else
                {
                    std::cout << "El nombre de usuario no esta disponible\n\n";
                    char choice;
                    std::cout << "¿Desea intentar con otro nombre? (s/n): ";
                    std::cin >> choice;
                    if (choice == 'n' || choice == 'N') {
                        break; // Salir del bucle si el usuario no quiere continuar
                    } else {
                        continue; // Volver al inicio del bucle
                    }
                }
            }
        }
    } while(option == 0);
}

void Menu::searchByUser() {
    clearConsole();
    std::string name;
    std::cout << "Ingrese nombre del usuario a buscar: ";
    std::cin.ignore();
    std::getline(std::cin, name);
    std::vector<User> users = userMapper.findByName(name);
    for (const User& user : users) {
        std::cout << "ID: " << user.id << ", Nombre: " << user.name << ", Email: " << user.email << std::endl;
    }

    if (users.empty()) {
        std::cout << "No se encontró ningún usuario con ese nombre." << std::endl;
    }
    pauseConsole();
}

void Menu::listUsers() {
    clearConsole();
    std::vector<User> users = userMapper.findAll();
    for (const User& user : users) {
        std::cout << "ID: " << user.id << ", Nombre: " << user.name << ", Email: " << user.email << std::endl;
    }
    pauseConsole();
}

void Menu::addGame() {
    while (true)
    {
        std::string title, genre;
        clearConsole();
        std::cout << "Ingrese título: ";
        std::cin.ignore();
        std::getline(std::cin, title);
        std::vector<Game> game = gameMapper.findByTitle(title);
        if(game.empty())
        {
            std::cout << "Ingrese género: ";
            std::getline(std::cin, genre);

            if (gameMapper.insert(title, genre)) {
                std::cout << "Juego agregado exitosamente." << std::endl;
            } else {
                std::cout << "Error al agregar juego." << std::endl;
            }
            pauseConsole();
            break;
        }else
        {
            std::cout << "El titulo no esta disponible\n";
            char choice;
            std::cout << "¿Desea intentar con otro titulo? (s/n): ";
            std::cin >> choice;
            if (choice == 'n' || choice == 'N') {
                break; // Salir del bucle si el usuario no quiere continuar
            } else {
                continue; // Volver al inicio del bucle
            }
        }
    }
    
}

void Menu::removeGame() {
    int id, option;
    std::string title,genre;
    do
    {
        clearConsole();
        std::cout << "Ingrese ID del juego a eliminar: ";
        std::cin >> id;
        std::vector<Game> games = gameMapper.findByID(id);
        for (const Game& game : games) 
        {
            std::cout << "ID: " << game.id << ", Título: " << game.title << ", Género: " << game.genre << std::endl;
        }
        std::cout << "Es el juego que quiere eliminar?\n";
        std::cout << "0. 'NO'\n";
        std::cout << "1. 'SI'\n";
        std::cout << "2. Salir\n";
        std::cin >>option;

        if(option < 0 || option > 2)
        {
            std::cout << "Opcion invalida\n";
            option = 0;
        }
        
        if (option == 1)
        {
            if (gameMapper.remove(id)) {
            std::cout << "Juego eliminado exitosamente." << std::endl;
            } else {
                std::cout << "Error al eliminar juego." << std::endl;
            }
        }
        pauseConsole();
    } while (option == 0);
    
}

void Menu::updateGame(){
    int id, option;
    std::string title,genre;
    do
    {
        clearConsole();
        std::cout << "Ingrese ID del juego a modificar: ";
        std::cin >> id;
        std::vector<Game> games = gameMapper.findByID(id);
        for (const Game& game : games) 
        {
            std::cout << "ID: " << game.id << ", Título: " << game.title << ", Género: " << game.genre << std::endl;
        }
        std::cout << "Es el juego que quiere modificar?\n";
        std::cout << "0. 'NO'\n";
        std::cout << "1. 'SI'\n";
        std::cout << "2. Salir\n";
        std::cin >>option;

        if(option < 0 || option > 2)
        {
            std::cout << "Opcion invalida\n";
            pauseConsole();
            option = 0;
        }

        if (option == 1)
        {
            while (true)
            {
                std::cout << "Ingrese nuevo título: ";
                std::cin.ignore();
                std::getline(std::cin, title);
                std::vector<Game> game = gameMapper.findByTitle(title);
                if(game.empty())
                {
                    std::cout << "Ingrese nuevo género: ";
                    std::getline(std::cin, genre);

                    if (gameMapper.update(id, title, genre)) {
                        std::cout << "Juego modificado exitosamente." << std::endl;
                    } else {
                        std::cout << "Error al modificar juego." << std::endl;
                    }
                    pauseConsole();
                    break;
                }else
                {
                    std::cout << "El titulo no esta disponible\n";
                    char choice;
                    std::cout << "¿Desea intentar con otro titulo? (s/n): ";
                    std::cin >> choice;
                    if (choice == 'n' || choice == 'N') {
                        break; // Salir del bucle si el usuario no quiere continuar
                    } else {
                        continue; // Volver al inicio del bucle
                    }
                }
            }
        }
    } while (option == 0);
}
 
void Menu::searchByGame() {
    clearConsole();
    std::string title;
    std::cout << "Ingrese título del juego a buscar: ";
    std::cin.ignore();
    std::getline(std::cin, title);

    std::vector<Game> games = gameMapper.findByTitle(title);
    for (const Game& game : games) {
        std::cout << "ID: " << game.id << ", Título: " << game.title << ", Género: " << game.genre << std::endl;
    }
    pauseConsole();
}

void Menu::listGames() {
    clearConsole();
    std::vector<Game> games = gameMapper.findAll();
    for (const Game& game : games) {
    std::cout << "ID: " << game.id << ", Título: " << game.title << ", Género: " << game.genre << std::endl;
    }
    pauseConsole();
}

void Menu::associateUserGame() {
    clearConsole();
    int userId, gameId;
    std::cout << "Ingrese ID del usuario: ";
    std::cin >> userId;
    std::cout << "Ingrese ID del juego: ";
    std::cin >> gameId;
    if (userGameAssociation.associate(userId, gameId)) {
        std::cout << "Asociación realizada exitosamente." << std::endl;
    } else {
        std::cout << "Error al asociar usuario y juego." << std::endl;
    }
    pauseConsole();
}

void Menu::listAssociations() {
    clearConsole();
    std::vector<std::pair<User, Game>> associations = userGameAssociation.findAllAssociations(userMapper, gameMapper);
    for (const auto& association : associations) {
    const User& user = association.first;
    const Game& game = association.second;
    std::cout << "Usuario: " << user.name << " (ID: " << user.id << ") - Juego: " << game.title << " (ID: " << game.id << ")" << std::endl;
    }
    pauseConsole();
}

void Menu::searchUserAssociation()
{
    clearConsole();
    std::string name;
    std::cout << "Ingrese nombre del usuario: ";
    std::cin.ignore();  // Ignorar el buffer de entrada anterior
    std::getline(std::cin, name);

    std::vector<User> users = userMapper.findByName(name);
    if (users.empty()) {
        std::cout << "No se encontró ningún usuario con ese nombre." << std::endl;
        return;
    }

    for (const User& user : users) {
        std::cout << "ID: " << user.id << ", Nombre: " << user.name << ", Email: " << user.email << std::endl;

        // Buscar todos los juegos asociados al usuario actual
        std::vector<std::pair<User, Game>> associations = userGameAssociation.findUserAssociations(user.id, gameMapper);

        if (associations.empty()) {
            std::cout << "Este usuario no tiene juegos asociados." << std::endl;
        } else {
            std::cout << "Juegos asociados:" << std::endl;
            for (const auto& association : associations) {
                const Game& game = association.second;
                std::cout << "    ID: " << game.id << ", Título: " << game.title << ", Género: " << game.genre << std::endl;
            }
        }
    }
    pauseConsole();
}

void Menu::searchGameAssociation() {
    clearConsole();
    std::string title;
    std::cout << "Ingrese título del juego: ";
    std::cin.ignore();
    std::getline(std::cin, title);

    std::vector<Game> games = gameMapper.findByTitle(title);
    if (games.empty()) {
        std::cout << "No se encontró ningún juego con ese titulo." << std::endl;
        return;
    }

    for (const Game& game : games) {
        std::cout << "ID: " << game.id << ", Título: " << game.title << ", Género: " << game.genre << std::endl;

        // Buscar todos los usuarios asociados al juego actual
        std::vector<std::pair<Game, User>> associations = userGameAssociation.findGameAssociations(game.id, userMapper);

        if (associations.empty()) {
            std::cout << "Este juego no tiene usuarios asociados." << std::endl;
        } else {
            std::cout << "Usuarios asociados:" << std::endl;
            for (const auto& association : associations) {
                const User& user = association.second;
                std::cout << "    ID: " << user.id << ", Nombre: " << user.name << ", Email: " << user.email << std::endl;
            }
        }
    }
    pauseConsole();
}