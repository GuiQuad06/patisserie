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

    // Recette objects retrospective
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
