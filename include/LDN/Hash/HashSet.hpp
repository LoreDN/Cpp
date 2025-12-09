// header guard
#pragma once
#define LDN__HASHSET_HPP

// standard library
#include <iostream>

// Hash library
#include "IF_Hash.hpp"

/* ---------------------------------------------------------------------------------------------------------------------------------
 *                                                                                                                      
 *                                              LDN::hash_set --- HashSet.hpp                                                       
 *                                                                                                                      
 * ---------------------------------------------------------------------------------------------------------------------------------
*/

namespace LDN::hash_set {

    // ------------------------------------------ 1. Hash-Set with Open hashing ------------------------------------------
    template <typename TYPE>
    class Open : public LDN::HashSet<TYPE> {

        private:

            // helper Bucket definition
            struct Bucket{

                TYPE value;
                struct Bucket* next;

                explicit Bucket(const TYPE& key): value(key), next(nullptr) {}
                ~Bucket() noexcept = default;

            };

            // attributes
            std::unique_ptr<Bucket*[]> table;

            // Method --- Hash Function
            [[nodiscard]] const size_t hash(const TYPE& key) const noexcept override;

        public:

            // constructor
            explicit Open(const size_t& sz);
            Open(const Open<TYPE>& other) = delete; // copy constructor
            Open(Open<TYPE>&& other) noexcept = default; // move constructor

            // assignement
            Open<TYPE>& operator=(const Open<TYPE>& other) = delete; // copy assignement
            Open<TYPE>& operator=(Open<TYPE>&& other) noexcept = default; // move assignement

            // destructor
            ~Open() noexcept override;

            // Hash Methods --- implementation
            void clear() noexcept override;
            [[nodiscard]] bool contains(const TYPE& key) const noexcept override;
            [[nodiscard]] std::string toString() const noexcept override;

            // HashSet Methods --- implementation
            void insert(const TYPE& key) override;
            void remove(const TYPE& key) noexcept override;
            void resize() noexcept override;


            // ------------------------- Iterator Implementation -------------------------

            // Class SpecificationIterator
            class SpecificationIterator : public LDN::HashSet<TYPE>::AbstractIterator {
                
                private:

                    // attributes
                    Bucket** table;
                    Bucket* node;
                    size_t size;
                    size_t index;

                public:

                    // constructor
                    SpecificationIterator(Bucket** t, size_t sz, size_t i) : table(t), size(sz), index(i) {
                        if (!table) [[unlikely]] {
                            node = nullptr;
                            index = size;
                        } else [[likely]] this->skipEmpty();
                    }

                    // Method --- Skip Empty
                    void skipEmpty() noexcept {
                        while (this->index < this->size && !this->table[this->index]) this->index++;
                        this->node = (this->index < this->size) ? this->table[this->index] : nullptr;
                    }

                    // AbstractIterator Methods --- implementation
                    [[nodiscard]] TYPE& deref() const override { return this->node->value; }
                    void increment() override {
                        Bucket* next = this->node->next;
                        if (next) this->node = next;
                        else {
                            this->index++;
                            this->skipEmpty();
                        }
                    }
                    [[nodiscard]] bool equals(const LDN::HashSet<TYPE>::AbstractIterator* other) const override {
                        auto other_iterator = dynamic_cast<const SpecificationIterator*>(other);
                        if (!other_iterator) [[unlikely]] return false;
                        return this->node == other_iterator->node;

                    }
                    [[nodiscard]] std::unique_ptr<typename LDN::HashSet<TYPE>::AbstractIterator> clone() const override {
                        return std::make_unique<SpecificationIterator>(this->table, this->size, this->index);
                    }

            };

            // Iterator Methods --- begin / end
            LDN::HashSet<TYPE>::Iterator begin() noexcept override {
                return typename LDN::HashSet<TYPE>::Iterator(
                    std::make_unique<SpecificationIterator>(
                        this->table.get(), this->size, 0
                    )
                );
            }
            LDN::HashSet<TYPE>::Iterator end() noexcept override {
                return typename LDN::HashSet<TYPE>::Iterator(
                    std::make_unique<SpecificationIterator>(
                        this->table.get(), this->size, this->size
                    )
                );
            }

    };

    
    // ------------------------------------------ 2. Hash-Set with Close hashing ------------------------------------------
    template <typename TYPE>
    class Close : public LDN::HashSet<TYPE> {

