#include "header/textio.h"


extern int interrupt(int int_number, int AX, int BX, int CX, int DX);

int puts(char *string) {
	// int a = 0;
	// // Kalau string bukan null, akan mencetak ke layar
  	// while (string[a] != 0x0) {
    // 	interrupt(0x10, 0xe * 256 + string[a], 0, 0, 0);
    // 	a++;
    // }
	// interrupt(0x10, 0xe * 256 + '\r', 0, 0, 0);
	// interrupt(0x10, 0xe * 256 + '\n', 0, 0, 0);

	interrupt(0x21, 0x0, string, 0, 0);
}

int gets(char * string) {
	// char input;
	// int i = 0;
	// bool read = true;
   	// while(read){
	// 	input = interrupt(0x16, 0, 0, 0, 0); // Pengambilan input dari keyboard
	// 	// Jika input berupa backspace
	// 	if(input == 0x8){
	// 		// Jika string tidak kosong, backspace menghapus satu character
	// 		if (i > 0) {
	// 			interrupt(0x10, 0xe08, 0, 0, 0);
	// 			interrupt(0x10, 0xe00, 0, 0, 0);
	// 			interrupt(0x10, 0xe08, 0, 0, 0);
	// 			i--;
	// 		}
	// 	// Jika input berupa enter
	// 	} else if(input == 0xd){
	// 		interrupt(0x10, 0xe0a, 0, 0, 0); // Interrupt newline
	// 		interrupt(0x10, 0xe0d, 0, 0, 0); // Interrupt carriage
	// 		string[i] = 0x0; // Menambahkan null di akhir kalimat
	// 		read = false;
	// 	// Jika input berupa character
	// 	} else {
	// 		interrupt(0x10, 0xe00 + input, 0, 0, 0); // Interrupt character
	// 		string[i] = input; // Menambahkan character pada string
	// 		i++;
	// 	}
	// }

	interrupt(0x21, 0x1, string, 0, 0);
}



