#include "header/filecontrol.h"
#include "header/textio.h"
#include "header/string.h"

extern int interrupt(int int_number, int AX, int BX, int CX, int DX);

void getDirIdxFromPath(byte *path, byte *resDirIdx, bool *isValid) {
	struct node_filesystem files;
	byte dirName[14];
	int fileIndex;
	int i, j;
	bool valid = true;
	int idx;

	clear(dirName, 14);

	// node sector 1
	readSector(&(files.nodes[0]), FS_NODE_SECTOR_NUMBER);
	// node sector 2
	readSector(&(files.nodes[32]), FS_NODE_SECTOR_NUMBER+1);

	i = 0;
	j = 0;

	if (path[0] == '/') {
		i++;
		*resDirIdx = FS_NODE_P_IDX_ROOT;
	}

	// iterate until null
	for (; path[i] != 0x0; i++) {
		if (path[i] != '/') {
			dirName[j] = path[i];
			j++;
		}
		else {
			for (; j<14; j++) {
				//null terminate
				dirName[j] = 0x0;
			}

			// find dir index in files
			for (idx = 0; idx < 64; idx++) {
				if ((files.nodes[idx].parent_node_index == *resDirIdx)
					&& strcmp(dirName, files.nodes[idx].name))
				 {
					*resDirIdx = idx;
					break;
				}
			}
		}

	if (dirName[0] != 0x0) {
		for (idx = 0; idx < 64; idx++) {
				if ((files.nodes[idx].parent_node_index == *resDirIdx)
					&& strcmp(dirName, files.nodes[idx].name))
				 {
					*resDirIdx = idx;
					break;
				}
			}
	}

	}
}

void getFilenameFromPath(byte *path, byte *resFileName) {
    int i, j;
    j = 0;

    // iterate until null
    for (i=0; path[i] != 0x0; i++) {
        if (path[i] != '/') {
            // child folder
            resFileName[j] = path[i];
            j++;
        }
        else {
            j = 0;
        }
    }
    // set to null
    for (; j<14; j++) {
        resFileName[j] = 0x0;
    }
}

void printCWD(char *path_str, byte idx_dir) {
	struct node_filesystem files;
	readSector(&(files.nodes[0]),  FS_NODE_SECTOR_NUMBER);
    	readSector(&(files.nodes[32]), FS_NODE_SECTOR_NUMBER + 1);

	if (idx_dir == FS_NODE_P_IDX_ROOT) {
		path_str = "root";
		interrupt(0x21, 0x00, path_str, 0, 0);
	}
	else {
		printCWD(path_str, files.nodes[idx_dir].parent_node_index);
		interrupt(0x21, 0x00, "/", 0, 0);
		path_str = files.nodes[idx_dir].name;
		interrupt(0x21, 0x00, path_str, 0, 0);
	}


}

/*void path_str_expand(char *path_str, char *exp_folderName) {
	// expand 1 level
	// concat

	strcpy(path_str + strlen(path_str), "/");
	strcpy(path_str + strlen(path_str), exp_folderName);
}

void path_str_cut(char *path_str) {
	// cut 1 level
	int i;
	int length;
	bool found;
	char *ptr;
	
	found = false;
	length = strlen(path_str);
	
	ptr = &(path_str[length-1]);

    while (*ptr != '/') {
        *ptr = 0x0;
        ptr -= 1;
    }
    *ptr = 0x0;


}*/
