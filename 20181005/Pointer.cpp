//**************************************************************
// ����: ������, ����ü, ���� �Ҵ� ����
// ���: ���� ����Ʈ ����� ���� ���� ����
// �����̸�: pointer.cpp
// ������¥: 2018��10��05��
// �ۼ���: �̿���
//************************************************************

#include <stdio.h>
#include <stdlib.h>

//����ü ���� : ���ο� �ڷ���(Type)�� ����� ����.
typedef struct complex{
	double real; //member variable(��� ����)
	double imag;
}Complex; //����ü ������ ;�� ������ ��.
//typedef : (������ Ư�� �ڷ����� ~�� �θ��ڴ�.)

//�Լ� printComplexVar
//�Է� : ���Ҽ�
//��� : ����
//�μ�ȿ��(Side Effect) : ȭ�鿡 ���Ҽ� ���
void printComplexVar(Complex a)
{
	printf("Complex = %f + j%f\n",a.real,a.imag);
}

//�Լ� printComplex
//�Է� : ���Ҽ� ����ü�� ������
//��� : ����
//�μ�ȿ��(Side Effect) : ȭ�鿡 ���Ҽ� ���
void printComplex(Complex *a)
{
	printf("Complex = %f + j%f\n",a->real,a->imag);
}

//�Լ� addComplexReturnVar
//�Է� : 2���� ���Ҽ� ����ü�� ������
//��� : �ջ�� ���Ҽ� ����ü
//�μ�ȿ��(Side Effect) : X
Complex addComplexReturnVar(Complex *ptr1, Complex *ptr2)
{
	Complex ptr;
	ptr.real = ptr1->real + ptr2->real;
	ptr.imag = ptr1->imag + ptr2->imag;

	return ptr;
}

//�Լ� addComplex
//�Է� : 2���� ���Ҽ� ����ü�� ������
//��� : �ջ�� ���Ҽ� ����ü�� ������
//�μ�ȿ��(Side Effect) : X
Complex *addComplex(Complex *ptr1, Complex *ptr2)
{
	//malloc �Լ��� ������ void *malloc �̱� ������ ����ȯ(Casting) ������ �� �ʿ��ϴ�.
	Complex *ptr = (Complex *)malloc(sizeof(Complex)); //���� �Ҵ� ����(Dynamic Memory Allocation)
	ptr->real = ptr1->real + ptr2->real;
	ptr->imag = ptr1->imag + ptr2->imag;

	return ptr;
}
//�Լ� ȣ���� ������ ���� ���� ������ �Ҹ�Ǳ� ������ ����� �۵����� ���� �� �ִ�.(�Լ� ���� ������ ����ϱ� �����̴�.)
//������ ���� ���� ���� �Ҵ��� �̿��Ͽ� ������ �ؾ� ���α׷����� ���迡 ���� �۵��� �� �ִ� ���̴�.

void main()
{
	int a=10,b=20,c=30;

	int *ptr; //������ ���� ����
	ptr = &a; //������ ������ �ּҿ� a������ �ּҸ� ����
	*ptr = b; //ptr ������ ������ ���� b�� ���� ����

	printf("a = %d\n",a);

	//����ü Ȱ��
	Complex c1={1.0,1.0}, c2={2.0,3.0}, c3={4.0,5.5}; //����ü ���� ����
	//c3 = c1+c2 �� �� �Ǵ� ���� : ��Һ��� ���� �����ؾ� ��.
	c3.real = c1.real + c2.real;
	c3.imag = c1.imag + c2.imag;
	//��� ���� ���� : ����ü ���� �̸�.��� ���� �̸�

	printf("c3 = %f + j%f\n", c3.real, c3.imag);

	//����ü ������ Ȱ��
	Complex *ptr1;
	ptr1 = &c3;
	ptr1->real = 10.0;
	ptr1->imag = 20.0;
	//��� ���� : ����ü ������ ���� �̸�->��� ���� �̸�
	printf("c3 = %f + j%f\n", c3.real, c3.imag);

	//����ü�� �Ű������� �Լ� ����.
	c3 = c1;
	printComplexVar(c3); //����ü ��ü�� ���ÿ� �����.(������ ���� ������)
	printComplex(&c3); //����ü�� �����Ͱ� ���ÿ� �����.(�ּҰ����� �����ϱ� ������ ��������� ���� ������ ����.)
	//���� C���� ȿ������ ���α׷����� ���ؼ��� �������� �Լ��� Ȱ���ϴ� ���� ȿ�����̴�.

	//���� �Ҵ�
	c3 = addComplexReturnVar(&c1,&c2);
	printComplex(&c3);

	ptr1 = addComplex(&c1,&c2);
	printComplex(ptr1);
	free(ptr1); //heap ���� �Ҹ�(���� �Ҵ� �� �ʼ����� �۾�.)

}