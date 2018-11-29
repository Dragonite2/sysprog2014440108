#define _CRT_SECURE_NO_WARNINGS
#define WIN32_LEAN_AND_MEAN
#include <stdio.h> //printf
#include <stdlib.h> //malloc
#include <windows.h>
#include <time.h>

typedef struct input {
	HANDLE hEvent;
	int threadNum;
	long *pCount;

} Input;

DWORD WINAPI ThreadFunc(LPVOID);

int main()
{
	int dummy;
	long count = 0;
	long *pCount = &count;
	HANDLE hEvent, hThrd[2];
	hEvent = CreateEvent(NULL,
		FALSE, //true = manual reset, false = auto reset
		FALSE, //initial state false = non-signaled, true = signaled
		NULL);

	Input input1 = {hEvent,1,pCount};
	Input input2 = {hEvent,2,pCount};

	//스레드 2개 생성
	hThrd[0] = CreateThread(NULL,0,ThreadFunc,(LPVOID)&input1,0,NULL);
	hThrd[1] = CreateThread(NULL,0,ThreadFunc,(LPVOID)&input2,0,NULL);

	printf("계속하려면 아무 버튼을 눌러라.\n");
	scanf("%d",&dummy);
	//수동 리셋이면 둘 다 트리거됨
	//자동 리셋이면 두 개의 스레드 중 하나만 트리거됨
	SetEvent(hEvent);
	//수동 리셋이면 둘 다 트리거됨
	//자동 리셋이면 두 개의 스레드 중 하나만 트리거됨
	printf("계속하려면 아무 버튼을 눌러라.\n");
	scanf("%d",&dummy);
	SetEvent(hEvent);
	//스레드 생성 직후 
	DWORD result = WaitForMultipleObjects(2,hThrd,TRUE,INFINITE);
	if(result == WAIT_FAILED) printf("Error code = %d\n",GetLastError());
	for(int i = 0;i<2;i++) CloseHandle(hThrd[i]);

	printf("count 값 = %d\n",count);
	printf("프로그램 끝\n");

	return EXIT_SUCCESS;
}



DWORD WINAPI ThreadFunc(LPVOID ptr){
	Input *pInput = (Input*) ptr;
	printf("Waiting for event to be signaled in Thread %d\n",pInput->threadNum);
	WaitForSingleObject(pInput->hEvent,INFINITE);
	printf("Event was just signaled in Thread %d\n",pInput->threadNum);
	InterlockedIncrement(pInput->pCount); //Count값 증가
    return 0;
}
