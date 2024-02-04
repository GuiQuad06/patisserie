// commandline_handler.cpp
// SPDX-FileCopyrightText: 2024 GuiQuad06 guillaume.cuadrado@gmail.com
// SPDX-License-Identifier: GPL-2.0-or-later

#include "commandline_handler.h"

/**
 * @brief Function pointer to handle the command line
 */
typedef void (*commandline_handler)(database_package_t &data);

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

commandline_handler_t commandline_handlers[] = {
    {"1", cmd_add_recette, "Add a Recette"},
    {"2", cmd_add_patisserie, "Add a Patisserie"},
    {"3", nullptr, "Add a Commande"},
    {"4", nullptr, "Generate a Shopping List"},
    {"5", nullptr, "Remove a Recette"},
    {"6", nullptr, "Remove a Patisserie"},
    {"7", nullptr, "Remove a Commande"},
    {0, nullptr, ""}};

void cmd_add_recette(database_package_t &data)
{
    std::cout << "Adding a Recette\n";

    data.v_recettes.push_back(new Recette());
}

void cmd_add_patisserie(database_package_t &data)
{
    std::cout << "Adding a Patisserie\n";

    data.v_patisseries.push_back(new Patisserie(data.v_recettes));
}

void cli_process(char c, database_package_t &databases)
{
    for (int i = 0; commandline_handlers[i].cmd_id != 0; i++)
    {
        if (c == commandline_handlers[i].cmd_id[0])
        {
            if (commandline_handlers[i].handler_callback != nullptr)
            {
                commandline_handlers[i].handler_callback(databases);
            }
            else
            {
                std::cout << "Not implemented yet\n";
            }
        }
    }
}

void cli_display(void)
{
    for (int i = 0; commandline_handlers[i].cmd_id != 0; i++)
    {
        std::cout << '\t' << commandline_handlers[i].cmd_id << ") " << commandline_handlers[i].cmd_help.c_str() << '\n';
    }
}
