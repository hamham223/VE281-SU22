#include "hash_prime.hpp"

#include <exception>
#include <functional>
#include <vector>
#include <forward_list>
#include <stdexcept>

/**
 * The Hashtable class
 * The time complexity of functions are based on n and k
 * n is the size of the hashtable
 * k is the length of Key
 * @tparam Key          key type
 * @tparam Value        data type
 * @tparam Hash         function object, return the hash value of a key
 * @tparam KeyEqual     function object, return whether two keys are the same
 */
template<
        typename Key, typename Value,
        typename Hash = std::hash<Key>,
        typename KeyEqual = std::equal_to<Key>
>
class HashTable {
public:
    typedef std::pair<const Key, Value> HashNode;
    typedef std::forward_list<HashNode> HashNodeList;
    typedef std::vector<HashNodeList> HashTableData;

    /**
     * A single directional iterator for the hashtable
     * ! DO NOT NEED TO MODIFY THIS !
     */
    class Iterator {
    private:
        typedef typename HashTableData::iterator VectorIterator;
        typedef typename HashNodeList::iterator ListIterator;

        const HashTable *hashTable;
        VectorIterator bucketIt;    // an iterator of the buckets
        ListIterator listItBefore;  // a before iterator of the list, here we use "before" for quick erase and insert
        bool endFlag = false;       // whether it is an end iterator

        /**
         * Increment the iterator
         * Time complexity: Amortized O(1)
         */
        void increment() {
            if (bucketIt == hashTable->buckets.end()) {
                endFlag = true;
                return;
            }
            auto newListItBefore = listItBefore;
            ++newListItBefore;
            if (newListItBefore != bucketIt->end()) {
                if (++newListItBefore != bucketIt->end()) {
                    // use the next element in the current forward_list
                    ++listItBefore;
                    return;
                }
            }
            while (++bucketIt != hashTable->buckets.end()) {
                if (!bucketIt->empty()) {
                    // use the first element in a new forward_list
                    listItBefore = bucketIt->before_begin();
                    return;
                }
            }
            endFlag = true;
        }

        explicit Iterator(HashTable *hashTable) : hashTable(hashTable) {
            bucketIt = hashTable->buckets.begin();
            listItBefore = bucketIt->before_begin();
            endFlag = bucketIt == hashTable->buckets.end();
        }

        Iterator(HashTable *hashTable, VectorIterator vectorIt, ListIterator listItBefore) :
                hashTable(hashTable), bucketIt(vectorIt), listItBefore(listItBefore) {
            endFlag = bucketIt == hashTable->buckets.end();
        }

    public:
        friend class HashTable;

        Iterator() = delete;

        Iterator(const Iterator &) = default;

        Iterator &operator=(const Iterator &) = default;

        Iterator &operator++() {
            increment();
            return *this;
        }

        Iterator operator++(int) {
            Iterator temp = *this;
            increment();
            return temp;
        }

        bool operator==(const Iterator &that) const {
            if (endFlag && that.endFlag) return true;
            if (bucketIt != that.bucketIt) return false;
            return listItBefore == that.listItBefore;
        }

        bool operator!=(const Iterator &that) const {
            if (endFlag && that.endFlag) return false;
            if (bucketIt != that.bucketIt) return true;
            return listItBefore != that.listItBefore;
        }

        HashNode *operator->() {
            auto listIt = listItBefore;
            ++listIt;
            return &(*listIt);
        }

        HashNode &operator*() {
            auto listIt = listItBefore;
            ++listIt;
            return *listIt;
        }
    };

protected:                                                                  // DO NOT USE private HERE!
    static constexpr double DEFAULT_LOAD_FACTOR = 0.5;                      // default maximum load factor is 0.5
    static constexpr size_t DEFAULT_BUCKET_SIZE = HashPrime::g_a_sizes[0];  // default number of buckets is 5

    HashTableData buckets;                                                  // buckets, of singly linked lists
    typename HashTableData::iterator firstBucketIt;                         // help get begin iterator in O(1) time

    size_t tableSize;                                                       // number of elements
    double maxLoadFactor;                                                   // maximum load factor
    Hash hash;                                                              // hash function instance
    KeyEqual keyEqual;                                                      // key equal function instance

    /**
     * Time Complexity: O(k)
     * @param key
     * @param bucketSize
     * @return the hash value of key with a new bucket size
     */
    inline size_t hashKey(const Key &key, size_t bucketSize) const {
        return hash(key) % bucketSize;
    }

    /**
     * Time Complexity: O(k)
     * @param key
     * @return the hash value of key with current bucket size
     */
    inline size_t hashKey(const Key &key) const {
        return hash(key) % buckets.size();
    }

