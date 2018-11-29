//**************************************************************
// ����: ���� ����Ʈ ����
// ���: ���� ����Ʈ �⺻ �����Լ� �ۼ�
// �����̸�: linkedlist.cpp
// ������¥: 2018��11��16��
// �ۼ���: �̿���
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

//�Լ� : insertNode
//�Է� : ��� ��� ������, �� ����� ������
//��� : X
//�μ�ȿ�� : ���Ḯ��Ʈ�� ��尡 �� ���� �����
void insertHead(LList *pLList, Node *pnewNode)
{
	WaitForSingleObject(pLList->hMutex,INFINITE);
	// Node **ppHead = &(*llHead)->pHead; //����� �ȵ�. List ���� ����ü�� ��� ����ü ������ ���� ȣȯ�� �� �Ǳ� ������ �Ű�ü�� �־����.
	pnewNode->pNext = pLList->pHead;
	pLList->pHead = pnewNode;
	ReleaseMutex(pLList->hMutex);
}

//�Լ��̸� : deleteHead
//�Է� : ��� �������� ������
//��� : ������ ���
//�μ�ȿ�� : X

//Node *deleteHead(LList **llist)
//{
//	Node **ppHead = &(*llist)->pHead;
//	if(*ppHead != NULL)
//	{
//		Node *temp = (Node *)malloc(sizeof(Node)); //���� ���� ���
//		temp = (*ppHead)->pNext;
//		*ppHead = temp;
//		return temp;
//		free(temp);
//	}
//	else
//	{
//		printf("���� : ���� ����Ʈ�� ������ϴ�.");
//		return NULL;
//	}
//}

//�Լ� printLL
//�Է� : Linked List�� ��� ������
//��� : X
//�μ�ȿ��(Side Effect) : ���� ����Ʈ ���
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
	//����ü ������ ���� ����(��� ������ ���� ����)
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

	printf("��� �� : %d\n",numNode(pLList));
	printf("�ð� : %f\n�� �ҿ�",duration);

    return EXIT_SUCCESS;
}
//���� ��� : MUTEX�� CriticalSection�� ���� �� 10�� ���� �ӵ��� ������.

DWORD WINAPI ThreadFunc(LPVOID ptr){
    Input *pInput = (Input *) ptr;
    for (int i=0;i<100000;i++)
	    insertHead(pInput->pLList,createNode(pInput->threadNum));
    return 0;
}
