#define IncludeTheEnd 1
#define NIncludeTheEnd 0
#define LENGTH(array) (sizeof(array)/sizeof(array[0]))
#define INFRONT 2
#define BEHIND 3
#define ERROR_NO_STR 12
#define SUCCESS 100
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef FILE file;
//char* TempReadFile(file* stream, size_t StrLength);
struct node
{
	char data;
	struct node* PtrToNextNode;
};

struct node* head = NULL;

void AddNode(struct node** PtrToHead, char InputData)
{
	struct node* PtrToNewNode = NULL;
	PtrToNewNode = (struct node*)malloc(sizeof(struct node));
	//(PtrToNewNode->PtrToNextNode) = NULL;
	PtrToNewNode->data = InputData;
	if ((*PtrToHead) == NULL)
	{
		//如果链表为空
		(*PtrToHead) = PtrToNewNode;//插入节点
		(PtrToNewNode->PtrToNextNode) = NULL;
		//fprintf(stdout, "节点添加成功\n");
	}
	else
	{
		//如果链表不为空
		struct node* PtrToEnd = NULL;
		PtrToEnd = (*PtrToHead);
		//移动到链表的尾部
		while (PtrToEnd->PtrToNextNode != NULL)
		{
			PtrToEnd = (PtrToEnd->PtrToNextNode);
		}
		PtrToEnd->PtrToNextNode = PtrToNewNode;
		PtrToNewNode->PtrToNextNode = NULL;
		//fprintf(stdout, "节点添加成功(链表不为空)\n");
	}
}

void PrintfAllNodes(struct node* Head)
{
	struct node* TempPtrANode = Head;
	while (TempPtrANode != NULL)
	{
		fprintf(stdout, "%c", TempPtrANode->data);
		TempPtrANode = TempPtrANode->PtrToNextNode;
	}
}

void DeleteAllNodes(struct node** PtrToHead)
{
	struct node* PtrANode = *PtrToHead;
	while (PtrANode != NULL)
	{
		struct node* TempPtrANode = PtrANode;
		PtrANode = PtrANode->PtrToNextNode;
		free(TempPtrANode);
	}
	*PtrToHead = NULL; // 将头节点置为 NULL
}

size_t NodeNumber(struct node* Head)
{
	size_t Number = 0;
	struct node* TempPtrToANode = Head;
	while (TempPtrToANode != NULL)
	{
		Number++;
		TempPtrToANode = TempPtrToANode->PtrToNextNode;
	}

	return Number;
}

void TransferStr(char* str, struct node* Head)
{
	struct node* TempPtrANode = Head;
	size_t i = 0;
	while (TempPtrANode != NULL)
	{
		str[i] = TempPtrANode->data;
		//移动节点和下标
		i++;
		TempPtrANode = TempPtrANode->PtrToNextNode;
	}
	str[i] = '\0';
}


char* FileMoveStr(FILE* _Stream, int EndInput, int DecideEnd)
{
	//注意:这个函数使用时不会把文件指示器移动到原来的位置
	char ch = 0;
	while (1)
	{
		if ((ch = fgetc(_Stream)) != EndInput)
		{
			AddNode(&head, ch);
		}
		else
		{
			if (DecideEnd == IncludeTheEnd)
			{
				//把input也吃进去
				AddNode(&head, ch);
			}
			else if (DecideEnd == NIncludeTheEnd)
			{
				//不把结尾(也就是input)吃进去
				NULL;
			}
			else
			{
				//error
				fprintf(stdout, "参数传递错误\n");
			}
			break;
		}
		//如果读到文件结尾依然没有找到终止符(EndInput)
		if (ch == EOF)
		{
			break;
			//error;
		}
	}
	//PrintfAllNodes(head);

	char* str_array = (char*)malloc(NodeNumber(head) + 1);

	TransferStr(str_array, head);
	//printf("%s", str_array);
	DeleteAllNodes(&head);//删除整个链表,防止占内存
	return str_array;
}

//这个是旧函数,有问题

