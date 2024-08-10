
#include "pirate.h"


Pirate::Pirate(int id, int pirate_original_fleet, int rank): m_pirate_id(id), m_original_fleet(pirate_original_fleet), m_pirate_rank(rank), m_treasure(0) {};

int Pirate::get_id()const{ 
    return m_pirate_id;
}

int Pirate::get_fleet(){ 
    return m_original_fleet;
}

int Pirate::get_rank(){ 
    return m_pirate_rank;
}

void Pirate::update_treasure(int salary){
    m_treasure += salary;
}

int Pirate::get_treasure(){
    return m_treasure;
}

bool operator<(const Pirate& one, const Pirate& other){
    return one.get_id() < other.get_id();
}


