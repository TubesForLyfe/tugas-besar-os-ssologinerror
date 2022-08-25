#include "../header/filesystem.h"
#include "../header/fileio.h"
#include "../header/string.h"
#include "../header/program.h"
#include "../header/utils.h"
#include "../header/string.h"



extern int interrupt(int int_number, int AX, int BX, int CX, int DX);

int main() {
    struct message msg;
    struct node_filesystem files;
	int idx;
    int parentIndex;
    enum fs_retcode retcode;

    getMsg(getCurrentSegment(), &msg, &retcode);
    parentIndex = msg.current_directory;

	readSector(&(files.nodes[0]), FS_NODE_SECTOR_NUMBER);

	// read node sector 2
	readSector(&(files.nodes[32]), FS_NODE_SECTOR_NUMBER + 1);

	for (idx=0; idx<64; idx++) {
		if (files.nodes[idx].parent_node_index == parentIndex && 
		files.nodes[idx].name[0] != 0x0) {
			// in this directory
			puts(files.nodes[idx].name);
			puts("\r\n");
		}
	}
	puts("\r\n");

	

	// while (true);

	// push message to this segment msg

    exit();
}

