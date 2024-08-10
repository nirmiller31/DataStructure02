#ifndef UNION_FIND_H_
#define UNION_FIND_H_


#include <iostream>
#include "hashTable.h"

template <typename T>
class UnionFind {
private:

    struct Set {
        T m_data;
        T m_parent;
        int m_fleet_size;                                                                   // Current status of the entry
        int m_pirate_size;
        int m_dynamic_rank;
        int m_rank;
        

        Set() : m_data(T()), m_parent(nullptr), m_fleet_size(1), m_pirate_size(0), m_rank(0), m_dynamic_rank(0) {} 
        Set(T data, T parent, int fleet_size, int pirate_size, int dynamic_rank) : m_data(data), m_parent(parent), m_fleet_size(fleet_size), m_pirate_size(pirate_size), m_dynamic_rank(dynamic_rank), m_rank(0) {}
        int get_id(){
            return m_data->get_id();
        }
        int get_fleet_size(){
            return m_fleet_size;
        }
        int get_pirate_size(){
            return m_pirate_size;
        }
        T get_parent(){
            return m_parent;
        }
        void set_parent(T& new_parent){
            m_parent = new_parent;
        }
        void increase_pirate_size(int size){
            m_pirate_size += size;
        }
        int get_rank(){
            return m_rank;
        }
        T get_data(){
            return m_data;
        }
        int get_dynamic_rank(){
            return m_dynamic_rank;
        }
        void add_to_dynamic_rank(int size){
            m_dynamic_rank += size;
        }
        void decrease_dynamic_rank(int size){
            m_dynamic_rank -= size;
        }
    };
    
    HashTable<Set*> m_sets;

    int m_total;
    int capacity;



public:

    UnionFind(int initial_capacity = 2) : m_total(0), capacity(initial_capacity) {

    }

    ~UnionFind() {

    }

    void make_set(T object) {

        m_sets.insert(new Set(object,nullptr,1,0,0));

    }

    void add_pirate(int id){                                                        // Add a pirate to the system
        m_sets.get_history(id)->add_to_dynamic_rank(1);

    }

    T find(int id) {                                                                // Give me and ID, ill give you it actual root, and maintain connection shortcut

        if(m_sets.get_history(id)->get_parent() == nullptr){

            return m_sets.get_history(id)->get_data();
        }
        else{
            return find(m_sets.get_history(id)->get_parent()->get_id());

        }
    }

    T find_root(int id) {                                                           // Give me an ID, ill give you its actual root
        T root = m_sets.get_history(id)->get_data();
        while (m_sets.get_history(id)->get_parent() != nullptr) {
            return find_root(m_sets.get_history(id)->get_parent()->get_id());
        }
        return root;
    }

    T find_root_from_fleet(T& fleet) {                                              // Give me a fleet, ill give you its actual root (used in unite)
        int fleet_id = fleet->get_id();
        return find(fleet_id);
    }


    bool check_if_excist(int id){                                                   // Check if excist in database, if there was historical fleet id
        return m_sets.search_history(id);
    }

    bool check_identifier_fleet(int id){                                            // Check if the identifier excist, if legit fleet
        return m_sets.search(id);
    }

    int get_pirate_size(int id){                                                    // Gets the updated (by identifier) pirate size
        // std::cout << "im searchong: " << id << std::endl;
        return m_sets.get_pirate_amount(id);
    }

    int get_fleet_size(int id){                                                     // Gets the updated (by identifier) fleet size (number of unites)
        return m_sets.get_fleet_size(id);
    }

    int get_pirate_amount_and_increase(int id, int increasment){                    // Gets the updated (by identifier) pirate size, and increase it by ##

        m_sets.get_pirate_size(id,increasment);

        return m_sets.get_pirate_size(id,0);
    }

    int get_rank(int id){                                                           // Get the fleet rank by moving up the upside tree

        int result = m_sets.get_history(id)->get_dynamic_rank();

        while (m_sets.get_history(id)->get_parent() != nullptr) {
            
            result += get_rank(m_sets.get_history(id)->get_parent()->get_id());
            return result;
        }
        return result;
    }


