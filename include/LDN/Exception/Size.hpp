// header guard
#pragma once
#define LDN_exceptions__File_HPP

// standard libraries
#include <iostream>

// Exceptions library
#include "IF_Exception.hpp"

/* ---------------------------------------------------------------------------------------------------------------------------------
 *                                                                                                                      
 *                                              LDN::exceptions --- Size.hpp                                                       
 *                                                                                                                      
 * ---------------------------------------------------------------------------------------------------------------------------------
*/      

namespace LDN::exceptions {

    // Class File Exception
    class Size : public LDN::Exception {

        public:

            // constructor / destructor
            explicit Size(const std::string& msg) : LDN::Exception("[Size Exception] --> " + msg) {}
            ~Size() noexcept override = default;

    };

    // Utility function to check Data-Structure usage and and throw Size Exception if full
    inline void throwIfSizeException(const size_t size, const size_t limit) {
        if (size >= limit) {
            throw LDN::exceptions::Size("Size " + std::to_string(size) + " is out of bounds for the maximum limit " + std::to_string(limit) + "!!!");
        }
    }

} // namespace LDN::exception