    /**
     * Find the minimum bucket size for the hashtable
     * The minimum bucket size must satisfy all of the following requirements:
     * - It is not less than (i.e. greater or equal to) the parameter bucketSize
     * - It is greater than floor(tableSize / maxLoadFactor)
     * - It is a (prime) number defined in HashPrime (hash_prime.hpp)
     * - It is minimum if satisfying all other requirements
     * Time Complexity: O(1)
     * @throw std::range_error if no such bucket size can be found
     * @param bucketSize lower bound of the new number of buckets
     */
    size_t findMinimumBucketSize(size_t bucketSize) const {
        // TODO: implement this function
        auto it = std::lower_bound(HashPrime::g_a_sizes,
                                   HashPrime::g_a_sizes+HashPrime::num_distinct_sizes-1,
                                   large_enough(bucketSize));
        if (it == HashPrime::g_a_sizes + HashPrime::num_distinct_sizes)
            throw std::range_error("To large! No such bucket size can be found!");
        return *it;
    }

     size_t large_enough(size_t bucketSize) const{
        /**
         * @return maximum of 
         * @param bucketSize and floor(tableSize / maxLoadFactor)
         * 
         */
        size_t tmp = size_t((double)size() / getMaxLoadFactor()) + 1;
        return tmp > bucketSize ? tmp : bucketSize;
    }
    // TODO: define your helper functions here if necessary


public:
    HashTable() :
            buckets(DEFAULT_BUCKET_SIZE), tableSize(0), maxLoadFactor(DEFAULT_LOAD_FACTOR),
            hash(Hash()), keyEqual(KeyEqual()) {
        firstBucketIt = buckets.end();
    }

    explicit HashTable(size_t bucketSize) :
            tableSize(0), maxLoadFactor(DEFAULT_LOAD_FACTOR),
            hash(Hash()), keyEqual(KeyEqual()) {
        bucketSize = findMinimumBucketSize(bucketSize);
        buckets.resize(bucketSize);
        firstBucketIt = buckets.end();
    }

    HashTable(const HashTable &that) {
        if (this != &that) *this = that;
        // TODO: implement this function
    }

    HashTable &operator=(const HashTable &that) {
        if (this != &that) {
            this->buckets = that.buckets;
            auto newfirstBucketIt = (this->buckets).begin();
            while (newfirstBucketIt->begin() == newfirstBucketIt->end()) newfirstBucketIt++;
            this->firstBucketIt = newfirstBucketIt;
            this->tableSize = that.tableSize;
            this->maxLoadFactor = that.maxLoadFactor;
            this->hash = that.hash;
            this->keyEqual = that.keyEqual;
        }
        return *this;
        // TODO: implement this function
    };

    ~HashTable() = default;

    Iterator begin() {
        if (firstBucketIt != buckets.end()) {
            return Iterator(this, firstBucketIt, firstBucketIt->before_begin());
        }
        return end();
    }

    Iterator end() {
        return Iterator(this, buckets.end(), buckets.begin()->before_begin());
    }

    /**
     * Find whether the key exists in the hashtable
     * Time Complexity: Amortized O(k)
     * @param key
     * @return whether the key exists in the hashtable
     */
    bool contains(const Key &key) {
        return find(key) != end();
    }

    /**
     * Find the value in hashtable by key
     * If the key exists, iterator points to the corresponding value, and it.endFlag = false
     * Otherwise, iterator points to the place that the key were to be inserted, and it.endFlag = true
     * Time Complexity: Amortized O(k)
     * @param key
     * @return a pair (success, iterator of the value)
     */
    Iterator find(const Key &key){
        Iterator result(this);
        result.bucketIt =   buckets.begin() + hashKey(key);
        result.endFlag = true;
        result.listItBefore = (result.bucketIt)->before_begin() ;
        if ((result.bucketIt)->begin() == (result.bucketIt)->end() ) return result;
        auto newlistItBefore = std::next(result.listItBefore);
        while ( newlistItBefore != (result.bucketIt)->end() ){
            if ( keyEqual((newlistItBefore)->first , key)) {
                result.endFlag = false; 
                break;
            }
            result.listItBefore = std::next(result.listItBefore);
            newlistItBefore = std::next(newlistItBefore);
        }
        return result;
        // TODO: implement this function
    }

    /**
     * Insert value into the hashtable according to an iterator returned by find
     * the function can be only be called if no other write actions are done to the hashtable after the find
     * If the key already exists, overwrite its value
     * firstBucketIt should be updated
     * If load factor exceeds maximum value, rehash the hashtable
     * Time Complexity: O(k)
     * @param it an iterator returned by find
     * @param key
     * @param value
     * @return whether insertion took place (return false if the key already exists)
     */
    bool insert(const Iterator &it, const Key &key, const Value &value) {
        //key already exists
        if (!it.endFlag) {
            (it.bucketIt)->erase_after(it.listItBefore);
            (it.bucketIt)->insert_after(it.listItBefore,std::pair<Key,Value>(key,value));
            return false;
        }
        // key does not exist, insertion happens
        else {
            if (it.bucketIt < firstBucketIt) firstBucketIt = it.bucketIt; // update firstBucket
            *(it.bucketIt)->insert_after(it.listItBefore,std::pair<Key,Value>(key,value)); // do insertion
            (this->tableSize) ++ ;
            if (loadFactor() > getMaxLoadFactor()) // load factor is too large, rehash
                rehash(bucketSize());
            return true;
        }
        return true;
        // TODO: implement this function
    }

