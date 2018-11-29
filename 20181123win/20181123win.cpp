// 20181123win.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"


int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_ALL,"");	
	TCHAR *buf = L"hello World 안녕하세요";
	wprintf(L"%s\n",buf);
	return 0;
}

