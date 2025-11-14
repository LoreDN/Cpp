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


    // ------------------------------------------ 2. Abstract Class HashSet ------------------------------------------

    // Abstract Class HashSet
    template <typename TYPE>
    class HashSet : public Hash<TYPE> {

        public:

            // constructor / destructor
            explicit HashSet(const size_t& sz) : Hash<TYPE>(sz) {}
            virtual ~HashSet() noexcept = default;

            // Methods --- insert / remove / resize /loadFactor
            virtual void insert(const TYPE& key) = 0;
            virtual void remove(const TYPE& key) noexcept = 0;
            virtual void resize() noexcept = 0;
            inline const double loadFactor() const {
                return static_cast<double>(this->elements) / static_cast<double>(this->size);
            }


            // ------------------------- Iterator Interface -------------------------

            // Abstract Struct AbstractIterator
            struct AbstractIterator {
                virtual ~AbstractIterator() = default;
                virtual TYPE& deref() const = 0;
                virtual void increment() = 0;
                virtual bool equals(const AbstractIterator* other) const = 0;
                virtual std::unique_ptr<AbstractIterator> clone() const = 0;
            };

            // Wrapper Class Iterator
            class Iterator {
                private:
                
                    // attribute
                    std::unique_ptr<AbstractIterator> iterator_pointer;
                
                public:
                    
                    // constructor
                    explicit Iterator(std::unique_ptr<AbstractIterator> p) : iterator_pointer(std::move(p)) {}

                    // operators *Iterator / ++ / bool() / == / != / =
                    TYPE& operator*() { return this->iterator_pointer->deref(); }
                    Iterator& operator++() {this->iterator_pointer->increment(); return *this; }
                    explicit operator bool() const noexcept { return static_cast<bool>(this->iterator_pointer); }
                    bool operator==(const Iterator& other) const { return !(*this != other); }
                    bool operator!=(const Iterator& other) const {
                        if (!this->iterator_pointer && !other.iterator_pointer) return false;
                        if (!this->iterator_pointer || !other.iterator_pointer) return true;
                        return !this->iterator_pointer->equals(other.iterator_pointer.get());
                    }
                    Iterator& operator=(const Iterator& other) {
                        iterator_pointer = (other.iterator_pointer) ? other.iterator_pointer->clone() : nullptr;
                        return *this;
                    }

            };

            // Iterator Methods --- begin / end
            virtual Iterator begin() noexcept = 0;
            virtual Iterator end() noexcept = 0;

    };
/*

    // ------------------------------------------ 3. Abstract Class HashMap ------------------------------------------

    // Abstract Class HashMap
    template <typename KEY, typename TYPE>
    class HashMap : public Hash<KEY> {

    };
*/
} // namespace LDN