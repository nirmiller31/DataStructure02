
#include "fleet.h"


Fleet::Fleet(int id):m_fleet_id(id), m_ships(1){};

Fleet::Fleet():m_fleet_id(0), m_ships(1){};

int Fleet::get_id()const{ 
    return m_fleet_id;
}

int Fleet::get_ship_number()const{ 
    return m_ships;
}

bool operator<(const Fleet& one, const Fleet& other){
    return one.get_id() < other.get_id();
}


