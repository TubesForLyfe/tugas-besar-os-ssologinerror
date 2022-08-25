#include "header/std_lib.h"



// Opsional : Tambahkan implementasi kode C



int div(int a, int b){

    int res = 0;

    while (a>=b) {

        a-=b;

        res++;

    }

    return res;

};



int mod(int a, int n) {

    while (a>=n) {

        a-=n;

    }

    return a;

};





// Operasi standar bahasa C

// Implementasikan

void memcpy(byte *dest, byte *src, unsigned int n) {

// Mengcopy n bytes yang ditunjuk src ke dest

    int i;

    for (i=0; i<n; i++) {

        dest[i] = src[i];

    }

};







// bool strcmp(char *s1, char *s2) {

// // Mengembalikan true jika string sama

//     while (*s1 != 0x0) {

//         if (*s1 != *s2) {

//             return false;

//         }

//         s1++;

//         s2++;

//     }

//     return true;

// };

// bool strcmpa(char *s1, char *s2) {

// // Mengembalikan true jika string sama

//     while (*s1 != 0x0) {

//         if (*s1 != *s2) {

//             return false;

//         }

//         s1++;

//         s2++;

//     }
//     if (*s2 == 0x0) {
//     	return true;
//     } else {
//         return false;
//     }
// };




// void strcpy(char *dst, char *src)

// // Melakukan penyalinan null terminated string

// {

//         while (*src != 0x0) {

//             *dst = *src;

//             src++;

//             dst++;

//         }

//         *dst = 0x0;

// };



void clear(byte *ptr, unsigned int n) {

// Mengosongkan byte array yang memiliki panjang n
    int i;
    for (i=0; i<n; i++) {
        ptr[i] = 0x0;
    }

};
