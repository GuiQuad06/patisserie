// patisserie.cpp
// SPDX-FileCopyrightText: 2024 GuiQuad06 guillaume.cuadrado@gmail.com
// SPDX-License-Identifier: GPL-2.0-or-later

#include "patisserie.h"

Patisserie::Patisserie(std::vector<Recette *> &recettes)
{
    char cat, response;
    uint16_t qty;
    std::string tmp_str;

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
    Recette* matching_recette = nullptr;

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

        // Find the corresponding object
        for (const auto& recette : recettes) {
            if (recette->get_recette_name() == tmp_str) {
                matching_recette = recette;
                break;
            }
        }

        if (matching_recette) {
            Recette recette_tmp(*matching_recette);

            //Insert the element in the map
            m_recette.insert({recette_tmp, qty});

        } else {
            std::cout << "Recette not found!\n";
        }

        std::cout << "Would you like to store another Recipe ? (Y/n)\n";
        std::cin >> response;
        std::cin.ignore();

    } while(response == 'y' || response == 'Y');

    matching_recette = nullptr;
}

Patisserie::Patisserie(e_pastry_type_t cat, std::string name, unsigned int pax) : m_type(cat), m_name(name), m_pax(pax)
{
    m_recette = std::map<Recette,uint16_t>();
}

Patisserie::Patisserie(const Patisserie& other) : m_type(other.m_type), m_name(other.m_name),  m_pax(other.m_pax)
{
    for (auto it = other.m_recette.begin(); it != other.m_recette.end(); ++it) {
        m_recette[it->first] = it->second;
    }
}

Patisserie::~Patisserie()
{
    // Map instance m_recette from std lib is freed by the lib...
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

    std::map<Recette,uint16_t>::const_iterator it_map;
    std::cout << "Category : " << cat << "\nName :" << m_name << "\nNb de pax:" << m_pax << '\n';

    for(it_map = m_recette.begin(); it_map != m_recette.end(); ++it_map) {
        std::cout << "\tKey:" << it_map->first << "\tValue:" << it_map->second << '\n';
    }
}

std::string Patisserie::get_patisserie_name()
{
    return m_name; 
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
            my_file << "### " << it_map->first << ';' << it_map->second << "\n";
        }
        my_file << "####\n"; // End Of Patisserie
    }
}

void Patisserie::load_patisseries(std::ifstream &my_file, std::vector<Patisserie*> &patisseries, std::vector<Recette*> &recettes)
{
    if(!my_file) {
        std::cerr << "Impossible d'ouvrir le fichier\n";
        return;
    }
    else {
        std::string current_line;
        Patisserie current_pastry(kTARTE, "tata", 6u);

        while (std::getline(my_file, current_line)) {
            if (current_line.empty()) {
                continue; // Skip empty lines
            }
            // End of Patisserie
            if (!current_line.compare(0, 5, "####")) {
                patisseries.push_back(new Patisserie(current_pastry));
                // Clean the map
                current_pastry.clean_recettes();
            }
            // Recette map insert
            else if (!current_line.compare(0, 4, "### ")) {
                // Extract recette and quantity
                size_t len = current_line.size() - 4;
                std::istringstream iss(current_line.substr(4, len));
                std::string recette_str, quantity_str;
                Recette* matching_recette = nullptr;
                int quantity;
                char delimiter = ';';

                if (std::getline(iss, recette_str, delimiter) && std::getline(iss, quantity_str)) {
                    quantity = std::stoi(quantity_str);
                    // Lookup for Recette object corresponding to the std::string recette
                    for (const auto& recette : recettes) {
                        if (recette->get_recette_name() == recette_str) {
                            matching_recette = recette;
                            break;
                        }
                    }
                    if (matching_recette) {
                        Recette recette_tmp(*matching_recette);
                        current_pastry.m_recette.insert({recette_tmp, quantity});
                    }
                }
            }
            // Name of Pastry
            else if (!current_line.compare(0, 3, "## ")) {
                size_t len = current_line.size() - 3;
                std::istringstream iss(current_line.substr(3, len));
                std::string name_str, pax_str;
                char delimiter = ';';

                if (std::getline(iss, name_str, delimiter) && std::getline(iss, pax_str)) {
                    current_pastry.m_pax = stoi(pax_str); 
                    current_pastry.m_name = name_str;
                }
            }
            // Type of Pastry
            else if (!current_line.compare(0, 2, "# ")) {
                size_t len = current_line.size() - 2;
                std::string::size_type end = current_line.rfind(':');
                current_pastry.m_type = Patisserie::type_converter(current_line.substr(2, end-2));
            }
        }
    }
}

void Patisserie::clean_recettes(void)
{
    m_recette.clear();
}

e_pastry_type_t Patisserie::type_converter(std::string str)
{
    return str == "TARTE" ? kTARTE :
        str == "ENTREMET" ? kENTREMET : kTRADI;
}

bool Patisserie::operator<(const Patisserie& other) const
{
    return (m_name < other.m_name);
}

std::ostream& operator<<(std::ostream& os, const Patisserie& patisserie)
{
    // Stream the m_name member to the output stream
    os << patisserie.m_name;
    return os;
}