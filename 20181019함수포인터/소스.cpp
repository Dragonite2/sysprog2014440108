#include <stdio.h>

int sum(int,int);
int (*fff)(int,int);//함수의 포인터

void main()
{
	//1. 함수의 이름(sum)은 그 함수의 시작 주소이다.
	//(포인터 변수 시간에서 몇 번 나왔던 내용이다.)
	//2. 함수 포인터를 지정하려면 두 함수의 타입이 동일해야 한다.
	//→반환형, 매개변수의 수, 자료형 모두 일치해야 함.

	fff = sum;
	printf("value = %d\n",sum(10,20));
	printf("value = %d\n",fff(680,720));
	

}

int sum(int a,int b)
{
	return a+b;
}
