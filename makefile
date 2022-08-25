# Makefile
all: diskimage bootloader interrupt utils program stdlib string filecontrol textio fileio ext shell kernel run

# Recipes
diskimage:
	dd if=/dev/zero of=out/system.img bs=512 count=2880

bootloader:
	nasm src/asm/bootloader.asm -o out/bootloader
	dd if=out/bootloader of=out/system.img bs=512 count=1 conv=notrunc

stdlib:
	bcc -ansi -c -o out/std_lib.o src/c/std_lib.c
		
filecontrol:
	bcc -ansi -c -o out/filecontrol.o src/c/filecontrol.c
	
textio:
	bcc -ansi -c -o out/textio.o src/c/textio.c

fileio:
	bcc -ansi -c -o out/fileio.o src/c/fileio.c

string:
	bcc -ansi -c -o out/string.o src/c/string.c

utils:
	nasm -f as86 src/asm/utils.asm -o out/lib_utils.o

program:
	bcc -ansi -c -o out/program.o src/c/program.c

interrupt:
	nasm -f as86 src/asm/interrupt.asm -o out/lib_interrupt.o



ext:
	bcc -ansi -c -o out/ls.o src/c/ext/ls.c
	bcc -ansi -c -o out/cd.o src/c/ext/cd.c
	bcc -ansi -c -o out/cat.o src/c/ext/cat.c
	bcc -ansi -c -o out/cp.o src/c/ext/cp.c
	bcc -ansi -c -o out/mkdir.o src/c/ext/mkdir.c
	bcc -ansi -c -o out/mv.o src/c/ext/mv.c
	ld86 -o out/ls -d out/ls.o out/std_lib.o out/filecontrol.o out/fileio.o out/textio.o out/ls.o out/string.o out/lib_interrupt.o out/program.o out/lib_utils.o
	ld86 -o out/cd -d out/cd.o out/std_lib.o out/filecontrol.o out/fileio.o out/textio.o out/ls.o out/string.o out/lib_interrupt.o out/program.o out/lib_utils.o
	ld86 -o out/cat -d out/cat.o out/std_lib.o out/filecontrol.o out/fileio.o out/textio.o out/ls.o out/string.o out/lib_interrupt.o out/program.o out/lib_utils.o
	ld86 -o out/cp -d out/cp.o out/std_lib.o out/filecontrol.o out/fileio.o out/textio.o out/ls.o out/string.o out/lib_interrupt.o out/program.o out/lib_utils.o
	ld86 -o out/mkdir -d out/mkdir.o out/std_lib.o out/filecontrol.o out/fileio.o out/textio.o out/ls.o out/string.o out/lib_interrupt.o out/program.o out/lib_utils.o
	ld86 -o out/mv -d out/mv.o out/std_lib.o out/filecontrol.o out/fileio.o out/textio.o out/ls.o out/string.o out/lib_interrupt.o out/program.o out/lib_utils.o

shell:
	bcc -ansi -c -o out/shell.o src/c/shell.c
	ld86 -o out/shell -d out/shell.o out/std_lib.o out/filecontrol.o out/shell.o out/fileio.o out/textio.o out/string.o out/ls.o out/cd.o out/cp.o out/cat.o out/lib_interrupt.o out/program.o out/lib_utils.o


kernel:
	bcc -ansi -c -o out/kernel.o src/c/kernel.c
	nasm -f as86 src/asm/kernel.asm -o out/kernel_asm.o
	ld86 -o out/kernel -d out/kernel.o out/std_lib.o out/kernel_asm.o out/filecontrol.o out/shell.o out/string.o out/fileio.o out/textio.o out/lib_interrupt.o
	dd if=out/kernel of=out/system.img bs=512 conv=notrunc seek=1
	
run:
	bochs -f src/config/if2230.config

build-run: all

