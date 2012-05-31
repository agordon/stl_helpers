/*
CPP/STL Helper functions

Copyright (c) 2012,  A. Gordon ( assafgordon at gmail dot com )
All rights reserved.

Released under BSD License:

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright
  notice, this list of conditions and the following disclaimer.
* Redistributions in binary form must reproduce the above copyright
  notice, this list of conditions and the following disclaimer in the
  documentation and/or other materials provided with the distribution.
* Neither the name of the <organization> nor the
  names of its contributors may be used to endorse or promote products
  derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#ifndef __STRING_TO_NUMBER__
#define __STRING_TO_NUMBER__

#include <cstring>
#include <cstdlib>
#include <string>
#include <cstddef>
#include <errno.h>

/*
   This file contains several wrappers for strtol,strtoul .
   combining the ease of STL's strings with the error checking of stdlib's functions.

   NOTE 1:
   All functions return boolean TRUE if the string was successfully converted to a number.
   (Note: the stdlib's functions return ZERO on failure too, but it is not the case here).
   if the functions returned TRUE, you can be sure the string contained a valid number.

   NOTE 2:
   The "_strict" variants check that the string DID NOT contain anything else after the number.
   The non "_strict" variants allow remaining charaters.
   Example:
	size_t v;
	assert(string_to_sizet("4321",v) == true); //this should work
	assert(string_to_sizet("4321AA",v) == true); //this should work, too (non-strict)
	assert(string_to_sizet_srict("4321AA",v) == false); //this should fail, the "strict" version doesn't allow following characters.


  NOTE 3:
  The "sizet" returns an unsigned "size_t" (which can be 32 or 64 bit in size, depending on your system).
  The "ssizet" returns a signed "ssize_t"  (which can be 32 or 64 bit in size, depending on your system).

  NOTE 4:
  This function IS NOT thread-safe, in the sence that if "str" parameter is changed in a parallel thread,
  the whole thing might boink.

  NOTE 5:
  The input "value" is NOT changed if the conversion failed.

  TODO:
    Add "int' and other types, too.

 */


inline bool string_to_sizet(const std::string& str, size_t& /*output*/ value, std::string &remains)
{
	errno = 0 ;
	char* endptr=NULL;
	const char* nptr = str.c_str();
	size_t result = strtoul(nptr, &endptr, 10);

	if (endptr == nptr)
		return false; //no digits found, no conversion was performed
	if (errno != 0)
		return false; //another error occured (ERANGE, usually)

	remains = endptr;
	value = result ;
	return true;
}

inline bool string_to_sizet_strict(const std::string& str, size_t& /*output*/ value)
{
	errno = 0 ;
	char* endptr=NULL;
	const char* nptr = str.c_str();
	size_t result = strtoul(nptr, &endptr, 10);

	if (endptr == nptr)
		return false; //no digits found, no conversion was performed
	if (errno != 0)
		return false; //another error occured (ERANGE, usually)
	if (*endptr != 0)
		return false; //found trailing non-digit characters

	value = result ;
	return true;
}

inline bool string_to_ssizet(const std::string& str, ssize_t& /*output*/ value, std::string &remains)
{
	errno = 0 ;
	char* endptr=NULL;
	const char* nptr = str.c_str();
	ssize_t result = strtol(nptr, &endptr, 10);

	if (endptr == nptr)
		return false; //no digits found, no conversion was performed
	if (errno != 0)
		return false; //another error occured (ERANGE, usually)

	remains = endptr;
	value = result ;
	return true;
}

inline bool string_to_ssizet_strict(const std::string& str, ssize_t& /*output*/ value)
{
	errno = 0 ;
	char* endptr=NULL;
	const char* nptr = str.c_str();
	ssize_t result = strtol(nptr, &endptr, 10);

	if (endptr == nptr)
		return false; //no digits found, no conversion was performed
	if (errno != 0)
		return false; //another error occured (ERANGE, usually)
	if (*endptr != 0)
		return false; //found trailing non-digit characters

	value = result ;
	return true;
}

#endif
