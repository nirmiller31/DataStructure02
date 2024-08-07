#ifndef HASH_TABLE_H_
#define HASH_TABLE_H_

#include <iostream>

template <typename T>
class HashTable {
private:

    enum class Status { FREE, DELETED, TAKEN };

    T* table;
    Status* indexStatus;
    int capacity;
    int size;
    int primeIndex;

    static unsigned long long primes[59];                                   // huge prime list

    int hash1(int key) const {                                              // main hash function
        return (key % capacity);
    }

    int hash2(int key) const {                                              // second hash function (the step function)
        return (primes[primeIndex] - (key % primes[primeIndex])) + 1;
    }

    void resize() {                                                         // when a table becomes tight, we double its size

        int oldCapacity = capacity;
        T* oldTable = table;
        Status* oldindexStatus = indexStatus;

        capacity = primes[++primeIndex];                                    // sample the next prime, to be the updated capacity

        table = new T[capacity];                                            // create new table
        indexStatus = new Status[capacity];
        for (int i = 0; i < capacity; ++i) {                                // declare all as free
            indexStatus[i] = Status::FREE;
        }
        size = 0;

        for (int i = 0; i < oldCapacity; ++i) {                             // reHash elements by the new function
            if (oldindexStatus[i] == Status::TAKEN) {
                // std::cout << "im inserting: " << oldTable[i]->get_id() << std::endl;
                insert(oldTable[i]);
            }
        }

        delete[] oldTable;                                                  // free old memory
        delete[] oldindexStatus;

        
    }

public:
    HashTable(int initialCapacity = 17) : capacity(initialCapacity), size(0), primeIndex(0) {
        table = new T[capacity];                                          // new empty table
        indexStatus = new Status[capacity];                                 // initiate new stsus controller
        for (int i = 0; i < capacity; ++i) {
            indexStatus[i] = Status::FREE;
        }
    }

    ~HashTable() {
        delete[] table;
        delete[] indexStatus;
    }

    void insert(const T& key) {

        if (size >= capacity / 2) {                                         // our method to resize it (takes more than half)
            resize();
        }

        int index = hash1(key->get_id());
        int step = hash2(key->get_id());        

        while (indexStatus[index] == Status::TAKEN) {                       // search the next free place
// std::cout << "im inserting: " << key->get_id() << std::endl;
            index = (index + step) % capacity;
        }

        table[index] = key;                                                 // insert the data
        indexStatus[index] = Status::TAKEN;                                 // mark as taken
        size++;                                                             // we added a new key
    }

    void remove(int key) {                                             
        int index = hash1(key);
        int step = hash2(key);

        while (indexStatus[index] != Status::FREE) {                        // search from all that are not free
            if (table[index]->get_id() == key && indexStatus[index] == Status::TAKEN) {   // if the key matches, and the place is taken
                indexStatus[index] = Status::DELETED;                       // update it as deleted
                size--;
                return;
            }
            index = (index + step) % capacity;                              // the next potential place to look for
        }
    }

    bool search(int key) const {   
        int index = hash1(key);
        int step = hash2(key);
        // std::cout << "im searchong" << key << std::endl;
        while (indexStatus[index] != Status::FREE) {                        // search from all that are not free
            if (table[index]->get_id() == key && indexStatus[index] == Status::TAKEN) {   // if the key matches, and the place is taken
                return true;                                                // if found
            }
            index = (index + step) % capacity;
        }
        return false;                                                       // passed throw all potential,didnt found
    }

    T& get(int key){   
        int index = hash1(key);
        int step = hash2(key);

        while (indexStatus[index] != Status::FREE) {                        // search from all that are not free
            if (table[index]->get_id() == key && indexStatus[index] == Status::TAKEN) {   // if the key matches, and the place is taken
                return table[index];                                        // if found
            }
            index = (index + step) % capacity;
        }
        static T defaultT;
        return defaultT;                                                    // passed throw all potential,didnt found
    }

    int get_pirate_amount(int key){
        int index = hash1(key);
        int step = hash2(key);

        while (indexStatus[index] != Status::FREE) {                        // search from all that are not free
            if (table[index]->get_id() == key && indexStatus[index] == Status::TAKEN) {   // if the key matches, and the place is taken
                return table[index]->get_pirate_size();                     // if found
            }
            index = (index + step) % capacity;
        }
        return 0;                                                           // passed throw all potential,didnt found
    }

    int get_fleet_size(int key){
        int index = hash1(key);
        int step = hash2(key);
        while (indexStatus[index] != Status::FREE) {                        // search from all that are not free
            if (table[index]->get_id() == key && indexStatus[index] == Status::TAKEN) {   // if the key matches, and the place is taken
                return table[index]->get_fleet_size();                      // if found
            }
            index = (index + step) % capacity;
        }
        return 0;                                                           // passed throw all potential,didnt found
    }

    int get_pirate_size(int key, int increasment){
        int index = hash1(key);
        int step = hash2(key);
        while (indexStatus[index] != Status::FREE) {                        // search from all that are not free
            if (table[index]->get_id() == key && indexStatus[index] == Status::TAKEN) {   // if the key matches, and the place is taken
                table[index]->increase_pirate_size(increasment);
                return table[index]->get_pirate_size();                     // if found
            }
            index = (index + step) % capacity;
        }
        return 0;                                                           // passed throw all potential,didnt found
    }

    void print() const {
        for (int i = 0; i < capacity; ++i) {
            if (indexStatus[i] == Status::TAKEN) {
                std::cout << "Index " << i << ": " << table[i]->get_id() << " (TAKEN), the fleet size is: " <<  table[i]->get_fleet_size() << ", the pirate amount is: " << table[i]->get_pirate_size() << std::endl;
                // std::cout << "Index " << i << ": " << table[i]->get_id()<< std::endl;           
            } else if (indexStatus[i] == Status::DELETED) {
                std::cout << "Index " << i << ": DELETED" << std::endl;
            } else {
                std::cout << "Index " << i << ": FREE" << std::endl;
            }
        }
    }

};

template <typename T>
unsigned long long HashTable<T>::primes[59] = {
    17, 37, 67, 131, 257, 521, 1031,
    2053, 4099, 8209, 16411, 32771, 65537, 131101, 262147, 524309, 1048583,
    2097169, 4194319, 8388617, 16777259, 33554467, 67108879, 134217757, 268435459, 536870923, 1073741827,
    2147483659, 4294967311, 8589934609, 17179869209, 34359738421, 68719476767, 137438953481, 274877906951, 549755813911, 1099511627791,
    2199023255579, 4398046511119, 8796093022237, 17592186044423, 35184372088891, 70368744177679, 140737488355333, 281474976710677, 
    562949953421381, 1125899906842679, 2251799813685269, 4503599627370517, 9007199254740997, 18014398509482143, 36028797018963971, 
    72057594037928017, 144115188075855881, 288230376151711813, 576460752303423619, 1152921504606847009, 2305843009213693967
};


#endif