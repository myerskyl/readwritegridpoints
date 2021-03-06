/*
	READWRITEGRIDPOINTS:  A program for reading the grid point IDs from GRID
						  in the file nodes.txt (Nastran format)
						  and writes the node set to the file surfacenodes.blk

	Written by:  Kyle R. Myers
				 Applied Research Laboratory
				 The Pennsylvania State University
				 University Park, PA 16804
				 December 2015
*/

#include <stdio.h>
#include <time.h>

int strcmp(const char *, const char *);
int atoi(const char *);

int main()
{
	clock_t start = clock(), diff;

	FILE *fi = fopen("nodes.txt","r");
	FILE *fo = fopen("surfacenodes.blk","w");
	char entry[8];
	int col = 1, nNodes = 0;

	if ((!fi) || (!fo)) {
		printf("Missing nodes.txt or could not open surfacenodes.blk");
		return(1);
	}

	fprintf(fo, "%s\n", "SET 1 = ");
	while (fgets(entry, 9, fi)) {

		if (strcmp(entry, "GRID    ") == 0) {
			fgets(entry, 9, fi);
			int gridID = atoi(entry);

			if (col <= 8) {
				fprintf(fo, "%8i%s", gridID,",");
			}

			else {
				fprintf(fo, "%s\n%8i%s","",gridID,",");
				col = 1;
			}
			++col;
			++nNodes;
		}
	}

	// delete the end comma	
	fseek(fo,-1,SEEK_CUR);
	fprintf(fo, "%s\n"," ");

	fclose(fi);
	fclose(fo);

	printf("%i nodes written to file\n", nNodes);
	diff = clock() - start;
	int msec = diff * 1000 / CLOCKS_PER_SEC;
	printf("CPU time: %d sec, %d ms", msec/1000, msec%1000);

	return(0);
}
