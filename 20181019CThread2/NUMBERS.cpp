/*
 * Numbers.c
 *
 * Sample code for "Multithreading Applications in Win32"
 * This is from Chapter 2, Listing 2-1
 *
 * Starts five threads and gives visible feedback
 * of these threads running by printing a number
 * passed in from the primary thread.
 *
 */

#define WIN32_LEAN_AND_MEAN
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

DWORD WINAPI ThreadFunc(LPVOID);
//LPVOID : 포인터

int main()
{
    HANDLE hThrd;
    DWORD threadId;
    int i;
    
    for (i=0; i<5; i++){
        hThrd = CreateThread(NULL,0,ThreadFunc,(LPVOID)i,0,&threadId );
        if (hThrd){
            printf("Thread launched %d\n", i);
            CloseHandle(hThrd);
        }

		/*ThreadFunc((LPVOID) i);*/
    }
    // Wait for the threads to complete.
    // We'll see a better way of doing this later.
    //Sleep(2000);
	while(1) i= 3*4*5*5;
    return EXIT_SUCCESS;
}
//숫자가 뒤죽박죽인 이유 : CPU Switch 

//LPVOID : (void *) void 형태 포인터
DWORD WINAPI ThreadFunc(LPVOID m){
    int i;
	int n = (int) m;
	while(1)
		i = 3*4*5*5;
    return 0;
}
