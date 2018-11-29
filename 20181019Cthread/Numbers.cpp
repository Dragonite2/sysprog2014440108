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
//LPVOID : ������

int main()
{
    HANDLE hThrd[5];
    DWORD threadId;
    int i;
    
    for (i=0; i<5; i++){
        hThrd[i] = CreateThread(NULL,0,ThreadFunc,(LPVOID)i,0,&threadId );
		//������ Ŀ�� ������Ʈ ����
		//signaled : �����尡 �����.
		//non-signaled : �����尡 ������� ����.

        /*if (hThrd){
            printf("Thread launched %d\n", i);
            CloseHandle(hThrd);
        }*/
    }
    // Wait for the threads to complete.
    // We'll see a better way of doing this later.
    //Sleep(2000);
	//���⼭ �ڵ��� ������ WaitForMultipleObject()���� �������� �ڵ��� ������ �� ����.
	//���� �����尡 ����� ���� Ȯ���� �� CloseHandle�� ȣ���ؾ� ��.

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
//���ڰ� ���׹����� ���� : CPU Switch 

//LPVOID : (void *) void ���� ������
DWORD WINAPI ThreadFunc(LPVOID m){
    int i;
	int n = (int) m;
    for (i=0;i<10;i++)
	    printf("%d%d%d%d%d%d%d%d\n",n,n,n,n,n,n,n,n);
    return 0;
}
