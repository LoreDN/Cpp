#pragma once

// standard libraries
#include <iostream>
#include <sstream>


namespace LDN::hash_set {

    // constructor
    template <typename TYPE>
    Open<TYPE>::Open(const size_t& sz) : HashSet<TYPE>(sz) {
        this->table = std::make_unique<Bucket*[]>(sz);
        for (size_t i = 0; i < sz; i++) {
            this->table[i] = nullptr;
        }
    }

    // destructor
    template <typename TYPE>
    Open<TYPE>::~Open() noexcept {
        this->clear();
    }

    // Method --- Hash Function
    template <typename TYPE>
    [[nodiscard]] const size_t Open<TYPE>::hash(const TYPE& key) const noexcept {
        return std::hash<TYPE>{}(key) % this->size;
    }


    /* ========================================== 1. Hash Methods ========================================== */

  
    // Method 1.1 --- Clear the Hash-Set
    template <typename TYPE>
    void Open<TYPE>::clear() noexcept {
        for (size_t i = 0; i < this->size; i++) {
            Bucket* bucket = this->table[i];
            while (bucket) {
                Bucket* temp = bucket;
                bucket = bucket->next;
                delete temp;
            }
            this->table[i] = nullptr;
        }
        this->elements = 0;
    }

    
    // Method 1.2 --- Check if an element is in the Hash-Set
    template <typename TYPE>
    [[nodiscard]] bool Open<TYPE>::contains(const TYPE& key) const noexcept {
        size_t index = this->hash(key);
        Bucket* bucket = this->table[index];
        for (; bucket && bucket->value != key; bucket = bucket->next);
        return bucket != nullptr;
    }


    // Method 1.3 --- Convert the Hash-Set to a String
    template <typename TYPE>
    [[nodiscard]] std::string Open<TYPE>::toString() const noexcept {
        std::ostringstream out_stream;
        for (size_t i = 0; i < this->size; ++i) {
            out_stream << "Bucket " << i << ":";
            Bucket* bucket = this->table[i];
            for (; bucket; bucket = bucket->next) {
                out_stream << '\t' << bucket->value;
            }
            out_stream << " //\n";
        }
        return out_stream.str();
    }



    /* ========================================= 2. HashSet Methods ======================================== */


    // Method 2.1 --- Insert a key in the Hash-Set
    template <typename TYPE>
    void Open<TYPE>::insert(const TYPE& key) {
        if (this->contains(key)) [[unlikely]] return;
        size_t index = this->hash(key);
        Bucket* bucket = this->table[index];
        if (bucket) {
            for (; bucket->next; bucket = bucket->next); 
            bucket->next = new Bucket(key);
        } else {
            this->table[index] = new Bucket(key);
        }
        this->elements++;
    }
    

    // Method 2.2 --- Remove a key from the Hash-Set
    template <typename TYPE>
    void Open<TYPE>::remove(const TYPE& key) noexcept {
        size_t index = this->hash(key);
        Bucket* bucket = this->table[index];

        // find the element
        if (!bucket) {
            return;
        } else if (bucket->value == key) {
            this->table[index] = bucket->next;
            delete bucket;
            this->elements--;
        } else {
            for (; bucket->next && bucket->next->value != key; bucket = bucket->next);
            if (bucket->next) {
                Bucket* temp = bucket->next;
                bucket->next = temp->next;
                delete temp;
                this->elements--;
            }
        }
    }


    // Method 2.3 --- Resize the Hash-Set
    template <typename TYPE>
    void Open<TYPE>::resize() noexcept {
        size_t new_size = this->size << 1;
        std::unique_ptr<Bucket*[]> new_table = std::make_unique<Bucket*[]>(new_size);
        for (auto element : *this) {
            size_t index = std::hash<TYPE>{}(element) % new_size;
            if (new_table[index]) {
                Bucket* bucket = new_table[index];
                for (; bucket->next; bucket = bucket->next);
                bucket->next = new Bucket(element);
            } else {
                new_table[index] = new Bucket(element);
            }
        }
        this->size = new_size;
        this->table = std::move(new_table);
    }

} // namespace LDN::hash_set