
/**  operate file
 *   theFile.c
 */

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

int iseof( FILE *targetFile ){
	if (targetFile==NULL) {
		return -1;				/* 可以return 可以 exit() 看情况定*/
	}
	if (fgetc(targetFile) != EOF ){		 /* 读取一个字节判断是否是文件末尾 */
		fseek( targetFile, -1L, SEEK_CUR );/* 不是文件末尾，退一字节回去 */
		return 0;
	}else{ /* 到了文件末尾 */
		return 1;
	}	
}//</is Empty file?>




int isEmpty( FILE *targetFile ){
	if (targetFile==NULL) {
		return -1;				/* 可以return 可以 exit() 看情况定*/
	}
	fseek( targetFile, 0, SEEK_SET );	 /* 要检查文件是否是空文件，就应该从开头开始检查 */
	if (fgetc(targetFile) != EOF ){		 /* 读取一个字节判断是否是文件末尾 */
		fseek( targetFile, 0L, SEEK_SET );/* 不是空文件，回到开头 */
		/* 这里不是空文件的处理 */
		return 0;
	}else{ /* 如果读入第一个直接就到了文件末尾，则空文件 */
		return 1;
	}	
}//</is Empty file?>


int is_End_of_Line(FILE *targetFile){
	char ch;
	if (targetFile==NULL) {
		return -1;
	}

	ch = fgetc(targetFile);
	if( ch == EOF ){						/* 到达文件末也是行末 */
		return 2;
	}//</if>

	// if( ch == '\r' ){						/* 读到回车符，行末 */
	// 	ch = fgetc(targetFile);
	// 	return 1;
	// }//</if>
	if( ch == '\r' ){						/* 读到回车符，行末 */
		if ((ch=fgetc(targetFile))=='\n')	{	// 读到换行符，确认行末
			return 1;
		} else { // 这种情况很少见。只有 \r 没有 \n ；需要改进程序。
			fseek( targetFile, -1L, SEEK_CUR );
		}//</if>
	}//</if>

	// 不是文件末尾，也不是行末尾，
	fseek( targetFile, -1L, SEEK_CUR );
	return 0;
}



unsigned long get_dataNum_of_line( FILE* targetFile ){
	unsigned long charNumber = 0;
	long			back_charNumber = 0;
	char neverActrullyUse;
	int  which_Kind_EndLine = 0;
	assert(targetFile);
	while( (which_Kind_EndLine = is_End_of_Line(targetFile))==0 ){ // Not end of line
		charNumber += fscanf(targetFile, "%c", &neverActrullyUse);
	}//<while>
	// break from while => end of line
	/** 让文件位置指针回到“行首” **
	 *	同时，如果是行末 => \r\n 的话，
	 *		将charNumber + 2;   
	 *	是文件末的话， 不变。
	 */
	switch( which_Kind_EndLine ){ 
	 case 1: /* end of line || not EOF */
			charNumber = charNumber+2;
			back_charNumber = -charNumber;
			fseek(targetFile, (long)back_charNumber, SEEK_CUR);	// case 1 不使用break，本句可省略。
			break;
	 case 2: /* EOF */
	 		back_charNumber = -charNumber;
			fseek( targetFile, (long)back_charNumber, SEEK_CUR );
			break;
	 case -1: /* targetFile == NULL */
			return -1;
			break;
	}//</switch>
	return charNumber;
}//</func>


char *readline( FILE *targetFile){
	char 			*malloc_p_line;
	unsigned long	line_data_num = 0;
	int				i = 0;
	if ( targetFile == NULL ){
		return NULL;
	}
	if( iseof(targetFile) == 1 ){
		return NULL;
	}

	line_data_num = get_dataNum_of_line(targetFile);
	malloc_p_line = (char *)malloc(line_data_num+1);

	/* 将一行的字符赋值到上文分配的heap 内存中 */
	for( i=0; i<line_data_num; i++){
		*(malloc_p_line+i)=fgetc(targetFile);
	}
	malloc_p_line[line_data_num] = '\0';

	return malloc_p_line;
}




