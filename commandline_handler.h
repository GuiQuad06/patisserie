// commandline_handler.h
// SPDX-FileCopyrightText: 2024 GuiQuad06 guillaume.cuadrado@gmail.com
// SPDX-License-Identifier: GPL-2.0-or-later

#ifndef COMMANDLINE_HANDLER_H_
#define COMMANDLINE_HANDLER_H_

/** Standard Includes */
#include <iostream>
#include <stdint.h>
#include <string>
#include <vector>

/** User Includes */
#include "commande.h"
#include "patisserie.h"
#include "recette.h"

/** 
 * @brief Structure to store the 3 vectors databases
 */
typedef struct {
    std::vector<Recette*> v_recettes;
    std::vector<Patisserie*> v_patisseries;
    std::vector<Commande*> v_commandes;
} database_package_t;

/** 
 * @brief Display the different commands
 * @return none
 */
void cli_display(void);

/** 
 * @brief Add a Recette
 * @return none
 */
void cmd_add_recette(database_package_t &data);

/**
 * @brief Add a Patisserie
 * @return none
 */
void cmd_add_patisserie(database_package_t &data);

/**
 * @brief Add a Commande
 * @return none
 */
void cmd_add_commande(database_package_t &data);

/** 
 * @brief Process the command line
 * @param c the command to process
 * @param databases the databases to process (3 vectors)
 * @return none
 */
void cli_process(char c, database_package_t &databases);

#endif // COMMANDLINE_HANDLER_H_
