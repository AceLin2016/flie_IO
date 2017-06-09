/**
 *
 */

#include <stdio.h>
#include <assert.h>

#include "theFile.h"



int main(int argc, char const *argv[])
{
	if (argc!=2) {
		puts("wrong command using get_CR_number!");
		return -1;
	}//</if argc != 2>

	FILE *pf;
	unsigned int lineNumber = 1;
	unsigned long dataNumber_in_line = 0;

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
		dataNumber_in_line = get_dataNum_of_line(pf);
		printf( 
			"the %d line has %d number of chars.\r\n",
			 lineNumber++,
			  dataNumber_in_line
			  );
		// 让文件指针跳过本行。随后读取下一行
		fseek( pf, (long)(dataNumber_in_line), SEEK_CUR );		
	}while( iseof(pf)==0 );

	return 0;
}//</main>








