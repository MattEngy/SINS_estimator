#include <fstream>
#include <string>
#include <iostream>
#include <stdio.h>
#include "progbar.h"
#include <ctime>
#include <unistd.h>
#include "../lib/filereader_sins.h"

using namespace std;

enum {
    COLS_CNT = 22
};

int main(int argc, char** argv)
{
	if (argc == 2) {
		FILE *infile;
        infile = fopen(argv[1], "r");
		int i;
		char *dummy = NULL;
        size_t len = 255;
		for (i = 0; !feof(infile) && getline(&dummy, &len, infile); ) {
			i++;
            printf("\r%d", i);
		}
		progbar_t prog(i, 20);
		prog.upd(0);
		rewind(infile);
        double data[COLS_CNT];
        for (i = 0; !feof(infile) && freadline(infile, data, COLS_CNT); ) {
            i++;
            prog.upd(i);
        }
		fclose(infile);
		printf("\nFile has %d lines\n", i);
        printf("%lf\n", data[COLS_CNT - 1]);
	} else {
		printf("Wrong amount of argument!\n");
	}
	return 0;
}
