#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <malloc.h>
#include <math.h>
int top = -1;
int capacity;
int MemoryCapacity;
int RemainMemory;
int Extra = 0;
//배열
typedef struct _Node	
{
	int *data;
	struct _Node* next;
}Node;
//연결
typedef struct _LinkList	
{
	Node* head;
	Node* current;
	Node* tail;
}LinkList;
//초기화, 배열선언
void initi(LinkList *L, int ArraySize, int MemorySize)	
{
	Node* temp = (Node*)malloc(sizeof(Node));
	L->head = temp;
	L->head->data = (int*)malloc(sizeof(int) * ArraySize);
	capacity = ArraySize-1;
	MemoryCapacity = (MemorySize / ArraySize)-1;
	if (MemorySize % ArraySize == 0)
	{
		RemainMemory= -1;
	}
	else
	{
		RemainMemory = (MemorySize % ArraySize);
	}
	L->head->next = NULL;
	L->current = L->head;
	L->tail = L->head;
}
//포화상태
int is_full()		
{
	return (top == capacity - 1);
}

int is_empty()		//공백상태
{
	return (top == -1);
}
//push
int push(LinkList* L, int item)
{	
	//꽉 찼을 때
	if (top == capacity && Extra == 0)
	{
		//메모리 남아있을 때
		if (MemoryCapacity > 0) {
			top = -1;
			Node* newnode = (Node*)malloc(sizeof(Node) * capacity);
			newnode->data = (int*)malloc(sizeof(int) * capacity);
			newnode->data[0] = item;
			(MemoryCapacity)--;
			//tail은 처음 들어왔던 노드로 고정
			L->head->next = newnode;
			if (L->tail->next == NULL)
			{
				L->tail = L->head;
			}
			L->head = newnode;
			L->head->next = NULL;
			(top)++;
		}
		//메모리가 꽉 찼을 때
		else
		{
			//RemindMemory 있을 때
			if (RemainMemory > 0)
			{
				//새로만든다
				top = -1;
				Node* newnode = (Node*)malloc(sizeof(Node) * capacity);
				newnode->data = (int*)malloc(sizeof(int) * RemainMemory);
				newnode->data[0] = item;
				L->head->next = newnode;
				L->head = newnode;
				L->head->next = NULL;
				(top)++;
				RemainMemory--;
				Extra++;
			}
			else
			{
				//꽉 찼을 때
				printf("Memory is full Can't Push %d\n", item);
				return 0;
			}
		}
	}
	//덜 찼을 때
	else
	{
		if (RemainMemory != 0 && top != capacity)
		{
			(top)++;
			L->head->data[top] = item;
		}
		else
		{
			//꽉 찼을 때
			printf("Memory is full Can't Push %d\n", item);
			return 0;
		}
	}
	
}
//출력
/*
void display(LinkList* L)
{
	//tail 와 같은위치에서 시작, 움직이는 current
	L->current = L->tail;
	//연결리스트
	do
	{
		//배열
		if (L->current->next == NULL)
		{
			for (int j = 0; j <= (top); j++)
			{
				//제일 처음 넣은 자료부터 보여준다.
				printf("%d ->", (L->current->data[j]));
			}
		}
		else
		{
			for (int j = 0; j <= (capacity); j++)
			{
				//제일 처음 넣은 자료부터 보여준다.
				printf("%d ->", (L->current->data[j]));
			}
		}
		L->current = L->current->next;
	} while (L->current != L->head);
	printf("\n");
}
*/
//pop
void pop(LinkList* L)
{
	//head 하나만 있을 때
	if (L->tail->next == NULL)
	{
		if (top != -1)
		{
			printf("%d\n", L->head->data[top]);
			//L->head->data[L->head->top] = NULL;
			(top)--;
		}
		else
		{
			fprintf(stderr, "비어있습니다.\n");
		}
	}
	//node가 여러개
	else
	{
		if (top != -1)
		{
			printf("%d\n", L->head->data[top]);
			(top)--;
		}
		//top == -1 배열삭제하고 다음배열 출력
		else
		{
			//tail부터 head하나 전 노드 찾기
			L->current = L->tail;
			while (L->current->next != L->head && L->current->next != NULL)
			{
				L->current = L->current->next;
			}
			L->head = L->current;
			if (L->tail == L->head)
			{
				L->tail->next = NULL;
			}
			top = capacity;
			printf("%d\n", L->head->data[top]);
			(top)--;
		}
	}
}
//peek 삭제 안하고 출력
int peek(LinkList *L)
{
	if (is_empty())//
	{
		fprintf(stderr, "스택 공백\n");
		exit(1);
	}
	else
		return (L->head->data[top]);
}
void main()
{
	LinkList L;
	int MemorySize=0;
	int ArraySize=0;
	printf("Array Memorry size? :");
	scanf_s("%d %d", &ArraySize, &MemorySize);
	initi(&L, ArraySize,MemorySize);
	for (int i = 1; i <= 6; i++)
	{
		push(&L, i);
	}
	printf("--------\n");
	printf("%d\n",peek(&L));
	printf("--------\n");
	/*
	for (int i = 1; i < 1; i++)
	{
		pop(&L);
	}
	*/
	
	
}