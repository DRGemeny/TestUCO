// ������� ��� ����� ������� �1

#ifndef timtest_01
#define timtest_01

//#include <conio.h>

// ������ ������� ������
#define _Fmt_Str "| %08lX | %08lX | %08lX | %08lX | %08lX | %08lX | %08lX | %08lX | %08lX | %08lX |  %c  |\n"

// ������ ��������� �������
#define _Out_Zag " TBeg St  | TBeg Ml   | TEnd St   | TEndMl    | DtZadSt   | DtZadMl   | DtTmrSt   | DtTmrMl   | RaznDtSt  | RaznDtMl  | Sgn \n"

// ������ ������� 11 ����� ��������� �����
#define _Out_Otbivka "\n----------------------------------------------------------------------------------------------------------------------------\n"

// �������� ���������� ����� � ������ ��������� � ���
#define _Open_Header {\
  if ( NULL == ( pTextFile = fopen("Test_Result.txt", "w+") ) )\
    {  printf("Text file opening error.\n");\
       getch();\
	   return 0;\
    }\
  fprintf(pTextFile, _Out_Zag);\
  fflush( NULL );\
} // _Open_Header

// ������ � ���� ������ � 10 ����������, 11-� - ���� ��������
#define _Print_Line( W1, W2, W3, W4, W5, W6, W7, W8, W9, W10, W11 ) {\
  char SignCh;\
  SignCh = ( (W11) ? '+':'-' );\
  /* 1 - '+', 0 - '-' */\
  fprintf(pTextFile, _Fmt_Str, (W1), (W2), (W3), (W4), (W5), (W6), (W7), (W8), (W9), (W10), SignCh);\
  fflush( NULL );\
} // _Print_Line

#endif /* timtest_01 */
