#include "Database.h"
#include "Menu.h"

int main() {
    Database db("database.db");

    // Inicializar la base de datos
    Database::initialize(db);

    Menu menu(db);
    menu.handleInput();

    return 0;
}