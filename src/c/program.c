#include "header/program.h"
#include "header/filesystem.h"
#include "header/fileio.h"
#include "header/utils.h"

extern int interrupt(int int_number, int AX, int BX, int CX, int DX);
void exec(struct file_metadata *meta, int segment);
void exit();

void exec(struct file_metadata *meta, int segment) {
    interrupt(0x21, 0x6, meta, segment, 0);
}


void exit() {
    struct file_metadata meta;
    struct message msg1, msg2;
    enum fs_retcode retcode;
    int currSegment;

    // get information
    currSegment = getCurrentSegment();
    clear(&msg1, 512);
    clear(&msg2, 512);
    // if (currSegment == 0x3000) {
    //     puts("YAKKK\n\r");
    // }
    // else {
    //     puts("TIDAAKKK\n\r");
    // }
    getMsg(currSegment, &msg1, &retcode);


    getMsg(msg1.next_program_segment, &msg2, &retcode);

    sendMsg(msg1.next_program_segment, msg1.current_directory, msg2.arg1, msg2.arg2, msg2.arg3, msg2.next_program_segment, msg2.next_program_name, 0);
    // if (msg1.next_program_segment == 0x2000) {
    //     puts("BETULL\n\r");
    // }
    // else {
    //     puts("SALAHHH\n\r");
    // }

    // set currentIndex of next segment
    // getMsg(msg1.next_program_segment, &msg2, &retcode);
    // msg2.current_directory = msg1.current_directory;
    // sendMsg(msg1.next_program_segment, msg2.current_directory, msg2.arg1, msg2.arg2, msg2.arg3, msg2.next_program_segment, msg2.next_program_name, msg2.other);

    



    strcpy(meta.node_name, msg1.next_program_name);
    
    	
          meta.parent_index = 0x0;


      
    

    exec(&meta, msg1.next_program_segment);
}