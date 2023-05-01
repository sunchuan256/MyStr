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

//@sun_x_chuan123版权所有,请认真遵循开源协议，谢谢

//特别感谢(赞助人):@---乐达---

//这个函数会从相应的文件流中读取数据，并储存在一个相应大小的char数组中，并返回指向这个数组的指针

char* FileMoveStr(FILE* _Stream, int EndInput, int DecideEnd);

long int searchStr(FILE* stream, const char* input, int front_OR_behind,size_t which_str);

long int getFileSize(FILE* fp);

int replaceStr(FILE* stream, const char* str1, const char* str2, size_t which_str);

int replaceAllStr(FILE* stream, const char* str1, const char* str2);

size_t filestrnum(FILE* stream, const char* str);
//该函数库只提供这6个函数
//这个库是为了将来mc启动器而打造

#endif