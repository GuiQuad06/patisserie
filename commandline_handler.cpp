// commandline_handler.cpp
// SPDX-FileCopyrightText: 2024 GuiQuad06 guillaume.cuadrado@gmail.com
// SPDX-License-Identifier: GPL-2.0-or-later

#include "commandline_handler.h"

typedef void (*commandline_handler)(uint16_t cmd_id);

/**
 * @brief Structure to store the command line handlers
 * @memberof cmd_id the command id (to be compared with the input)
 * @memberof handler_callback the function pointer to handle the command
 * @memberof cmd_help the help message to display
 */
typedef struct {
    uint16_t cmd_id;
    commandline_handler handler_callback;
    std::string cmd_help;

} commandline_handler_t;

commandline_handler_t commandline_handlers[] = {
    {1, nullptr, "Add a Recette"},
    {2, nullptr, "Add a Patisserie"},
    {3, nullptr, "Add a Commande"},
    {4, nullptr, "Generate a Shopping List"},
    {5, nullptr, "Remove a Recette"},
    {6, nullptr, "Remove a Patisserie"},
    {7, nullptr, "Remove a Commande"},
    {0, nullptr, ""}};
