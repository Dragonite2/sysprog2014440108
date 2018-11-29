//**************************************************************
// 제목: 연결 리스트 예제
// 기능: 연결 리스트 기본 연산함수 작성
// 파일이름: linkedlist.cpp
// 수정날짜: 2018년11월16일
// 작성자: 이용준
//************************************************************

#define WIN32_LEAN_AND_MEAN
#include <stdio.h> //printf
#include <stdlib.h> //malloc
#include <windows.h>
#include <time.h>

DWORD WINAPI ThreadFunc(LPVOID);

typedef struct node {
	int data;
	struct node* pNext;
} Node;

typedef struct llist {
	Node *pHead;
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

//함수 : insertNode
//입력 : 헤드 노드 포인터, 새 노드의 포인터
//출력 : X
//부수효과 : 연결리스트의 헤드가 새 노드로 변경됨
void insertHead(LList *pLList, Node *pnewNode)
{
	WaitForSingleObject(pLList->hMutex,INFINITE);
	// Node **ppHead = &(*llHead)->pHead; //지우면 안됨. List 군집 구조체와 노드 구조체 연산이 서로 호환이 안 되기 때문에 매개체가 있어야함.
	pnewNode->pNext = pLList->pHead;
	pLList->pHead = pnewNode;
	ReleaseMutex(pLList->hMutex);
}

//함수이름 : deleteHead
//입력 : 헤드 포인터의 포인터
//출력 : 삭제된 노드
//부수효과 : X

//Node *deleteHead(LList **llist)
//{
//	Node **ppHead = &(*llist)->pHead;
//	if(*ppHead != NULL)
//	{
//		Node *temp = (Node *)malloc(sizeof(Node)); //쓰고 버릴 노드
//		temp = (*ppHead)->pNext;
//		*ppHead = temp;
//		return temp;
//		free(temp);
//	}
//	else
//	{
//		printf("오류 : 연결 리스트가 비었습니다.");
//		return NULL;
//	}
//}

//함수 printLL
//입력 : Linked List의 헤드 포인터
//출력 : X
//부수효과(Side Effect) : 연결 리스트 출력
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

typedef struct input {
	LList *pLList;
	int threadNum;
} Input;

int main()
{
	time_t start,finish;
	double duration;
	LList myLList;
	LList *pLList = &myLList;
	pLList->hMutex = CreateMutex(NULL,FALSE,NULL);
	pLList->pHead = NULL;
	//구조체 포인터 변수 선언(노드 포인터 변수 선언)
	Input input;
	Input *pInput = &input;
	pInput->pLList = pLList;
	
	HANDLE hThrd[5];
    DWORD threadId;
	int i;
    start = clock();
	for (i=0; i<5; i++){
		pInput->threadNum = i;
        hThrd[i] = CreateThread(NULL,0,ThreadFunc,(LPVOID)pInput,0,&threadId);
    }


	DWORD result;
	result = WaitForMultipleObjects(5,hThrd,TRUE,INFINITE);
	if(result == WAIT_FAILED)
		printf("Error code = %d\n",GetLastError());
	for(i=0;i<5;i++)
		CloseHandle(hThrd[i]);

	finish = clock();
	duration = (double) (finish - start) / CLOCKS_PER_SEC;

	printf("노드 수 : %d\n",numNode(pLList));
	printf("시간 : %f\n초 소요",duration);

    return EXIT_SUCCESS;
}
//시행 결과 : MUTEX는 CriticalSection에 비해 약 10배 정도 속도가 느리다.

DWORD WINAPI ThreadFunc(LPVOID ptr){
    Input *pInput = (Input *) ptr;
    for (int i=0;i<100000;i++)
	    insertHead(pInput->pLList,createNode(pInput->threadNum));
    return 0;
}
