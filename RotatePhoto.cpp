#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <iostream>
#include "image_processing.cpp"

using namespace std;

void sagaDondur(short n, int resim);
void solaDondur(short n, int resim);

int main(void) {
	int M, N, Q, i, j, k;
	bool type;
	int efile, islem;
	char resimadi[100], sonek[10];
	printf("Isim Soyisim: Mehmet Hayri Cakir\nNumara: 16011023\n");   //Ad-Soyad ve Numara Yazdýrma
	do {
		printf("Islem yapilacak resmin yolunu (path) giriniz:\n-> ");
		scanf("%s", &resimadi);
		system("CLS");
		efile = readImageHeader(resimadi, N, M, Q, type);
	} while (efile > 1);
	printf("%s\n", resimadi);
	int** resim = resimOku(resimadi);

	short *resimdizi;
	resimdizi = (short*) malloc(N*M * sizeof(short));

	for (i = 0; i < N; i++) 
		for (j = 0; j < M; j++) 
			resimdizi[i*N + j] = (short) resim[i][j];

	int resimadres = (int) resimdizi;

	do {
		system("CLS");
		printf("\t     ISLEMLER\n");
		printf("------------------------------------\n");
		printf("1)  Resmi saga dondur\n");
		printf("2)  Resmi sola dondur\n");
		printf("0)  Cikis\n\n");
		printf("\"%s\" yolundaki resim icin yapilacak islemi seciniz\n-> ", resimadi);
		scanf("%d", &islem);
	} while (islem > 2 || islem < 0);

	switch (islem) {
		case 0:
			exit(0);
		case 1:
			sagaDondur(N, resimadres);
			strcpy(sonek, "_sag.pgm");
			break;
		case 2:
			solaDondur(N , resimadres);
			strcpy(sonek, "_sol.pgm");
			break;
		default:
			strcpy(sonek, "_orj.pgm");
			break;
	}

	for (k = 0; k < N * M; k++) {
		j = k % N;
		i = k / N;
		resim[i][j] = (int)resimdizi[k];
	}
	
	string::size_type pos = string(resimadi).find_last_of(".");
	resimadi[pos] = '\0';
	strcat(resimadi, sonek);
	resimYaz(resimadi, resim, N, M, Q);
	printf("\nIslem basariyla tamamlandi :)\n\"%s\" yolunda resim olusturuldu.\n\n", resimadi);
	system("PAUSE");
	return 0;
}

void sagaDondur(short n, int resim) {
	//KODUNUZU BURADAN BASLAYARAK YAZINIZ
	__asm {
//------------------------------------TRANSPOSE KODU BAÞLANGICI-------------------------------------------------------------------------
		XOR ECX,ECX
		XOR ESI,ESI
		MOV EBX,resim
		MOV CX,n
L1: 	MOV EDI,ESI
		MOV AX,n
		CWDE
		MUL ESI
		MOV EDX,EAX
W1:		CMP DI,n
		JNB L1_INC
		CMP SI,DI
		JE DIAGNL 
		PUSH ESI
		PUSH EDI
		MOV AX,n
		CWDE
		PUSH EDX
		MUL EDI
		POP EDX
		ADD ESI,EAX
		ADD EDI,EDX
		SHL ESI,1
		SHL EDI,1
		ADD ESI,EBX
		ADD EDI,EBX
		MOV AX,WORD PTR[ESI]
		XCHG AX,WORD PTR[EDI]
		MOV WORD PTR[ESI],AX
		POP EDI
		POP ESI
DIAGNL:	INC EDI
		JMP W1
L1_INC:	INC ESI
		LOOP L1
//------------------------------------TRANSPOSE KODU BÝTÝÞÝ-----------------------------------------------------------------------------
//------------------------------------exchgCOLS KODU BAÞLANGICI-------------------------------------------------------------------------
		MOV CX,n
		MOV ESI,resim
L3: 	XOR EBX,EBX
		XOR EDI,EDI
		MOV BX,n
		DEC EBX
W3:		CMP DI,BX
		JNB L3_INC
		PUSH EDI
		PUSH EBX
		SHL EDI,1
		SHL EBX,1
		ADD EDI,ESI
		ADD EBX,ESI
		MOV AX,WORD PTR[EBX]
		XCHG AX,WORD PTR[EDI]
		MOV WORD PTR[EBX],AX
		POP EBX
		POP EDI
		INC EDI
		DEC EBX
		JMP W3
L3_INC:	MOV AX,n
		CWDE
		SHL AX,1
		ADD ESI,EAX
		LOOP L3
//------------------------------------exchgCols KODU BÝTÝÞÝ-----------------------------------------------------------------------------
	}
	//KODUNUZU YAZMAYI BURADA BITIRINIZ
}

void solaDondur(short n, int resim) {
	//KODUNUZU BURADAN BASLAYARAK YAZINIZ
	__asm {
//------------------------------------TRANSPOSE KODU BAÞLANGICI-------------------------------------------------------------------------
		XOR ECX,ECX
		XOR ESI,ESI
		MOV EBX,resim
		MOV CX,n
L1: 	MOV EDI,ESI
		MOV AX,n
		CWDE
		MUL ESI
		MOV EDX,EAX
W1:		CMP DI,n
		JNB L1_INC
		CMP SI,DI
		JE DIAGNL 
		PUSH ESI
		PUSH EDI
		MOV AX,n
		CWDE
		PUSH EDX
		MUL EDI
		POP EDX
		ADD ESI,EAX
		ADD EDI,EDX
		SHL ESI,1
		SHL EDI,1
		ADD ESI,EBX
		ADD EDI,EBX
		MOV AX,WORD PTR[ESI]
		XCHG AX,WORD PTR[EDI]
		MOV WORD PTR[ESI],AX
		POP EDI
		POP ESI
DIAGNL:	INC EDI
		JMP W1
L1_INC:	INC ESI
		LOOP L1
//------------------------------------TRANSPOSE KODU BÝTÝÞÝ-----------------------------------------------------------------------------
//------------------------------------exchgRows KODU BAÞLANGICI-------------------------------------------------------------------------
		MOV CX,n
		MOV ESI,resim
L2: 	XOR EBX,EBX
		XOR EDI,EDI	
		MOV BX,n
		DEC EBX
W2:		CMP DI,BX
		JNB L2_INC
		PUSH EDI
		PUSH EBX
		MOV AX,n
		CWDE
		MUL EDI
		MOV EDI,EAX
		MOV AX,n
		CWDE
		MUL EBX
		MOV EBX,EAX
		SHL EDI,1
		SHL EBX,1
		ADD EDI,ESI
		ADD EBX,ESI
		MOV AX,WORD PTR[EBX]
		XCHG AX,WORD PTR[EDI]
		MOV WORD PTR[EBX],AX
		POP EBX
		POP EDI
		INC EDI
		DEC EBX
		JMP W2
L2_INC:	ADD ESI,2
		LOOP L2
//------------------------------------exchgRows KODU BÝTÝÞÝ-----------------------------------------------------------------------------
	}
	//KODUNUZU YAZMAYI BURADA BITIRINIZ
}

