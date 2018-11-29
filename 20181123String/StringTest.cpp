#include <stdio.h>
#include <Windows.h>
#include <locale.h> //유니코드 사용 시 이 헤더가 필요하다.(날짜 표기법, 글자 표기법)

int main()
{
	setlocale(LC_ALL,"");
	WCHAR *b = L"this is a test";
	wchar_t a = L'a';
	wchar_t *str = L"こんにちは / 안녕하세요 / Hello";

	wprintf(L"%s\n",str);
	//유니코드로 동작 시 사용 함수에도 변화가 필요하다.
	//근데 외한글않됌

	return 0;
}