//**************************************************************
// 제목: 포인터, 구조체, 동적 할당 강의
// 기능: 연결 리스트 사용을 위한 기초 강의
// 파일이름: pointer.cpp
// 수정날짜: 2018년10월05일
// 작성자: 이용준
//************************************************************

#include <stdio.h>
#include <stdlib.h>

//구조체 선언 : 새로운 자료형(Type)을 만드는 개념.
typedef struct complex{
	double real; //member variable(멤버 변수)
	double imag;
}Complex; //구조체 선언은 ;로 끝나야 함.
//typedef : (앞으로 특정 자료형을 ~로 부르겠다.)

//함수 printComplexVar
//입력 : 복소수
//출력 : 없음
//부수효과(Side Effect) : 화면에 복소수 출력
void printComplexVar(Complex a)
{
	printf("Complex = %f + j%f\n",a.real,a.imag);
}

//함수 printComplex
//입력 : 복소수 구조체의 포인터
//출력 : 없음
//부수효과(Side Effect) : 화면에 복소수 출력
void printComplex(Complex *a)
{
	printf("Complex = %f + j%f\n",a->real,a->imag);
}

//함수 addComplexReturnVar
//입력 : 2개의 복소수 구조체의 포인터
//출력 : 합산된 복소수 구조체
//부수효과(Side Effect) : X
Complex addComplexReturnVar(Complex *ptr1, Complex *ptr2)
{
	Complex ptr;
	ptr.real = ptr1->real + ptr2->real;
	ptr.imag = ptr1->imag + ptr2->imag;

	return ptr;
}

//함수 addComplex
//입력 : 2개의 복소수 구조체의 포인터
//출력 : 합산된 복소수 구조체의 포인터
//부수효과(Side Effect) : X
Complex *addComplex(Complex *ptr1, Complex *ptr2)
{
	//malloc 함수의 원형은 void *malloc 이기 때문에 형변환(Casting) 과정이 꼭 필요하다.
	Complex *ptr = (Complex *)malloc(sizeof(Complex)); //동적 할당 선언(Dynamic Memory Allocation)
	ptr->real = ptr1->real + ptr2->real;
	ptr->imag = ptr1->imag + ptr2->imag;

	return ptr;
}
//함수 호출이 끝나는 순간 지역 변수는 소멸되기 때문에 제대로 작동하지 않을 수 있다.(함수 또한 스택을 사용하기 때문이다.)
//때문에 위와 같이 동적 할당을 이용하여 선언을 해야 프로그래머의 설계에 따라 작동할 수 있는 것이다.

void main()
{
	int a=10,b=20,c=30;

	int *ptr; //포인터 변수 선언
	ptr = &a; //포인터 변수의 주소에 a변수의 주소를 대입
	*ptr = b; //ptr 포인터 변수의 값에 b의 값을 대입

	printf("a = %d\n",a);

	//구조체 활용
	Complex c1={1.0,1.0}, c2={2.0,3.0}, c3={4.0,5.5}; //구조체 변수 선언
	//c3 = c1+c2 → 안 되는 이유 : 요소별로 따로 접근해야 함.
	c3.real = c1.real + c2.real;
	c3.imag = c1.imag + c2.imag;
	//멤버 변수 접근 : 구조체 변수 이름.멤버 변수 이름

	printf("c3 = %f + j%f\n", c3.real, c3.imag);

	//구조체 포인터 활용
	Complex *ptr1;
	ptr1 = &c3;
	ptr1->real = 10.0;
	ptr1->imag = 20.0;
	//멤버 접근 : 구조체 포인터 변수 이름->멤버 변수 이름
	printf("c3 = %f + j%f\n", c3.real, c3.imag);

	//구조체가 매개변수인 함수 선언.
	c3 = c1;
	printComplexVar(c3); //구조체 자체가 스택에 저장됨.(공간을 많이 차지함)
	printComplex(&c3); //구조체의 포인터가 스택에 저장됨.(주소값으로 접근하기 때문에 상대적으로 공간 차지가 적다.)
	//따라서 C언어에서 효율적인 프로그래밍을 위해서는 포인터형 함수를 활용하는 것이 효율적이다.

	//동적 할당
	c3 = addComplexReturnVar(&c1,&c2);
	printComplex(&c3);

	ptr1 = addComplex(&c1,&c2);
	printComplex(ptr1);
	free(ptr1); //heap 공간 소멸(동적 할당 시 필수적인 작업.)

}