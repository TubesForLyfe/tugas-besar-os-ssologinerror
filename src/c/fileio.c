#include "header/fileio.h"
#include "header/std_type.h"
#include "header/filesystem.h"
#include "header/std_lib.h"
#include "header/string.h"


extern int interrupt(int int_number, int AX, int BX, int CX, int DX);

void readSector(byte *buffer, int sector_number) {
    int sector_read_count = 0x01;
    int cylinder, sector;
    int head, drive;

    cylinder = div(sector_number, 36) << 8; // CH
    sector   = mod(sector_number, 18) + 1;  // CL

    head  = mod(div(sector_number, 18), 2) << 8; // DH
    drive = 0x00;                                // DL

    interrupt(
        0x13,                       // Interrupt number
        0x0200 | sector_read_count, // AX
        buffer,                     // BX
        cylinder | sector,          // CX
        head | drive                // DX
    );
}

void writeSector(byte *buffer, int sector_number) {
  int sector_read_count = 0x01;
    int cylinder, sector;
    int head, drive;

    cylinder = div(sector_number, 36) << 8; // CH
    sector   = mod(sector_number, 18) + 1;  // CL

    head  = mod(div(sector_number, 18), 2) << 8; // DH
    drive = 0x00;                                // DL

    interrupt(
        0x13,                       // Interrupt number
        0x0300 | sector_read_count, // AX
        buffer,                     // BX
        cylinder | sector,          // CX
        head | drive                // DX
    );
}

void read(struct file_metadata *metadata, enum fs_retcode *return_code) {
  struct node_filesystem   node_fs_buffer;
  struct node_entry        node_buffer;
  struct sector_filesystem sector_fs_buffer;
  struct sector_entry      sector_entry_buffer;
  // Tambahkan tipe data yang dibutuhkan
  bool nodefound;
  int i, j;
  char buf[8192];

  // Masukkan filesystem dari storage ke memori buffer
  readSector(&(sector_fs_buffer), FS_SECTOR_SECTOR_NUMBER);
  readSector(&(node_fs_buffer.nodes[0]),  FS_NODE_SECTOR_NUMBER);
  readSector(&(node_fs_buffer.nodes[32]), FS_NODE_SECTOR_NUMBER + 1);

  // 1. Cari node dengan nama dan lokasi yang sama pada filesystem.
  //    Jika ditemukan node yang cocok, lanjutkan ke langkah ke-2.
  //    Jika tidak ditemukan kecocokan, tuliskan retcode FS_R_NODE_NOT_FOUND
  //    dan keluar.  
  
  nodefound = false;
  i = 0;
  while (i < 64 && !nodefound) {
	  	if (strcmpa(node_fs_buffer.nodes[i].name, metadata->node_name) && node_fs_buffer.nodes[i].name[0] != 0x0 && node_fs_buffer.nodes[i].parent_node_index == metadata->parent_index) {
		  	nodefound = true;
	  	} else {
        i++;
      }
  }

  if (nodefound) {
    if (node_fs_buffer.nodes[i].sector_entry_index != 0xFF) {
      for (j = 0; j < 16; j++) {
        if(sector_fs_buffer.sector_list[node_fs_buffer.nodes[i].sector_entry_index].sector_numbers[j]==0x0){
          
      	  break;
    	}
      // puts("NOBREAK");
      // puts("HERE3");
    	readSector(&(buf[512 * j]), sector_fs_buffer.sector_list[node_fs_buffer.nodes[i].sector_entry_index].sector_numbers[j]);
    	metadata->filesize += 512;
      }
      metadata->buffer = buf;
      // puts(metadata->buffer);
      *return_code = FS_SUCCESS;
      return;
    } else {
      *return_code = FS_R_TYPE_IS_FOLDER;
      puts("TYPE IS FOLDER");
      return;
    }

  } else {
    *return_code = FS_R_NODE_NOT_FOUND;
    return;
  }

  // 2. Cek tipe node yang ditemukan
  //    Jika tipe node adalah file, lakukan proses pembacaan.
  //    Jika tipe node adalah folder, tuliskan retcode FS_R_TYPE_IS_FOLDER
  //    dan keluar.

  // Pembacaan
  // 1. memcpy() entry sector sesuai dengan byte S
  // 2. Lakukan iterasi proses berikut, i = 0..15
  // 3. Baca byte entry sector untuk mendapatkan sector number partisi file
  // 4. Jika byte bernilai 0, selesaikan iterasi
  // 5. Jika byte valid, lakukan readSector() 
  //    dan masukkan kedalam buffer yang disediakan pada metadata
  // 6. Lompat ke iterasi selanjutnya hingga iterasi selesai
  // 7. Tulis retcode FS_SUCCESS dan ganti filesize 
        // pada akhir proses pembacaan.
}

