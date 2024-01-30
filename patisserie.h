// patisserie.h
// SPDX-FileCopyrightText: 2024 GuiQuad06 guillaume.cuadrado@gmail.com
// SPDX-License-Identifier: GPL-2.0-or-later

#ifndef PATISSERIE_H
#define PATISSERIE_H

#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "recette.h"
#include "utility.h"

/*
 * Enum to identify pastry categories
 */
typedef enum {
    kTARTE,
    kENTREMET,
    kTRADI
} e_pastry_type_t;

/**
 * Patisserie class will handle pastry objects which will contains a map of recipes
 */
class Patisserie
{
public:
    /**
     * Default constructor
     * It is a CLI to let the user tell about the Patisserie
     * and fill the members accordingly
     */
    Patisserie(std::vector<Recette *> &recettes);

    /*
     * Constructor with arguments :
     * cat is the category of the pastry
     * name is the name of the pastry we want to give in the database
     */
    Patisserie(e_pastry_type_t cat, std::string name, unsigned int pax);

    /**
     * Copy constructor
     *
     * @param other (the object we want to use for the copy)
     */
    Patisserie(const Patisserie& other);

    /**
     * Destructor
     */
    ~Patisserie();

    /**
     * Assignment operator
     *
     * @param other (the object we want to use for the assignment)
     * @return a reference to a Patisserie object we will assign
     */
    Patisserie& operator=(const Patisserie& other);

    /**
     * Category Interpreter
     * This method convert the category constant enum
     * to a string in order to send it in a file
     * @return a string
     */
    std::string type_interpreter();

    /**
     * Display Patisserie
     * This method display within cout all the members of the object Patisserie
     */
    void display_patisserie();

    /**
     * Patisserie name getter
     * This method get the name of the recipe
     */
    std::string get_patisserie_name();

    /**
     * Save Patisserie
     * This method save information in a pastry database
     * (a text file for instance)
     * @param my_file (a reference to the file handler)
     */
    void save_patisserie(std::ofstream &my_file);

    /**
     * Operator << non-member overloading function
     * This is used to print a Patisserie object within its map
     * @param os output stream
     * @param patisserie const reference to a Patisserie object 
     * @return output stream (e.g std::cout)
     */
    friend std::ostream& operator<<(std::ostream& os, const Patisserie& patisserie);

protected:
    e_pastry_type_t m_type;
    std::string m_name;
    unsigned int m_pax;
    std::map<Recette,uint16_t> m_recette;

};

#endif // PATISSERIE_H
