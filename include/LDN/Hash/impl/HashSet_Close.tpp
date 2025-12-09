#pragma once

// standard libraries
#include <iostream>
#include <sstream>
#include <memory>

// Exception library
#include <LDN/Exceptions.hpp>

namespace LDN::hash_set {

    // constructor
    template <typename TYPE>
    Close<TYPE>::Close(const size_t& sz, bool probing, TYPE empty, TYPE tombstone) 
        : HashSet<TYPE>(sz), quadratic(probing), EMPTY(empty), TOMBSTONE(tombstone) {
        this->table = std::make_unique<TYPE[]>(sz);
        for (size_t i = 0; i < sz; i++) this->table[i] = this->EMPTY;
    }

    // Method --- Hash Function
    template <typename TYPE>
    [[nodiscard]] const size_t Close<TYPE>::hash(const TYPE& key) const noexcept {
        size_t bucket = std::hash<TYPE>{}(key) % this->size;
        if (this->table[bucket] == this->EMPTY || this->table[bucket] == this->TOMBSTONE) return bucket;
        for(size_t step = 1; step < this->size; step++) {
            size_t index = bucket;
            index += (this->quadratic) ? static_cast<size_t>(0.5 * step * (1 + step)) : step;
            index %= this->size;
            if (this->table[index] == this->EMPTY || this->table[index] == this->TOMBSTONE) return index;
        }
        return static_cast<size_t>(-1);
    }


    /* ========================================== 1. Hash Methods ========================================== */

  
    // Method 1.1 --- Clear the Hash-Set
    template <typename TYPE>
    void Close<TYPE>::clear() noexcept {
        for (size_t i = 0; i < this->size; i++) this->table[i] = this->EMPTY;
        this->elements = 0;
    }

    
    // Method 1.2 --- Check if an element is in the Hash-Set
    template <typename TYPE>
    [[nodiscard]] bool Close<TYPE>::contains(const TYPE& key) const noexcept {
        size_t bucket = std::hash<TYPE>{}(key) % this->size;
        if (this->table[bucket] == key) return true;
        else if (this->table[bucket] == this->EMPTY) return false;
        for (size_t step = 1; step < this->size; step++) {
            size_t index = (bucket + step) % this->size;
            if (this->table[index] == key) return true;
        }
        return false;
    }


    // Method 1.3 --- Convert the Hash-Set to a String
    template <typename TYPE>
    [[nodiscard]] std::string Close<TYPE>::toString() const noexcept {
        std::ostringstream out_stream;
        for (size_t i = 0; i < this->size; ++i) {
            out_stream << "Bucket " << i << ":";
            if (this->table[i] == this->EMPTY) out_stream << "//";
            else if (this->table[i] == this->TOMBSTONE) out_stream << "XX";
            else out_stream << this->table[i];
            out_stream << "\n";
        }
        return out_stream.str();
    }



    /* ========================================= 2. HashSet Methods ======================================== */


    // Method 2.1 --- Insert a key in the Hash-Set
    template <typename TYPE>
    void Close<TYPE>::insert(const TYPE& key) {
        if (this->contains(key)) [[unlikely]] return;
        size_t bucket = this->hash(key);
        if (bucket == static_cast<size_t>(-1)) [[unlikely]] throw LDN::exceptions::Size("No avaiable Bucket has been found in the Hash-Set!!!");
        else [[likely]] {
            this->table[bucket] = key;
            this->elements++; 
        }
    }
    

    // Method 2.2 --- Remove a key from the Hash-Set
    template <typename TYPE>
    void Close<TYPE>::remove(const TYPE& key) noexcept {
        size_t bucket = std::hash<TYPE>{}(key) % this->size;
        for (size_t step = 0; step < this->size; step++) {
            size_t index = bucket;
            index += (this->quadratic) ? static_cast<size_t>(0.5 * step * (1 + step)) : step;
            index %= this->size;
            if (this->table[index] == key) {
                this->table[index] = this->TOMBSTONE;
                this->elements--;
                break;
            }
        }
    }


    // Method 2.3 --- Resize the Hash-Set
    template <typename TYPE>
    void Close<TYPE>::resize() noexcept {
        size_t new_size = this->size << 1;
        std::unique_ptr<TYPE[]> new_table = std::make_unique<TYPE[]>(new_size);
        for (size_t i = 0; i < new_size; i++) new_table[i] = this->EMPTY;
        for (auto element : *this) {
            size_t bucket = std::hash<TYPE>{}(element) % new_size;
            if (new_table[bucket] == this->EMPTY) new_table[bucket] = element;
            else {
                for (size_t step = 1; step < new_size; step++) {
                    size_t index = bucket;
                    index += (this->quadratic) ? static_cast<size_t>(0.5 * step * (1 + step)) : step;
                    index %= new_size;
                    if (new_table[index] == this->EMPTY) new_table[index] = element;
                }
            }
        }
        this->size = new_size;
        this->table = std::move(new_table);
    }

} // namespace LDN::hash_set