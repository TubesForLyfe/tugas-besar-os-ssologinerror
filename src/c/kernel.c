// Kode kernel
// PENTING : FUNGSI PERTAMA YANG DIDEFINISIKAN ADALAH main(),
//   cek spesifikasi untuk informasi lebih lanjut

// TODO : Tambahkan implementasi kode C

#include "header/kernel.h"
#include "header/fileio.h" // delete



int main() {
	struct file_metadata meta;


    fillKernelMap();
    makeInterrupt21();
    clearScreen();

    printString("OPERATING SYSTEM [v 2.0] ssologinerror 2022\n\n\r");




    meta.node_name = "shell";
	  meta.parent_index = 0x0;
	  interrupt(0x21, 0x6, &meta, 0x2000, 0);
	// executeProgram(&meta, 0x2000);

    while (true);
}






void handleInterrupt21(int AX, int BX, int CX, int DX) {
    switch (AX) {
        case 0x0:
            printString(BX);
            break;
        case 0x1:
            readString(BX);
            break;
        case 0x2:
            readSector(BX, CX);
            break;
        case 0x3:
            writeSector(BX, CX);
            break;
        case 0x4:
            read(BX, CX);
            break;
        case 0x5:
            write(BX, CX);
            break;
        case 0x6:
            executeProgram(BX, CX);
            break;
            
        default:
            printString("Invalid Interrupt");
    }
}

void executeProgram(struct file_metadata *metadata, int segment) {
  enum fs_retcode fs_ret;
  byte buf[8192];
  
  metadata->buffer = buf;
  read(metadata, &fs_ret);
// puts(metadata->buffer);
  
  if (fs_ret == FS_SUCCESS) {
    int i = 0;
    for (i = 0; i < 8192; i++) {
      if (i < metadata->filesize)
        putInMemory(segment, i, metadata->buffer[i]);
      else
        putInMemory(segment, i, 0x00);
    }
	// while (true);
    launchProgram(segment);
  }
  else
    printString("exec: file not found\r\n");
}


void printString(char *string) {
	int a = 0;
	// Kalau string bukan null, akan mencetak ke layar
  	while (string[a] != 0x0) {
    	interrupt(0x10, 0xe * 256 + string[a], 0, 0, 0);
    	a++;
    }
}

void readString(char* string)
{
	char input;
	int i = 0;
	bool read = true;
   	while(read){
		input = interrupt(0x16, 0, 0, 0, 0); // Pengambilan input dari keyboard
		// Jika input berupa backspace
		if(input == 0x8){
			// Jika string tidak kosong, backspace menghapus satu character
			if (i > 0) {
				interrupt(0x10, 0xe08, 0, 0, 0);
				interrupt(0x10, 0xe00, 0, 0, 0);
				interrupt(0x10, 0xe08, 0, 0, 0);
				i--;
			}
		// Jika input berupa enter
		} else if(input == 0xd){
			interrupt(0x10, 0xe0a, 0, 0, 0); // Interrupt newline
			interrupt(0x10, 0xe0d, 0, 0, 0); // Interrupt carriage
			string[i] = 0x0; // Menambahkan null di akhir kalimat
			read = false;
		// Jika input berupa character
		} else {
			interrupt(0x10, 0xe00 + input, 0, 0, 0); // Interrupt character
			string[i] = input; // Menambahkan character pada string
			i++;
		}
	}
}

void clearScreen()
{
  interrupt(0x10, 0x0003, 0, 0, 0); // Menghapus screen
  interrupt(0x10, 0x0200, 0, 0, 0); // Memindahkan cursor
}


void fillKernelMap() {
struct map_filesystem map_fs_buffer;
  int i;

  // Load filesystem map
  readSector(&map_fs_buffer, FS_MAP_SECTOR_NUMBER);

  for (i = 0; i < 16; i++) {
	  map_fs_buffer.is_filled[i] = true;
  }

  for (i = 256; i < 512; i++) {
	  map_fs_buffer.is_filled[i] = true;
  }

  // Update filesystem map
  writeSector(&map_fs_buffer, FS_MAP_SECTOR_NUMBER); 
}



void mkdir(byte curr_dir, byte *name) {
	struct file_metadata file;
	int retcode;

	strcpy(file.node_name, name);
	file.parent_index = curr_dir;
	file.filesize = 0;
	write(&file, &retcode);
}
