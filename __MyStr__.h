#ifndef __MyStr__
#define __MyStr__
#define IncludeTheEnd 1
#define NIncludeTheEnd 0
#define LENGTH(array) (sizeof(array)/sizeof(array[0]))
#define INFRONT 2
#define BEHIND 3
#define ERROR_NO_STR 12
#define SUCCESS 100
#define _CRT_SECURE_NO_WARNINGS

//@sun_x_chuan123��Ȩ����,��������ѭ��ԴЭ�飬лл

//�ر��л(������):@---�ִ�---

//������������Ӧ���ļ����ж�ȡ���ݣ���������һ����Ӧ��С��char�����У�������ָ����������ָ��

char* FileMoveStr(FILE* _Stream, int EndInput, int DecideEnd);

long int searchStr(FILE* stream, const char* input, int front_OR_behind,size_t which_str);

long int getFileSize(FILE* fp);

int replaceStr(FILE* stream, const char* str1, const char* str2, size_t which_str);

int replaceAllStr(FILE* stream, const char* str1, const char* str2);

size_t filestrnum(FILE* stream, const char* str);
//�ú�����ֻ�ṩ��6������
//�������Ϊ�˽���mc������������

#endif