#include <stdio.h>

int sum(int,int);
int (*fff)(int,int);//�Լ��� ������

void main()
{
	//1. �Լ��� �̸�(sum)�� �� �Լ��� ���� �ּ��̴�.
	//(������ ���� �ð����� �� �� ���Դ� �����̴�.)
	//2. �Լ� �����͸� �����Ϸ��� �� �Լ��� Ÿ���� �����ؾ� �Ѵ�.
	//���ȯ��, �Ű������� ��, �ڷ��� ��� ��ġ�ؾ� ��.

	fff = sum;
	printf("value = %d\n",sum(10,20));
	printf("value = %d\n",fff(680,720));
	

}

int sum(int a,int b)
{
	return a+b;
}
