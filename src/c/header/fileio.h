#ifndef __FILE_IO_H__
#define __FILE_IO_H__

#include "std_type.h"
#include "filesystem.h"
#include "textio.h"

struct message {
    int current_directory;
    char arg1[64];
    char arg2[64];
    char arg3[64];
    int next_program_segment; // Dapat digunakan untuk bagian 3.5
    char next_program_name[64];
    byte other[251];
};


void readSector(byte *buffer, int sector_number);
void writeSector(byte *buffer, int sector_number);

void read(struct file_metadata *metadata, enum fs_retcode *return_code);
void write(struct file_metadata *metadata, enum fs_retcode *return_code);

void sendMsg(int this_segment, int currentIdx, char *arg1, char *arg2, char *arg3, int nextSegment, char *nextProgramName, byte *other);
void getMsg(int this_segment, struct message *msg, enum fs_retcode *retcode);






#endif
