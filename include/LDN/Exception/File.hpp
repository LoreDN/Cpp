// header guard
#pragma once
#define LDN_exceptions__File_HPP

// standard libraries
#include <iostream>
#include <fstream>
#include <concepts>

// Exceptions library
#include "IF_Exception.hpp"

/* ---------------------------------------------------------------------------------------------------------------------------------
 *                                                                                                                      
 *                                              LDN::exceptions --- File.hpp                                                       
 *                                                                                                                      
 * ---------------------------------------------------------------------------------------------------------------------------------
*/      

namespace LDN::exceptions {

    // Class File Exception
    class File : public LDN::Exception {

        public:

            // constructor / destructor
            explicit File(const std::string& msg) : LDN::Exception("[File Exception] --> " + msg) {}
            ~File() noexcept override = default;

    };

    // File modes
    enum class FileMode { Read, Write, IO };

    // Concept to check if a type is a File stream
    template <typename Stream>
    concept FileStream = requires(Stream s) { { s.is_open() } -> std::convertible_to<bool>; };

    // Utility function to check FileStream validity and throw File exception if invalid
    template <FileStream Stream>
    inline void throwIfFileException(Stream& stream, const std::string& path, FileMode mode) {
        if (!stream.is_open()) {
            std::string prefix;
            switch (mode) {
                case FileMode::Read:    prefix = "Input";   break;
                case FileMode::Write:   prefix = "Output";  break;
                case FileMode::IO:      prefix = "IO";      break;
            }
            throw LDN::exceptions::File(prefix + " file error: unable to open '" + path + "'!!!");
        }
    }
    
    // Overload from FileStream to C style FILE*
    inline void throwIfFileException(FILE* file, const std::string& path, FileMode mode) {
        if (!file) {
            std::string prefix;
            switch (mode) {
                case FileMode::Read:    prefix = "Input";   break;
                case FileMode::Write:   prefix = "Output";  break;
                case FileMode::IO:      prefix = "IO";      break;
            }
            throw LDN::exceptions::File(prefix + " file error: unable to open '" + path + "'!!!");
        }
    }

} // namespace LDN::exception