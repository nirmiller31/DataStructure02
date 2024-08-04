// 
// 234218 Data Structures 1.
// Semester: 2024B (spring).
// Wet Exercise #2.
// 
// Recommended TAB size to view this file: 8.
// 
// The following header file contains all methods we expect you to implement.
// You MAY add private methods and fields of your own.
// DO NOT erase or modify the signatures of the public methods.
// DO NOT modify the preprocessors in this file.
// DO NOT use the preprocessors in your other code files.
// 

#ifndef PIRATESA2_H_
#define PIRATESA2_H_

#include "wet2util.h"
#include "pirate.h"
#include "fleet.h"
#include "unionFind.h"

class oceans_t {
private:

    UnionFind<Fleet*> m_fleet_find;
    HashTable<Pirate*> m_pirate_table;
	//
	// Here you may add anything you want
	//
	
public:
	// <DO-NOT-MODIFY> {

    oceans_t();

	virtual ~oceans_t();

    StatusType add_fleet(int fleetId);

    StatusType add_pirate(int pirateId, int fleetId);

    StatusType pay_pirate(int pirateId, int salary);

    output_t<int> num_ships_for_fleet(int fleetId);

    output_t<int> get_pirate_money(int pirateId);

    StatusType unite_fleets(int fleetId1, int fleetId2);

    StatusType pirate_argument(int pirateId1, int pirateId2);
	
	// } </DO-NOT-MODIFY>

    void print_fleet(){
        m_fleet_find.print();
    }

    void print_rank(int id){
        std::cout << "the rank is: " << m_fleet_find.get_rank(id) << std::endl;
    }
};

#endif // PIRATESA2_H_