void write(struct file_metadata *metadata, enum fs_retcode *return_code) {
  struct node_filesystem   node_fs_buffer;
  struct sector_filesystem sector_fs_buffer;
  struct map_filesystem    map_fs_buffer;
  // tipe data
  bool nodefound, emptyNodeFound, isFolder, sec_entry_empty_found, isWrite;
  int i, j, k, nodeIdx, sector_empty_count, sec_need, sectorIdx, mapIdx;
  
  // Masukkan filesystem dari storage ke memori buffer
  readSector(&(sector_fs_buffer), FS_SECTOR_SECTOR_NUMBER);
  readSector(&(map_fs_buffer), FS_MAP_SECTOR_NUMBER);
  readSector(&(node_fs_buffer.nodes[0]),  FS_NODE_SECTOR_NUMBER);
  readSector(&(node_fs_buffer.nodes[32]), FS_NODE_SECTOR_NUMBER + 1);

  // proses
  nodefound = false;
  i = 0;
  while (i < 64 && !nodefound) {
	  	if (strcmpa(metadata->node_name, node_fs_buffer.nodes[i].name) && node_fs_buffer.nodes[i].parent_node_index == metadata->parent_index) {
		  	nodefound = true;
	  	} else {
        i++;
      }
  }

  // if (nodefound) {
  //   *return_code = FS_W_FILE_ALREADY_EXIST;
  //   puts("FILE ALREADY EXIST\r\n");
  //   return;
  // }

  if (nodefound) {
    nodeIdx = i;
    // clear(sector_fs_buffer.sector_list[node_fs_buffer.nodes[nodeIdx].sector_entry_index], 16*32);
  }

  if (!nodefound) {
  emptyNodeFound = false;
  nodeIdx = 0;
  while (nodeIdx < 64 && !emptyNodeFound) {
    if(node_fs_buffer.nodes[nodeIdx].name[0] == 0x0) {
      emptyNodeFound = true;
    } else {
      nodeIdx++;
    }
  }

  if (!emptyNodeFound) {
    *return_code = FS_W_MAXIMUM_NODE_ENTRY;
    puts("MAXIMUM NODE ENTRY\r\n");
    return;
  }
  }


  /*if(node_fs_buffer.nodes[nodeIdx].sector_entry_index == 0xFF) {
    isFolder = true;
  } else {
    isFolder = false;
  }

  if(!isFolder) {
    *return_code = FS_W_INVALID_FOLDER;
    puts("FOLDER INVALID\r\n");
    return;
  }*/

  if (metadata->filesize > 8192) {
    *return_code = FS_W_NOT_ENOUGH_STORAGE;
    puts("NOT ENOUGH STORAGE\r\n");
    return;
  }

  sector_empty_count = 0;
  j = 0;
  sec_need = div(metadata->filesize, 512);
  if (mod(metadata->filesize, 512) != 0) {
    sec_need ++;
  }
  while (sector_empty_count < sec_need && j < 512) {
    if(!map_fs_buffer.is_filled[j]) {
      sector_empty_count++;
    }
    j++;
  }
  if (sec_need > sector_empty_count) {
    *return_code = FS_W_NOT_ENOUGH_STORAGE;
    puts("NOT ENOUGH STORAGE\r\n");
    return;
  }

  sec_entry_empty_found = false;
  sectorIdx = 0;
  while (!sec_entry_empty_found && sectorIdx < 32) {
    if (sector_fs_buffer.sector_list[sectorIdx].sector_numbers[0] == 0x0) {
      sec_entry_empty_found = true;
    } else {
      sectorIdx++;
    }
  }


  if (!sec_entry_empty_found) {
    *return_code = FS_W_MAXIMUM_SECTOR_ENTRY;
    puts("MAXIUM SECTOR ENTRY\r\n");
    return;
  }
  


  strcpy(node_fs_buffer.nodes[nodeIdx].name, metadata->node_name);
  node_fs_buffer.nodes[nodeIdx].parent_node_index = metadata->parent_index;

  


  if (metadata->filesize > 0) {
    // puts("HERE1");
    node_fs_buffer.nodes[nodeIdx].sector_entry_index = sectorIdx;
    isWrite = false;
    mapIdx = 0; //
    k = 0; // in buffer
    while (!isWrite && mapIdx < 256) {
      if (!map_fs_buffer.is_filled[mapIdx]) {
        map_fs_buffer.is_filled[mapIdx] = true;
        sector_fs_buffer.sector_list[sectorIdx].sector_numbers[k] = mapIdx;
        
        writeSector(&(metadata->buffer[k * 512]), mapIdx);
        k++;

        if (k * 512 >= metadata->filesize) {
          isWrite = true;
        }

       
      }
      mapIdx++;
    }
    writeSector(&(sector_fs_buffer), FS_SECTOR_SECTOR_NUMBER);
    writeSector(&(map_fs_buffer), FS_MAP_SECTOR_NUMBER);
    writeSector(&(node_fs_buffer.nodes[0]),  FS_NODE_SECTOR_NUMBER);
    writeSector(&(node_fs_buffer.nodes[32]), FS_NODE_SECTOR_NUMBER + 1);
  } else  {
    // puts("HERE2");
    node_fs_buffer.nodes[nodeIdx].sector_entry_index = FS_NODE_S_IDX_FOLDER;
    writeSector(&(node_fs_buffer.nodes[0]),FS_NODE_SECTOR_NUMBER);
    writeSector(&(node_fs_buffer.nodes[32]),FS_NODE_SECTOR_NUMBER + 1);
    *return_code = FS_SUCCESS;
  }
  // puts(metadata->buffer);
  return;
}

