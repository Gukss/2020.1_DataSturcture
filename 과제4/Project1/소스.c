#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
//�ܾ�迭ũ��
#define MAX_WORD_SIZE 100
//�� ������ 255�� ���ڷ� ����
#define MAX 10
//��ǥ��
int line = 1;
//�� ���� ����
char top_word[MAX_WORD_SIZE];
//count(��) ����
int top = 0;
//������ ���� element
typedef struct _element
{
    char word[MAX_WORD_SIZE];
    struct Line* index;
    int count;
}element;
//���μ� �����ϴ� ���Ḯ��Ʈ
typedef struct _Line
{
    int num;
    struct Line* next;
}Line;
//��� ����
typedef struct _Node
{
    element key;
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
int Compare(element e1, element e2)
{
    //e1 < e2 : -1
    //e1 == e2 : 0
    //e1 > e2 : 1
    return strcmp(e1.word, e2.word);
}
Node* new_node(element item)
{
    Node* temp = (Node*)malloc(sizeof(Node));
    strcpy(temp->key.word, &item.word);
    temp->left = temp->right = NULL;
    temp->key.count = 1;
    Line* linetemp = (Line*)malloc(sizeof(Line));
    linetemp->num = line;
    linetemp->next = NULL;
    temp->key.index = linetemp;
    return temp;
}
//���� ����
Node* Insert_Node(Node* node, element item)
{
    //Ʈ���� ������ ��
    if (Is_Empty(node)) return new_node(item);
    //��ȯ������ Ʈ���� ��������.
    if (Compare(item, node->key) == 0)
    {
        node->key.count++;
        Line* flag = node->key.index;
        if (flag->num != line)
        {
            Line* temp = (Line*)malloc(sizeof(Line));
            temp->num = line;
            temp->next = node->key.index;
            node->key.index = temp;
        }
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
    int line_MAX = MAX;
    FILE* fp = fopen("Harry.txt", "r");
    if (fp == NULL)
        printf("���� ���� ����\n");
    while (1)
    {
        //������ ������ �о����� üũ
        if (feof(fp) != 0)
            break;
        if ((line_MAX) <= 0)
        {
            line++;
            line_MAX = MAX;
            continue;
        }
        element e;
        //�ܾ� �о� ����
        fscanf(fp, "%s", e.word);
        //�빮�ڸ� �ҹ��ڷ� ��ȯ
        int len = strlen(&e.word);
        for (int i = 0; i < len; i++)
        {
            if (e.word[i] >= 65 && e.word[i] <= 90)
            {
                e.word[i] = e.word[i] + 32;
            }
            //���ھƴ� ������ ����
            if ((e.word[i] >= 33 && e.word[i] <= 47 && e.word != 39) 
                || (e.word[i] >= 58 && e.word[i] <= 64) ||
                (e.word[i] >= 91 && e.word[i] <= 95) || 
                (e.word[i] >= 123 && e.word[i] <= 126))
                e.word[i] = NULL;
        }
        line_MAX = line_MAX - len;
        node = Insert_Node(node, e);
    }
    fclose(fp);
    return node;
}
//Ž���Լ�
Node* Search(Node* node, element* item)
{
    //Node* e = node;
    while (node != NULL)
    {
        if (Is_Empty(node)) return NULL;
        if (Compare(node->key, *item) == 0) return node;
        else if (Compare(*item, node->key) < 0) return Search(node->left, item);
        else return (node->right, item);//(Compare(*item, node->key) > 0) 
    }
    return node;//Ž�� ���� ���� �� NULL��ȯ
}
//�� ���� �ܾ� ã��
void Frequency(Node* node)
{
    if (node != NULL)
    {
        Frequency(node->left);
        
        if (top < node->key.count)
        {
            top = node->key.count;
            strcpy(top_word, node->key.word);
        }
        Frequency(node->right);
    }
}
//��� �Լ�
void Display(Node* node)
{
    if (node != NULL)
    {
        Display(node->left);
        printf("%-15s | %-7d | ", node->key.word, node->key.count);
        Line* temp = (Line*)malloc(sizeof(Line));
        temp = node->key.index;
        while ((temp) != NULL)
        {
            printf("%3d ", temp->num);
            temp = temp->next;
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
    if (Compare(*item, node->key) < 0)
        node->left = Delete(node->left, item);
    //Ű�� ��Ʈ���� Ŭ �� ; �����ʿ� �ִ�.
    else if (Compare(*item, node->key) > 0)
        node->right = Delete(node->right, item);
    //Ű�� ��Ʈ�� ������ ; ����
    else
    {
        if (node->left == NULL)
        {
            Node* temp = node->right;
            free(node->key.index);
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
        node->right = Delete(node->right, &temp->key);
    }
    return node;
}

void main()
{
    int select = -1;
    char String[MAX_WORD_SIZE];
    element* e = (element*)malloc(sizeof(element));
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
            printf("=============================================\n");
            break;
        case 3:
            printf("������ �ܾ� �Է� : ");
            gets_s(e->word, sizeof(e->word));
            node = Delete(node, e);
            break;
        case 4:
            printf("Ž���� �ܾ� �Է� : ");
            gets_s(e->word, sizeof(e->word));
            Node* p = Search(node, e);
            printf("=============================================\n");
            printf("words           | count   | line numbers\n");
            printf("---------------------------------------------\n");
            printf("%-15s | %-7d | ", p->key.word, p->key.count);
            Line* temp = (Line*)malloc(sizeof(Line));
            temp = p->key.index;
            while ((temp) != NULL)
            {
                printf("%3d ", temp->num);
                temp = temp->next;
            }
            printf("\n");
            printf("=============================================\n");
           
            break;
        case 5:
            printf("���� �� ���� �ܾ� : ");
            Frequency(node);
            printf("%s - %d��\n", top_word, top);
            break;
        case 0:
            printf("���α׷��� �����մϴ�.\n");
            break;
        default:
            break;
        }
    }

}
