#ifndef PIRATE_H
#define PIRATE_H

#include <iostream>

class Pirate{
    int m_pirate_id;

    public:
    Pirate(int id);
    Pirate();
    Pirate(Pirate& p) = default;
    int get_id()const;

    friend bool operator<(const Pirate& one, const Pirate& other);
};


#endif