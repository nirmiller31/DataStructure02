
#include "pirate.h"


Pirate::Pirate(int id):m_pirate_id(id){};

Pirate::Pirate():m_pirate_id(0){};

int Pirate::get_id()const{ 
    return m_pirate_id;
}

bool operator<(const Pirate& one, const Pirate& other){
    return one.get_id() < other.get_id();
}


