#include <fstream>
#include <iostream>
#include <memory>
#include <vector>

#include "commande.h"
#include "patisserie.h"
#include "recette.h"

/*
 * The purpose of this program is to PoC Pastry and Recipes Classes,
 * and how they will interact with each other
 */
int main(int argc, char **argv) {

    std::string path_to_file;
    std::vector<Recette*> my_recettes;
    std::vector<Patisserie*> my_patisseries;
    std::vector<Commande*> my_commandes;
    char response;

    std::cout << "Hello, world!\n" ;

    // Without passing argument to the exe the database path is the origin worktree
    if (argc == 1)
        path_to_file = "../";
    else if (argc == 2)
        path_to_file = argv[1];
    else {
        std::cerr << "On se calme gamin ! Pas plus de un argument en plus de l'executable...\n";
        return 1;
    }

    // Open recette file in read mode
    std::ifstream recettes_database_r(path_to_file + "recettes.txt", std::ios::in);
    // Static Recette method to parse read only recettes.txt database file
    // and create a Recette's vector
    Recette::load_recettes(recettes_database_r, my_recettes);

    // Open patisserie file in read mode
    std::ifstream patisseries_database_r(path_to_file + "patisseries.txt", std::ios::in);
    // Static Patisserie method to parse read only patisseries.txt database file
    // and create a Patisserie's vector
    Patisserie::load_patisseries(patisseries_database_r, my_patisseries, my_recettes);

    // Open commande file in write mode
    std::ofstream commandes_database_w(path_to_file + "commandes.txt", std::ios::out | std::ios::app);

    // CLI Handler Loop
    do {
        std::cout << "Formulaire de Commande:\n";

        my_commandes.push_back(new Commande(my_patisseries));

        std::cout << "Would you like to store another order ? (Y/n)\n";
        std::cin >> response;
        std::cin.ignore();

    } while(response == 'y' || response == 'Y');

    // Commande objects retrospective
    for (auto my_commande : my_commandes) {
        my_commande->display_commande();
        // Je free tout propre
        delete my_commande;
        my_commande = nullptr;
    }
    for (auto my_patisserie : my_patisseries) {
        my_patisserie->display_patisserie();
        // Je free tout propre
        delete my_patisserie;
        my_patisserie = nullptr;
    }
    // Recette objects retrospective
    for (auto my_recette : my_recettes) {
        my_recette->display_recette();
        // Je free tout propre
        delete my_recette;
        my_recette= nullptr;
    }
    //*****************************************************//

    return 0;
}
