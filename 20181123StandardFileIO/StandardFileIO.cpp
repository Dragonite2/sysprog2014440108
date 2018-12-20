#define _CRT_SECURE_NO_WARNINGS
#define WIN32_LEAN_AND_MEAN
#include <stdio.h> //printf
#include <stdlib.h> //malloc
#include <windows.h>
#include <time.h>

int main()
{
	FILE *fp;
	char buff[] = "느아아아아아아앍!!";
	char rBuff[100];

	fp = fopen("test.txt","r");
	//r : 읽기
	//w : 쓰기(파일이 없을 경우 새 파일 생성)
	if(fp == NULL)
	{
		printf("파일 접근에 오류가 발생함.\n");
		return 0;
	}
6
	//fprintf(fp,"괴성 지르기! : %s\n",buff);
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