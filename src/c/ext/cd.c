#include "../header/filesystem.h"
#include "../header/fileio.h"
#include "../header/string.h"
#include "../header/program.h"
#include "../header/utils.h"


extern int interrupt(int int_number, int AX, int BX, int CX, int DX);
void printcd(char *string);
// void exit();


int main() {
    struct message msg, msg2;
	int idx;
    int parentIndex;
    char folderName[64];
    enum fs_retcode retcode;
    struct file_metadata meta;
    bool found;

    struct node_filesystem files;
	int i;
	char *tempPath;

	clear(folderName, 64);
    getMsg(getCurrentSegment(), &msg, &retcode);
    strcpy(folderName, msg.arg1);

    parentIndex = msg.current_directory;


	readSector(&(files.nodes[0]), FS_NODE_SECTOR_NUMBER);
	readSector(&(files.nodes[32]), FS_NODE_SECTOR_NUMBER + 1);

	if (strcmpa(folderName, "/")) {

		parentIndex = FS_NODE_P_IDX_ROOT;

	}
	else if (strcmpa(folderName, "..")) {
        if (parentIndex != 0xFF) {
		parentIndex = files.nodes[parentIndex].parent_node_index;
        }

	}
	else if (folderName[0] == 0x0) {

	}
	else {
        found = false;
		for (i=0; i<64; i++) {
			if (files.nodes[i].parent_node_index == parentIndex &&
			strcmpa(files.nodes[i].name, folderName) && files.nodes[i].name[0] != 0x0 && files.nodes[i].sector_entry_index == 0xFF) {
				parentIndex = i;
                found = true;
                break;
			}
		}


	}
    





	sendMsg(getCurrentSegment(), parentIndex, 0, 0, 0, msg.next_program_segment, msg.next_program_name, 0);


    

    exit();
}

void printcd(char *string) {
    interrupt(0x21, 0x00, string, 0, 0);
}


