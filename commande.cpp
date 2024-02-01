// commande.cpp
// SPDX-FileCopyrightText: 2024 GuiQuad06 guillaume.cuadrado@gmail.com
// SPDX-License-Identifier: GPL-2.0-or-later

#include "commande.h"

uint32_t Commande::count = 0;

Commande::Commande(std::vector<Patisserie *> &patisseries)
{
    char response;
    std::string tmp_str;
    uint16_t pax; 
    int16_t remaining;
    uint16_t acc_pax = 0;

    // Getting the client's name
    std::cout << "What's the name of the consumer you want to make happy ?:\n";
    std::getline(std::cin, m_nom_client);
    remove_trailing_spaces(m_nom_client);

    // Getting the total people number
    std::cout << "For how many pepole the order is required for ?\n";
    std::cin >> m_tot_pax;
    std::cin.ignore();

    // Create an empty map
    // Key is a pointer to Patisserie, Value is a unsigned int...
    m_patisserie = std::map<Patisserie,uint16_t>();
    Patisserie* matching_pastry = nullptr;

    do {
        std::cout << "Order Wizard !\n";

        // Filling the pastry dictionnary
        std::cout << "What Pastry would you like to add ?\n";

        // Display the available pastries
        for(auto patisserie : patisseries) {
            std::cout << patisserie->get_patisserie_name() << '\n';
        }

        std::getline(std::cin, tmp_str);
        remove_trailing_spaces(tmp_str);

        std::cout << "For how many people the pastry ?\n";
        std::cin >> pax;
        std::cin.ignore();
        acc_pax += pax;

        // Find the corresponding object
        for (const auto& patisserie : patisseries) {
            if (patisserie->get_patisserie_name() == tmp_str) {
                matching_pastry = patisserie;
                break;
            }
        }

        if (matching_pastry) {
            Patisserie pastry_tmp(*matching_pastry);

            //Insert the element in the map
            m_patisserie.insert({pastry_tmp, pax});

        } else {
            std::cout << "Patisserie not found!\n";
        }

        remaining = remaining_pax(acc_pax);
        if (remaining <= 0) {
            remaining == 0 ? std::cout << "Quantite Parfaite!\n" : std::cout << "oopss il va y avoir des restes !\n";
            break;
        }

        std::cout << "We still need pastry for " << remaining << " people\n";
        std::cout << "Would you like to store another Patisserie ? (Y/n)\n";
        std::cin >> response;
        std::cin.ignore();

    } while(response == 'y' || response == 'Y'); 

    matching_pastry = nullptr;

    m_command_id = ++Commande::count;
}

Commande::Commande(std::string nom_client, unsigned int tot_pax) : m_nom_client(nom_client), m_tot_pax(tot_pax)
{
    m_patisserie = std::map<Patisserie,uint16_t>();

    m_command_id = ++Commande::count;
}

Commande::Commande(const Commande& other) : m_nom_client(other.m_nom_client), m_tot_pax(other.m_tot_pax), m_command_id(other.m_command_id)
{
    for (auto it = other.m_patisserie.begin(); it != other.m_patisserie.end(); ++it) {
        m_patisserie[it->first] = it->second;
    }
}

Commande::~Commande()
{
    // Map instance m_patisserie from std lib is freed by the lib...

    Commande::count--;
}

Commande& Commande::operator=(const Commande& other)
{
    if(this != &other) {
        m_nom_client = other.m_nom_client;
        m_tot_pax = other.m_tot_pax;
        for (auto it = other.m_patisserie.begin(); it != other.m_patisserie.end(); ++it) {
            m_patisserie[it->first] = it->second;
        }
    }
    return *this;
}

void Commande::display_commande(void)
{
    std::map<Patisserie,uint16_t>::const_iterator it_map;
    std::cout << "Command ID: " << m_command_id << "\nClient :" << m_nom_client << "\nNb de pax total:" << m_tot_pax << '\n';

    for(it_map = m_patisserie.begin(); it_map != m_patisserie.end(); ++it_map) {
        std::cout << "\tKey:" << it_map->first << "\tValue:" << it_map->second << '\n';
    }
}

void Commande::save_commande(std::ofstream &my_file)
{
    std::map<Patisserie,uint16_t>::const_iterator it_map;

    if(!my_file) {
        std::cerr << "Impossible d'ouvrir le fichier\n";
    }
    else {
        my_file << "# " << m_command_id << ":\n";
        my_file << "## " << m_nom_client << ";" << m_tot_pax << ":\n";
        for(it_map = m_patisserie.begin(); it_map != m_patisserie.end(); ++it_map) {
            my_file << "### " << it_map->first << ';' << it_map->second << "\n";
        }
        my_file << "####\n"; // End Of Commande
    }
}

void Commande::load_commandes(std::ifstream &my_file, std::vector<Commande*> &commandes, std::vector<Patisserie*> &patisseries)
{
    if(!my_file) {
        std::cerr << "Impossible d'ouvrir le fichier\n";
        return;
    }
    else {
        std::string current_line;
        Commande current_commande("foo", 10u);

        while (std::getline(my_file, current_line)) {
            if (current_line.empty()) {
                continue; // Skip empty lines
            }
            // End of Commande
            if (!current_line.compare(0, 5, "####")) {
                commandes.push_back(new Commande(current_commande));
                // Clean the map
                current_commande.clean_patisseries();
                Commande::count++;
            }
            // Patisserie map insert
            else if (!current_line.compare(0, 4, "### ")) {
                // Extract recette and quantity
                size_t len = current_line.size() - 4;
                std::istringstream iss(current_line.substr(4, len));
                std::string pastry_str, pax_str;
                Patisserie* matching_patisserie = nullptr;
                int pax;
                char delimiter = ';';

                if (std::getline(iss, pastry_str, delimiter) && std::getline(iss, pax_str)) {
                    pax = std::stoi(pax_str);
                    // Lookup for Patisserie object corresponding to the std::string patisserie
                    for (const auto& patisserie : patisseries) {
                        if (patisserie->get_patisserie_name() == pastry_str) {
                            matching_patisserie = patisserie;
                            break;
                        }
                    }
                    if (matching_patisserie) {
                        Patisserie patisserie_tmp(*matching_patisserie);
                        current_commande.m_patisserie.insert({patisserie_tmp, pax});
                    }
                }
            }
            // Name of the consumer + total nb of people
            else if (!current_line.compare(0, 3, "## ")) {
                size_t len = current_line.size() - 3;
                std::istringstream iss(current_line.substr(3, len));
                std::string name_str, pax_str;
                char delimiter = ';';

                if (std::getline(iss, name_str, delimiter) && std::getline(iss, pax_str)) {
                    current_commande.m_tot_pax = stoi(pax_str); 
                    current_commande.m_nom_client = name_str;
                }
            }
            // Command ID
            else if (!current_line.compare(0, 2, "# ")) {
                size_t len = current_line.size() - 2;
                std::string::size_type end = current_line.rfind(':');
                current_commande.m_command_id = std::stoi(current_line.substr(2, end-2));
            }
        }
    }
}

int16_t Commande::remaining_pax(uint16_t acc)
{
    if(acc > m_tot_pax) {
        return -1;
    }
    else {
        return (m_tot_pax - acc);
    }
}