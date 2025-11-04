// Exception library
#include "../../include/LDN/Exception/Exceptions.hpp"


// !!! TEST FUNCTION !!!
int main() {

    // allocate the Data Structure to test
    int const dim = 10;
    int array[dim] = {0};
    int index;
    
    // catch the Exception
    try {
        index = 1;
        LDN::exceptions::throwIfIndexException(index, dim);      // no catch (0 <= index < dim)
        array[index] = 1;
    } catch (LDN::Exception e) {
        e.print();
    }

    try {
        index = -7;
        LDN::exceptions::throwIfIndexException(index, dim);      // catch (index < 0) !!!
        array[index] = 2;
    } catch (LDN::Exception e) {
        e.print();
        array[-index] = 2;
    }

    try {
        index = 15;
        LDN::exceptions::throwIfIndexException(index, dim);      // catch (0 <= dim < index) !!!
        array[index] = 3;
    } catch (LDN::Exception e) {
        e.print();
        array[index % dim] = 3;
    }

    // print the modified Data Structure
    for (index = 0; index < dim; index++) {
        std::cout << "Element " << index << ": " << array[index] << std::endl;
    }
    
    // end of test
    return 0;

}