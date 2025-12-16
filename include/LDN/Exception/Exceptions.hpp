// header guard
#pragma once
#define LDN__EXCEPTIONS_HPP

/* ---------------------------------------------------------------------------------------------------------------------------------
 *
 *  This library defines all the Exceptions that can be found in the various LDN/libraries.
 *  The structure is based on the Interface "IF_Exception" ( as an abstract class "Exception"), which is implemented by 
 *  all the specific Exceptions.
 *
 *
 *  |-----** IMPORTANT!!! **-----|
 *  From this library depend all the other LDN/libraries, however it is indipendent from them and available to be used alone.
 *
 * ---------------------------------------------------------------------------------------------------------------------------------
*/

// Exceptions library
#include "IF_Exception.hpp"
#include "Index.hpp"
#include "Size.hpp"
#include "File.hpp"
#include "Dimension.hpp"