    void union_sets(T first_fleet, T second_fleet, int fleetId1, int fleetId2) {

        T first = find_root_from_fleet(first_fleet);
        T second = find_root_from_fleet(second_fleet);

        int first_fleet_size = m_sets.get(fleetId1)->get_fleet_size();
        int second_fleet_size = m_sets.get(fleetId2)->get_fleet_size();

        int first_pirate_size = m_sets.get(fleetId1)->get_pirate_size();
        int second_pirate_size = m_sets.get(fleetId2)->get_pirate_size();

        int new_fleet_size = first_fleet_size + second_fleet_size;
        int new_pirate_size = first_pirate_size + second_pirate_size;

        T parent;
        T old_root;

        T new_root = (first_pirate_size >= second_pirate_size) ? m_sets.get(fleetId1)->get_data() : m_sets.get(fleetId2)->get_data();

            if (first_fleet_size < second_fleet_size) {
                old_root = m_sets.get(fleetId1)->get_parent();
                m_sets.get_history(first->get_id())->set_parent(second);
                if(first_pirate_size >= second_pirate_size){                   //in case second is actual root, first is identifier root
                    m_sets.get_history(second->get_id())->add_to_dynamic_rank(first_pirate_size);
                    m_sets.get_history(first->get_id())->decrease_dynamic_rank((m_sets.get_history(second->get_id())->get_dynamic_rank()));
                    
                    if(old_root == nullptr){
                        parent = second;
                    }
                    else{
                        parent = old_root;
                    }
                }
                else{                                                          //in case second is both actual and identifier root
                    m_sets.get_history(first->get_id())->add_to_dynamic_rank((second_pirate_size - m_sets.get_history(second->get_id())->get_dynamic_rank()));
                    parent = m_sets.get(fleetId2)->get_parent();
                }
            } else if(first_fleet_size > second_fleet_size){
                old_root = m_sets.get(fleetId2)->get_parent();
                m_sets.get_history(second->get_id())->set_parent(first);
                if(first_pirate_size >= second_pirate_size){                   //in case first is both actual and identifier root
                    m_sets.get_history(second->get_id())->add_to_dynamic_rank((first_pirate_size - m_sets.get_history(first->get_id())->get_dynamic_rank()));
                    parent = m_sets.get(fleetId1)->get_parent();
                }
                else{                                                          //in case first is actual root, second is identifier root
                    m_sets.get_history(first->get_id())->add_to_dynamic_rank(second_pirate_size);
                    m_sets.get_history(second->get_id())->decrease_dynamic_rank((m_sets.get_history(first->get_id())->get_dynamic_rank()));
                    if(old_root == nullptr){                                    
                        parent = first;
                    }
                    else{
                        parent = old_root;
                    }
                }
            } else{
                if(first_pirate_size >= second_pirate_size){                    //what size equal, we can secide, it is good to go by the fleet size
                    parent = m_sets.get(fleetId1)->get_parent();
                    m_sets.get_history(second->get_id())->set_parent(first);
                    m_sets.get_history(second->get_id())->add_to_dynamic_rank((first_pirate_size - m_sets.get_history(first->get_id())->get_dynamic_rank()));
                    
                }
                else{
                    parent = m_sets.get(fleetId2)->get_parent();  
                    m_sets.get_history(first->get_id())->set_parent(second);
                    m_sets.get_history(first->get_id())->add_to_dynamic_rank((second_pirate_size - m_sets.get_history(second->get_id())->get_dynamic_rank()));  
                                    
                }
            }

        int dynamic;
        if(first_pirate_size >= second_pirate_size){
            dynamic = m_sets.get_history(fleetId1)->get_dynamic_rank();
            m_sets.remove(fleetId2);
        }
        else{
            dynamic = m_sets.get_history(fleetId2)->get_dynamic_rank();  
            m_sets.remove(fleetId1);
        }

        m_sets.insert_union(new Set(new_root,parent,new_fleet_size,new_pirate_size,dynamic));

    }

//------------------------------------------------------------------------------------------
//----------------------------------print shit utilities------------------------------------
//-----------------------------------remember to remove-------------------------------------

    // void print_parent() {
    //     std::cout << "Elements in the parent: ";
    //     for (int i = 0; i < m_total; ++i) {
    //         if(m_parent[i] != nullptr)
    //             std::cout << i << ":" << m_parent[i]->get_id() << " | ";
    //         else
    //             std::cout << i << ":" << "00" << " | ";                
    //     }
    //     std::cout << std::endl;
    // }


    // void print_data() {
    //     std::cout << "Elements in the data:   ";
    //     for (int i = 0; i < m_total; ++i) {
    //         if(m_data[i] != nullptr)
    //             std::cout << i << ":" << m_data[i]->get_id() << " | "; 
    //         else
    //             std::cout << i << ":" <<  "00" << " | ";                
    //     }
    //     std::cout << std::endl;
    // }

    // void print_rank() {
    //     std::cout << "Elements in the rank:   ";
    //     for (int i = 0; i < m_total; ++i) {
    //         if(m_dynamic_rank[i] != 0)
    //             std::cout << i << ":" << m_dynamic_rank[i] << " | "; 
    //         else
    //             std::cout << i << ":" <<  m_dynamic_rank[i] << " | ";                
    //     }
    //     std::cout << std::endl;
    // }


    void print() {
        // print_data();
        // print_parent();
        // print_rank();
        m_sets.print();
    }


//-------------------------------end ofprint shit utilities---------------------------------
//------------------------------------------------------------------------------------------
    
};


#endif