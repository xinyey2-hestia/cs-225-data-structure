#include "dhhashtable.h"

using hashes::hash;
using hashes::hash2;
using std::pair;

/**
 * Inserts the given key, value pair into the HashTable.
 *
 * @param key The key to be inserted.
 * @param value The value to be inserted.
 */
template <class K, class V>
void DHHashTable<K, V>::insert(K const& key, V const& value) {
    // TODO: Implement this function
    elems += 1;

    if (shouldResize()){
      resizeTable();
    }
    int probeDistance = hash2(key);
    size_t i = hash(key,size);
    while (table[i]!=NULL){
      i = (i +probeDistance)%size;
    }

    table[i] = new pair<K,V>(key,value);
    should_probe[i]= true;
}

/**
 * Removes the given key (and its associated data) from the
 * HashTable.
 *
 * @param key The key to be removed.
 */
template <class K, class V>
void DHHashTable<K, V>::remove(K const& key) {
    // TODO: Implement this function
    int index = findIndex(key);
    if (index!=-1){
      delete table[index];
      table[index]=NULL;
      elems--;
    }
}

/****************************************************
 * Provided code; you should not need to modify this.
 ****************************************************/
template <class K, class V>
DHHashTable<K, V>::DHHashTable(size_t tsize) {
    if (tsize <= 0) {
        tsize = 17;
    }
    size = findPrime(tsize);
    table = new pair<K, V>*[size];
    should_probe = new bool[size];
    for (size_t i = 0; i < size; i++) {
        table[i] = NULL;
        should_probe[i] = false;
    }
    elems = 0;
}

template <class K, class V>
DHHashTable<K, V>::~DHHashTable() {
    clear_();
}

template <class K, class V>
DHHashTable<K, V> const& DHHashTable<K, V>::operator=(DHHashTable const& rhs) {
    if (this != &rhs) {
        clear_();
        copy_(rhs);
    }
    return *this;
}

template <class K, class V>
DHHashTable<K, V>::DHHashTable(DHHashTable<K, V> const& other){
    copy_(other);
}


template <class K, class V>
int DHHashTable<K, V>::findIndex(const K& key) const
{
    int idx = hash(key, size);
    int probeDistance = hash2(key);
    int start = idx;
    while (should_probe[idx]) {
        if (table[idx] != NULL && table[idx]->first == key) {
            return idx;
        }
        idx = (idx + probeDistance) % size;
        // if we've looped all the way around, the key has not been found
        if (idx == start) {
            break;
        }
    }
    return -1;
}

template <class K, class V>
V DHHashTable<K, V>::find(K const& key) const {
    int idx = findIndex(key);
    if (idx != -1) {
        return table[idx]->second;
    }
    return V();
}

template <class K, class V>
V& DHHashTable<K, V>::operator[](K const& key) {
    // First, attempt to find the key and return its value by reference
    int idx = findIndex(key);
    if (idx == -1) {
        // otherwise, insert the default value and return it
        insert(key, V());
        idx = findIndex(key);
    }
    return table[idx]->second;
}

template <class K, class V>
bool DHHashTable<K, V>::keyExists(K const& key) const
{
    return findIndex(key) != -1;
}

template <class K, class V>
void DHHashTable<K, V>::clear() {
    for (size_t i = 0; i < size; i++) {
        delete table[i];
    }
    delete[] table;
    delete[] should_probe;
    table = new pair<K, V>*[17];
    should_probe = new bool[17];
    for (size_t i = 0; i < 17; i++)
        should_probe[i] = false;
    size = 17;
    elems = 0;
}

template <class K, class V>
void DHHashTable<K, V>::resizeTable() {
    size_t newSize = findPrime(size * 2);
    pair<K, V>** temp = new pair<K, V>*[newSize];
    delete[] should_probe;
    should_probe = new bool[newSize];
    for (size_t i = 0; i < newSize; i++) {
        temp[i] = NULL;
        should_probe[i] = false;
    }

    for (size_t i = 0; i < size; i++) {
        if (table[i] != NULL) {
            int idx = hash(table[i]->first, newSize);
            int probeDistance = hash2(table[i]->first);
            while (temp[idx] != NULL) {
                idx = (idx + probeDistance) % newSize;
            }
            temp[idx] = table[i];
            should_probe[idx] = true;
        }
    }

    delete[] table;
    // don't delete elements since we just moved their pointers around
    table = temp;
    size = newSize;
}

template <class K, class V>
void DHHashTable<K, V>::clear_() {
    for (size_t i = 0; i < size; i++) {
        delete table[i];
    }
    delete[] table;
    delete[] should_probe;
}

template <class K, class V>
void DHHashTable<K, V>::copy_(const DHHashTable<K, V> &other) {
    table = new pair<K, V>*[other.size];
    should_probe = new bool[other.size];
    for (size_t i = 0; i < other.size; i++) {
        should_probe[i] = other.should_probe[i];
        if (other.table[i] == NULL)
            table[i] = NULL;
        else
            table[i] = new pair<K, V>(*(other.table[i]));
    }
    size = other.size;
    elems = other.elems;
}
