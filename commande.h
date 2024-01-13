// commande.h
// SPDX-FileCopyrightText: 2024 GuiQuad06 guillaume.cuadrado@gmail.com
// SPDX-License-Identifier: GPL-2.0-or-later

#ifndef COMMANDE_H
#define COMMANDE_H

/**
 * @todo write docs
 */
class Commande
{
public:
    /**
     * Default constructor
     */
    Commande();

    /**
     * Copy constructor
     *
     * @param other TODO
     */
    Commande(const Commande& other);

    /**
     * Destructor
     */
    ~Commande();

    /**
     * Assignment operator
     *
     * @param other TODO
     * @return TODO
     */
    Commande& operator=(const Commande& other);

};

#endif // COMMANDE_H
