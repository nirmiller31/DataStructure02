#include <iostream>
#include <string>
#include <stdexcept>

template <typename T>
class UnionFind {
private:
    T* m_parent;
    int m_total;
    int* m_size;
    T* m_data;
    int capacity;

    void resize() {
        int new_capacity = capacity * 2;
        T* new_parent = new T[new_capacity];
        int* new_rank = new int[new_capacity];
        T* new_data = new T[new_capacity];

        for (int i = 0; i < capacity; ++i) {
            new_parent[i] = m_parent[i];
            new_rank[i] = m_size[i];
            new_data[i] = m_data[i];
        }

        delete[] m_parent;
        delete[] m_size;
        delete[] m_data;

        m_parent = new_parent;
        m_size = new_rank;
        m_data = new_data;
        capacity = new_capacity;
    }

public:

    UnionFind(int initial_capacity = 2) : m_total(0), capacity(initial_capacity) {
        m_parent = new T[capacity];
        m_size = new int[capacity];
        m_data = new T[capacity];
    }

    ~UnionFind() {
        delete[] m_parent;
        delete[] m_size;
        delete[] m_data;
    }

    void make_set(T object) {
        while (object->get_id() >= capacity) {
            resize();
        }
        m_parent[object->get_id()] = nullptr;
        m_size[object->get_id()] = 1;
        m_data[object->get_id()] = object;

        if (object->get_id() >= m_total) {
            m_total = object->get_id() + 1;
        }
    }

    T find(int id) {
        T root = find_root(id);
        if(root == m_data[id]){
            return root;
        }
        else{
            while (m_parent[id] != nullptr) {
                m_parent[id] = root;
                return find(m_parent[id]->get_id());
            }
        }
        return root;
    }

    T find_root(int id) {
        T root = m_data[id];
        while (m_parent[id] != nullptr) {
            return find(m_parent[id]->get_id());
        }
        return root;
    }

    void union_sets(T first, T second) {

        if (first->get_id() != second->get_id()) {
            if (m_size[first->get_id()] < m_size[second->get_id()]) {
                m_parent[first->get_id()] = second;
                m_size [second->get_id()] += m_size[first->get_id()];
            } else if (m_size[first->get_id()] > m_size[second->get_id()]) {
                m_parent[second->get_id()] = first;
                m_size [first->get_id()] += m_size[second->get_id()];
            } else {
                m_parent[second->get_id()] = first;
                m_size [first->get_id()] += m_size[second->get_id()];
            }
        }
    }

    T get_data(int i) {
        return m_data[find(i)];
    }

    int get_size() {
        return m_total;
    }

    int get_capacity() {
        return capacity;
    }

    void print_set(int root_id) {
        std::cout << "Elements in the set with root " << root_id << ": ";
        for (int i = 0; i < m_total; ++i) {
            if (find(i) == root_id) {
                std::cout << m_data[i] << " ";
            }
        }
        std::cout << std::endl;
    }

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

void print_rank() {
    std::cout << "Elements in the rank:   ";
    for (int i = 0; i < m_total; ++i) {
        std::cout << m_size[i] << " ";                
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

void print() {
    print_data();
    print_parent();
    print_rank();
}



    
};


