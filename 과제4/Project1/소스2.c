/*
#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
//�ܾ�迭ũ��
#define MAX_WORD_SIZE 100
//�� �ܾ ���° ���ο� ���Դ��� ����
#define LINE_NUMBER	2000
//�� ������ 255�� ���ڷ� ����
#define MAX 255
int line = 0;

//������ ���� element
typedef struct _element
{
	char* word;
	int* Line;
	int count;
}element;
//��� ����
typedef struct _Node
{
	element* key;
	struct Node* left, * right;
}Node;
//Ʈ�� ����
Node* node = NULL;
//������� 1
int Is_Empty(Node* node)
{
	return (node == NULL);
}
int Is_Full()
{
	return ((Node*)malloc(sizeof(Node)) == NULL);
}
int Compare(element* e1, element* e2)
{
	//e1 < e2 : -1
	//e1 == e2 : 0
	//e1 > e2 : 1
	return strcmp(e1->word, e2->word);
}
Node* new_node(element* item)
{
	Node* temp = (Node*)malloc(sizeof(Node));
	temp->key = (element*)malloc(sizeof(element));
	temp->key->Line = (int*)malloc(sizeof(int) * LINE_NUMBER);
	temp->key->word = (char*)malloc(sizeof(char) * MAX_WORD_SIZE);
	strcpy(temp->key->word, item->word);
	temp->left = temp->right = NULL;
	temp->key->count = 1;
	return temp;
}
//���� ����
Node* Insert_Node(Node* node, element* item)
{
	//Ʈ���� ������ ��
	if (Is_Empty(node)) return new_node(item);
	//��ȯ������ Ʈ���� ��������.
	if (Compare(item, node->key) == 0)
	{
		node->key->count++;
		node->key->Line[line] = 1;
	}
	else if (Compare(item, node->key) < 0)
		node->left = Insert_Node(node->left, item);
	else if (Compare(item, node->key) > 0)
		node->right = Insert_Node(node->right, item);
	//��Ʈ ������ ��ȯ
	return node;
}
//���� �б�
Node* Read_Text(Node *node)
{
	char String[MAX];
	FILE* fp = fopen("Harry.txt", "r");
	if (fp == NULL)
		printf("���� ���� ����\n");
	while (1)
	{
		//������ ������ �о����� üũ
		if (feof(fp) != 0)
			break;
		//�� ���� �о� ����
		fgets(String, MAX, fp);
		//�� ���� ���̸�ŭ �ݺ���
		int len1 = strlen(&String);
		for (int i = 0; i < len1; i++)
		{
			element* e = (element*)malloc(sizeof(element));
			e->Line = (int*)malloc(sizeof(int) * LINE_NUMBER);
			e->word = (char*)malloc(sizeof(char) * MAX_WORD_SIZE);
			e->Line[line] = 1;
			fscanf(fp, "%s", e->word);
			//�빮�ڸ� �ҹ��ڷ� ��ȯ
			int len2 = strlen(e->word);
			for (int i = 0; i < len2; i++)
			{
				if (e->word[i] >= 65 && e->word[i] <= 90)
				{
					e->word[i] = e->word[i] + 32;
				}
				//���ھƴ� ������ ����
				if ((e->word[i] >= 33 && e->word[i] <= 47 && e->word != 39) || (e->word[i] >= 58 && e->word[i] <= 64) ||
					(e->word[i] >= 91 && e->word[i] <= 95) || (e->word[i] >= 123 && e->word[i] <= 126))
					e->word[i] = NULL;
			}

			node = Insert_Node(node, e);
			//printf("%s ", e.word);
		}
		//�ѹ� �� �� ���� line ����
		line++;
	}
	fclose(fp);
	return node;
}
//Ž���Լ�
Node* Search(Node* node, element* item)
{
	while (node != NULL)
	{
		if (Is_Empty(node)) return NULL;
		if (Compare(node->key, item) == 0) return node;
		else if (Compare(item, node->key) < 0) node = node->left;
		else if (Compare(item, node->key) > 0) node = node->right;
	}
	return node;//Ž�� ���� ���� �� NULL��ȯ
}
//�� ���� �ܾ� ã��
char Frequency(Node* node)
{
	int top = node->key->count;
	char top_word[MAX_WORD_SIZE];
	if (node != NULL)
	{
		Frequency(node->left);
		if (top < node->key->count)
		{
			top = node->key->count;
			strcpy(top_word, node->key->word);
		}
		Frequency(node->right);
	}
	return top_word;
}
//��� �Լ�
void Display(Node* node)
{
	if (node != NULL)
	{
		Display(node->left);
		printf("%-15s | %-7d | ", node->key->word, node->key->count);
		for (int i = 0; i < LINE_NUMBER; i++)
		{
			if (node->key->Line[i] == 1)
			{
				printf("%3d ", i + 1);
			}
		}
		printf("\n");
		Display(node->right);
	}
}
//�� ���� ���ã��
Node* Min_Value_Node(Node* node)
{
	Node* current = node;
	while (current->left != NULL)
		current = current->left;
	return current;
}
//���� �Լ�, Ű�� ����� ��� �����ϰ� ���ο� ��Ʈ��� ��ȯ
Node* Delete(Node* node, element* item)
{
	if (node == NULL) return node;
	//Ű�� ��Ʈ���� ���� �� ; ���ʿ� �ִ�.
	if (Compare(item, node->key) < 0)//(item->word < node->key->word)
		node->left = Delete(node->left, item);
	//Ű�� ��Ʈ���� Ŭ �� ; �����ʿ� �ִ�.
	if (Compare(item, node->key) > 0)//(item->word > node->key->word)
		node->right = Delete(node->left, item);
	//Ű�� ��Ʈ�� ������ ; ����
	else
	{
		if (node->left == NULL)
		{
			Node* temp = node->right;
			free(node);
			return temp;
		}
		else if (node->right == NULL)
		{
			Node* temp = node->left;
			free(node);
			return temp;
		}
		Node* temp = Min_Value_Node(node->right);
		node->key = temp->key;
		node->right = Delete(node->right, temp->key);
	}
	return node;
}

char* DeleteEnter(char* str)
{
	char* p = str;
	while (*p)p++;
	p--;
	if (*p == '\n') *p = '\0';
	return str;
}

void main()
{
	int select = -1;
	element* e = (element*)malloc(sizeof(element));
	e->word = (char*)malloc(sizeof(char) * MAX_WORD_SIZE);
	while (select != 0)
	{
		printf("1) txt�б� 2) ��� 3)���� 4)Ž�� 5)����󵵳����ܾ� 0)����\n");
		scanf_s(" %d", &select);
		getchar();
		switch (select)
		{
		case 1:
			node = Read_Text(node);
			break;
		case 2:
			printf("=============================================\n");
			printf("words           | count   | line numbers\n");
			printf("---------------------------------------------\n");
			Display(node);
			break;
		case 3:
			printf("������ �ܾ� �Է� : ");
			fgets(e->word, MAX_WORD_SIZE, stdin);
			e->word = DeleteEnter(e->word);
			node = Delete(node, e);
			break;
		case 4:
			printf("Ž���� �ܾ� �Է� : ");
			scanf_s(" %s", e->word);
			//fgets(e->word, sizeof(e->word) + 1, stdin);
			Node* p = Search(node, e);
			printf("%-15s | %-7d | ", p->key->word, p->key->count);
			for (int i = 0; i < LINE_NUMBER; i++)
			{
				if (p->key->Line[i] == 1)
				{
					printf("%3d ", i + 1);
				}
			}
			printf("\n");
		case 5:
			printf("���� �� ���� �ܾ� : ");
			printf("%s", Frequency(node));
		case 0:
			printf("���α׷��� �����մϴ�.\n");
			break;
		default:
			break;
		}
	}

}
*/