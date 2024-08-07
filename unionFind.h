#ifndef UNION_FIND_H_
#define UNION_FIND_H_


#include <iostream>
#include "hashTable.h"

template <typename T>
class UnionFind {
private:

    struct Set {
        T root;
        int m_fleet_size;                                                                   // Current status of the entry
        int m_pirate_size;
        int m_rank;
        Set() : root(T()), m_fleet_size(1), m_pirate_size(0), m_rank(0) {} 
        Set(T t, int fleet_size, int pirate_size) : root(t), m_fleet_size(fleet_size), m_pirate_size(pirate_size), m_rank(0) {}
        int get_id(){
            return root->get_id();
        }
        int get_fleet_size(){
            return m_fleet_size;
        }
        int get_pirate_size(){
            return m_pirate_size;
        }
        void increase_pirate_size(int size){
            m_pirate_size += size;
        }
        int get_rank(){
            return m_rank;
        }
        void increase_rank(){
            m_rank += 1;
        }
    };
    
    HashTable<Set*> m_sets;
    T* m_parent;
    T* m_data;
    int* m_dynamic_rank;
    int m_total;
    int capacity;

    void resize() {
        
        int new_capacity = capacity * 2;
        T* new_parent = new T[new_capacity];
        T* new_data = new T[new_capacity];
        int* new_dynamic_rank = new int[new_capacity];

        for (int i = 0; i < capacity; ++i) {
            new_parent[i] = m_parent[i];
            new_data[i] = m_data[i];
            new_dynamic_rank[i] = m_dynamic_rank[i];
        }

        delete[] m_parent;
        delete[] m_data;
        delete[] m_dynamic_rank;

        m_parent = new_parent;
        m_data = new_data;
        m_dynamic_rank = new_dynamic_rank;
        capacity = new_capacity;
    }

public:

    UnionFind(int initial_capacity = 2) : m_total(0), capacity(initial_capacity) {
        m_parent = new T[capacity];
        m_data = new T[capacity];
        m_dynamic_rank = new int[capacity];
    }

    ~UnionFind() {
        delete[] m_parent;
        delete[] m_data;
        delete[] m_dynamic_rank;
    }

    void make_set(T object) {
        while (object->get_id() >= capacity) {
            resize();
        }
        m_parent[object->get_id()] = nullptr;
        m_dynamic_rank[object->get_id()] = 0;
        m_sets.insert(new Set(object,1,0));
        m_data[object->get_id()] = object;

        if (object->get_id() >= m_total) {
            m_total = object->get_id() + 1;
        }
    }

    void add_pirate(int id){                                                        // Add a pirate to the system
        m_dynamic_rank[id]++;
    }

    T find(int id) {                                                                // Give me and ID, ill give you it actual root, and maintain connection shortcut
        
        // std::cout << "im looking for " << id << std::endl;
        
        T root = find_root(id);
        if(root == m_data[id]){
            return root;
        }
        else{
            while (m_parent[id] != nullptr) {
                // m_parent[id] = root;
                return find(m_parent[id]->get_id());
            }
        }
        return root;
    }

    T find_root(int id) {                                                           // Give me an ID, ill give you its actual root
        T root = m_data[id];
        while (m_parent[id] != nullptr) {
            
            return find_root(m_parent[id]->get_id());
        }
        return root;
    }

    T find_root_from_fleet(T& fleet) {                                              // Give me a fleet, ill give you its actual root (used in unite)
        T root = fleet;
        while (m_parent[fleet->get_id()] != nullptr) {
            
            return find_root(m_parent[fleet->get_id()]->get_id());
        }
        return root;
    }

    bool check_if_excist(int id){                                                   // Check if excist in database, if there was historical fleet id
        return (m_data[id] != nullptr);
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
        return m_sets.get_pirate_size(id,increasment);
    }

    int get_rank(int id){                                                           // Get the fleet rank by moving up the upside tree
        int result = m_dynamic_rank[id];
        while (m_parent[id] != nullptr) {
            result += get_rank(m_parent[id]->get_id());
            return result;
        }
        return result;
    }

    void union_sets(T first_fleet, T second_fleet, int fleetId1, int fleetId2) {

        // std::cout << "the original first root:" << first_fleet->get_id() << std::endl;
        // std::cout << "the original second root:" << second_fleet->get_id() << std::endl;

        T first = find_root_from_fleet(first_fleet);
        T second = find_root_from_fleet(second_fleet);

        // std::cout << "the original first root:" << first->get_id() << std::endl;
        // std::cout << "the original second root:" << second->get_id() << std::endl;

        int first_fleet_size = m_sets.get(fleetId1)->get_fleet_size();
        int second_fleet_size = m_sets.get(fleetId2)->get_fleet_size();

        int first_pirate_size = m_sets.get(fleetId1)->get_pirate_size();
        int second_pirate_size = m_sets.get(fleetId2)->get_pirate_size();

        int new_fleet_size = first_fleet_size + second_fleet_size;
        int new_pirate_size = first_pirate_size + second_pirate_size;

        T new_root = (first_pirate_size >= second_pirate_size) ? first : second;

            if (first_fleet_size < second_fleet_size) {
                m_parent[first->get_id()] = second;
                if(first_pirate_size >= second_pirate_size){                   //in case second is actual root, first is identifier root
                    m_dynamic_rank[second->get_id()] -= second_pirate_size;
                    m_dynamic_rank[first->get_id()] += first_pirate_size;
                }
                else{                                                          //in case second is both actual and identifier root
                    m_dynamic_rank[first->get_id()] += second_pirate_size;
                }
            } else {
                m_parent[second->get_id()] = first;
                if(first_pirate_size >= second_pirate_size){                   //in case first is both actual and identifier root
                    m_dynamic_rank[second->get_id()] += first_pirate_size;
                }
                else{                                                          //in case first is actual root, second is identifier root
                    m_dynamic_rank[first->get_id()] -= first_pirate_size;
                    m_dynamic_rank[second->get_id()] += second_pirate_size;
                }
            }

        m_sets.remove(fleetId1);
        m_sets.remove(fleetId2);
        m_sets.insert(new Set(new_root,new_fleet_size,new_pirate_size));
        
        // m_sets.print();
    }

//------------------------------------------------------------------------------------------
//----------------------------------print shit utilities------------------------------------
//-----------------------------------remember to remove-------------------------------------

    void print_parent() {
        std::cout << "Elements in the parent: ";
        for (int i = 0; i < m_total; ++i) {
            if(m_parent[i] != nullptr)
                std::cout << m_parent[i]->get_id() << " ";
            else
                std::cout << m_parent[i] << " ";                
        }
        std::cout << std::endl;
    }


    void print_data() {
        std::cout << "Elements in the data:   ";
        for (int i = 0; i < m_total; ++i) {
            if(m_data[i] != nullptr)
                std::cout << m_data[i]->get_id() << " "; 
            else
                std::cout << m_data[i] << " ";                
        }
        std::cout << std::endl;
    }

    void print_rank() {
        std::cout << "Elements in the rank:   ";
        for (int i = 0; i < m_total; ++i) {
            if(m_dynamic_rank[i] != 0)
                std::cout << m_dynamic_rank[i] << " "; 
            else
                std::cout << m_dynamic_rank[i] << " ";                
        }
        std::cout << std::endl;
    }


    void print() {
        print_data();
        print_parent();
        print_rank();
        m_sets.print();
    }


//-------------------------------end ofprint shit utilities---------------------------------
//------------------------------------------------------------------------------------------
    
};


#endif