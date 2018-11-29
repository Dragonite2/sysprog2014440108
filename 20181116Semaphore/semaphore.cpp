//**************************************************************
// 제목: 연결 리스트 예제
// 기능: 연결 리스트 기본 연산함수 작성
// 파일이름: linkedlist.cpp
// 수정날짜: 2018년10월05일
// 작성자: 이용준
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
	//중간 매개변수가 FALSE일 경우 SignalState로 진입
	//TRUE일 경우 Non-Signaled 상태에서 동일 스레드만 통과 가능(타 스레드는 절대 진입 불가)
	WaitForSingleObject(hMutex,INFINITE);
	WaitForSingleObject(hMutex,INFINITE);
	printf("Mutex 종료\n");

	//CriticalSection, Mutex = 동일 스레드 내에서는 상관 없음
	//Semaphore = 동일 스레드라도 관여함
	hSemaphore = CreateSemaphore(NULL,1,2,NULL);
	//초기 카운트가 1
	//최대 카운트가 2
	//Semaphore의 경우 여러 스레드를 허락할 수 있으나, count값을 가지고 있어 동일 스레드를 반복하여 허락시킬 수 없다.
	WaitForSingleObject(hSemaphore,INFINITE);
	printf("Semaphore1 종료\n");
	ReleaseSemaphore(hSemaphore,1,NULL);
	WaitForSingleObject(hSemaphore,INFINITE);
	printf("Semaphore2 종료\n"); //ReleaseSemaphore 구문이 없을 경우 스레드가 같지만 접근할 수 없다.
	ReleaseSemaphore(hSemaphore,2,NULL);
	ReleaseMutex(hMutex);
	ReleaseMutex(hMutex);

	HANDLE hSem[3];
	HANDLE hSem = CreateSemaphore(NULL,3,3,NULL);
	hSem[0] = hSem[1] = hSem[2] = hSem;
	WaitForMultipleObjects(3,hSem,TRUE,INFINITE);
	printf("Semaphore3 종료\n");

	return EXIT_SUCCESS;
}