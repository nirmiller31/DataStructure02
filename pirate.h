#ifndef PIRATE_H
#define PIRATE_H

#include <iostream>

class Pirate{
    int m_pirate_id;
    int m_original_fleet;
    int m_pirate_rank;
    int m_treasure;

    public:
    Pirate(int id, int pirate_original_fleet, int rank);
    // Pirate();
    Pirate(Pirate& p) = default;
    int get_id()const;
    int get_fleet();
    int get_rank();
    void update_treasure(int salary);
    int get_treasure();

    friend bool operator<(const Pirate& one, const Pirate& other);
};


#endif