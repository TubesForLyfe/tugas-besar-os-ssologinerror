#include "../header/filesystem.h"
#include "../header/fileio.h"
#include "../header/string.h"
#include "../header/program.h"
#include "../header/utils.h"

extern int interrupt(int int_number, int AX, int BX, int CX, int DX);



int main() {
    struct message msg;
	int idx;
    int parentIndex;
    enum fs_retcode return_code;
    struct file_metadata files_src;
	struct file_metadata files_dest;
	struct node_filesystem files;
	struct node_entry src_file;
	struct node_entry dest_file;
	struct sector_filesystem system;
	char *buffer;

	int i, src_count;
	bool found_src, found_dest, sector_end;
    struct file_metadata meta;


    getMsg(getCurrentSegment(), &msg, &return_code);
    parentIndex = msg.current_directory;





	readSector(&(files.nodes[0]), FS_NODE_SECTOR_NUMBER);
	readSector(&(files.nodes[32]), FS_NODE_SECTOR_NUMBER+1);
	readSector(system.sector_list, FS_SECTOR_SECTOR_NUMBER);
	
	found_src = false;
	for (i=0; i<64; i++) {
		if (files.nodes[i].parent_node_index == parentIndex && strcmpa(files.nodes[i].name, msg.arg1) && files.nodes[i].name[0] != 0x0) {
			found_src = true;
			src_file = files.nodes[i];
			break;
		}
	}
	sector_end = false;
	src_count = 0;
	while (!sector_end && src_count < 16) {
		if (system.sector_list[src_file.sector_entry_index].sector_numbers[src_count] == 0x0) {
			sector_end = true;
		} else {
			src_count++;
		}
	}
	
	found_dest = false;
	for (i=0; i<64; i++) {
		if (files.nodes[i].parent_node_index == parentIndex && strcmpa(files.nodes[i].name, msg.arg2) && files.nodes[i].name[0] != 0x0) {
			found_dest = true;
			dest_file = files.nodes[i];
			break;
		}
	}
	
	if (found_src && !found_dest) {
		// puts("CORRECT\r\n");
		// strcpy(files_src.buffer, buffer);
		// clear(files_src.buffer, 8192);
		files_src.node_name = msg.arg1;
		files_src.parent_index = src_file.parent_node_index;
		
		files_dest.node_name = msg.arg2;
		files_dest.parent_index = src_file.parent_node_index;
		
		read(&files_src, &return_code);
		// puts(files_src.node_name);
        // puts(files_dest.node_name);
		files_dest.filesize = files_src.filesize;
		files_dest.buffer = files_src.buffer;
		// puts("HERE2\r\n");
		// puts(files_dest.buffer);
		write(&files_dest, &return_code);
	} else {
		
	}


    exit();

    
}