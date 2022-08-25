#include "header/std_lib.h"
#include <stdio.h>

void path_str_cut(char *path_str) {
	// cut 1 level
	int i;
	int length;
	length = strlen(path_str);
	bool found;
	found = false;

	char *ptr = path_str;

    while (*ptr != '/') {
        *ptr = 0x0;
        ptr -= 1;
    }
    *ptr = 0x0;
}
void path_str_expand(char *path_str, char *exp_folderName) {
	// expand 1 level
	// concat

	strcpy(path_str + strlen(path_str), "/");
	strcpy(path_str + strlen(path_str), exp_folderName);
}

int main() {

    char *path = "C:/Users/Asus";
    printf("hi\n");
    
    printf("%d", strlen(path));

    path_str_expand(path, "halo");

    printf("%s", path);

    return 0;
}