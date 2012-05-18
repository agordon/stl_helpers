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
#include <cstdarg>
#include <cstdlib>
#include <cstdio>

#include <errno.h>
#include <err.h>

#include "std_sprintf.h"

using namespace std;

std::string std_sprintf(const char* format, ...)
{
	int n, size = 1000;
	char *p=NULL, *np;
	va_list ap;

	if ((p = (char*)malloc (size)) == NULL)
		err(1,"Fatal error: can't allocate memory for error message");

	while (1) {
		/* Try to print in the allocated space. */
		va_start(ap, format);
		n = vsnprintf (p, size, format, ap);
		va_end(ap);

		/* If that worked, return the string. */
		if (n > -1 && n < size)
			break;  //p will contain the result
		/* Else try again with more space. */
		if (n > -1)    /* glibc 2.1 */
			size = n+1; /* precisely what is needed */
		else           /* glibc 2.0 */
			size *= 2;  /* twice the old size */
		if ((np = (char*)realloc (p, size)) == NULL) {
			free(p);
			p = NULL;
			break;
		} else {
			p = np;
		}
	}

	if (p==NULL) {
		//serious problem allocation memory for message, terminate immediately
		err(1,"Fatal error: can't allocate memory for error message");
	}

	std::string s(p);
	free(p);
	return s;
}
