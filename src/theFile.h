

/** head of operate file
 *	theFile.h
 */

#ifndef	__THEFILE_H
#define __THEFILE_H

// FIEL* OP_tag_file = NULL;

int iseof( FILE* );
int isEmpty( FILE* );
int is_End_of_Line(FILE *);

unsigned long get_dataNum_of_line( FILE* targetFile );

/**
 *  readline 通过malloc 分配刚好容下一行字符
 *  同时在 分配的内容后加一字节。用于存放 '/0'
 *  这样，该函数返回的“数组”就几乎等同于字符串。 
 */
char *readline( FILE *targetFile);

#endif /* no define __THEFILE_H */