//long int getFileSize(FILE* fp) 
//{
//	long size, cur_pos;
//
//	cur_pos = ftell(fp); // 获取当前文件指针所在位置
//	fseek(fp, 0L, SEEK_END); // 将文件指针移动到文件末尾
//	size = ftell(fp); // 获取文件大小
//	fseek(fp, cur_pos, SEEK_SET); // 恢复文件指针位置
//
//	return size;
//}
//
//long int searchStr(FILE* stream, const char* input)
//{
//	FILE* input_stream = stream;//方便操作文件指针
//	char* input_str = input;//方便操作字符串
//
//	//对比文件和字符串的大小,如果输入的字符串大于文件的大小则返回0
//	if (strlen(input_str) > getFileSize(input_stream))
//	{
//		return 0;
//	}
//
//	input_str[strlen(input)] = '\0';//给字符串一个结尾
//
//	long int file_pointer = ftell(input_stream);//记录文件指示器当前的位置
//
//	size_t i = 0;//i用来迭代
//
//	while (1)
//	{
//		int end = 0;
//		char* temp = (char*)malloc(strlen(input_str) + 1);
//		//处理内存分配失败的错误
//		if (temp == NULL)
//		{
//			return 0;
//		}
//		temp[strlen(input_str)] = '\0';//给字符串一个结尾
//		end = fread(temp, strlen(input_str), 1, input_stream);//从文件中读取数据
//
//		fseek(input_stream, i, SEEK_SET);
//
//		//如果搜索到了字符串
//		if (strcmp(temp, input_str) == 0)
//		{
//			fseek(input_stream, file_pointer, SEEK_SET);
//			free(temp);
//			return (i + strlen(temp));
//		}
//
//		//如果已经达到文件末尾还没有读取到相应的字符串
//		if (end == 0)
//		{
//			fseek(input_stream, file_pointer, SEEK_SET);
//			free(temp);
//			return 0;
//		}
//
//		free(temp);
//
//		i++;
//
//		fseek(input_stream, 0, SEEK_SET);
//	}
//	fseek(input_stream, file_pointer, SEEK_SET);
//}


// 获取文件大小的函数
long int getFileSize(FILE* fp)
{
	long int size = 0;

	long int file_pointer = ftell(fp);

	// 将文件指针移到文件末尾
	fseek(fp, 0L, SEEK_END);

	// 获取文件大小
	size = ftell(fp);

	// 将文件指针移到原来的位置
	fseek(fp, file_pointer, SEEK_SET);

	return size;
}

// 在文件中搜索字符串的函数
long int searchStr(FILE* stream, const char* input, int front_OR_behind, size_t which_str)
{
	// 获取文件指针的当前位置
	long int file_pointer = ftell(stream);

	// 获取文件大小
	long int file_size = getFileSize(stream);

	// 如果输入字符串的长度大于文件大小，则返回 0
	if (strlen(input) > file_size)
	{
		fseek(stream, file_pointer, SEEK_SET);
		return 0;
	}

	// 将文件指针移到文件开头
	fseek(stream, 0L, SEEK_SET);

	// 动态分配一个缓冲区，并将文件中的数据读入到缓冲区中
	char* buffer = (char*)malloc(file_size + 1);

	// 如果分配内存失败，则返回 0
	if (buffer == NULL) 
	{
		fseek(stream, file_pointer, SEEK_SET);
		return 0;
	}

	fread(buffer, file_size, 1, stream);

	// 在缓冲区中添加字符串结尾符
	buffer[file_size] = '\0';

	// 在缓冲区中搜索输入字符串
	char* ptr = strstr(buffer, input);

	// 如果没有找到输入字符串，则返回 0
	if (ptr == NULL) 
	{
		fseek(stream, file_pointer, SEEK_SET);
		free(buffer);
		return 0;
	}

	// 找到输入字符串后，继续查找后面的匹配字符串
	for (size_t i = 1; i < which_str; i++)
	{
		// 计算当前匹配字符串的位置
		long int position = ptr - buffer;

		// 移动指针到当前匹配字符串的结尾位置
		ptr += strlen(input);

		// 继续在剩余的缓冲区中查找匹配字符串
		ptr = strstr(ptr, input);

		// 如果没有找到，则返回 0
		if (ptr == NULL) 
		{
			fseek(stream, file_pointer, SEEK_SET);
			free(buffer);
			return 0;
		}
	}

	// 计算输入字符串在文件中的位置
	long int position = ptr - buffer;

	// 将文件指针移到原来的位置
	fseek(stream, file_pointer, SEEK_SET);

	// 释放缓冲区的内存
	free(buffer);

	// 返回匹配项的位置
	if (front_OR_behind == INFRONT)
	{
		return position + file_pointer;
	}
	else if (front_OR_behind == BEHIND)
	{
		return position + file_pointer + strlen(input);
	}
	else
	{
		return 0;
		//error
	}
}

