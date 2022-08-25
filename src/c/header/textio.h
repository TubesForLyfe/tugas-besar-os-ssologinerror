#ifndef __TEXT_IO_H__
#define __TEXT_IO_H__

#include "std_type.h"

extern int interrupt(int int_number, int AX, int BX, int CX, int DX);
int puts(char *string);
int gets(char * string);
void splitter(char* cmd, char** arr);

#endif
