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
//�迭
typedef struct _Node	
{
	int *data;
	struct _Node* next;
}Node;
//����
typedef struct _LinkList	
{
	Node* head;
	Node* current;
	Node* tail;
}LinkList;
//�ʱ�ȭ, �迭����
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
//��ȭ����
int is_full()		
{
	return (top == capacity - 1);
}

int is_empty()		//�������
{
	return (top == -1);
}
//push
int push(LinkList* L, int item)
{	
	//�� á�� ��
	if (top == capacity && Extra == 0)
	{
		//�޸� �������� ��
		if (MemoryCapacity > 0) {
			top = -1;
			Node* newnode = (Node*)malloc(sizeof(Node) * capacity);
			newnode->data = (int*)malloc(sizeof(int) * capacity);
			newnode->data[0] = item;
			(MemoryCapacity)--;
			//tail�� ó�� ���Դ� ���� ����
			L->head->next = newnode;
			if (L->tail->next == NULL)
			{
				L->tail = L->head;
			}
			L->head = newnode;
			L->head->next = NULL;
			(top)++;
		}
		//�޸𸮰� �� á�� ��
		else
		{
			//RemindMemory ���� ��
			if (RemainMemory > 0)
			{
				//���θ����
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
				//�� á�� ��
				printf("Memory is full Can't Push %d\n", item);
				return 0;
			}
		}
	}
	//�� á�� ��
	else
	{
		if (RemainMemory != 0 && top != capacity)
		{
			(top)++;
			L->head->data[top] = item;
		}
		else
		{
			//�� á�� ��
			printf("Memory is full Can't Push %d\n", item);
			return 0;
		}
	}
	
}
//���
/*
void display(LinkList* L)
{
	//tail �� ������ġ���� ����, �����̴� current
	L->current = L->tail;
	//���Ḯ��Ʈ
	do
	{
		//�迭
		if (L->current->next == NULL)
		{
			for (int j = 0; j <= (top); j++)
			{
				//���� ó�� ���� �ڷ���� �����ش�.
				printf("%d ->", (L->current->data[j]));
			}
		}
		else
		{
			for (int j = 0; j <= (capacity); j++)
			{
				//���� ó�� ���� �ڷ���� �����ش�.
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
	//head �ϳ��� ���� ��
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
			fprintf(stderr, "����ֽ��ϴ�.\n");
		}
	}
	//node�� ������
	else
	{
		if (top != -1)
		{
			printf("%d\n", L->head->data[top]);
			(top)--;
		}
		//top == -1 �迭�����ϰ� �����迭 ���
		else
		{
			//tail���� head�ϳ� �� ��� ã��
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
//peek ���� ���ϰ� ���
int peek(LinkList *L)
{
	if (is_empty())//
	{
		fprintf(stderr, "���� ����\n");
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