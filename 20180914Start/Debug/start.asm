; Listing generated by Microsoft (R) Optimizing Compiler Version 17.00.50727.1 

	TITLE	C:\Users\216-15\Desktop\2014440108이용준 (2)\20180914Start\start.cpp
	.686P
	.XMM
	include listing.inc
	.model	flat

INCLUDELIB MSVCRTD
INCLUDELIB OLDNAMES

PUBLIC	_main
EXTRN	__RTC_InitBase:PROC
EXTRN	__RTC_Shutdown:PROC
;	COMDAT rtc$TMZ
rtc$TMZ	SEGMENT
__RTC_Shutdown.rtc$TMZ DD FLAT:__RTC_Shutdown
rtc$TMZ	ENDS
;	COMDAT rtc$IMZ
rtc$IMZ	SEGMENT
__RTC_InitBase.rtc$IMZ DD FLAT:__RTC_InitBase
rtc$IMZ	ENDS
; Function compile flags: /Odtp /RTCsu /ZI
; File c:\users\216-15\desktop\2014440108이용준 (2)\20180914start\start.cpp
;	COMDAT _main
_TEXT	SEGMENT
_c$ = -32						; size = 4
_b$ = -20						; size = 4
_a$ = -8						; size = 4
_main	PROC						; COMDAT

; 4    : {

	push	ebp
	mov	ebp, esp
	sub	esp, 228				; 000000e4H
	push	ebx
	push	esi
	push	edi
	lea	edi, DWORD PTR [ebp-228]
	mov	ecx, 57					; 00000039H
	mov	eax, -858993460				; ccccccccH
	rep stosd

; 5    : 	int a,b,c;
; 6    : 	a = 0x12345678;

	mov	DWORD PTR _a$[ebp], 305419896		; 12345678H

; 7    : 	b = 20;

	mov	DWORD PTR _b$[ebp], 20			; 00000014H

; 8    : 	c = a + b;

	mov	eax, DWORD PTR _a$[ebp]
	add	eax, DWORD PTR _b$[ebp]
	mov	DWORD PTR _c$[ebp], eax

; 9    : 
; 10   : 	return 0;

	xor	eax, eax

; 11   : }

	pop	edi
	pop	esi
	pop	ebx
	mov	esp, ebp
	pop	ebp
	ret	0
_main	ENDP
_TEXT	ENDS
END
