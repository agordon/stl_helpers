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
#ifndef __NATURAL_SORT_STL_H__
#define __NATURAL_SORT_STL_H__

/*
 * std_natural_sort.h -
 * STL-compatible interface to Martin Pool's Natural-Order sorting routines.
 *
 * see http://sourcefrog.net/projects/natsort/ for more details
 *
 * Note 1:
 * There's a boost equivalent version of 'composable natural sort'
 * at http://www.boostcookbook.com/Recipe:/1235053
 * But it requires the boost library (including the regex engine),
 * and I prefer not to use it for now.
 *
 * Note 2:
 * As of FSF GNU Coreutils version 7.1, the 'sort' progarm as a similar sorting order
 * called 'version' (with the -V command argument).
 * Coreutils's implementation is found in <coreutils-7.1>/src/filevercmp.{ch}.
 * The results are similar to Matrin Poo's NatSort, but not identical
 * if the sorted strings are more complex than <prefixNUM>.
 */

/*
Usage:
	// sort an array in natural order
	vector<string> v;
	v.push_back("chr20");
	v.push_back("chr10");
	v.push_back("chr5");
	v.push_back("chr1");
	v.push_back("chr2");

	// "regular" sort
	sort(v.begin(), v.end() );
	// order will be:  
	//	chr1
	//	chr10
	//	chr2
	//	chr20
	//	chr5
	
	// "natural order" sort
	sort(v.begin(), v.end(), natural_sort_predicate() );
	// order will be: 
	// 	chr1
	// 	chr2
	// 	chr5
	// 	chr10
	// 	chr20
*/


extern "C" {
/*
  strnatcmp.{h,c} -- Perform 'natural order' comparisons of strings in C.
  Copyright (C) 2000, 2004 by Martin Pool <mbp sourcefrog net>
*/
#include "strnatcmp.h"
}

#include <string>

struct natural_sort_predicate : public std::binary_function<std::string, std::string, bool>
{
	bool operator() ( const std::string& s1, const std::string& s2 )
	{
		return strnatcmp(s1.c_str(), s2.c_str()) < 0 ;
	}
};

struct natural_sort_ignore_case_predicate : public std::binary_function<std::string, std::string, bool>
{
	bool operator() ( const std::string& s1, const std::string& s2 )
	{
		return strnatcasecmp(s1.c_str(), s2.c_str()) < 0 ;
	}
};

/*
inline bool natural_sort_predicate(const std::string& s1, const std::string& s2)
{
	return strnatcmp(s1.c_str(), s2.c_str()) < 0 ;
}

inline bool natural_sort_ignore_case_predicate(const std::string& s1, const std::string& s2)
{
	return strnatcasecmp(s1.c_str(), s2.c_str()) < 0 ;
}*/


#endif

