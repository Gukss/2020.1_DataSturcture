#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

typedef char element;
//��� ����ü
typedef struct _Node
{
	element data;
	struct Node* next;
	struct Node* prev;
}Node;
//�� ����ü
typedef struct _DequeType
{
	Node* front;
	Node* rear;

}DequeType;
//�ʱ�ȭ
void Init(DequeType* D)
{
	D->front = NULL;
	D->rear = NULL;
}
//�޸� ���� á���� �Ǻ�
int Is_Full()
{
	//�޸𸮰� ���� á�� �� NULL, 1��ȯ
	return ((Node*)malloc(sizeof(Node)) == NULL);
}
//front���� �Է�
void Add_Front(DequeType* D, element item)
{
	//Is_Full�� 1�� ��
	if (Is_Full())
	{
		fprintf(stderr, "�޸𸮰� �����մϴ�.\n");
	}
	else
	{
		//ó�� ���� �� ��
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
			
			//�ι�° ���� rear->prev�� NULL
			if (D->rear->prev == NULL)
			{
				D->rear->prev = new_node;
			}
			//����° ���� front �� �Ű澲�� �ȴ�
			else
			{
				D->front->prev = new_node;
			}
			D->front = new_node;
		}
	}
}
//rear���� �Է�
void Add_Rear(DequeType* D, element item)
{
	//Is_Full�� 1�� ��
	if (Is_Full())
	{
		fprintf(stderr, "�޸𸮰� �����մϴ�.\n");
	}
	else
	{
		//ó�� ���� �� ��
		Node* new_node = (Node*)malloc(sizeof(Node));
		if (D->rear->data == NULL)
		{

			new_node->data = item;
			new_node->next = NULL;
			new_node->prev = NULL;
			D->front = new_node;
			D->rear = new_node;
		}
		//������ ��尡 ���� ��
		else
		{
			new_node->data = item;
			new_node->next = D->front;
			new_node->prev = NULL;

			//�ι�° ���� front->next�� NULL
			if (D->front->next == NULL)
			{
				D->front->next = new_node;
			}
			//����° ���� rear �� �Ű澲�� �ȴ�
			else
			{
				D->rear->next = new_node;
			}
			D->rear = new_node;
		}
	}
}
//front�� rear�� NULL�� �� 1
int Is_Empty(DequeType *D)
{
	return ((D->front == NULL) && (D->rear == NULL));
}
//front���� ����ϰ� ����
element Delete_Front(DequeType* D)
{
	element return_value = NULL;
	if (Is_Empty(&D))
	{
		fprintf(stderr, "���� ������ϴ�.\n");
	}
	else
	{
		//��尡 �ϳ�
		Node* temp = NULL;
		if (D->front == D->rear)
		{
			return_value = D->front->data;
			temp = D->front;
			free(temp);
			return return_value;
		}
		//��尡 ������
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
//rear���� ����ϰ� ����
element Delete_Rear(DequeType* D)
{
	element return_value = NULL;
	if (Is_Empty(&D))
	{
		fprintf(stderr, "���� ������ϴ�.\n");
	}
	else
	{
		//��尡 �ϳ�
		Node* temp = NULL;
		if (D->front == D->rear)
		{
			return_value = D->rear->data;
			temp = D->rear;
			free(temp);
			return return_value;
		}
		//��尡 ������
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
//front���� ���
element Get_Front(DequeType* D)
{
	element return_value = NULL;
	if (Is_Empty(&D))
	{
		fprintf(stderr, "���� ������ϴ�.\n");
	}
	else
	{
		return D->front->data;
	}
}
//rear���� ���
element Get_Rear(DequeType* D)
{
	element return_value = NULL;
	if (Is_Empty(&D))
	{
		fprintf(stderr, "���� ������ϴ�.\n");
	}
	else
	{
		return D->rear->data;
	}
}
//ȸ�� ���� �Լ�
int Circular(DequeType *D)
{
	int string_len;
	printf("���� ���ڿ� ���� �Է�\n");
	scanf_s("%d", &string_len);
	
	//���� ���ڿ� ���̸�ŭ �����ϰ� ���ڸ� ���� �Է�
	printf("���ڸ� �Ѱ��� �Է�\n");
	for (int i = 0; i < string_len; i++)
	{
		char letter = NULL;
		getchar();
		scanf_s("%c", &letter);
		Add_Front(&D, letter);
	}
	//���ڿ� ������ �ݸ�ŭ �ݺ�(Ȧ���϶� ��� ���ڴ� �������.)
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
		printf("ȸ���� �ƴմϴ�.\n");
	else
		printf("ȸ�� �Դϴ�.\n");
		
}