/*
#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
//단어배열크기
#define MAX_WORD_SIZE 100
//한 단어가 몇번째 라인에 나왔는지 저장
#define LINE_NUMBER	2000
//한 문장은 255개 문자로 구성
#define MAX 255
int line = 0;

//데이터 형식 element
typedef struct _element
{
	char* word;
	int* Line;
	int count;
}element;
//노드 구조
typedef struct _Node
{
	element* key;
	struct Node* left, * right;
}Node;
//트리 정의
Node* node = NULL;
//비었으면 1
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
//삽입 연산
Node* Insert_Node(Node* node, element* item)
{
	//트리가 공백일 때
	if (Is_Empty(node)) return new_node(item);
	//순환적으로 트리를 내려간다.
	if (Compare(item, node->key) == 0)
	{
		node->key->count++;
		node->key->Line[line] = 1;
	}
	else if (Compare(item, node->key) < 0)
		node->left = Insert_Node(node->left, item);
	else if (Compare(item, node->key) > 0)
		node->right = Insert_Node(node->right, item);
	//루트 포인터 반환
	return node;
}
//파일 읽기
Node* Read_Text(Node *node)
{
	char String[MAX];
	FILE* fp = fopen("Harry.txt", "r");
	if (fp == NULL)
		printf("파일 열기 오류\n");
	while (1)
	{
		//파일을 끝까지 읽었는지 체크
		if (feof(fp) != 0)
			break;
		//한 줄을 읽어 저장
		fgets(String, MAX, fp);
		//한 줄의 길이만큼 반복문
		int len1 = strlen(&String);
		for (int i = 0; i < len1; i++)
		{
			element* e = (element*)malloc(sizeof(element));
			e->Line = (int*)malloc(sizeof(int) * LINE_NUMBER);
			e->word = (char*)malloc(sizeof(char) * MAX_WORD_SIZE);
			e->Line[line] = 1;
			fscanf(fp, "%s", e->word);
			//대문자를 소문자로 변환
			int len2 = strlen(e->word);
			for (int i = 0; i < len2; i++)
			{
				if (e->word[i] >= 65 && e->word[i] <= 90)
				{
					e->word[i] = e->word[i] + 32;
				}
				//문자아닌 구두점 제거
				if ((e->word[i] >= 33 && e->word[i] <= 47 && e->word != 39) || (e->word[i] >= 58 && e->word[i] <= 64) ||
					(e->word[i] >= 91 && e->word[i] <= 95) || (e->word[i] >= 123 && e->word[i] <= 126))
					e->word[i] = NULL;
			}

			node = Insert_Node(node, e);
			//printf("%s ", e.word);
		}
		//한번 돌 때 마다 line 증가
		line++;
	}
	fclose(fp);
	return node;
}
//탐색함수
Node* Search(Node* node, element* item)
{
	while (node != NULL)
	{
		if (Is_Empty(node)) return NULL;
		if (Compare(node->key, item) == 0) return node;
		else if (Compare(item, node->key) < 0) node = node->left;
		else if (Compare(item, node->key) > 0) node = node->right;
	}
	return node;//탐색 실패 했을 때 NULL반환
}
//빈도 높은 단어 찾기
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
//출력 함수
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
//맨 왼쪽 노드찾기
Node* Min_Value_Node(Node* node)
{
	Node* current = node;
	while (current->left != NULL)
		current = current->left;
	return current;
}
//삭제 함수, 키가 저장된 노드 삭제하고 새로운 루트노드 반환
Node* Delete(Node* node, element* item)
{
	if (node == NULL) return node;
	//키가 루트보다 작을 때 ; 왼쪽에 있다.
	if (Compare(item, node->key) < 0)//(item->word < node->key->word)
		node->left = Delete(node->left, item);
	//키가 루트보다 클 때 ; 오른쪽에 있다.
	if (Compare(item, node->key) > 0)//(item->word > node->key->word)
		node->right = Delete(node->left, item);
	//키와 루트가 같을때 ; 삭제
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
		printf("1) txt읽기 2) 출력 3)삭제 4)탐색 5)가장빈도높은단어 0)종료\n");
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
			printf("삭제할 단어 입력 : ");
			fgets(e->word, MAX_WORD_SIZE, stdin);
			e->word = DeleteEnter(e->word);
			node = Delete(node, e);
			break;
		case 4:
			printf("탐색할 단어 입력 : ");
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
			printf("가장 빈도 높은 단어 : ");
			printf("%s", Frequency(node));
		case 0:
			printf("프로그램을 종료합니다.\n");
			break;
		default:
			break;
		}
	}

}
*/