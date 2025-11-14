// header guard
#pragma once
#define LDN__IF_HASH_HPP

// standard library
#include <iostream>
#include <memory>

/* ---------------------------------------------------------------------------------------------------------------------------------
 *                                                                                                                      
 *                                              LDN --- IF_Hash.hpp                                                       
 *                                                                                                                      
 * ---------------------------------------------------------------------------------------------------------------------------------
*/      

namespace LDN {

    // ------------------------------------------ 1. Interface Hash ------------------------------------------

    // Abstract Class Hash
    template <typename TYPE>
    class Hash {
        
        protected:

            // attributes
            size_t size;
            size_t elements;

            // Method --- Hash Function
            virtual const size_t hash(const TYPE& key) const noexcept = 0;

        public:

            // constructor / destructor
            explicit Hash(const size_t& sz) : size(sz), elements(0) {}
            virtual ~Hash() noexcept = default;

            // getters
            inline const size_t& getSize() const noexcept { return this->size; }
            inline const size_t& getElements() const noexcept { return this->elements; }

            // Methods --- clear / contains / toString
            virtual void clear() noexcept = 0;
            virtual bool contains(const TYPE& key) const noexcept = 0;
            virtual std::string toString() const noexcept = 0;
    };

    // output stream operator <<
    template <typename TYPE>
    inline std::ostream& operator<<(std::ostream& out_stream, const LDN::Hash<TYPE>& hash) {
        out_stream << hash.toString();
        return out_stream;
    }
/*

    // ------------------------------------------ 2. Abstract Class HashSet ------------------------------------------

    // Abstract Class HashSet
    template <typename TYPE>
    class HashSet : public Hash<TYPE> {


    };


    // ------------------------------------------ 3. Abstract Class HashMap ------------------------------------------

    // Abstract Class HashMap
    template <typename KEY, typename TYPE>
    class HashMap : public Hash<KEY> {

    };
*/
} // namespace LDN