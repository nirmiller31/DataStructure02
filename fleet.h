#ifndef FLEET_H
#define FLEET_H

#include <iostream>

class Fleet{
    int m_fleet_id;
    int m_ships;

    public:
    Fleet(int id);
    Fleet();
    Fleet(Fleet& f) = default;
    int get_id()const;
    int get_ship_number()const;

    friend bool operator<(const Fleet& one, const Fleet& other);
};


#endif