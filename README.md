# Tugas Besar IF2230

### Deskripsi singkat program

Program dalam bahasa C untuk membuat kernel, <i>syscall</i>, dan shell sederhana beserta utility pada shell tersebut. Utility yang dibuat meliputi <i>cd</i>, <i>ls</i>, <i>mkdir</i>, <i>cat</i>, <i>cp</i>, <i>mv</i>.

### Requirement program dan instalasi

Pengunduhan VM VirtualBox dapat dilakukan melalui situs berikut.

https://www.virtualbox.org/wiki/Downloads

Pengunduhan Ubuntu dapat dilakukan melalui situs berikut.

https://ubuntu.com/download/desktop/thank-you?version=20.04.4&architecture=amd64

### Cara menggunakan program

- pindahkan file dan folder pada folder tc_gen ke dalam folder out


- Untuk mengkompilasi dan mengeksekusi source code, jalankan makefile pada terminal dengan perintah berikut
```
> make
```

- Untuk mengeksekusi source code perlu menggunakan tc_gen A yang dimodifikasi (memasukan shell dan utility program)
```
> cd out
> gcc tc_gen.c tc_lib -o tc_gen
> ./tc_gen A
> cd ..
> make run

### Author
Kelompok 13: SSOLoginError
| Nama | NIM |
| ---- | ------ |
| Ziyad Dhia Rafi | 13520064 |
| Vincent Christian Siregar | 13520136 | 
| Willy Wilsen | 13520160 | 
