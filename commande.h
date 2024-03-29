// commande.h
// SPDX-FileCopyrightText: 2024 GuiQuad06 guillaume.cuadrado@gmail.com
// SPDX-License-Identifier: GPL-2.0-or-later

#ifndef COMMANDE_H
#define COMMANDE_H

#include <map>
#include <string>
#include <vector>

#include "patisserie.h"

/**
 * Command class will handle orders objects which will contains a map of pastries
 */
class Commande
{
public:
    /**
     * Default constructor
     * It is a CLI to let the user tell about the Command
     * and fill the members accordingly
     */
    Commande(std::vector<Patisserie *> &patisseries);

    /**
     * Constructor with arguments :
     * @param nom_client is the name of the consumer
     */
    Commande(std::string nom_client, unsigned int tot_pax);

    /**
     * Copy constructor
     *
     * @param other (the object we want to use for the copy)
     */
    Commande(const Commande& other);

    /**
     * Destructor
     */
    ~Commande();

    /**
     * Assignment operator
     *
     * @param other (the object we want to use for the assignment)
     * @return a reference to a Commande object we will assign
     */
    Commande& operator=(const Commande& other);

    /**
     * Display Commande
     * This method display within cout all the members of the object Commande
     */
    void display_commande();

    /**
     * Save Commande
     * This method save information in a commande database
     * (a text file for instance)
     * @param my_file (a reference to the file handler)
     */
    void save_commande(std::ofstream &my_file);

    /**
     * Load Commande
     * This static method load information from a order database
     * (a text file for instance)
     * @param my_file a reference to the file handler
     * @param commande a reference to the Commande vector
     * @param patisserie a reference to Patisserie vector
     */
    static void load_commandes(std::ifstream &my_file, std::vector<Commande*> &commande, std::vector<Patisserie*> &patisserie);

    /**
     * Clean Commande's patisseries
     * This method can clean all the patisseries's maps contained in a Commande
     */
    void clean_patisseries();

    /**
     * Provide verification on people number
     * @param acc this is the pastries nb of people sum
     * @return unsigned int nb of remaining pax
     */
    int16_t remaining_pax(uint16_t acc);

protected:
    static uint32_t count;

    std::string m_nom_client;
    uint16_t m_command_id;
    uint16_t m_tot_pax;
    std::map<Patisserie,uint16_t> m_patisserie;
};

#endif // COMMANDE_H
