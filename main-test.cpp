#ifndef MAIN_H
#define MAIN_H
#include <iostream>
#include "unionFind.h"
#include "pirate.h"
// #include "hashTable.h"

int main() {

    UnionFind<Pirate*> union_find;
    hashTable<Pirate*> pirate_table;

    Pirate* pirate_1 = new Pirate(20);
    Pirate* pirate_2 = new Pirate(5);
    Pirate* pirate_3 = new Pirate(10);
    Pirate* pirate_4 = new Pirate(15);
    Pirate* pirate_5 = new Pirate(22);
    Pirate* pirate_6 = new Pirate(9);
    Pirate* pirate_7 = new Pirate(11);

    // pirate_table.insert(pirate_1);
    // pirate_table.insert(pirate_2);
    // pirate_table.insert(pirate_3);
    // pirate_table.insert(pirate_4);
    // pirate_table.insert(pirate_5);
    // pirate_table.insert(pirate_6);
    // pirate_table.insert(pirate_7);
    // pirate_table.print();
    // pirate_table.remove(17);
    // pirate_table.remove(34);
    // pirate_table.remove(51);
    // pirate_table.remove(68);
    // pirate_table.remove(85);
    // pirate_table.print();
    // pirate_table.insert(pirate_1);
    // pirate_table.insert(pirate_2);
    // pirate_table.insert(pirate_3);
    // pirate_table.insert(pirate_4);
    // pirate_table.insert(pirate_5);
    // pirate_table.print();


    union_find.make_set(pirate_1);
    union_find.make_set(pirate_2);
    union_find.make_set(pirate_3);
    union_find.make_set(pirate_4);
    union_find.make_set(pirate_5);
    union_find.make_set(pirate_6);
    union_find.make_set(pirate_7);


    union_find.print();

    union_find.union_sets(union_find.find(20),union_find.find(5));
    union_find.union_sets(union_find.find(10),union_find.find(15));
    union_find.union_sets(union_find.find(22),union_find.find(9));

    union_find.union_sets(union_find.find(11),union_find.find(10));
    union_find.union_sets(union_find.find(9),union_find.find(5));

    union_find.union_sets(union_find.find(22),union_find.find(15));

    union_find.find(5);
    union_find.find(11);
    union_find.find(15);

    union_find.print();

    // union_find.find(7);
    // union_find.find(4);
    // union_find.find(6);

    // union_find.print();

    // std::cout << "root of find " << union_find.find(1)->get_id() << std::endl;
    // std::cout << "root of find " << union_find.find(2)->get_id() << std::endl;
    // std::cout << "root of find " << union_find.find(3)->get_id() << std::endl;
    // std::cout << "root of find " << union_find.find(9)->get_id() << std::endl;
    // std::cout << "root of find " << union_find.find(15)->get_id() << std::endl;
    // std::cout << "root of find " << union_find.find(9)->get_id() << std::endl;
    
    return 0;
}

#endif