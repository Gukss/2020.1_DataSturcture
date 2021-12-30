#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

typedef char element;
//노드 구조체
typedef struct _Node
{
	element data;
	struct Node* next;
	struct Node* prev;
}Node;
//덱 구조체
typedef struct _DequeType
{
	Node* front;
	Node* rear;

}DequeType;
//초기화
void Init(DequeType* D)
{
	D->front = NULL;
	D->rear = NULL;
}
//메모리 가득 찼는지 판별
int Is_Full()
{
	//메모리가 가득 찼을 때 NULL, 1반환
	return ((Node*)malloc(sizeof(Node)) == NULL);
}
//front에서 입력
void Add_Front(DequeType* D, element item)
{
	//Is_Full이 1일 때
	if (Is_Full())
	{
		fprintf(stderr, "메모리가 부족합니다.\n");
	}
	else
	{
		//처음 삽입 할 때
		Node *new_node = (Node*)malloc(sizeof(Node));
		if (D->front->data == NULL)
		{
			
			new_node->data = item;
			new_node->next = NULL;
			new_node->prev = NULL;
			D->front = new_node;
			D->rear = new_node;
		}
		else
		{
			new_node->data = item;
			new_node->next = D->front;
			new_node->prev = NULL;
			
			//두번째 노드라 rear->prev가 NULL
			if (D->rear->prev == NULL)
			{
				D->rear->prev = new_node;
			}
			//세번째 부터 front 만 신경쓰면 된다
			else
			{
				D->front->prev = new_node;
			}
			D->front = new_node;
		}
	}
}
//rear에서 입력
void Add_Rear(DequeType* D, element item)
{
	//Is_Full이 1일 때
	if (Is_Full())
	{
		fprintf(stderr, "메모리가 부족합니다.\n");
	}
	else
	{
		//처음 삽입 할 때
		Node* new_node = (Node*)malloc(sizeof(Node));
		if (D->rear->data == NULL)
		{

			new_node->data = item;
			new_node->next = NULL;
			new_node->prev = NULL;
			D->front = new_node;
			D->rear = new_node;
		}
		//기존에 노드가 있을 때
		else
		{
			new_node->data = item;
			new_node->next = D->front;
			new_node->prev = NULL;

			//두번째 노드라 front->next가 NULL
			if (D->front->next == NULL)
			{
				D->front->next = new_node;
			}
			//세번째 부터 rear 만 신경쓰면 된다
			else
			{
				D->rear->next = new_node;
			}
			D->rear = new_node;
		}
	}
}
//front와 rear가 NULL일 때 1
int Is_Empty(DequeType *D)
{
	return ((D->front == NULL) && (D->rear == NULL));
}
//front에서 출력하고 삭제
element Delete_Front(DequeType* D)
{
	element return_value = NULL;
	if (Is_Empty(&D))
	{
		fprintf(stderr, "덱이 비었습니다.\n");
	}
	else
	{
		//노드가 하나
		Node* temp = NULL;
		if (D->front == D->rear)
		{
			return_value = D->front->data;
			temp = D->front;
			free(temp);
			return return_value;
		}
		//노드가 여러개
		else
		{
			return_value = D->front->data;
			temp = D->front;
			D->front = D->front->next;
			free(temp);
			return return_value;
		}
	}
}
//rear에서 출력하고 삭제
element Delete_Rear(DequeType* D)
{
	element return_value = NULL;
	if (Is_Empty(&D))
	{
		fprintf(stderr, "덱이 비었습니다.\n");
	}
	else
	{
		//노드가 하나
		Node* temp = NULL;
		if (D->front == D->rear)
		{
			return_value = D->rear->data;
			temp = D->rear;
			free(temp);
			return return_value;
		}
		//노드가 여러개
		else
		{
			return_value = D->rear->data;
			temp = D->rear;
			D->rear = D->rear->prev;
			free(temp);
			return return_value;
		}
	}
}
//front에서 출력
element Get_Front(DequeType* D)
{
	element return_value = NULL;
	if (Is_Empty(&D))
	{
		fprintf(stderr, "덱이 비었습니다.\n");
	}
	else
	{
		return D->front->data;
	}
}
//rear에서 출력
element Get_Rear(DequeType* D)
{
	element return_value = NULL;
	if (Is_Empty(&D))
	{
		fprintf(stderr, "덱이 비었습니다.\n");
	}
	else
	{
		return D->rear->data;
	}
}
//회문 판정 함수
int Circular(DequeType *D)
{
	int string_len;
	printf("판정 문자열 길이 입력\n");
	scanf_s("%d", &string_len);
	
	//덱을 문자열 길이만큼 생성하고 문자를 덱에 입력
	printf("문자를 한개씩 입력\n");
	for (int i = 0; i < string_len; i++)
	{
		char letter = NULL;
		getchar();
		scanf_s("%c", &letter);
		Add_Front(&D, letter);
	}
	//문자열 길이의 반만큼 반복(홀수일때 가운데 글자는 관계없다.)
	for (int i = 0; i < (string_len / 2); i++)
	{
		element x = Delete_Front(&D);
		element y = Delete_Rear(&D);
		if (x != y)
		{
			return 0;
		}
	}
}

void main()
{
	DequeType D;
	Init(&D);
	
	if (Circular(&D) == 0)
		printf("회문이 아닙니다.\n");
	else
		printf("회문 입니다.\n");
		
}