#include <fstream>
#include <iostream>
#include <memory>
#include <vector>

#include "recette.h"
#include "patisserie.h"

/*
 * The purpose of this program is to PoC Pastry and Recipes Classes,
 * and how they will interact with each other
 */
int main(int argc, char **argv) {

    std::string path_to_file;
    std::vector<Recette*> my_recettes;
    std::vector<Patisserie*> my_patisseries;
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

    //**** TESTCASE 2: Filling the patisserie database ****//
    // Open recette file in read mode
    std::ifstream recettes_database_r(path_to_file + "recettes.txt", std::ios::in);
    // Static Recette method to parse read only recettes.txt database file
    // and create a Recette's vector
    Recette::load_recettes(recettes_database_r, my_recettes);

    // Open patisserie file in append mode
    std::ofstream patisseries_database_w(path_to_file + "patisseries.txt", std::ios::out | std::ios::app);

    do {
        std::cout << "Patisserie Wizard:\n";

        my_patisseries.push_back(new Patisserie(my_recettes));

        std::cout << "Would you like to store another pastry ? (Y/n)\n";
        std::cin >> response;

    } while(response == 'y' || response == 'Y');

    // Recette objects retrospective
    for (auto my_patisserie : my_patisseries) {
        // J'affiche le contenu de mon vecteur
        my_patisserie->display_patisserie();
        // J'enregistre eventuellement ds un file
        std::cout << "Would you like to store the recipe in a file ? (Y/n)\n";
        std::cin >> response;
        if(response == 'y' || response =='Y') {
            my_patisserie->save_patisserie(patisseries_database_w);
        }
        // Je free tout propre
        delete my_patisserie;
        my_patisserie = nullptr;
    }
    // Recette objects retrospective
    for (auto my_recette : my_recettes) {
        // Je free tout propre
        delete my_recette;
        my_recette= nullptr;
    }
    //*****************************************************//

    return 0;
}
