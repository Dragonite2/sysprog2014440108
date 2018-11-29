//**************************************************************
// 제목: 데드락 예제
// 기능: 교착 상태에 빠질 경우 일어날 수 있는 경우의 수
// 파일이름: deadlock.cpp
// 수정날짜: 2018년 11월 16일
// 작성자: 이용준
//************************************************************
#define WIN32_LEAN_AND_MEAN
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>

DWORD WINAPI ThreadFunc(LPVOID);

typedef struct node {
	int data;
	struct node* pNext;
} Node;

typedef struct llist {
	Node *pHead;
	CRITICAL_SECTION criticalSection;
	HANDLE hMutex;
} LList;

//함수 createNode
//입력 : 데이터
//출력 : Heap에서 생성한 노드의 포인터
//부수효과(Side Effect) : X
Node *createNode(int dat)
{
	Node *ptr = (Node *)malloc(sizeof(Node)); //동적 할당
	ptr->data = dat;
	ptr->pNext = NULL;

	return ptr;
}

void printLL(LList *llist)
{
	Node *ptr = llist->pHead;
	while(ptr!= NULL)
	{
		printf("%d",ptr->data);
		if(ptr->pNext != NULL) //조건문 : 마지막 노드 전까지 화살표 표시로 노드 표기를 직관적으로 함.
			printf("→"); 
		ptr = ptr->pNext;
	}

	printf("\n"); //공백 띄우기 용
}


int numNode(LList *pLList)
{
	Node *ptr = pLList->pHead;
	int num = 0;
	while(ptr)
	{
		num++;
		ptr = ptr -> pNext;
	}

	return num;
}
//함수 : insertNode
//입력 : 헤드 노드 포인터, 새 노드의 포인터
//출력 : X
//부수효과 : 연결리스트의 헤드가 새 노드로 변경됨
void insertHead(LList *pLList, Node *pnewNode)
{
	EnterCriticalSection(&(pLList->criticalSection));
	// Node **ppHead = &(*llHead)->pHead; //지우면 안됨. List 군집 구조체와 노드 구조체 연산이 서로 호환이 안 되기 때문에 매개체가 있어야함.
	pnewNode->pNext = pLList->pHead;
	pLList->pHead = pnewNode;
	LeaveCriticalSection(&(pLList->criticalSection));
}


//함수 : swapNode
//입력 : 두 연결 리스트의 포인터
//출력 : X
//부수효과 : 두 연결리스트를 바꾼다.(헤드가 바뀐다는 뜻)

/*
EnterCriticalSection을 통해 멀티스레드 프로그램을 설계한 결과 : 교착이 일어났다
이유 : 
Mutex를 통해 멀티스레드 프로그램을 설계한 결과 : 교착이 일어나지 않았다.
이유 : 커널 오브젝트라서
*/
void swapList(LList *list1, LList *list2)
{
	Node *tmp_list;
	HANDLE arrHandles[2];
	arrHandles[0] = list1->hMutex;
	arrHandles[1] = list2->hMutex;
	WaitForMultipleObjects(2,arrHandles,TRUE,INFINITE);
	tmp_list = list1->pHead;
	list1->pHead = list2->pHead;
	list2->pHead = tmp_list;
	ReleaseMutex(arrHandles[0]);
	ReleaseMutex(arrHandles[1]);
}
typedef struct input {
	LList *pLList1;
	LList *pLList2;
} Input;


int main()
{
	time_t start,finish;
	double duration;
	LList myLList, yourLList;
	LList *pLList1 = &myLList;
	LList *pLList2 = &yourLList;
	InitializeCriticalSection(&(pLList1->criticalSection));
	InitializeCriticalSection(&(pLList2->criticalSection));
	pLList1->pHead = NULL;
	pLList2->pHead = NULL;
	insertHead(pLList1,createNode(10));
	insertHead(pLList2,createNode(10));
	Input input1, input2;


	HANDLE hThrd[2];
	DWORD threadId;

	int i;
	start = clock();
	input1.pLList1 = pLList1;
	input1.pLList2 = pLList2;
	hThrd[0] = CreateThread(NULL,0,ThreadFunc,(LPVOID)&input1,0,&threadId);
	input2.pLList1 = pLList2;
	input2.pLList2 = pLList1;
	hThrd[1] = CreateThread(NULL,0,ThreadFunc,(LPVOID)&input2,0,&threadId);
	DWORD result;
	result = WaitForMultipleObjects(2,hThrd,TRUE,INFINITE);
	if(result == WAIT_FAILED) printf("Error Code : %d\n",GetLastError());
	for(i=0;i<2;i++) CloseHandle(hThrd[i]);
	finish = clock();
	duration = (double) (finish - start) / CLOCKS_PER_SEC;
	printf("프로그램 끝\n");
	printf("시간 : %f초 소요\n",duration);
	return EXIT_SUCCESS;
}

DWORD WINAPI ThreadFunc(LPVOID n)
{
	int i;
	Input *pInput = (Input*) n;
	for(i=0;i<100000;i++)
		swapList(pInput->pLList1,pInput->pLList2);

	return 0;
}