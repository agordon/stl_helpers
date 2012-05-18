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
#ifndef __STD_STRING_NUC_TWOBIT__
#define __STD_STRING_NUC_TWOBIT__

#include <unistd.h>
#include <string>


inline size_t seq_to_twobit ( const std::string & seq )
{
	size_t twobit = 0;

	for (size_t i=0;i<seq.length();++i) {
		twobit <<=2;

		const char ch = seq[i];
		switch(ch)
		{
			default:
			case 'A':
			case 'a':
				twobit |= 0 ; //will be optimized out? I hope
				break;

			case 'C':
			case 'c':
				twobit |= 1;
				break;

			case 'G':
			case 'g':
				twobit |= 2;
				break;

			case 'T':
			case 't':
				twobit |= 3;
				break;
		}
	}
	return twobit;
}

inline std::string twobit_to_seq (  size_t twobit, size_t length )
{
	std::string seq(length, ' ');

	for (ssize_t i=length-1;i>=0;--i) {
		const size_t value = twobit&0x3;
		twobit >>= 2;
		switch(value)
		{
		default:
		case 0:
			seq[i]='A';
			break;
		case 1:
			seq[i]='C';
			break;
		case 2:
			seq[i]='G';
			break;
		case 3:
			seq[i]='T';
			break;
		}
	}
	return seq;
}

#endif
