// Hash library
#include "../../include/LDN/Hash/Hash.hpp"

// !!! TEST FUNCTION !!!
int main() {

    // Hash-Set with Open hashing
    LDN::HashSet<int>* hash_set;
    hash_set = new LDN::hash_set::Close<int>(static_cast<size_t>(10), true, __INT_MAX__, __INT_MAX__ -1);

    // fill the Hash-Set
    for (size_t i = 0; i < hash_set->getSize() << 1; i++) {
        try {
            hash_set->insert(i << 1);
        } catch (LDN::Exception e) {
            e.print();
            break;
        }
    }
    hash_set->remove(2);
    hash_set->remove(14);
    hash_set->remove(3);        // will do nothing since 3 is not there !!!
    hash_set->insert(8);        // will do nothing since 8 is already there !!!
    hash_set->resize();
    
    // print the Hash-Set
    std::cout << *hash_set << std::endl;
    std::cout << "Number of elements: " << hash_set->getElements() << std::endl;
    std::cout << "Load Factor: " << hash_set->loadFactor() << std::endl;
    std::cout << "There is one 3? " << (hash_set->contains(3) ? "True" : "False") << std::endl;
    std::cout << "There is one 16? " << (hash_set->contains(16) ? "True" : "False") << std::endl;

    // print the Hash-Set as Iterator
    std::cout << "Print as Iterator:" << std::endl;
    for (auto& x : *hash_set) {
        std::cout << x << "\t";
    }
    std::cout << std::endl;

    // end of test
    return 0;

}