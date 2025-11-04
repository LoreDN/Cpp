// Exception library
#include "../../include/LDN/Exception/Exceptions.hpp"


// !!! TEST FUNCTION !!!
int main() {

    // allocate the Data Structure to test
    int dim = 10;
    int* array = new int[10];
    int array_usage = 0;
    
    // catch the Exception
    try {
        for (size_t i = 0; i < dim; i++) {
            LDN::exceptions::throwIfSizeException(array_usage, dim);      // no catch (array_usage < dim)
            array[array_usage++] = i;
        }
    } catch (LDN::Exception e) {
        e.print();
    }

    try {
        for (size_t i = 0; i < dim; i++) {
            LDN::exceptions::throwIfSizeException(array_usage, dim);      // catch (array_usage >= dim)
            array[array_usage++] = i;
        }
    } catch (LDN::Exception e) {
        e.print();
        delete[] array;
        dim <<= 1;
        array = new int[dim];
        array_usage = 0;
    }

    try {
        for (size_t i = 0; i < dim; i++) {
            LDN::exceptions::throwIfSizeException(array_usage, dim);      // no catch (array_usage < dim)
            array[array_usage++] = i;
        }
    } catch (LDN::Exception e) {
        e.print();
    }

    // print the modified Data Structure
    std::cout << "Array usage: " << array_usage << std::endl;
    for (size_t i = 0; i < dim; i++) {
        std::cout << "Element " << i << ": " << array[i] << std::endl;
    }
    
    // end of test
    return 0;

}