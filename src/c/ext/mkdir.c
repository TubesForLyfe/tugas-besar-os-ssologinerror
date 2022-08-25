#include "../header/filesystem.h"
#include "../header/fileio.h"
#include "../header/string.h"
#include "../header/program.h"
#include "../header/utils.h"


extern int interrupt(int int_number, int AX, int BX, int CX, int DX);


int main() {
    struct message msg;
    enum fs_retcode return_code;

    struct file_metadata meta;

    int parentIndex;
    char folderName[64];

    struct file_metadata file;
	int retcode;

    clear(folderName, 64);

    getMsg(getCurrentSegment(), &msg, &retcode);

    strcpy(folderName, msg.arg1);
    parentIndex = msg.current_directory;

	strcpy(file.node_name, folderName);
	file.parent_index = parentIndex;
	file.filesize = 0;
	write(&file, &retcode);
    

    exit();
}