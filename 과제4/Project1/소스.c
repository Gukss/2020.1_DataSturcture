#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
//단어배열크기
#define MAX_WORD_SIZE 100
//한 문장은 255개 문자로 구성
#define MAX 10
//줄표시
int line = 1;
//빈도 높은 문자
char top_word[MAX_WORD_SIZE];
//count(빈도) 저장
int top = 0;
//데이터 형식 element
typedef struct _element
{
    char word[MAX_WORD_SIZE];
    struct Line* index;
    int count;
}element;
//라인수 저장하는 연결리스트
typedef struct _Line
{
    int num;
    struct Line* next;
}Line;
//노드 구조
typedef struct _Node
{
    element key;
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
//삽입 연산
Node* Insert_Node(Node* node, element item)
{
    //트리가 공백일 때
    if (Is_Empty(node)) return new_node(item);
    //순환적으로 트리를 내려간다.
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
    //루트 포인터 반환
    return node;
}
//파일 읽기
Node* Read_Text(Node *node)
{
    int line_MAX = MAX;
    FILE* fp = fopen("Harry.txt", "r");
    if (fp == NULL)
        printf("파일 열기 오류\n");
    while (1)
    {
        //파일을 끝까지 읽었는지 체크
        if (feof(fp) != 0)
            break;
        if ((line_MAX) <= 0)
        {
            line++;
            line_MAX = MAX;
            continue;
        }
        element e;
        //단어 읽어 저장
        fscanf(fp, "%s", e.word);
        //대문자를 소문자로 변환
        int len = strlen(&e.word);
        for (int i = 0; i < len; i++)
        {
            if (e.word[i] >= 65 && e.word[i] <= 90)
            {
                e.word[i] = e.word[i] + 32;
            }
            //문자아닌 구두점 제거
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
//탐색함수
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
    return node;//탐색 실패 했을 때 NULL반환
}
//빈도 높은 단어 찾기
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
//출력 함수
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
    if (Compare(*item, node->key) < 0)
        node->left = Delete(node->left, item);
    //키가 루트보다 클 때 ; 오른쪽에 있다.
    else if (Compare(*item, node->key) > 0)
        node->right = Delete(node->right, item);
    //키와 루트가 같을때 ; 삭제
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
            printf("=============================================\n");
            break;
        case 3:
            printf("삭제할 단어 입력 : ");
            gets_s(e->word, sizeof(e->word));
            node = Delete(node, e);
            break;
        case 4:
            printf("탐색할 단어 입력 : ");
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
            printf("가장 빈도 높은 단어 : ");
            Frequency(node);
            printf("%s - %d번\n", top_word, top);
            break;
        case 0:
            printf("프로그램을 종료합니다.\n");
            break;
        default:
            break;
        }
    }

}
