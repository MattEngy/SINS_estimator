#include <fstream>
#include <string>
#include <iostream>
#include <stdio.h>
#include "progbar.h"
#include <ctime>
#include <unistd.h>

using namespace std;

int main(int argc, char** argv)
{
	if (argc == 2) {
		ifstream infile(argv[1]);
		int i;
		string dummy;
		for (i = 0; !infile.eof(); )
		{
			i++;
			getline(infile, dummy);
		}
		progbar_t prog(i, 2);
		prog.upd(0);
		infile.close();
		infile.open(argv[1]);
		for (i = 0; !infile.eof(); )
                {
                        i++;
                        getline(infile, dummy);
                        prog.upd(i);
                }
		infile.close();
		printf("\nFile has %d lines\n", i);
	} else {
		printf("Wrong amount of argument!\n");
	}
	return 0;
}
