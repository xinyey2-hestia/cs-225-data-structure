#ifndef _DHHASHTABLE_H_
#define _DHHASHTABLE_H_

#include "hashes.h"
#include <algorithm>
#include <stddef.h>
#include <utility>

template <class K, class V>
class DHHashTable {
public:
    /**
     * Constructs a DHHashTable of the given size.
     *
     * @param tsize The desired number of starting cells in the
     *  DHHashTable.
     */
    DHHashTable(size_t tsize);

    /**
     * Destructor for the DHHashTable. We use dynamic memory, and thus
     * require the big three.
     */
    virtual ~DHHashTable();

    /**
     * Assignment operator.
     *
     * @param rhs The DHHashTable we want to assign into the current
     *  one.
     * @return A const reference to the current DHHashTable.
     */
    const DHHashTable<K, V>& operator=(const DHHashTable<K, V>& rhs);

    /**
     * Copy constructor.
     *
     * @param other The DHHashTable to be copied.
     */
    DHHashTable(const DHHashTable<K, V>& other);

    /**
     * Inserts the given key, value pair into the HashTable.
     *
     * @param key The key to be inserted.
     * @param value The value to be inserted.
     */
    void insert(const K& key, const V& value);

    /**
     * Removes the given key (and its associated data) from the
     * HashTable.
     *
     * @param key The key to be removed.
     */
    void remove(const K& key);

    /**
     * Finds the value associated with a given key.
     *
     * @param key The key whose data we want to find.
     * @return The value associated with this key, or the default value
     *    (V()) if it was not found.
     */
    V find(const K& key) const;

    /**
     * Determines if the given key exists in the HashTable.
     *
     * @param key The key we want to find.
     * @return A boolean value indicating whether the key was found in
     *    the HashTable.
     */
    bool keyExists(const K& key) const;

    /**
     * Empties the HashTable (that is, all keys and values are
     * removed).
     */
    void clear();

    /**
     * Determines if the HashTable is empty. O(1).
     *
     * @note This depends on elems being set properly in derived
     *  classes.
     *
     * @return A boolean value indicating whether the HashTable is
     *  empty.
     */
    bool isEmpty() const { return elems == 0; }

    /**
     * Access operator: Returns a reference to a value in the
     * HashTable, so that it may be modified. If the key you are
     * searching for is not found in the table, this method inserts it
     * with the default value V() (which you then may modify).
     *
     * Examples:
     *
     *     hashtable["mykey"]; // returns the value for "mykey", or the
     *                         // default value if "mykey" is not in
     *                         // the table
     *
     *     hashtable["myOtherKey"] = "myNewValue";
     *
     * @param key The key to be found in the HashTable.
     * @return A reference to the value for this key contained in the
     *    table.
     */
    V& operator[](const K& key);

    /**
     * Used to determine the total size of the HashTable. Used for
     * grading purposes.
     *
     * @return The size of the HashTable (that is, the total number of
     *  available cells, not the number of elements the table
     *  contains).
     */
    size_t tableSize() const { return size; }

    /**
     * Allows access to the underlying array of elements. Used for grading
     * purposes.
     *
     * @return The array of std::pair<K, V>* that stores all elements.
     */
    std::pair<K, V>** getTable() const { return table; }

private:
    /**
     * The current number of elements stored in the HashTable.
     */
    size_t elems;
    /**
     * The current size of the HashTable (total cells).
     */
    size_t size;

    /**
     * Storage for our DHHashTable.
     *
     * Because we're probing, we only need the array, not buckets for each
     * array index. Note that we use an array of pointers to pairs in this
     * case since the check for an "empty" slot is simply a check against
     * NULL in that cell.
     */
    std::pair<K, V>** table;

    /**
     * Flags for whether or not to probe forward when looking at a
     * particular cell in the table.
     *
     * This is a dynamic array of booleans that represents if a slot is
     * (or previously was) occupied. This allows us determine whether
     * or not we need to probe forward to look for our key.
     */
    bool* should_probe;

    /**
     * Private helper function to resize the HashTable. This should be
     * called when the load factor is >= 0.7 (this is somewhat
     * arbitrary, but used for grading).
     */
    void resizeTable();

    /**
     * Determines if the HashTable should resize.
     * @return Whether the HashTable should resize.
     */
    inline bool shouldResize() const {
        return static_cast<double>(elems) / size >= 0.7;
    }

    /**
     * List of primes for resizing.
     */
    static const size_t primes[];

    /**
     * Finds the closest prime in our list to the given number.
     *
     * @param num The number to find the closest prime to in our list.
     * @return The closest prime we have to num in our list of primes.
     */
    size_t findPrime(size_t num);

    /**
     * Helper function to determine the index where a given key lies in
     * the DHHashTable. If the key does not exist in the table, it will
     * return -1.
     *
     * @param key The key to look for.
     * @return The index of this key, or -1 if it was not found.
     */
    int findIndex(const K& key) const;

    /**
     * Helper functions for the Big Three.
     */
    void copy_(const DHHashTable<K, V> &other);
    void clear_();
};

/**
 * List of primes for resizing. "borrowed" from boost::unordered.
 */
template <class K, class V>
const size_t DHHashTable<K, V>::primes[]
    = {17ul,         29ul,         37ul,        53ul,        67ul,
       79ul,         97ul,         131ul,       193ul,       257ul,
       389ul,        521ul,        769ul,       1031ul,      1543ul,
       2053ul,       3079ul,       6151ul,      12289ul,     24593ul,
       49157ul,      98317ul,      196613ul,    393241ul,    786433ul,
       1572869ul,    3145739ul,    6291469ul,   12582917ul,  25165843ul,
       50331653ul,   100663319ul,  201326611ul, 402653189ul, 805306457ul,
       1610612741ul, 3221225473ul, 4294967291ul};

template <class K, class V>
size_t DHHashTable<K, V>::findPrime(size_t num)
{
    size_t len = sizeof(primes) / sizeof(size_t);
    const size_t* first = primes;
    const size_t* last = primes + len;
    const size_t* prime = std::upper_bound(first, last, num);
    if (prime == last)
        --prime;
    return *prime;
}

#include "dhhashtable.cpp"
#endif
