#define _CRT_SECURE_NO_WARNINGS
#define WIN32_LEAN_AND_MEAN
#include <stdio.h> //printf
#include <stdlib.h> //malloc
#include <windows.h>
#include <time.h>

int main()
{
	FILE *fp;
	char buff[] = "���ƾƾƾƾƾƾ�!!";
	char rBuff[100];

	fp = fopen("test.txt","r");
	//r : �б�
	//w : ����(������ ���� ��� �� ���� ����)
	if(fp == NULL)
	{
		printf("���� ���ٿ� ������ �߻���.\n");
		return 0;
	}
6
	//fprintf(fp,"���� ������! : %s\n",buff);
	fscanf(fp,"%s",rBuff);
	printf("%s\n",rBuff);
	fgets(rBuff,100,(FILE*)fp);
	printf("%s\n",rBuff);
	fgets(rBuff,100,(FILE*)fp);
	printf("%s\n",rBuff);
	fgets(rBuff,100,(FILE*)fp);
	printf("%s\n",rBuff);
	/*
	fscanf(fp,"%s",buff);
	printf("Queen Bohemian Rapsody : %s\n",buff);

	fgets(buff,255,(FILE*)fp);
	printf("2 : %s\n",buff);

	fgets(buff,255,(FILE*)fp);
	printf("3 : %s\n",buff);
	*/
	fclose(fp);

	return EXIT_SUCCESS;
}