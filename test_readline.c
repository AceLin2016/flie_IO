/**
 *
 */

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include "theFile.h"



int main(int argc, char const *argv[])
{
	if (argc!=2) {
		puts("wrong command using get_CR_number!");
		return -1;
	}//</if argc != 2>

	FILE            *pf;
	unsigned int    lineNumber = 1;
	unsigned long   dataNumber_in_line = 0;
    char            *line_data;
    int             i=0;

	pf = fopen( argv[1], "rb" );
	if (pf == NULL)	{
		putchar('\a');
		puts( "WARNING: can't open the file!");
		puts( "Please check that you had input the full directory correct and the file exist!" );
		return 1;	// exit(1);		
	}
	if ( isEmpty(pf)== 1) {
	 	puts("Empty file.");
	 	fclose(pf);
	 	return 0;
	}//</if is Empty file>

	do {
        
		line_data = readline(pf);
		printf( "%s", line_data );
		free( line_data );
	}while( iseof(pf)==0 );

	return 0;
}//</main>