////这个函数用来替换文件中的指定字符串,问题比较大
//void replaceStr(file* stream, const char* str1, const char* str2, size_t which_str)
//{
//	long int pointer = ftell(stream);//获取文件指针当前的位置
//
//	//获取要被替换的字符串后面的位置
//	char* file_BehindPointer = searchStr(stream, str1, BEHIND, which_str);
//
//	fseek(stream, file_BehindPointer, SEEK_SET);//移动到要被替换的字符串后面的位置
//	
//	//把要被替换的字符串后面的数据读取了
//	char* Behind_data = FileMoveStr(stream, EOF, IncludeTheEnd);
//
//	long int file_infrontPointer = searchStr(stream, str1, INFRONT, which_str);//获取要被替换的字符串前面的位置
//
//	//移动到被替换的字符串前面的位置
//	fseek(stream, file_infrontPointer, SEEK_SET);
//
//	fwrite(str2, strlen(str2), 1, stream);//写入想要的字符串
//
//	fwrite(Behind_data, strlen(Behind_data), 1, stream);//写入后面的数据
//
//	fseek(stream, pointer, SEEK_SET);
//}



//这个函数用来替换文件中的指定字符串
int replaceStr(file* stream, const char* str1, const char* str2, size_t which_str)
{
	fseek(stream, 0, SEEK_SET);//文件指示器归0
	size_t file_size = (size_t)getFileSize(stream);//获取要读取的文件大小

	long int str_place = searchStr(stream, str1, INFRONT, which_str);//获取要被替换的字符串位置
	//没找到字符串
	if (str_place == 0)
	{
		return ERROR_NO_STR;
	}
	fseek(stream, str_place, SEEK_SET);//移动到要被替换的字符串前面

	fseek(stream, str_place + strlen(str1), SEEK_SET);//移动到被替换的字符串后面

	char* buffer = FileMoveStr(stream, EOF, NIncludeTheEnd);//读取后面的文件
	
	fseek(stream, str_place, SEEK_SET);//移动到被替换的字符串前面

	fwrite(str2, strlen(str2), 1, stream);

	fwrite(buffer, strlen(buffer), 1, stream);

	free(buffer);

	fseek(stream, 0, SEEK_SET);//文件指示器归0

	return SUCCESS;
}

//计算文件中包含指定字符串的个数
//
//@param stream 文件指针
//
//@param str 指定字符串
//
//@return 包含指定字符串的个数

size_t filestrnum(FILE* stream, const char* str)
{
	long int pointer = ftell(stream); // 记录文件指示器当前位置
	fseek(stream, 0, SEEK_SET); // 文件指示器归位

	size_t inspect;
	size_t i = 0;
	size_t strnum = 0;
	char* buffer = (char*)malloc(strlen(str) + 1); // 分配缓冲区
	buffer[strlen(str)] = '\0';

	while (1)
	{
		inspect = fread(buffer, strlen(str), 1, stream);
		if (inspect == 0)
		{
			break;
		}

		// 如果找到了相应的字符串
		if (strcmp(buffer, str) == 0)
		{
			strnum++;
		}
		fseek(stream, i, SEEK_SET);
		i++;
	}

	free(buffer);
	fseek(stream, pointer, SEEK_SET); // 恢复文件指示器

	return strnum;
}


int replaceAllStr(file* stream, const char* str1, const char* str2)
{
	int inspect = 0;
	size_t strnum = filestrnum(stream, str1);
	size_t i = 1;
	//只要还有字符串，就一直循环
	while (i <= strnum)
	{
		replaceStr(stream, str1, str2, i);
		replaceStr(stream, str1, str2, i - 1);
		replaceStr(stream, str1, str2, i + 1);
		i++;
	}
	return SUCCESS;
}