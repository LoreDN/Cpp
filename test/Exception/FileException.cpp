// Exception library
#include "../../include/LDN/Exception/Exceptions.hpp"

// standard libraries
#include <iostream>
#include <fstream>

// !!! TEST FUNCTION !!!
int main() {
    
    // catch the Exception
    try {
        std::string path = "FakeINPUT.txt";
        std::ifstream file(path);
        LDN::exceptions::throwIfFileException(file, path, LDN::exceptions::FileMode::Read);      // catch (no input file)
        file.close();
    } catch (LDN::Exception e) {
        e.print();
    }

    try {
        std::string path = "FakeOUTPUT.txt";
        std::ofstream file(path);
        LDN::exceptions::throwIfFileException(file, path, LDN::exceptions::FileMode::Write);      // no catch (new output file)
        file.close();
    } catch (LDN::Exception e) {
        e.print();
    }

    try {
        std::string path = "FakeIO.txt";
        std::fstream file(path);
        LDN::exceptions::throwIfFileException(file, path, LDN::exceptions::FileMode::IO);      // catch (no IO file)
        file.close();
    } catch (LDN::Exception e) {
        e.print();
    }
    
    // end of test
    return 0;

}