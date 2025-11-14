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
            const size_t hash(const TYPE& key) const noexcept override;

        public:

            // constructor / destructor
            explicit Open(const size_t& sz);
            ~Open() noexcept override;

            // Hash Methods --- implementation
            void clear() noexcept override;
            bool contains(const TYPE& key) const noexcept override;
            std::string toString() const noexcept override;

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
                        this->skipEmpty();
                    }

                    // Method --- Skip Empty
                    void skipEmpty() noexcept {
                        while (this->index < this->size && !this->table[this->index]
                        ) this->index++;
                        this->node = (this->index < this->size) ? this->table[this->index] : nullptr;
                    }

                    // AbstractIterator Methods --- implementation
                    TYPE& deref() const override { return this->node->value; }
                    void increment() override {
                        Bucket* next = this->node->next;
                        if (next) this->node = next;
                        else {
                            this->index++;
                            this->skipEmpty();
                        }
                    }
                    bool equals(const LDN::HashSet<TYPE>::AbstractIterator* other) const override {
                        auto other_iterator = dynamic_cast<const SpecificationIterator*>(other);
                        return this->node == other_iterator->node;

                    }
                    std::unique_ptr<typename LDN::HashSet<TYPE>::AbstractIterator> clone() const override {
                        return std::make_unique<SpecificationIterator>(this->table, this->size, this->index);
                    }

            };

            // Iterator Methods --- begin / end
            LDN::HashSet<TYPE>::Iterator begin() noexcept override {
                SpecificationIterator it(this->table.get(), this->size, 0);
                return typename LDN::HashSet<TYPE>::Iterator(it.clone());
            }
            LDN::HashSet<TYPE>::Iterator end() noexcept override {
                SpecificationIterator it(this->table.get(), this->size, this->size);
                return typename LDN::HashSet<TYPE>::Iterator(it.clone());
            }

    };

} // namespace LDN::hash_set

// template implementations
#include "impl/HashSet_Open.tpp"