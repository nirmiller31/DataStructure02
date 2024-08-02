#ifndef MAIN_H
#define MAIN_H
#include <iostream>
#include "unionFind.h"
#include "pirate.h"

int main() {

    UnionFind<Pirate*> union_find;

    Pirate* pirate_1 = new Pirate(1);
    Pirate* pirate_2 = new Pirate(2);
    Pirate* pirate_3 = new Pirate(3);
    Pirate* pirate_4 = new Pirate(4);
    Pirate* pirate_5 = new Pirate(5);
    Pirate* pirate_6 = new Pirate(6);
    Pirate* pirate_7 = new Pirate(7);

    union_find.make_set(pirate_1);
    union_find.make_set(pirate_2);
    union_find.make_set(pirate_3);
    union_find.make_set(pirate_4);
    union_find.make_set(pirate_5);
    union_find.make_set(pirate_6);
    union_find.make_set(pirate_7);


    // union_find.print();

    union_find.union_sets(union_find.find(1),union_find.find(2));
    union_find.union_sets(union_find.find(3),union_find.find(4));
    union_find.union_sets(union_find.find(2),union_find.find(3));

    union_find.union_sets(union_find.find(5),union_find.find(6));
    union_find.union_sets(union_find.find(6),union_find.find(7));

    union_find.union_sets(union_find.find(1),union_find.find(7));

    union_find.print();

    union_find.find(7);
    union_find.find(4);
    union_find.find(6);

    union_find.print();

    // std::cout << "root of find " << union_find.find(1)->get_id() << std::endl;
    // std::cout << "root of find " << union_find.find(2)->get_id() << std::endl;
    // std::cout << "root of find " << union_find.find(3)->get_id() << std::endl;
    // std::cout << "root of find " << union_find.find(9)->get_id() << std::endl;
    // std::cout << "root of find " << union_find.find(15)->get_id() << std::endl;
    // std::cout << "root of find " << union_find.find(9)->get_id() << std::endl;
    
    return 0;
}

#endif