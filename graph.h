#ifndef _MY_GRAPHND
#define _MY_GRAPHND

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

typedef struct arcLink{
	int adjvex;
	struct arcLink *nextarc;
}ArcLink;

typedef struct vertex{
	char data;
	struct arcLink *firstarc;
}Vertex;

typedef struct alGraph{
	Vertex *vertices;
	int vexnum;
}ALGraph;

//建立头结点
ALGraph* CreateALGraph(char *content);

//添加弧
void AddArcToALGraph(ALGraph *g,char head,char tail);

//找到关节点
void FindArticul(ALGraph *g);
#endif
