// patisserie.cpp
// SPDX-FileCopyrightText: 2024 GuiQuad06 guillaume.cuadrado@gmail.com
// SPDX-License-Identifier: GPL-2.0-or-later

#include "patisserie.h"

Patisserie::Patisserie(std::vector<Recette *> &recettes)
{
    char cat, response;
    uint16_t qty;
    std::string tmp_str;
    Recette recette_tmp(kPATE, "toto");

    // Getting the pastry's category
    std::cout << "What's the category of the pastry you want to store ?:\n";
    std::cout << "\t-0 if TARTE\n\t-1 if ENTREMET\n\t-2 if TRADI\n";
    std::cin >> cat;
    std::cin.ignore();

    switch (cat) {
    case '0':
        m_type = kTARTE;
        break;
    case '1':
        m_type = kENTREMET;
        break;
    case '2':
        m_type = kTRADI;
        break;
    default:
        std::cout << "Not supported Category, set to TARTE instead...\n";
        m_type = kTARTE;
    }

    // Getting the pastry's name
    std::cout << "What's the name of the pastry you want to store ?:\n";
    std::getline(std::cin, m_name);
    remove_trailing_spaces(m_name);

    // Getting the people number
    std::cout << "For how many pepole the pastry is made for ?\n";
    std::cin >> m_pax;
    std::cin.ignore();

    // Create an empty map
    // Key is a pointer to Recette, Value is a uint16...
    m_recette = std::map<Recette,uint16_t>();

    do {
        std::cout << "Patry Wizard !\n";

        // Filling the recipes dictionnary
        std::cout << "What Recipe would you like to add ?\n";

        // Display the available recipes
        for(auto recette : recettes) {
            std::cout << recette->get_recette_name() << '\n';
        }

        std::getline(std::cin, tmp_str);
        remove_trailing_spaces(tmp_str);

        std::cout << "What will be the quantity of the recipe ?\n";
        std::cin >> qty;
        std::cin.ignore();

        //Insert the element in the map
        // TODO : implement operator< in Recette
        //m_recette.insert({recette_tmp, qty});

        std::cout << "Would you like to store another Recipe ? (Y/n)\n";
        std::cin >> response;
        std::cin.ignore();

    } while(response == 'y' || response == 'Y');
}

Patisserie::Patisserie(e_pastry_type_t cat, std::string name, unsigned int pax) : m_type(cat), m_name(name), m_pax(pax)
{
    m_recette = std::map<Recette,uint16_t>();
}

Patisserie::Patisserie(const Patisserie& other) : m_type(other.m_type), m_name(other.m_name),  m_pax(other.m_pax)
{
    for (auto it = other.m_recette.begin(); it != other.m_recette.end(); ++it) {
        //m_recette[it->first] = it->second;
    }
}

Patisserie::~Patisserie()
{
    //TODO ???
}

Patisserie& Patisserie::operator=(const Patisserie& other)
{
    if(this != &other) {
        m_name = other.m_name;
        m_type = other.m_type;
        m_pax = other.m_pax;
        for (auto it = other.m_recette.begin(); it != other.m_recette.end(); ++it) {
            //m_recette[it->first] = it->second;
        }
    }
    return *this;
}

std::string Patisserie::type_interpreter()
{
    return m_type == kTARTE ? "TARTE" :
        m_type == kENTREMET ? "ENTREMET" : "TRADI" ;
}

void Patisserie::display_patisserie()
{
    std::string cat = type_interpreter();

    std::map<Recette,uint16_t>::const_iterator it_map;
    std::cout << "Category : " << cat << "\nName :" << m_name << "\nNb de pax:" << m_pax << '\n';

    for(it_map = m_recette.begin(); it_map != m_recette.end(); ++it_map) {
        // TODO : Implement operator<< in Recette
        //std::cout << "\tKey:" << it_map->first << "\tValue:" << it_map->second << '\n';
    }
}

void Patisserie::save_patisserie(std::ofstream& my_file)
{
    std::map<Recette,uint16_t>::const_iterator it_map;
    std::string cat = type_interpreter();

    if(!my_file) {
        std::cerr << "Impossible d'ouvrir le fichier\n";
    }
    else {
        my_file << "# " + cat + ":\n";
        my_file << "## " + m_name << ';' << m_pax << ":\n";
        for(it_map = m_recette.begin(); it_map != m_recette.end(); ++it_map) {
            // TODO : Implement operator<< in Recette
            //my_file << "### " << it_map->first << ';' << it_map->second << "\n";
        }
        my_file << "####\n"; // End Of Patisserie
    }
}
