// Kernel header

#ifndef __KERNEL_H__
#define __KERNEL_H__


#include "std_type.h"
#include "std_lib.h"
#include "filecontrol.h"
#include "filesystem.h"

// Fungsi bawaan
extern void putInMemory(int segment, int address, char character);
extern int interrupt(int int_number, int AX, int BX, int CX, int DX);
extern void launchProgram(int segment);
void makeInterrupt21();
void handleInterrupt21(int AX, int BX, int CX, int DX);
void executeProgram(struct file_metadata *metadata, int segment);
void fillKernelMap();


// TODO : Implementasikan
void printString(char *string);
void readString(char *string);
void clearScreen();

void writeSector(byte *buffer, int sector_number);
void readSector(byte *buffer, int sector_number);

void write(struct file_metadata *metadata, enum fs_retcode *return_code);
void read(struct file_metadata *metadata, enum fs_retcode *return_code);


void exit();
void shell();
// void splitter(char* cmd, char** arr);
void mkdir(byte curr_dir, byte *name);
void ls(byte parentIndex);
void cat(char *path, byte parentIdx);
void cd(byte *cur_dir_idx, char *folderName, byte *ret_code);
void path_str_cut(char *path_str);
void path_str_expand(char *path_str, char *exp_folderName);
void cp(byte curr_dir, char *src, char *dest);
void mv(byte curr_dir, char *name, char *arg3);
void printString(char *string);

#endif

