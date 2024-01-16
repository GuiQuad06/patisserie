// patisserie.h
// SPDX-FileCopyrightText: 2024 GuiQuad06 guillaume.cuadrado@gmail.com
// SPDX-License-Identifier: GPL-2.0-or-later

#ifndef PATISSERIE_H
#define PATISSERIE_H

#include <fstream>
#include <iostream>
#include <limits>
#include <map>
#include <string>

#include "recette.h"

// This define allows to bufferize the newline char to let the user answer the questions
#define IGNORE_NEWLINE    (std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'))

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
    Patisserie();

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
     * Save Patisserie
     * This method save information in a pastry database
     * (a text file for instance)
     * @param my_file (a reference to the file handler)
     */
    void save_patisserie(std::ofstream &my_file);

protected:
    e_pastry_type_t m_type;
    std::string m_name;
    unsigned int m_pax;
    std::map<Recette*,uint16_t> m_recette;

};

#endif // PATISSERIE_H
