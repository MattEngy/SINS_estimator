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
    ifstream eoftest("0");
    string d1;
    printf("%d\n%d\n%d\n", eoftest.eof(), (int)getline(eoftest, d1), eoftest.eof());
	if (argc == 2) {
		ifstream infile(argv[1]);
		int i = 0;
		string dummy;
        while (getline(infile, dummy)) {
            i++;
        }
        printf("\ninited prigbar with maxal=%d\n", i);
		progbar_t prog(i, 50);
		prog.upd(0);
		infile.close();
		infile.open(argv[1]);
        i = 0;
        while (getline(infile, dummy)) {
            i++;
            prog.upd(i);
            printf("\nupdated progbar with i=%d\n", i);
        }
		infile.close();
		printf("\nFile has %d line(s)\n", i);
	} else {
		printf("Wrong amount of argument!\n");
	}
	return 0;
}
