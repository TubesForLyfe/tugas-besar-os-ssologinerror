#include "header/string.h"

unsigned int strlen(char *string) {
// Mengembalikan panjang suatu null terminated string
    int count = 0;

    while (*string != 0x0) {

        count++;

        string++;

    }

    return count;
}

bool strcmp(char *s1, char *s2) {

// Mengembalikan true jika string sama

    while (*s1 != 0x0) {

        if (*s1 != *s2) {

            return false;

        }

        s1++;

        s2++;

    }

    return true;

};

bool strcmpa(char *s1, char *s2) {

// Mengembalikan true jika string sama

    while (*s1 != 0x0) {

        if (*s1 != *s2) {

            return false;

        }

        s1++;

        s2++;

    }
    if (*s2 == 0x0) {
    	return true;
    } else {
        return false;
    }
};




void strcpy(char *dst, char *src)

// Melakukan penyalinan null terminated string

{

        while (*src != 0x0) {

            *dst = *src;

            src++;

            dst++;

        }

        *dst = 0x0;

};

