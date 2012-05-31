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
#ifndef __LIBGTEXTUTILS_CONTAINER_JOIN_H__
#define __LIBGTEXTUTILS_CONTAINER_JOIN_H__

/* 
 * Easily joins a container and outputs it to a stream.
 * 
 * Tries to emulate Perl's join in an STL way.

Usage:

 send container's elements into an output-stream:

	STD::OSTREAM << join ( CONTAINER, [DELIMITER] ) ;
	STD::OSTREAM << join ( BEGIN-ITERATOR, END-ITERATOR, [DELIMITER] ) ;

 send container's elements into a string:

	STD::STRING = join ( CONTAINER, [DELIMITER] ) ;
	STD::STRING = join ( BEGIN-ITERATOR, END-ITERATOR, [DELIMITER] ) ;

	[DELIMITER] = optional std::string, will be used as delimiter between two elements.
	              defaults to a single tab.
		      can contain multiple characters.

Usage example:

	// A simple container (could also be a list/deque/stack/whatever):
	vector<int> v;
	for (int i=0;i<10;++i)
		v.push_back(i);

	// Print the entire container:
	cout << join(v,",") << endl;
	// Will output:  0,1,2,3,4,5,6,7,8,9

	// Print specific range, using begin/end iterators
	cout << join(v.begin(), v.end(),"-") << endl;
	// Will output: 0-1-2-3-4-5-6-7-8-9

	// An std::pair<> based container 
	// map/set/multimap/multiset/unorederd_map etc.
	//   or
	// vector< pair<A,B> > etc.
	map<int, string> m;
	m[42] = "Don't Panic";
	m[666]= "Beast" ;
	
	// Print the first values (of the pair) of the entire container:
	cout << "keys  = " << join_firsts(m) << endl;
	// Will output: 42 <tab> 666

	// Print the first values (of the pair) of a specific range:
	cout << "keys  = " << join_firsts(m.begin(), m.end(), ",") << endl;
	// Will output: 42,666

	// Print the second values (of the pair) of the entire container:
	cout << "values= " << join_seconds(m) << endl;
	// Will output: Don't Panic<tab>Beast

	// Print the second values (of the pair) of a specific range:
	cout << "values= " << join_seconds(m.begin(), m.end(), ",") << endl;
	// Will output: Don't Panic,Beast


	// Store result in a string (instead of an output stream):
	string s = join_firsts(m);
	// 's' will contain: "42\t666";


*/


#include <ostream>
#include <sstream>
#include <iostream>
#include <iterator>
#include <algorithm>

template<typename ITERATOR, typename OP> 
struct joiner
{
	joiner ( ITERATOR _begin, ITERATOR _end, const std::string& _delimiter="\t" ) : 
		begin(_begin), 
		end(_end),
		delimiter(_delimiter)
	{} 

	ITERATOR begin, end;
	std::string delimiter;
	OP op;

	operator std::string() const
	{
		std::ostringstream os;
		os << *this;
		return os.str();
	}
};

template<typename ITERATOR, typename OP>
inline std::ostream& operator<< ( std::ostream& strm, const joiner<ITERATOR, OP>& j )
{
	ITERATOR it = j.begin;
	if (it != j.end) {
		//first element - doesn't need a delimiter
		strm << j.op(*it);
		it++;
	}
	for (; it != j.end ; ++it) {
		//print a delimiter before all other elements
		strm << j.delimiter ;
		strm << j.op(*it);
	}
	return strm;
}

template <typename T>
struct joiner_noop
{
const T& operator() (const T& t) const { return t; }
};

template <typename FIRST, typename SECOND>
struct joiner_select1st
{
const FIRST& operator() ( const std::pair<FIRST,SECOND>& pair ) const { return pair.first ; }
};

template <typename FIRST, typename SECOND>
struct joiner_select2nd
{
const SECOND& operator() ( const std::pair<FIRST,SECOND>& pair ) const { return pair.second; }
};

template<typename ITERATOR >
inline 
joiner< ITERATOR, joiner_noop<typename ITERATOR::value_type> > 
join(ITERATOR begin, ITERATOR end, const std::string& delimiter="\t")
{
	return joiner< ITERATOR, joiner_noop<typename ITERATOR::value_type> > (begin, end, delimiter);
}

template<typename ITERATOR >
inline 
joiner< ITERATOR, joiner_select1st<typename ITERATOR::value_type::first_type, typename ITERATOR::value_type::second_type> > 
join_firsts(ITERATOR begin, ITERATOR end, const std::string& delimiter="\t")
{
	return joiner< ITERATOR, joiner_select1st<typename ITERATOR::value_type::first_type, typename ITERATOR::value_type::second_type> > (begin, end, delimiter);
}

template<typename ITERATOR >
inline 
joiner< ITERATOR, joiner_select2nd<typename ITERATOR::value_type::first_type, typename ITERATOR::value_type::second_type> > 
join_seconds(ITERATOR begin, ITERATOR end, const std::string& delimiter="\t")
{
	return joiner< ITERATOR, joiner_select2nd<typename ITERATOR::value_type::first_type, typename ITERATOR::value_type::second_type> > (begin, end, delimiter);
}

template<typename CONTAINER>
inline 
joiner< typename CONTAINER::const_iterator, joiner_noop<typename CONTAINER::value_type>	> 
join(const CONTAINER& a, const std::string& delimiter="\t")
{
	return join(a.begin(), a.end(), delimiter);
}


template<typename CONTAINER>
inline 
joiner< typename CONTAINER::const_iterator, joiner_select1st<typename CONTAINER::value_type::first_type, typename CONTAINER::value_type::second_type> > 
join_firsts(const CONTAINER& a, const std::string& delimiter="\t")
{
	return join_firsts(a.begin(), a.end(), delimiter);
}

template<typename CONTAINER>
inline 
joiner< typename CONTAINER::const_iterator, joiner_select2nd<typename CONTAINER::value_type::first_type, typename CONTAINER::value_type::second_type> > 
join_seconds(const CONTAINER& a, const std::string& delimiter="\t")
{
	return join_seconds(a.begin(), a.end(), delimiter);
}

#endif
