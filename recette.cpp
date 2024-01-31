// recette.cpp
// SPDX-FileCopyrightText: 2024 GuiQuad06 guillaume.cuadrado@gmail.com
// SPDX-License-Identifier: GPL-2.0-or-later

#include "recette.h"

Recette::Recette()
{
    char cat, response;
    uint16_t qty;
    std::string tmp_str;

    // Getting the recipe's category
    std::cout << "What's the category of the recipe you want to store ?:\n";
    std::cout << "\t-0 if PATE\n\t-1 if CREME\n\t-2 if BISCUIT\n\t-3 if MOUSSE\n\t-4 if GLACAGE\n";
    std::cin >> cat;
    std::cin.ignore();

    switch (cat) {
    case '0':
        m_category = kPATE;
        break;
    case '1':
        m_category = kCREME;
        break;
    case '2':
        m_category = kBISCUIT;
        break;
    case '3':
        m_category = kMOUSSE;
        break;
    case '4':
        m_category = kGLACAGE;
        break;
    default:
        std::cout << "Not supported Category, set to PATE instead...\n";
        m_category = kPATE;
    }

    // Getting the recipe's name
    std::cout << "What's the name of the recipe you want to store ?:\n";
    std::getline(std::cin, m_name);
    remove_trailing_spaces(m_name);

    // Create an empty map
    // Key is a string, Value is a uint16...
    m_ingredient = std::map<std::string,uint16_t>();

    do {
        std::cout << "Ingredient Wizard !\n";

        // Filling the ingredients dictionnary
        std::cout << "What ingredient would you like to add ?\n";
        std::getline(std::cin, tmp_str);
        remove_trailing_spaces(tmp_str);

        std::cout << "What will be the quantity of the ingredient ?\n";
        std::cin >> qty;
        std::cin.ignore();

        m_ingredient.insert({tmp_str, qty});

        std::cout << "Would you like to store another Ingredient ? (Y/n)\n";
        std::cin >> response;
        std::cin.ignore();

    } while(response == 'y' || response == 'Y');
}

Recette::Recette(e_category_t cat, std::string name) : m_category(cat), m_name(name)
{
    m_ingredient = std::map<std::string,uint16_t>();
}

Recette::Recette(const Recette& other) : m_category(other.m_category), m_name(other.m_name)
{
    for (auto it = other.m_ingredient.begin(); it != other.m_ingredient.end(); ++it) {
        m_ingredient[it->first] = it->second;
    }
}

Recette::~Recette()
{
    // Map instance m_ingredient from std lib is freed by the lib...
}

Recette& Recette::operator=(const Recette& other)
{
    if(this != &other) {
        m_name = other.m_name;
        m_category = other.m_category;
        for (auto it = other.m_ingredient.begin(); it != other.m_ingredient.end(); ++it) {
            m_ingredient[it->first] = it->second;
        }
    }
    return *this;
}

std::string Recette::category_interpreter()
{
    return m_category == kPATE ? "PATE" :
        m_category == kCREME ? "CREME" :
        m_category == kBISCUIT ? "BISCUIT" :
        m_category == kMOUSSE ? "MOUSSE" : "GLACAGE";
}

void Recette::display_recette()
{
    std::string cat = category_interpreter();

    std::map<std::string,uint16_t>::const_iterator it_map;
    std::cout << "Category : " << cat << "\nName :" << m_name << '\n';

    for(it_map = m_ingredient.begin(); it_map != m_ingredient.end(); ++it_map) {
        std::cout << "\tKey:" << it_map->first << "\tValue:" << it_map->second << '\n';
    }
}

std::string Recette::get_recette_name()
{
    return m_name; 
}

void Recette::save_recette(std::ofstream& my_file)
{
    std::map<std::string,uint16_t>::const_iterator it_map;
    std::string cat = category_interpreter();

    if(!my_file) {
        std::cerr << "Impossible d'ouvrir le fichier\n";
        return;
    }
    else {
        my_file << "# " + cat + ":\n";
        my_file << "## " + m_name + ":\n";
        for(it_map = m_ingredient.begin(); it_map != m_ingredient.end(); ++it_map) {
            my_file << "### " << it_map->first << ';' << it_map->second << "\n";
        }
        my_file << "####\n"; // End Of Recette
    }
}

void Recette::load_recettes(std::ifstream& my_file, std::vector<Recette*> &recettes)
{
    if(!my_file) {
        std::cerr << "Impossible d'ouvrir le fichier\n";
        return;
    }
    else {
        std::string current_line;
        Recette current_recipe(kPATE, "toto");

        while (std::getline(my_file, current_line)) {
            if (current_line.empty()) {
                continue; // Skip empty lines
            }
            // End of Recette
            if (!current_line.compare(0, 5, "####")) {
                recettes.push_back(new Recette(current_recipe));
                //Clear the map
                current_recipe.clean_ingredients();
            }
            // Ingredient map insert
            else if (!current_line.compare(0, 4, "### ")) {
                // Extract ingredient and quantity
                size_t len = current_line.size() - 4;
                std::istringstream iss(current_line.substr(4, len));
                std::string ingredient, quantity_str;
                int quantity;
                char delimiter = ';';

                if (std::getline(iss, ingredient, delimiter) && std::getline(iss, quantity_str)) {
                    quantity = std::stoi(quantity_str);
                    current_recipe.m_ingredient.insert({ingredient, quantity});
                }
            }
            // Name of Recipe
            else if (!current_line.compare(0, 3, "## ")) {
                size_t len = current_line.size() - 3;
                std::string::size_type end = current_line.rfind(':');
                current_recipe.m_name = current_line.substr(3, end-3);
            }
            // Category of Recipe
            else if (!current_line.compare(0, 2, "# ")) {
                size_t len = current_line.size() - 2;
                std::string::size_type end = current_line.rfind(':');
                current_recipe.m_category = Recette::category_converter(current_line.substr(2, end-2));
            }
        }
    }
}

void Recette::clean_ingredients(void)
{
    m_ingredient.clear();
}

e_category_t Recette::category_converter(std::string str)
{
    return str == "PATE" ? kPATE :
        str == "CREME" ? kCREME :
        str == "BISCUIT" ? kBISCUIT :
        str == "MOUSSE" ? kMOUSSE : kGLACAGE;
}

bool Recette::operator<(const Recette& other) const
{
    return (m_name < other.m_name);
}

std::ostream& operator<<(std::ostream& os, const Recette& recette)
{
    // Stream the m_name member to the output stream
    os << recette.m_name;
    return os;
}
