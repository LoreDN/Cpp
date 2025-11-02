// header guard
#pragma once
#define LDN__IF_EXCEPTION_HPP

// standard libraries
#include <iostream>

/* ---------------------------------------------------------------------------------------------------------------------------------
 *                                                                                                                      
 *                                              LDN --- IF_Exception.hpp                                                       
 *                                                                                                                      
 * ---------------------------------------------------------------------------------------------------------------------------------
*/      

namespace LDN {

    // Interface Exception 
    class Exception {

        protected:

            // attributes
            std::string message;

        public:

            // constructor / destructor
            explicit Exception(const std::string& msg) : message(msg) {}
            virtual ~Exception() noexcept = default;

            // getter
            inline const std::string& getMessage() const noexcept { return message; }

            // Default Method --- Print Exception message
            virtual void print(std::ostream& exc_stream = std::cerr) const {
                exc_stream << "[Exception]: " << message << std::endl;
            }

    };

} // namespace LDN