#include "../header/filesystem.h"
#include "../header/fileio.h"
#include "../header/program.h"
#include "../header/utils.h"
#include "../header/string.h"


extern int interrupt(int int_number, int AX, int BX, int CX, int DX);

int main() {
    struct message msg;
    struct file_metadata file;
	int idx;
    int parentIndex;
    enum fs_retcode return_code;
    char *buffer;
	int a;
    char *path;
    struct file_metadata meta;

    // puts("HALOOO INI LS\r\n");
    // puts("HERE2\r\n");
    // get arguments
    getMsg(getCurrentSegment(), &msg, &return_code);
    parentIndex = msg.current_directory;
    strcpy(path, msg.arg1);
    // puts(path);
    // while (true);



	
	
	strcpy(file.node_name, path);
	file.parent_index = parentIndex;
	file.filesize = 0;
	
	read(&file, &return_code);
	
	if (return_code == FS_SUCCESS) {
		a = 0;
  	       while (file.buffer[a] != 0x0) {
  	        if(file.buffer[a] != '\n') {
  	        	interrupt(0x10, 0xe * 256 + file.buffer[a], 0, 0, 0);
  	        } else {
  	        	interrupt(0x10, 0xe * 256 + '\r', 0, 0, 0);
  	        	interrupt(0x10, 0xe * 256 + '\n', 0, 0, 0);
  	        }
    	
    		a++;
    		}
	}

    exit();
}