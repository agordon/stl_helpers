#include <iostream>
#include <cstdlib>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

#include <std_string_error.h>

using namespace std;

int main(int, char*[])
{
	//This call should fail
	int fd = open("/non/existing/file", 0);
	if (fd == -1) {
		cout << "Open failed as expected. error message = " << string_error(errno) << endl;
	} else {
		cerr << "Error: open didn't fail (and it should have)." << endl;
		exit(1);
	}

	return 0;
}
