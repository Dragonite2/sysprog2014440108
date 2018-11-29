//**************************************************************
// ����: ���� ����Ʈ ����
// ���: ���� ����Ʈ �⺻ �����Լ� �ۼ�
// �����̸�: linkedlist.cpp
// ������¥: 2018��10��05��
// �ۼ���: �̿���
//************************************************************

#define WIN32_LEAN_AND_MEAN
#include <stdio.h> //printf
#include <stdlib.h> //malloc
#include <windows.h>
#include <time.h>
int main()
{
	HANDLE hMutex,hSemaphore;
	hMutex = CreateMutex(NULL, TRUE, NULL);
	//�߰� �Ű������� FALSE�� ��� SignalState�� ����
	//TRUE�� ��� Non-Signaled ���¿��� ���� �����常 ��� ����(Ÿ ������� ���� ���� �Ұ�)
	WaitForSingleObject(hMutex,INFINITE);
	WaitForSingleObject(hMutex,INFINITE);
	printf("Mutex ����\n");

	//CriticalSection, Mutex = ���� ������ �������� ��� ����
	//Semaphore = ���� ������� ������
	hSemaphore = CreateSemaphore(NULL,1,2,NULL);
	//�ʱ� ī��Ʈ�� 1
	//�ִ� ī��Ʈ�� 2
	//Semaphore�� ��� ���� �����带 ����� �� ������, count���� ������ �־� ���� �����带 �ݺ��Ͽ� �����ų �� ����.
	WaitForSingleObject(hSemaphore,INFINITE);
	printf("Semaphore1 ����\n");
	ReleaseSemaphore(hSemaphore,1,NULL);
	WaitForSingleObject(hSemaphore,INFINITE);
	printf("Semaphore2 ����\n"); //ReleaseSemaphore ������ ���� ��� �����尡 ������ ������ �� ����.
	ReleaseSemaphore(hSemaphore,2,NULL);
	ReleaseMutex(hMutex);
	ReleaseMutex(hMutex);

	HANDLE hSem[3];
	HANDLE hSem = CreateSemaphore(NULL,3,3,NULL);
	hSem[0] = hSem[1] = hSem[2] = hSem;
	WaitForMultipleObjects(3,hSem,TRUE,INFINITE);
	printf("Semaphore3 ����\n");

	return EXIT_SUCCESS;
}