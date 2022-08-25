#include "../header/filesystem.h"
#include "../header/fileio.h"
#include "../header/string.h"
#include "../header/program.h"
#include "../header/utils.h"

extern int interrupt(int int_number, int AX, int BX, int CX, int DX);
void mv(byte curr_dir, char *name, char *arg3);

void main() {
    struct message msg;
    enum fs_retcode retcode;

    struct file_metadata meta;

    int parentIndex;
    char *arg1;
    char *arg2;

    getMsg(getCurrentSegment(), &msg, &retcode);

    arg1 = msg.arg1;
    arg2 = msg.arg2;
    parentIndex = msg.current_directory;

    mv(parentIndex, arg1, arg2);

    exit();
}

void mv(byte curr_dir, char *name, char *arg3) {
	// struct file_metadata fOut;
	struct node_filesystem files;
	struct node_entry *fIn;
	int retval;
	bool found;
	int i;

	readSector(&(files.nodes[0]), FS_NODE_SECTOR_NUMBER);
	readSector(&(files.nodes[32]), FS_NODE_SECTOR_NUMBER+1);

	found = false;
	for (i=0; i<64; i++) {
		if (files.nodes[i].parent_node_index == curr_dir && strcmpa(files.nodes[i].name, name) && files.nodes[i].name[0] != 0x0) {
			found = true;
			fIn = &(files.nodes[i]);
			break;
		}
	}

	if (found) {
		if (strcmp("/", arg3)) {
			// to root
			fIn->parent_node_index = FS_NODE_P_IDX_ROOT;
			if (arg3[1] == 0x0) {
				// no rename
			}
			else {
				// + rename
				strcpy(fIn->name, arg3+1);
			}
		}
		else if (strcmp("../", arg3)) {
			// puts("Masuk ../\r\n");
			fIn->parent_node_index = files.nodes[curr_dir].parent_node_index;
			// to parent
			if (arg3[3] == 0x0) {
				// no rename
				
			}
			else {
				// rename
				strcpy(fIn->name, arg3+3);
			}
		}
		else {
			// to folder
			found = false;
			for (i=0; i<64; i++) {
				if (files.nodes[i].parent_node_index == curr_dir && strcmpa(arg3, files.nodes[i].name) && files.nodes[i].name[0] != 0x0 && files.nodes[i].sector_entry_index == 0xFF) {
					fIn->parent_node_index = i;
					found = true;
					break;
				}
			}
		}
		if (found) {
			writeSector(&(files.nodes[0]),  FS_NODE_SECTOR_NUMBER);
  			writeSector(&(files.nodes[32]), FS_NODE_SECTOR_NUMBER + 1);
		}
		else {
			puts("Invalid File or Folder \r\n");
		}


	}
	else {
		puts("Invalid File or Folder \r\n");
	}
}