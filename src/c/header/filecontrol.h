#ifndef __FILECONTROL_H__
#define __FILECONTROL_H__

#include "std_type.h"
#include "std_lib.h"
#include "filesystem.h"
#include "kernel.h"

void getDirIdxFromPath(byte *path, byte *resDirIdx, bool *isValid);
void getFilenameFromPath(byte *path, byte *resFileName);
void printCWD(char *path_str, byte idx_dir);

void path_str_expand(char *path_str, char *exp_folderName);

void path_str_cut(char *path_str);
#endif