        private:

            // helper fake-constants declaration
            TYPE EMPTY;
            TYPE TOMBSTONE;

            // attributes
            std::unique_ptr<TYPE[]> table;
            bool quadratic;

            // Method --- Hash Function
            [[nodiscard]] const size_t hash(const TYPE& key) const noexcept override;

        public:

            // constructor
            explicit Close(const size_t& sz, bool probing, TYPE empty, TYPE tombstone);
            Close(const Close<TYPE>& other) = delete; // copy constructor
            Close(Close<TYPE>&& other) noexcept = default; // move constructor

            // assignement
            Close<TYPE>& operator=(const Close<TYPE>& other) = delete; // copy assignement
            Close<TYPE>& operator=(Close<TYPE>&& other) noexcept = default; // move assignement

            // destructor
            ~Close() noexcept override = default;

            // Hash Methods --- implementation
            void clear() noexcept override;
            [[nodiscard]] bool contains(const TYPE& key) const noexcept override;
            [[nodiscard]] std::string toString() const noexcept override;

            // HashSet Methods --- implementation
            void insert(const TYPE& key) override;
            void remove(const TYPE& key) noexcept override;
            void resize() noexcept override;


            // ------------------------- Iterator Implementation -------------------------

            // Class SpecificationIterator
            class SpecificationIterator : public LDN::HashSet<TYPE>::AbstractIterator {
                
                private:
                    
                    // helper fake-constants declaration
                    TYPE EMPTY;
                    TYPE TOMBSTONE;

                    // attributes
                    TYPE* table;
                    size_t size;
                    size_t index;

                public:

                    // constructor
                    SpecificationIterator(TYPE* t, size_t sz, size_t i, TYPE empty, TYPE tombstone) 
                        : table(t), size(sz), index(i), EMPTY(empty), TOMBSTONE(tombstone) {
                        if (!table) [[unlikely]] index = size;
                        else [[likely]] this->skipEmpty();
                    }

                    // Method --- Skip Empty
                    void skipEmpty() noexcept {
                        while (this->index < this->size &&
                                (this->table[this->index] == this->EMPTY
                                || this->table[this->index] == this->TOMBSTONE)
                        ) this->index++;
                    }

                    // AbstractIterator Methods --- implementation
                    [[nodiscard]] TYPE& deref() const override { return this->table[this->index]; }
                    void increment() override {
                        this->index++;
                        this->skipEmpty();
                    }
                    [[nodiscard]] bool equals(const LDN::HashSet<TYPE>::AbstractIterator* other) const override {
                        auto other_iterator = dynamic_cast<const SpecificationIterator*>(other);
                        if (!other_iterator) [[unlikely]] return false;
                        return this->index == other_iterator->index && this->table == other_iterator->table;
                    }
                    [[nodiscard]] std::unique_ptr<typename LDN::HashSet<TYPE>::AbstractIterator> clone() const override {
                        return std::make_unique<SpecificationIterator>(this->table, this->size, this->index, this->EMPTY, this->TOMBSTONE);
                    }

            };

            // Iterator Methods --- begin / end
            LDN::HashSet<TYPE>::Iterator begin() noexcept override {
                return typename LDN::HashSet<TYPE>::Iterator(
                    std::make_unique<SpecificationIterator>(
                        this->table.get(), this->size, 0, this->EMPTY, this->TOMBSTONE
                    )
                );
            }
            LDN::HashSet<TYPE>::Iterator end() noexcept override {
                return typename LDN::HashSet<TYPE>::Iterator(
                    std::make_unique<SpecificationIterator>(
                        this->table.get(), this->size, this->size, this->EMPTY, this->TOMBSTONE
                    )
                );
            }

    };

} // namespace LDN::hash_set

// template implementations
#include "impl/HashSet_Open.tpp"
#include "impl/HashSet_Close.tpp"