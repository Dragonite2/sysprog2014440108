//**************************************************************
// ����: ����� ����
// ���: ���� ���¿� ���� ��� �Ͼ �� �ִ� ����� ��
// �����̸�: deadlock.cpp
// ������¥: 2018�� 11�� 16��
// �ۼ���: �̿���
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

//�Լ� createNode
//�Է� : ������
//��� : Heap���� ������ ����� ������
//�μ�ȿ��(Side Effect) : X
Node *createNode(int dat)
{
	Node *ptr = (Node *)malloc(sizeof(Node)); //���� �Ҵ�
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
		if(ptr->pNext != NULL) //���ǹ� : ������ ��� ������ ȭ��ǥ ǥ�÷� ��� ǥ�⸦ ���������� ��.
			printf("��"); 
		ptr = ptr->pNext;
	}

	printf("\n"); //���� ���� ��
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
//�Լ� : insertNode
//�Է� : ��� ��� ������, �� ����� ������
//��� : X
//�μ�ȿ�� : ���Ḯ��Ʈ�� ��尡 �� ���� �����
void insertHead(LList *pLList, Node *pnewNode)
{
	EnterCriticalSection(&(pLList->criticalSection));
	// Node **ppHead = &(*llHead)->pHead; //����� �ȵ�. List ���� ����ü�� ��� ����ü ������ ���� ȣȯ�� �� �Ǳ� ������ �Ű�ü�� �־����.
	pnewNode->pNext = pLList->pHead;
	pLList->pHead = pnewNode;
	LeaveCriticalSection(&(pLList->criticalSection));
}


//�Լ� : swapNode
//�Է� : �� ���� ����Ʈ�� ������
//��� : X
//�μ�ȿ�� : �� ���Ḯ��Ʈ�� �ٲ۴�.(��尡 �ٲ�ٴ� ��)

/*
EnterCriticalSection�� ���� ��Ƽ������ ���α׷��� ������ ��� : ������ �Ͼ��
���� : 
Mutex�� ���� ��Ƽ������ ���α׷��� ������ ��� : ������ �Ͼ�� �ʾҴ�.
���� : Ŀ�� ������Ʈ��
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
	printf("���α׷� ��\n");
	printf("�ð� : %f�� �ҿ�\n",duration);
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