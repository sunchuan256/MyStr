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
		//�������Ϊ��
		(*PtrToHead) = PtrToNewNode;//����ڵ�
		(PtrToNewNode->PtrToNextNode) = NULL;
		//fprintf(stdout, "�ڵ���ӳɹ�\n");
	}
	else
	{
		//�������Ϊ��
		struct node* PtrToEnd = NULL;
		PtrToEnd = (*PtrToHead);
		//�ƶ��������β��
		while (PtrToEnd->PtrToNextNode != NULL)
		{
			PtrToEnd = (PtrToEnd->PtrToNextNode);
		}
		PtrToEnd->PtrToNextNode = PtrToNewNode;
		PtrToNewNode->PtrToNextNode = NULL;
		//fprintf(stdout, "�ڵ���ӳɹ�(����Ϊ��)\n");
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
	*PtrToHead = NULL; // ��ͷ�ڵ���Ϊ NULL
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
		//�ƶ��ڵ���±�
		i++;
		TempPtrANode = TempPtrANode->PtrToNextNode;
	}
	str[i] = '\0';
}


char* FileMoveStr(FILE* _Stream, int EndInput, int DecideEnd)
{
	//ע��:�������ʹ��ʱ������ļ�ָʾ���ƶ���ԭ����λ��
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
				//��inputҲ�Խ�ȥ
				AddNode(&head, ch);
			}
			else if (DecideEnd == NIncludeTheEnd)
			{
				//���ѽ�β(Ҳ����input)�Խ�ȥ
				NULL;
			}
			else
			{
				//error
				fprintf(stdout, "�������ݴ���\n");
			}
			break;
		}
		//��������ļ���β��Ȼû���ҵ���ֹ��(EndInput)
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
	DeleteAllNodes(&head);//ɾ����������,��ֹռ�ڴ�
	return str_array;
}

//����Ǿɺ���,������

//long int getFileSize(FILE* fp) 
//{
//	long size, cur_pos;
//
//	cur_pos = ftell(fp); // ��ȡ��ǰ�ļ�ָ������λ��
//	fseek(fp, 0L, SEEK_END); // ���ļ�ָ���ƶ����ļ�ĩβ
//	size = ftell(fp); // ��ȡ�ļ���С
//	fseek(fp, cur_pos, SEEK_SET); // �ָ��ļ�ָ��λ��
//
//	return size;
//}
//
//long int searchStr(FILE* stream, const char* input)
//{
//	FILE* input_stream = stream;//��������ļ�ָ��
//	char* input_str = input;//��������ַ���
//
//	//�Ա��ļ����ַ����Ĵ�С,���������ַ��������ļ��Ĵ�С�򷵻�0
//	if (strlen(input_str) > getFileSize(input_stream))
//	{
//		return 0;
//	}
//
//	input_str[strlen(input)] = '\0';//���ַ���һ����β
//
//	long int file_pointer = ftell(input_stream);//��¼�ļ�ָʾ����ǰ��λ��
//
//	size_t i = 0;//i��������
//
//	while (1)
//	{
//		int end = 0;
//		char* temp = (char*)malloc(strlen(input_str) + 1);
//		//�����ڴ����ʧ�ܵĴ���
//		if (temp == NULL)
//		{
//			return 0;
//		}
//		temp[strlen(input_str)] = '\0';//���ַ���һ����β
//		end = fread(temp, strlen(input_str), 1, input_stream);//���ļ��ж�ȡ����
//
//		fseek(input_stream, i, SEEK_SET);
//
//		//������������ַ���
//		if (strcmp(temp, input_str) == 0)
//		{
//			fseek(input_stream, file_pointer, SEEK_SET);
//			free(temp);
//			return (i + strlen(temp));
//		}
//
//		//����Ѿ��ﵽ�ļ�ĩβ��û�ж�ȡ����Ӧ���ַ���
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


// ��ȡ�ļ���С�ĺ���
long int getFileSize(FILE* fp)
{
	long int size = 0;

	long int file_pointer = ftell(fp);

	// ���ļ�ָ���Ƶ��ļ�ĩβ
	fseek(fp, 0L, SEEK_END);

	// ��ȡ�ļ���С
	size = ftell(fp);

	// ���ļ�ָ���Ƶ�ԭ����λ��
	fseek(fp, file_pointer, SEEK_SET);

	return size;
}

