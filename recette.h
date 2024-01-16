// recette.h
// SPDX-FileCopyrightText: 2024 GuiQuad06 guillaume.cuadrado@gmail.com
// SPDX-License-Identifier: GPL-2.0-or-later

#ifndef RECETTE_H
#define RECETTE_H

#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#include "utility.h"

/*
 * Enum to identify recipes categories
 */
typedef enum {
    kPATE,
    kCREME,
    kBISCUIT,
    kMOUSSE,
    kGLACAGE
} e_category_t;

/**
 * Recette class will handle recipe objects which will contains a map of ingredients
 */
class Recette
{
public:
    /**
     * Default constructor
     * It is a CLI to let the user tell about the Recette
     * and fill the members accordingly
     */
    Recette();

    /*
     * Constructor with arguments :
     * cat is the category of the recipes
     * name is the name of the recipe we want to give in the database
     */
    Recette(e_category_t cat, std::string name);

    /**
     * Copy constructor
     *
     * @param other (the object we want to use for the copy)
     */
    Recette(const Recette& other);

    /**
     * Destructor
     */
    ~Recette();

    /**
     * Assignment operator
     *
     * @param other (the object we want to use for the assignment)
     * @return a reference to a Recette object we will assign
     */
    Recette& operator=(const Recette& other);

    /**
     * Category Interpreter
     * This method convert the category constant enum
     * to a string in order to send it in a file
     * @return a string
     */
    std::string category_interpreter();

    /**
     * Display Recette
     * This method display within cout all the members of the object Recette
     */
    void display_recette();

    /**
     * Save Recette
     * This method save information in a recipe database
     * (a text file for instance)
     * @param my_file (a reference to the file handler)
     */
    void save_recette(std::ofstream &my_file);

    /**
     * Load Recettes
     * This static method load information from a recipe database
     * (a text file for instance)
     * @param my_file (a reference to the file handler)
     * @param recettes (a reference to the recettes vector)
     */
    static void load_recettes(std::ifstream &my_file, std::vector<Recette*> &recettes);

    /**
     * Category Converter
     * This method convert the string from database
     * to a constant enum
     * @return a e_category_t category recipe
     */
    static e_category_t category_converter(std::string str);

protected:

    e_category_t m_category;
    std::string m_name;
    std::map<std::string,uint16_t> m_ingredient;

};

#endif // RECETTE_H
