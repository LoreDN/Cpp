// header guard
#pragma once
#define LDN_exceptions__Index_HPP

// standard libraries
#include <iostream>

// Exceptions library
#include "IF_Exception.hpp"

/* ---------------------------------------------------------------------------------------------------------------------------------
 *                                                                                                                      
 *                                              LDN::exceptions --- Index.hpp                                                       
 *                                                                                                                      
 * ---------------------------------------------------------------------------------------------------------------------------------
*/      

namespace LDN::exceptions {

    // Class Index Exception
    class Index : public LDN::Exception {

        public:

            // constructor / destructor
            explicit Index(const std::string& msg) : LDN::Exception("[Index Exception] --> " + msg) {}
            ~Index() noexcept override = default;

    };

    // Utility function to check index validity and throw Index exception if invalid
    inline void throwIfIndexException(int index, size_t size) {
        if (index < 0 || static_cast<size_t>(index) >= size) {
            throw LDN::exceptions::Index("Index " + std::to_string(index) + " is out of bounds for size " + std::to_string(size) + "!!!");
        }
    } 

} // namespace LDN::exception