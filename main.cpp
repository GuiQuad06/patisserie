/** Standard Includes */
#include <fstream>
#include <iostream>
#include <memory>
#include <vector>

/** User Includes */
#include "commande.h"
#include "commandline_handler.h"
#include "patisserie.h"
#include "recette.h"

/** Private Functions Prototypes */
/**
 * @brief Load databases from files to objects
 * @param path path to the databases
 * @param databases structure to store the 3 vectors databases
 * @return 0 if success, 1 if error
*/
static int load_databases(std::string path,
                    database_package_t &databases);

/*
 * The purpose of this program is to PoC Pastry and Recipes Classes,
 * and how they will interact with each other
 */
int main(int argc, char **argv) {

    std::string path_to_file;
    char response;

    database_package_t my_databases;

    std::cout << "Salut a toi jeune Patissier!\n\n" ;

    // Without passing argument to the exe the database path is the origin worktree
    if (argc == 1)
        path_to_file = "../";
    else if (argc == 2) {
        if (argv[1] != nullptr) {
            path_to_file = argv[1];
        }
    }
    else {
        std::cerr << "On se calme gamin ! Pas plus de un argument en plus de l'executable...\n";
        return 1;
    }

    if (load_databases(path_to_file, my_databases) != 0) {
        std::cerr << "Error loading databases\n";
        return 1;
    }

    // CLI Handler Loop
    do {
        std::cout << "What would you like to do ?\n";

        cli_display();

        std::cout << "Press on q or Q to quit\n";
        std::cin >> response;
        std::cin.ignore();

        cli_process(response, my_databases);

    } while(!(response == 'q' || response == 'Q'));

    //*** Show objects contents and free memory ***********//
    // Commande objects retrospective
    for (auto my_commande : my_databases.v_commandes) {
        my_commande->display_commande();
        // Je free tout propre
        delete my_commande;
        my_commande = nullptr;
    }
    // Patisseries objects retrospective
    for (auto my_patisserie : my_databases.v_patisseries) {
        my_patisserie->display_patisserie();
        // Je free tout propre
        delete my_patisserie;
        my_patisserie = nullptr;
    }
    // Recette objects retrospective
    for (auto my_recette : my_databases.v_recettes) {
        my_recette->display_recette();
        // Je free tout propre
        delete my_recette;
        my_recette= nullptr;
    }
    //*****************************************************//

    return 0;
}

static int load_databases(std::string path, 
                    database_package_t &databases)
{
    if (path.empty()) {
        std::cerr << "Error: path is empty\n";
        return 1;
    }

    // Open recette file in read mode
    std::ifstream recettes_database_r(path + "recettes.txt", std::ios::in);

    if (recettes_database_r.fail()) {
        std::cerr << "Error opening recettes.txt file\n";
        return 1;
    }

    // Static Recette method to parse read only recettes.txt database file
    // and create a Recette's vector
    Recette::load_recettes(recettes_database_r, databases.v_recettes);

    // Open patisserie file in read mode
    std::ifstream patisseries_database_r(path + "patisseries.txt", std::ios::in);

    if(patisseries_database_r.fail()) {
        std::cerr << "Error opening patisseries.txt file\n";
        return 1;
    }

    // Static Patisserie method to parse read only patisseries.txt database file
    // and create a Patisserie's vector
    Patisserie::load_patisseries(patisseries_database_r, databases.v_patisseries, databases.v_recettes);

    // Open commande file in read mode
    std::ifstream commandes_database_r(path + "commandes.txt", std::ios::in);

    if(commandes_database_r.fail()) {
        std::cerr << "Error opening commandes.txt file\n";
        return 1;
    }

    // Static Commande method to parse read only commandes.txt database file
    // and create a Commande's vector
    Commande::load_commandes(commandes_database_r, databases.v_commandes, databases.v_patisseries);

    return 0;
}