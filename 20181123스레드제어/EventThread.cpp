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

	//������ 2�� ����
	hThrd[0] = CreateThread(NULL,0,ThreadFunc,(LPVOID)&input1,0,NULL);
	hThrd[1] = CreateThread(NULL,0,ThreadFunc,(LPVOID)&input2,0,NULL);

	printf("����Ϸ��� �ƹ� ��ư�� ������.\n");
	scanf("%d",&dummy);
	//���� �����̸� �� �� Ʈ���ŵ�
	//�ڵ� �����̸� �� ���� ������ �� �ϳ��� Ʈ���ŵ�
	SetEvent(hEvent);
	//���� �����̸� �� �� Ʈ���ŵ�
	//�ڵ� �����̸� �� ���� ������ �� �ϳ��� Ʈ���ŵ�
	printf("����Ϸ��� �ƹ� ��ư�� ������.\n");
	scanf("%d",&dummy);
	SetEvent(hEvent);
	//������ ���� ���� 
	DWORD result = WaitForMultipleObjects(2,hThrd,TRUE,INFINITE);
	if(result == WAIT_FAILED) printf("Error code = %d\n",GetLastError());
	for(int i = 0;i<2;i++) CloseHandle(hThrd[i]);

	printf("count �� = %d\n",count);
	printf("���α׷� ��\n");

	return EXIT_SUCCESS;
}



DWORD WINAPI ThreadFunc(LPVOID ptr){
	Input *pInput = (Input*) ptr;
	printf("Waiting for event to be signaled in Thread %d\n",pInput->threadNum);
	WaitForSingleObject(pInput->hEvent,INFINITE);
	printf("Event was just signaled in Thread %d\n",pInput->threadNum);
	InterlockedIncrement(pInput->pCount); //Count�� ����
    return 0;
}
