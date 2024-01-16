// patisserie.cpp
// SPDX-FileCopyrightText: 2024 GuiQuad06 guillaume.cuadrado@gmail.com
// SPDX-License-Identifier: GPL-2.0-or-later

#include "patisserie.h"

/**
* Remove the trailing spaces
*
* @param input (reference to a standard string)
* @return a reference to a standard string (without trailing spaces)
*/
static std::string& remove_trailing_spaces(std::string& input)
{
    size_t pos = input.find_last_not_of(' ');
    if (pos != std::string::npos)
        input.erase(pos + 1);
    else
        input.clear();  // input is all spaces
    return input;
}

Patisserie::Patisserie()
{
    char cat, response;
    uint16_t qty;
    std::string tmp_str;

    // Getting the pastry's category
    std::cout << "What's the category of the pastry you want to store ?:\n";
    std::cout << "\t-0 if TARTE\n\t-1 if ENTREMET\n\t-2 if TRADI\n";
    std::cin >> cat;
    IGNORE_NEWLINE;

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
    IGNORE_NEWLINE;

    // Create an empty map
    // Key is a pointer to Recette, Value is a uint16...
    m_recette = std::map<Recette*,uint16_t>();

    do {
        std::cout << "Recipe Wizard !\n";

        // Filling the recipes dictionnary
        std::cout << "What Recipe would you like to add ?\n";

        // TODO Parse recette.txt and display the available recipes

        std::cout << "What will be the quantity of the recipe ?\n";
        std::cin >> qty;
        IGNORE_NEWLINE;

        // TODO insert the element in the map

        std::cout << "Would you like to store another Recipe ? (Y/n)\n";
        std::cin >> response;
        IGNORE_NEWLINE;

    } while(response == 'y' || response == 'Y');
}

Patisserie::Patisserie(e_pastry_type_t cat, std::string name, unsigned int pax) : m_type(cat), m_name(name), m_pax(pax)
{
    m_recette = std::map<Recette*,uint16_t>();
}

Patisserie::Patisserie(const Patisserie& other) : m_type(other.m_type), m_name(other.m_name),  m_pax(other.m_pax)
{
    for (auto it = other.m_recette.begin(); it != other.m_recette.end(); ++it) {
        m_recette[it->first] = it->second;
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
            m_recette[it->first] = it->second;
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

    std::map<Recette*,uint16_t>::const_iterator it_map;
    std::cout << "Category : " << cat << "\nName :" << m_name << "\nNb de pax:" << m_pax << '\n';

    for(it_map = m_recette.begin(); it_map != m_recette.end(); ++it_map) {
        std::cout << "\tKey:" << it_map->first << "\tValue:" << it_map->second << '\n';
    }
}

void Patisserie::save_patisserie(std::ofstream& my_file)
{
    std::map<Recette*,uint16_t>::const_iterator it_map;
    std::string cat = type_interpreter();

    if(!my_file) {
        std::cerr << "Impossible d'ouvrir le fichier\n";
    }
    else {
        my_file << "# " + cat + ":\n";
        my_file << "## " + m_name << ';' << m_pax << ":\n";
        for(it_map = m_recette.begin(); it_map != m_recette.end(); ++it_map) {
            my_file << "### " << it_map->first << ';' << it_map->second << "\n";
        }
        my_file << "####\n"; // End Of Patisserie
    }
}