// ���ļ��������ַ����ĺ���
long int searchStr(FILE* stream, const char* input, int front_OR_behind, size_t which_str)
{
	// ��ȡ�ļ�ָ��ĵ�ǰλ��
	long int file_pointer = ftell(stream);

	// ��ȡ�ļ���С
	long int file_size = getFileSize(stream);

	// ��������ַ����ĳ��ȴ����ļ���С���򷵻� 0
	if (strlen(input) > file_size)
	{
		fseek(stream, file_pointer, SEEK_SET);
		return 0;
	}

	// ���ļ�ָ���Ƶ��ļ���ͷ
	fseek(stream, 0L, SEEK_SET);

	// ��̬����һ���������������ļ��е����ݶ��뵽��������
	char* buffer = (char*)malloc(file_size + 1);

	// ��������ڴ�ʧ�ܣ��򷵻� 0
	if (buffer == NULL) 
	{
		fseek(stream, file_pointer, SEEK_SET);
		return 0;
	}

	fread(buffer, file_size, 1, stream);

	// �ڻ�����������ַ�����β��
	buffer[file_size] = '\0';

	// �ڻ����������������ַ���
	char* ptr = strstr(buffer, input);

	// ���û���ҵ������ַ������򷵻� 0
	if (ptr == NULL) 
	{
		fseek(stream, file_pointer, SEEK_SET);
		free(buffer);
		return 0;
	}

	// �ҵ������ַ����󣬼������Һ����ƥ���ַ���
	for (size_t i = 1; i < which_str; i++)
	{
		// ���㵱ǰƥ���ַ�����λ��
		long int position = ptr - buffer;

		// �ƶ�ָ�뵽��ǰƥ���ַ����Ľ�βλ��
		ptr += strlen(input);

		// ������ʣ��Ļ������в���ƥ���ַ���
		ptr = strstr(ptr, input);

		// ���û���ҵ����򷵻� 0
		if (ptr == NULL) 
		{
			fseek(stream, file_pointer, SEEK_SET);
			free(buffer);
			return 0;
		}
	}

	// ���������ַ������ļ��е�λ��
	long int position = ptr - buffer;

	// ���ļ�ָ���Ƶ�ԭ����λ��
	fseek(stream, file_pointer, SEEK_SET);

	// �ͷŻ��������ڴ�
	free(buffer);

	// ����ƥ�����λ��
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

////������������滻�ļ��е�ָ���ַ���,����Ƚϴ�
//void replaceStr(file* stream, const char* str1, const char* str2, size_t which_str)
//{
//	long int pointer = ftell(stream);//��ȡ�ļ�ָ�뵱ǰ��λ��
//
//	//��ȡҪ���滻���ַ��������λ��
//	char* file_BehindPointer = searchStr(stream, str1, BEHIND, which_str);
//
//	fseek(stream, file_BehindPointer, SEEK_SET);//�ƶ���Ҫ���滻���ַ��������λ��
//	
//	//��Ҫ���滻���ַ�����������ݶ�ȡ��
//	char* Behind_data = FileMoveStr(stream, EOF, IncludeTheEnd);
//
//	long int file_infrontPointer = searchStr(stream, str1, INFRONT, which_str);//��ȡҪ���滻���ַ���ǰ���λ��
//
//	//�ƶ������滻���ַ���ǰ���λ��
//	fseek(stream, file_infrontPointer, SEEK_SET);
//
//	fwrite(str2, strlen(str2), 1, stream);//д����Ҫ���ַ���
//
//	fwrite(Behind_data, strlen(Behind_data), 1, stream);//д����������
//
//	fseek(stream, pointer, SEEK_SET);
//}



//������������滻�ļ��е�ָ���ַ���
int replaceStr(file* stream, const char* str1, const char* str2, size_t which_str)
{
	fseek(stream, 0, SEEK_SET);//�ļ�ָʾ����0
	size_t file_size = (size_t)getFileSize(stream);//��ȡҪ��ȡ���ļ���С

	long int str_place = searchStr(stream, str1, INFRONT, which_str);//��ȡҪ���滻���ַ���λ��
	//û�ҵ��ַ���
	if (str_place == 0)
	{
		return ERROR_NO_STR;
	}
	fseek(stream, str_place, SEEK_SET);//�ƶ���Ҫ���滻���ַ���ǰ��

	fseek(stream, str_place + strlen(str1), SEEK_SET);//�ƶ������滻���ַ�������

	char* buffer = FileMoveStr(stream, EOF, NIncludeTheEnd);//��ȡ������ļ�
	
	fseek(stream, str_place, SEEK_SET);//�ƶ������滻���ַ���ǰ��

	fwrite(str2, strlen(str2), 1, stream);

	fwrite(buffer, strlen(buffer), 1, stream);

	free(buffer);

	fseek(stream, 0, SEEK_SET);//�ļ�ָʾ����0

	return SUCCESS;
}

//�����ļ��а���ָ���ַ����ĸ���
//
//@param stream �ļ�ָ��
//
//@param str ָ���ַ���
//
//@return ����ָ���ַ����ĸ���

size_t filestrnum(FILE* stream, const char* str)
{
	long int pointer = ftell(stream); // ��¼�ļ�ָʾ����ǰλ��
	fseek(stream, 0, SEEK_SET); // �ļ�ָʾ����λ

	size_t inspect;
	size_t i = 0;
	size_t strnum = 0;
	char* buffer = (char*)malloc(strlen(str) + 1); // ���仺����
	buffer[strlen(str)] = '\0';

	while (1)
	{
		inspect = fread(buffer, strlen(str), 1, stream);
		if (inspect == 0)
		{
			break;
		}

		// ����ҵ�����Ӧ���ַ���
		if (strcmp(buffer, str) == 0)
		{
			strnum++;
		}
		fseek(stream, i, SEEK_SET);
		i++;
	}

	free(buffer);
	fseek(stream, pointer, SEEK_SET); // �ָ��ļ�ָʾ��

	return strnum;
}


int replaceAllStr(file* stream, const char* str1, const char* str2)
{
	int inspect = 0;
	size_t strnum = filestrnum(stream, str1);
	size_t i = 1;
	//ֻҪ�����ַ�������һֱѭ��
	while (i <= strnum)
	{
		replaceStr(stream, str1, str2, i);
		replaceStr(stream, str1, str2, i - 1);
		replaceStr(stream, str1, str2, i + 1);
		i++;
	}
	return SUCCESS;
}