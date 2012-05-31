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
#include <iostream>
#include <string>
#include <cassert>
#include <std_string_to_number.h>

using namespace std;

int main(int, char*[])
{
	cout << "Testing string_to_number variants...." << endl;

	size_t v;
	string remains;

	//test 1
	assert ( string_to_sizet("1432", v, remains) == true ) ;
	assert ( v == 1432 ) ;
	assert ( remains == "" ) ;

	//test 2
	assert ( string_to_sizet("987123456789100000AAXX", v, remains) == true ) ;
	assert ( v == 987123456789100000 ) ;
	assert ( remains == "AAXX" ) ;

	//test 3
	v = 42 ;
	assert ( string_to_sizet("AABB987123456789100000AAXX", v, remains) == false ) ;
	assert ( v == 42 ) ; // value should remain unchanged

	//test 4
	ssize_t sv;
	assert ( string_to_ssizet("-987123456789100000BBYY", sv, remains) == true ) ;
	assert ( sv == -987123456789100000 ) ;
	assert ( remains == "BBYY" ) ;

	//test 5
	sv = 999 ;
	remains = "Yo";
	assert ( string_to_ssizet("---987123456789100000BBYY", sv, remains) == false ) ;
	assert ( sv == 999 );  // value should remain unchanged
	assert ( remains == "Yo" );  // value should remain unchanged

	//test 6
	assert ( string_to_sizet_strict("12345123451234512345", v) == true ) ;
	assert ( v == 12345123451234512345UL ) ;

	//test 7
	v = 1111;
	assert ( string_to_sizet_strict("12345123451234512345AAXX", v) == false ) ;
	assert ( v == 1111 ) ; // value should remain unchanged

	//test 8
	assert ( string_to_ssizet_strict("-12", sv) == true ) ;
	assert ( sv == -12 ) ;

	//test 7
	sv = -314;
	assert ( string_to_ssizet_strict("-12CCZZ", sv) == false ) ;
	assert ( sv == -314 ) ; // value should remain unchanged

	//test 8
	sv = -1000;
	assert ( string_to_ssizet_strict("", sv) == false ) ;
	assert ( sv == -1000 ) ; // value should remain unchanged

	//test 9
	v = 2000;
	assert ( string_to_sizet_strict("", v) == false ) ;
	assert ( v == 2000 ) ; // value should remain unchanged

	//test 10
	sv = -1000;
	assert ( string_to_ssizet("", sv,remains) == false ) ;
	assert ( sv == -1000 ) ; // value should remain unchanged

	//test 11
	v = 3000;
	assert ( string_to_sizet("", v,remains) == false ) ;
	assert ( v == 3000 ) ; // value should remain unchanged

	cout << "string_to_number - all ok" << endl;

	return 0;
}
