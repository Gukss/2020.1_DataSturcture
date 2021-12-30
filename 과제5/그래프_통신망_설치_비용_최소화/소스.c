#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#define _CRT_SECURE_NO_WARNINGS
#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100
//무한대 (연결 없을 때)
#define INF 1000000
#define MAX_NAME 50

typedef struct _GraphType
{
	//정점 개수
	int vertex;
	//간선 개수
	int edge;
	char name[MAX_VERTICES][MAX_NAME];
	int weight[MAX_VERTICES][MAX_VERTICES];
}GraphType;

//시작정점부터 최단경로 거리
int distance[MAX_VERTICES];
//방문한 정점 표시
int found[MAX_VERTICES];
//경로
int path[MAX_VERTICES][MAX_VERTICES] = {NULL};
//가중치 작은 간선과 연결된 정점
int choose(int disetance[], int n, int found[])
{
	int i, min, minpos;
	min = INT_MAX;
	minpos = -1;
	for (i = 0; i < n; i++)
	{
		if ((distance[i] < min) && !found[i])
		{
			min = distance[i];
			minpos = i;
		}
	}
	return minpos;
}

void print_status(GraphType* g)
{
	static int step = 1;
	printf("STEP %d: ", step++);
	printf("distance: ");
	for (int i = 0; i < g->vertex; i++)
	{
		if (distance[i] == INF)
			printf("*");
		else
			printf("%2d ", distance[i]);
	}
	printf("\n");
	printf(" found: ");
	for (int i = 0; i < g->vertex; i++)
		printf("%2d ", found[i]);
	printf("\n\n");
}
//초기화
GraphType init(GraphType g)
{
	int r, c;
	g.vertex = 0;
	g.edge = 0;
	for (r = 0; r < MAX_VERTICES; r++)
	{
		for (c = 0; c < MAX_VERTICES; c++)
		{
			g.weight[r][c] = INF;
			
		}
		strcpy(g.name[r],"");
	}
	return g;
}
//정점삽입
GraphType insert_vertex(GraphType g, int vertex)
{
	char name[MAX_NAME];
	if ((g.vertex) + 1 > MAX_VERTICES)
	{
		fprintf(stderr, "정점 개수 초과");
		return;
	}
	g.vertex = vertex;
	for (int i = 0; i < vertex; i++)
	{
		printf("%d.", i);
		printf("정점 이름 : ");
		scanf_s("%s", name);
		strcpy(g.name[i], name);
	}
	return g;
}
//간선삽입
GraphType insert_edge(GraphType g,int start, int end, int weight)
{
	if (start >= g.vertex || end >= g.vertex)
	{
		fprintf(stderr, "정점 번호 오류");
		return;
	}
	g.weight[start][end] = weight;
	return g;
}

GraphType shortest_path(GraphType g, int start)
{
	int i, u, w;
	//초기화
	for (i = 0; i < g.vertex; i++)
	{
		distance[i] = g.weight[start][i];
		found[i] = FALSE;
		path[i][i] = -1;;
	}
	found[start] = TRUE;
	distance[start] = 0;
	for (i = 1; i < g.vertex; i++)
	{	
		//print_status(g);
		u = choose(distance, g.vertex, found);
		found[u] = TRUE;
		for (w = 0; w < g.vertex; w++)
		{
			if (!found[w])
			{
				if (distance[u] + g.weight[u][w] < distance[w])
				{
					distance[w] = distance[u] + g.weight[u][w];
					if (path[u][start] == NULL)
					{
						path[u][start] = u;
					}
					for(int k = 0 ; k < g.vertex ; k++)
					{
						if ((path[w][k] != -1) && (path[u][k] != -1))
						{
							path[w][k] = path[u][k];
						}
					}
					path[w][u] = w;
				}
			}
		}
	}
	return g;
}

void print_path(GraphType g, int start, int end)
{
		int flag = start;
		while (flag != -1)
		{	
			printf("%s - ", g.name[flag]);
			flag = path[end][flag];
			if (flag == 0)
			{
				printf("%s (으)로 가는 경로가 없습니다.\n", g.name[end]);
				return;
			}
		}
		printf("%d\n", distance[end]);
}

void main()
{
	GraphType g;/* = { 15,26,
		{{"금오공대"},{"옥계동"},{"4공단"},{"2공단"},
		{"구평동"},{"3공단"},{"중리"},{"1공단"},{"신평동"},{"시청"},
		{"구미역"},{"도량동"},{"봉곡동"},{"형곡동"},{"상모동"},},
		{{0,400,INF,800,INF,INF,INF,INF,800,INF,1800,1800,INF,INF,INF},
		{INF,0,200,200,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF},
		{INF,INF,0,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF},
		{INF,INF,INF,0,500,600,INF,INF,INF,INF,INF,INF,INF,INF,INF},
		{INF,INF,INF,INF,0,300,600,INF,INF,INF,INF,INF,INF,INF,INF},
		{INF,INF,INF,INF,INF,0,300,500,INF,INF,INF,INF,INF,INF,INF},
		{INF,INF,INF,INF,INF,INF,0,INF,INF,INF,INF,INF,INF,INF,800},
		{INF,INF,INF,INF,INF,INF,500,0,INF,INF,INF,INF,INF,400,300},
		{INF,INF,INF,INF,INF,300,INF,200,0,300,INF,INF,INF,INF,INF},
		{INF,INF,INF,INF,INF,INF,INF,INF,INF,0,200,INF,INF,200,INF},
		{INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,0,400,500,300,INF},
		{INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,0,200,INF,INF},
		{INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF},
		{INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,0,200},
		{INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,0}} 
		};
		*/
	int vertex_num = 0;
	int edge_num = 0;
	//FILE* fp = fopen("C:\\Temp\\data.bin", "rb");
	//fread(&g, sizeof(g), 1, fp);
	//fclose(fp);

	
	g=init(g);
	printf("정점의 갯수를 입력하시오 : ");
	scanf_s("%d", &vertex_num);
	g=insert_vertex(g, vertex_num);
	printf("간선의 갯수를 입력하시오 : ");
	scanf_s("%d", &g.edge);
	for (int i = 0; i < g.edge; i++)
	{
		int x, y, z;
		printf("시작, 끝, 가중치 : ");
		scanf_s("%d %d %d", &x, &y, &z);
		g=insert_edge(g, x, y, z);
	}
	for (int i = 0; i < g.vertex; i++)
	{
		g=insert_edge(g, i, i, 0);
		printf("%d 입력완료", i);
	}
	
	int start = 0;
	int end=-1;
	while (1)
	{
		printf("시작과 끝을 입력하시오 : ");
		scanf_s("%d %d", &start, &end);
		g=shortest_path(g, start);
		print_path(g, start, end);
	}
}
