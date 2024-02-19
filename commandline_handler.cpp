// commandline_handler.cpp
// SPDX-FileCopyrightText: 2024 GuiQuad06 guillaume.cuadrado@gmail.com
// SPDX-License-Identifier: GPL-2.0-or-later

#include "commandline_handler.h"

#include <fstream>
#include <stdio.h>

#define MAX_LEN    (128u)

/**
 * @brief Function pointer to handle the command line
 */
typedef int (*commandline_handler)(database_package_t &data);

/**
 * @brief Structure to store the command line handlers
 * @memberof cmd_id the command id (to be compared with the input)
 * @memberof handler_callback the function pointer to handle the command
 * @memberof cmd_help the help message to display
 */
typedef struct {
    const char * cmd_id;
    commandline_handler handler_callback;
    std::string cmd_help;

} commandline_handler_t;

static void print_image(std::ifstream& fptr);

commandline_handler_t commandline_handlers[] = {
    {"1", cmd_add_recette, "Add a Recette"},
    {"2", cmd_add_patisserie, "Add a Patisserie"},
    {"3", cmd_add_commande, "Add a Commande"},
    {"4", nullptr, "Generate a Shopping List"},
    {"5", nullptr, "Remove a Recette"},
    {"6", nullptr, "Remove a Patisserie"},
    {"7", nullptr, "Remove a Commande"},
    {0, nullptr, ""}};

int cmd_add_recette(database_package_t &data)
{
    std::cout << "Adding a Recette\n";

    Recette *r = new Recette();

    if (r == nullptr)
    {
        std::cerr << "Error while creating the Recette\n";
        return 1;
    }
    data.v_recettes.push_back(r);
    return 0;
}

int cmd_add_patisserie(database_package_t &data)
{
    std::cout << "Adding a Patisserie\n";

    Patisserie *p = new Patisserie(data.v_recettes);

    if (p == nullptr)
    {
        std::cerr << "Error while creating the Patisserie\n";
        return 1;
    }
    data.v_patisseries.push_back(p);
    return 0;
}

int cmd_add_commande(database_package_t &data)
{
    std::cout << "Adding a Commande\n";

    Commande *c = new Commande(data.v_patisseries);

    if (c == nullptr)
    {
        std::cerr << "Error while creating the Commande\n";
        return 1;
    }
    data.v_commandes.push_back(c);
    return 0;
}

int cli_process(char c, database_package_t &databases)
{
    for (int i = 0; commandline_handlers[i].cmd_id != 0; i++)
    {
        if (c == commandline_handlers[i].cmd_id[0])
        {
            if (commandline_handlers[i].handler_callback != nullptr)
            {
                if (commandline_handlers[i].handler_callback(databases)) {
                    std::cerr << "Error while processing the command\n";
                    return 1;
                }
            }
            else
            {
                std::cout << "Not implemented yet\n";
            }
        }
    }
    return 0;
}

void cli_display(void)
{
    for (int i = 0; commandline_handlers[i].cmd_id != 0; i++)
    {
        std::cout << '\t' << commandline_handlers[i].cmd_id << ") " << commandline_handlers[i].cmd_help.c_str() << '\n';
    }
}

int cli_title(void)
{
    // Open ASCII Title file in read mode
    std::ifstream title_ascii_r("../macarons.txt", std::ios::in);

    if (title_ascii_r.fail()) {
        std::cerr << "Error opening macarons.txt file\n";
        return 1;
    }

    print_image(title_ascii_r);

    return 0;
}

static void print_image(std::ifstream& fptr)
{
    std::string read_string;

    if(!fptr) {
        std::cerr << "Impossible d'ouvrir le fichier\n";
        return;
    }
    else {
        while(std::getline(fptr, read_string)) {
            std::cout << read_string;
        }
    }
}

