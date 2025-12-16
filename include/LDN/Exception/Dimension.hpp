// header guard
#pragma once
#define LDN_exceptions__Dimension_HPP

// standard libraries
#include <iostream>

// Exceptions library
#include "IF_Exception.hpp"

/* ---------------------------------------------------------------------------------------------------------------------------------
 *                                                                                                                      
 *                                            LDN::exceptions --- Dimension.hpp                                                       
 *                                                                                                                      
 * ---------------------------------------------------------------------------------------------------------------------------------
*/      

namespace LDN::exceptions {

    // Class Dimension Exception
    class Dimension : public LDN::Exception {

        public:

            // constructor / destructor
            explicit Dimension(const std::string& msg) : LDN::Exception("[Dimension Exception] --> " + msg) {}
            ~Dimension() noexcept override = default;

    };

    // Utility function to check index validity and throw Index exception if invalid
    inline void throwIfDimensionException(const size_t& DIM1, const size_t& DIM2) {
        if (DIM1 != DIM2) {
            throw LDN::exceptions::Dimension("The two objects have not compatible dimensions " + std::to_string(DIM1) + " vs " + std::to_string(DIM2) + " !!!");
        }
    } 

} // namespace LDN::exception