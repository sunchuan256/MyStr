#define IncludeTheEnd 1
#define NIncludeTheEnd 0
#define LENGTH(array) (sizeof(array)/sizeof(array[0]))
#define INFRONT 2
#define BEHIND 3
#define ERROR_NO_STR 12
#define SUCCESS 100
#define _CRT_SECURE_NO_WARNINGS
#define FAIL 0
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

//注意:这个函数使用时不会把文件指示器移动到原来的位置
char* FileMoveStr(file* _Stream, int EndInput, int DecideEnd)
{
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

// 获取文件大小的函数,放心,函数调用完后会把文件指示器放回原位
size_t getFileSize(file* fp)
{
	size_t pointer = ftell(fp);

	size_t file_size = 0;

	fseek(fp, 0, SEEK_END);

	file_size = ftell(fp);

	fseek(fp, pointer, SEEK_SET);

	return file_size;

}

// 在文件中搜索字符串的函数,返回值为该字符串到文件开头的距离,放心,这个函数调用完后会把文件指示器移动到原位
size_t searchstr(file* fp, const char* str, int front_OR_behind, size_t which_str)
{
	//错误
	if (which_str < 1)
	{
		return 0;
	}
	//如果输入的字符串大于文件大小
	if (strlen(str) > getFileSize(fp))
	{
		return 0;
	}

	//记录文件指示器刚刚开始的位置
	size_t pointer = ftell(fp);
	//文件指示器归零
	fseek(fp, 0, SEEK_SET);
	//获取文件大小
	size_t file_size = getFileSize(fp);
	//申请一块文件大小的内存区域
	char* buffer = (char*)malloc(file_size + 1);
	//申请内存失败
	if (buffer == NULL)
	{
		return 0;
	}

	buffer[file_size] = '\0';
	char* buffer_free = buffer;
	//把数据读入缓冲区
	fread(buffer, file_size, 1, fp);
	fseek(fp, pointer, SEEK_SET);//文件指示器复位
	//搜索字符串
	for (size_t i = 0; i < which_str; i++)
	{
		buffer = strstr(buffer, str);
		if (buffer == NULL)
		{
			//没找到字符串
			free(buffer_free);
			return 0;
		}
		//移动指针用于继续搜索
		buffer += 1;
	}
	//-1是因为为了搜索,buffer偏移了1位
	buffer -= 1;
	if (front_OR_behind == INFRONT)
	{
		size_t temp = file_size - strlen(buffer);
		free(buffer_free);
		return temp;
	}
	else if (front_OR_behind == BEHIND)
	{
		size_t temp = file_size - strlen(buffer) + strlen(str);
		free(buffer_free);
		return temp;
	}
	else
	{
		free(buffer_free);
		return 0;
	}
}

//这个函数用来替换文件中的指定字符串
int replaceStr(file* stream, const char* str1, const char* str2, size_t which_str)
{
	fseek(stream, 0, SEEK_SET);//文件指示器归0
	size_t file_size = getFileSize(stream);//获取要读取的文件大小

	size_t str_place = searchstr(stream, str1, INFRONT, which_str);//获取要被替换的字符串位置
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

//这是一个用于统计文件中某个字符串出现次数的函数
size_t filestrnum(file* fp, const char* str)
{
	//获取文件指示器当前位置
	size_t pointer = ftell(fp);
	//文件指示器归零
	fseek(fp, 0, SEEK_SET);
	//获取文件大小
	size_t file_size = getFileSize(fp);
	//如果输入的字符串大小大于文件大小
	if (strlen(str) > file_size)
	{
		return 0;
	}
	//申请缓冲区
	char*buffer =  malloc(file_size + 1);
	if (buffer == NULL)
	{
		return 0;
	}
	buffer[file_size] = '\0';
	char* buffer_free = buffer;
	//读入数据
	fread(buffer, file_size, 1, fp);
	fseek(fp, pointer, SEEK_SET);//文件指示器复位
	//统计字符串
	size_t i = 0;
	while (1)
	{
		buffer = strstr(buffer, str);
		if (buffer == NULL)
		{
			break;
		}
		i++;
		buffer += 1;
	}
	free(buffer_free);
	return i;

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

//此函数搜索文件指示器后面相应的字符串,并且返回该字符串到文件开头的距离,放心,这个函数调用完后文件指示器会回归原位
size_t searchBehPoiStr(file* fp, const char* str, int front_OR_behind, size_t which_str)
{
	//获取文件指示器当前位置
	size_t pointer = ftell(fp);
	//获取文件大小
	size_t file_size = getFileSize(fp);
	//计算文件指示器后面的数据大小
	size_t behind_size = file_size - pointer;
	//申请一块内存
	char* behind_buffer = (char*)malloc(behind_size + 1);
	behind_buffer[behind_size] = '\0';
	fread(behind_buffer, behind_size, 1, fp);//读入数据
	fseek(fp, pointer, SEEK_SET);//文件指示器复位
	char* behind_free = behind_buffer;
	//搜索字符串
	for (size_t i = 0; i < which_str; i++)
	{
		behind_buffer = strstr(behind_buffer, str);
		if (behind_buffer == NULL)
		{
			free(behind_free);
			return 0;
		}
		behind_buffer += 1;
	}
	behind_buffer -= 1;
	
	if (front_OR_behind == INFRONT)
	{
		size_t temp = behind_size - strlen(behind_buffer) + pointer;
		free(behind_free);
		return temp;
	}
	else if (front_OR_behind == BEHIND)
	{
		size_t temp = behind_size - strlen(behind_buffer) + pointer + strlen(str);
		free(behind_free);
		return temp;
	}
	else
	{
		//error
		return 0;
	}
}

//此函数功能是替换两段字符串之间的字符串,以第一组字符串的位置为准,第二组字符串只可以在第一组后面
void between_write(file* fp, const char* str1, const char* str2, const char* write_str, size_t which_str)
{
	//获取文件大小
	size_t file_size = getFileSize(fp);
	//获取文件指示器位置
	size_t pointer = ftell(fp);

	//替换前
	char* temp0 = (char*)malloc(file_size + 1);
	temp0[file_size] = '\0';
	fread(temp0, file_size, 1, fp);
	printf("替换前:%s\n", temp0);



	//搜索两个字符串的位置,以第一组字符串的位置为准,第二组字符串只可以在第一组后面
	size_t str1_position = searchstr(fp, str1, BEHIND, which_str);
	printf("str1_position(behind) = %zd\n", str1_position);
	//移动文件指示器便于搜索在str1之后的str2
	fseek(fp, str1_position, SEEK_SET);
	size_t str2_position = searchBehPoiStr(fp, str2, INFRONT, 1);
	printf("str2_position(front) = %zd\n", str2_position);
	fseek(fp, pointer, SEEK_SET);//文件指示器复位
	//如果没有找到字符串
	/*if (str1_position == 0 || str2_position == 0)
	{
		return 0;
	}*/
	//如果两个字符串重叠
	/*if (str1_position == str2_position)
	{
		return 0;
	}*/
	fseek(fp, str2_position, SEEK_SET);//文件指示器移动到str2前面
	//读入str2及其后面的数据
	size_t behind_str2_size = file_size - str2_position;
	char* behind_str2 = (char*)malloc(behind_str2_size + 1);
	behind_str2[behind_str2_size] = '\0';
	fread(behind_str2, behind_str2_size, 1, fp);
	//写入要替换的字符串以及str2及其之后的数据
	fseek(fp, str1_position, SEEK_SET);//文件指示器移动到str1后面
	fwrite(write_str, strlen(write_str), 1, fp);
	fwrite(behind_str2, strlen(behind_str2), 1, fp);;
	//再次获取当前文件大小,并重新读取文件数据
	size_t file_size2 = getFileSize(fp);
	fseek(fp, 0, SEEK_SET);//文件指示器再次移动到开头便于读取数据
	char* temp1 = (char*)malloc(file_size2 + 1);
	temp1[file_size] = '\0';
	fread(temp1, file_size, 1, fp);
	printf("替换后:%s\n", temp1);
	//return 0;
}


/*
 *                    _ooOoo_
 *                   o8888888o
 *                   88" . "88
 *                   (| -_- |)
 *                    O\ = /O
 *                ____/`---'\____
 *              .   ' \\| |// `.
 *               / \\||| : |||// \
 *             / _||||| -:- |||||- \
 *               | | \\\ - /// | |
 *             | \_| ''\---/'' | |
 *              \ .-\__ `-` ___/-. /
 *           ___`. .' /--.--\ `. . __
 *        ."" '< `.___\_<|>_/___.' >'"".
 *       | | : `- \`.;`\ _ /`;.`/ - ` : | |
 *         \ \ `-. \_ __\ /__ _/ .-` / /
 * ======`-.____`-.___\_____/___.-`____.-'======
 *                    `=---='
 *
 * .............................................
 *          佛祖保佑             永无BUG
 */
