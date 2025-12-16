// Exception library
#include "../../include/LDN/Exception/Exceptions.hpp"


// !!! TEST FUNCTION !!!
int main() {

    // allocate the Data Structures to test
    size_t const dimV = 10;
    size_t rows = 2, columns = 3;
    int vector[dimV];
    int matrixA[rows][columns];

    // catch the Exception
    try {
        LDN::exceptions::throwIfDimensionException(dimV, columns);              // catch (dimV > columns) !!!
        std::cout << "Can be calculted MatrixA * Vector!" << std::endl;
    } catch (LDN::Exception e) {
        e.print();
        columns = dimV;
    }

    int matrixB[rows][columns];
    try {
        LDN::exceptions::throwIfDimensionException(dimV, columns);              // no catch (dimV == columns)
        std::cout << "Can be calculted MatrixB * Vector!" << std::endl;
    } catch (LDN::Exception e) {
        e.print();
    }
    
    // end of test
    return 0;

}