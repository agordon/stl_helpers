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
#ifndef __STD_STRING_TOKENIZER_H__
#define __STD_STRING_TOKENIZER_H__

#include <vector>
#include <string>
#include <iterator>

/*
   Splits a string into tokens, based on delimiter

   Usage Example:

	string input = "Hello|Token|World";
	vector<string> tokens;
	String_Tokenize ( input, "|", back_inserter<string>(tokens) );

 */
template <typename OutputIterator>
void String_Tokenize(const std::string& str,
		const std::string& delimiters ,
		OutputIterator          output_iter)
{
	std::string::size_type last  = str.find_first_not_of(delimiters, 0);
	std::string::size_type pos   = str.find_first_of(delimiters, last);

	while (std::string::npos != pos || std::string::npos != last)
	{
		*output_iter = str.substr(last, pos - last);
		++output_iter;

		last = str.find_first_not_of(delimiters, pos);
		pos = str.find_first_of(delimiters, last);
	}
}


/*
   Quick-and Dirty string tokenizer, output goes to vector<string>,
   specialized version of the above templated-function.

   Given an input string and a string of possible delimiters,
   populates the output vector with the fields.

   Returns the number of elements in the output vector
   (NOTE: if the output vector wasn't empty in input, the returned value will be higher than number of extracted elements from the input string).

   Example:
	string a("hello|world|foo|bar");
	vector<string> items;
	if (std_string_split(a, "|", items) != 4) {
		//some weird error
	}
 */
inline size_t std_string_split(const std::string& input,
		const std::string& delimiters,
		std::vector<std::string>& /*output*/ output)
{
	String_Tokenize(input, delimiters, std::back_inserter(output));
	return output.size();
}

#endif
