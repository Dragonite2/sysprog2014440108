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
    HANDLE hThrd[5];
    DWORD threadId;
    int i;
    
    for (i=0; i<5; i++){
        hThrd[i] = CreateThread(NULL,0,ThreadFunc,(LPVOID)i,0,&threadId );
		//쓰레드 커널 오브젝트 상태
		//signaled : 쓰레드가 종료됨.
		//non-signaled : 쓰레드가 종료되지 않음.

        /*if (hThrd){
            printf("Thread launched %d\n", i);
            CloseHandle(hThrd);
        }*/
    }
    // Wait for the threads to complete.
    // We'll see a better way of doing this later.
    //Sleep(2000);
	//여기서 핸들을 닫으면 WaitForMultipleObject()에서 쓰레드의 핸들을 접근할 수 없다.
	//따라서 스레드가 종료된 것을 확인한 후 CloseHandle을 호출해야 함.

	DWORD result;
	result = WaitForMultipleObjects(5,hThrd,TRUE,INFINITE);
	if(result == WAIT_FAILED)
	{
		printf("Error code = %d\n",GetLastError());
	}
	for(i=0;i<5;i++)
	{
		CloseHandle(hThrd[i]);
	}

    return EXIT_SUCCESS;
}
//숫자가 뒤죽박죽인 이유 : CPU Switch 

//LPVOID : (void *) void 형태 포인터
DWORD WINAPI ThreadFunc(LPVOID m){
    int i;
	int n = (int) m;
    for (i=0;i<10;i++)
	    printf("%d%d%d%d%d%d%d%d\n",n,n,n,n,n,n,n,n);
    return 0;
}
