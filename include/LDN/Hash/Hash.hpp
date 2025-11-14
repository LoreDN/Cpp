// header guard
#pragma once
#define LDN__HASH_HPP

/* ---------------------------------------------------------------------------------------------------------------------------------
 *
 *  This library contains the definition of different Hash Classes, such as Hash-Sets.
 *  The structure is based on the Interface "IF_Hash" ( as an abstract class "Hash"), which is implemented by 
 *  all the specific Hash-Data-Structures.
 *
 *
 *  |-----** IMPORTANT!!! **-----|
 *  The keys of the Hash-Data-Structures have been implemented using templates: this means that can be virtually used 
 *  all custom types and Classes you want to use.
 *  However, the library has been already compiled for the most commonly used tipes via "explicit template instantiations".
 *
 * ---------------------------------------------------------------------------------------------------------------------------------
*/

// Hash library
#include "IF_Hash.hpp"
#include "HashSet.hpp"