void sendMsg(int this_segment, int currentIdx, char *arg1, char *arg2, char *arg3, int nextSegment, char *nextProgramName, byte *other) {
	struct message msg;
	struct file_metadata metadata;
	enum fs_retcode retcode;

	msg.current_directory = currentIdx;
	strcpy(msg.arg1, arg1);
	strcpy(msg.arg2, arg2);
	strcpy(msg.arg3, arg3);
	msg.next_program_segment = nextSegment;
  strcpy(msg.next_program_name, nextProgramName);
	strcpy(msg.other, other);

if (this_segment == 0x2000) {
  metadata.node_name = "msg0";
}
else if (this_segment == 0x3000) {
  metadata.node_name = "msg1";
}
else if (this_segment == 0x4000) {
  metadata.node_name = "msg2";
}
else if (this_segment == 0x5000) {
  metadata.node_name = "msg3";
}
else if (this_segment == 0x6000) {
  metadata.node_name = "msg4";
}
else if (this_segment == 0x7000) {
  metadata.node_name = "msg5";
}

// metadata.node_name = "msg1";

	metadata.buffer = &msg;
	metadata.filesize = 512;
	metadata.parent_index = 0xFF;

 

	write(&metadata, &retcode);

}

void getMsg(int this_segment, struct message *msg, enum fs_retcode *retcode) {
	struct file_metadata metadata;

	metadata.parent_index = 0xFF;

if (this_segment == 0x2000) {
  metadata.node_name = "msg0";
}
else if (this_segment == 0x3000) {
  metadata.node_name = "msg1";
}
else if (this_segment == 0x4000) {
  metadata.node_name = "msg2";
}
else if (this_segment == 0x5000) {
  metadata.node_name = "msg3";
}
else if (this_segment == 0x6000) {
  metadata.node_name = "msg4";
}
else if (this_segment == 0x7000) {
  metadata.node_name = "msg5";
}
// metadata.node_name = "msg1";

	read(&metadata, retcode);
	memcpy(msg, metadata.buffer, 512);

  

}
