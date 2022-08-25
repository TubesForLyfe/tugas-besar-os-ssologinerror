// #include "header/shell.h"

#include "header/std_type.h"
#include "header/string.h"
#include "header/filesystem.h"
#include "header/fileio.h"
#include "header/filecontrol.h"
#include "header/program.h"
#include "header/textio.h"

extern int interrupt(int int_number, int AX, int BX, int CX, int DX);
void printShell(char *string);
void split(char cmd[128], char arr_input[64][64]);

int main() {
char path_str[128];
int current_dir;
enum fs_retcode retcode;
struct message msg;
struct file_metadata meta;
char input_buf[128];
char command_arr[64][64];
int i, j, seg_idx, clr;



// sendMsg(0xFF, "-", "-", "-", 0, "-");


// puts(msg.arg1);
//   printShell("Halooo\r\n");
  while(true) {
	//   puts("\n\n\r\rHERE");
	  clear(&msg, 512);
	  getMsg(0x2000, &msg, &retcode);



if (retcode == FS_SUCCESS) {
	// puts("\n\rSUCCESSS0");
	current_dir = msg.current_directory;
}
else {
	// puts("\n\rFAIL");
	current_dir = 0xFF;

}
	  //setup
	  clear(input_buf, 128);
	  clear(command_arr, 64*64);
	// puts("\n\n\r\rHERE");
	  printShell("OS@IF2230:");
	  printCWD(path_str, current_dir);
	  printShell("$");
	  // readString
	  clear(input_buf, 128);
	  for (clr = 0; clr < 64; clr++) {
		  clear(command_arr[i], 64);
	  }
	  interrupt(0x21, 0x01, input_buf, 0, 0);
	  split(input_buf, command_arr);

		// puts("SINI\r\n");
		// puts(command_arr[0]);
		// puts("\r\n");
		// puts(command_arr[1]);
		// puts("\r\n");  
		// puts(command_arr[2]);
		// puts("\r\n");


		// PARSE PROGRAM

  seg_idx = 1;
  i = 0;
  j = 0;

  strcpy(meta.node_name, command_arr[0]);
//   puts("A\r\n");
//   puts(command_arr[0]);

clear(&msg, 512);


  while (command_arr[i][0] != 0x0) { // while not null
	  if (!strcmpa(command_arr[i], ";")) {
		  if (j == 0) {
			  // program name
		  }
		  else if (j == 1) {
			  // arg 1
			  strcpy(msg.arg1, command_arr[i]);

		  }
		  else if (j == 2) {
			  // arg 2
			  strcpy(msg.arg2, command_arr[i]);

		  }
		  else if (j == 3) {
			  // arg 3
			  strcpy(msg.arg3, command_arr[i]);

		  }
		  j++;
	  }
	  else {
		  // semicolon
		  j = 0;

		  // send message
		  sendMsg((seg_idx+2)*(0x1000), // this segment idx
		  current_dir, 
		  msg.arg1, // arg1
		  msg.arg2, // arg2
		  msg.arg3, // arg3
		  (seg_idx+3)*(0x1000), // next segment number
		  command_arr[i+1], // next program name
		  0);
		  clear(&msg, 512);



		  seg_idx++;
	  }
	  i++;
  }
//   puts("B\r\n");

  // last program
  
  sendMsg((seg_idx+2)*(0x1000), current_dir, msg.arg1, msg.arg2, msg.arg3, 0x2000, "shell", 0);
  
  seg_idx++;

  // execute first
//   puts("C\r\n");
  
  meta.parent_index = 0x0;


	  clear(input_buf, 128);
	  clear(command_arr, 64*64);

  exec(&meta, 0x3000);

  }
}

void printShell(char *string) {
	// call printString from kernel mode
	interrupt(0x21, 0x00, string, 0, 0);
}

void split(char cmd[128], char arr[64][64]) {
  int idx, i, j;

  

  idx = 0;
  i = 0;
  j = 0;

  while (*cmd != 0x0) {
    if (*cmd != ' ') {
      arr[i][j] = *cmd;
      j++;
    }
    else {
      i++;
      j = 0;
    }
    cmd++;
  }
}