    /**
     * Insert <key, value> into the hashtable
     * If the key already exists, overwrite its value
     * firstBucketIt should be updated
     * If load factor exceeds maximum value, rehash the hashtable
     * Time Complexity: Amortized O(k)
     * @param key
     * @param value
     * @return whether insertion took place (return false if the key already exists)
     */
    bool insert(const Key &key, const Value &value) {
        return insert(find(key),key,value);
        // TODO: implement this function
    }

    /**
     * Erase the key if it exists in the hashtable, otherwise, do nothing
     * DO NOT rehash in this function
     * firstBucketIt should be updated
     * Time Complexity: Amortized O(k)
     * @param key
     * @return whether the key exists
     */
    bool erase(const Key &key) {
        Iterator to_be_del = find(key);
        if (to_be_del.endFlag) return false;
        erase(to_be_del);
        return true;
        // TODO: implement this function
    }

    /**
     * Erase the key at the input iterator
     * If the input iterator is the end iterator, do nothing and return the input iterator directly
     * firstBucketIt should be updated
     * Time Complexity: O(1)
     * @param it
     * @return the iterator after the input iterator before the erase
     */
    Iterator erase(const Iterator &it) {
        if (it == end()) return it;
        // otherwise, the input iterator is not the end iterator, do deletion
        if (++ (it.bucketIt)->begin() == (it.bucketIt)->end()){ // the bucket has only one element
            if (it.bucketIt == firstBucketIt) {
                firstBucketIt = buckets.end();
                for (auto _it = buckets.begin(); _it!=buckets.end(); _it++){
                    if ((_it)->begin()!=(_it)->end()) {
                        firstBucketIt = _it;break;
                    }
                }
            }
            (it.bucketIt)->erase_after((it.bucketIt)->before_begin());
        }
        else   (it.bucketIt)->erase_after(it.listItBefore);
        tableSize--;
        return it;
        // TODO: implement this function
    }

    /**
     * Get the reference of value by key in the hashtable
     * If the key doesn't exist, create it first (use default constructor of Value)
     * firstBucketIt should be updated
     * If load factor exceeds maximum value, rehash the hashtable
     * Time Complexity: Amortized O(k)
     * @param key
     * @return reference of value
     */
    Value &operator[](const Key &key) {
        Iterator to_visit = find(key);
        if (!to_visit.endFlag) return to_visit->second;
        Value default_value = 0;
        insert(to_visit,key,default_value); // firstBucketIt updates, rehash within this call
        return this->operator[](key);
        // TODO: implement this function
    }

    /**
     * Rehash the hashtable according to the (hinted) number of buckets
     * The bucket size after rehash need not be same as the parameter bucketSize
     * Instead, findMinimumBucketSize is called to get the correct number
     * firstBucketIt should be updated
     * Do nothing if the bucketSize doesn't change
     * Time Complexity: O(nk)
     * @param bucketSize lower bound of the new number of buckets
     */
    void rehash(size_t bucketSize) {
        bucketSize = findMinimumBucketSize(bucketSize);
        if (bucketSize == buckets.size()) return;
        (this->buckets).resize(bucketSize);
        auto new_hash_it = (this->buckets).begin();
        std::pair<Key,Value> content = std::pair<Key,Value>(0,0);
        auto _bucket_it = (this->buckets).begin();
        auto _list_it = _bucket_it->begin();
        for ( ; _bucket_it != (this->buckets).end();_bucket_it ++){
            _list_it = _bucket_it->before_begin();
            while (std::next(_list_it) != _bucket_it->end()){
                new_hash_it = (this->buckets).begin() + hashKey(std::next(_list_it)->first,bucketSize);
                if (new_hash_it == _bucket_it) { ++ _list_it; continue;} //no need to modify
                // otherwise, this element need to be erased and re-inserted
                content = *(std::next(_list_it));
                _bucket_it->erase_after(_list_it);
                new_hash_it->push_front(content);
            }
        }
        auto newfirstBucketIt = (this->buckets).begin();
        while (newfirstBucketIt->begin() == newfirstBucketIt->end()) newfirstBucketIt++;
        this->firstBucketIt = newfirstBucketIt;
        // TODO: implement this function
    }

    /**
     * @return the number of elements in the hashtable
     */
    size_t size() const { return tableSize; }

    /**
     * @return the number of buckets in the hashtable
     */
    size_t bucketSize() const { return buckets.size(); }

    /**
     * @return the current load factor of the hashtable
     */
    double loadFactor() const { return (double) tableSize / (double) buckets.size(); }

    /**
     * @return the maximum load factor of the hashtable
     */
    double getMaxLoadFactor() const { return maxLoadFactor; }

    /**
     * Set the max load factor
     * @throw std::range_error if the load factor is too small
     * @param loadFactor
     */
    void setMaxLoadFactor(double loadFactor) {
        if (loadFactor <= 1e-9) {
            throw std::range_error("invalid load factor!");
        }
        maxLoadFactor = loadFactor;
        rehash(buckets.size());
    }

};

