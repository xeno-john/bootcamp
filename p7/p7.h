#ifndef P7_H_
#define P7_H_

/* influenced by
 https://www.cprogramming.com/tutorial/shared-libraries-linux-gcc.html 
 this is how to create a library and also a link for it
 gcc -c -Wall -Werror -fpic p7.c 
 gcc -shared -o libsample.so foo.o
 gcc -L"/home/uic/bootcamp/p7" -Wall -o test main.c -lsample
 export LD_LIBRARY_PATH=/home/uic/bootcamp/p7:$LD_LIBRARY_PATH

*/
extern int* allocInLib();
extern void freeInLib( int* );

#endif