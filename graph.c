#include "graph.h"

//获取字母数目
int getLetterNum(char *content,size_t clen){
	int len = 0;
	
	if( clen ){
		for(size_t i = 0; i < clen; ++i){
			if( isalpha(content[i]) ){
				++len;
			}
		}
	}

	return len;
}

//获取结点位置
int findVerPos(ALGraph *g,char flag){
	int pos = 0;

	for(int i = 0; i < g->vexnum; ++i){
		if( g->vertices[i].data == flag ){
			pos = i;
			break;
		}
	}

	return pos;
}

//插入弧
void addArc(Vertex *vers,int prev,int child){
	ArcLink *cur = vers[prev].firstarc;
	ArcLink *addArc = (ArcLink*)malloc(sizeof(ArcLink));

	if( addArc ){
		addArc->adjvex = child;
		addArc->nextarc = NULL;

		if( !cur ){
			vers[prev].firstarc = addArc;
		}else{
			for( ; cur->nextarc; cur = cur->nextarc);
			cur->nextarc = addArc;
		}
	}
}

//建立头结点
ALGraph* CreateALGraph(char *content){
	size_t clen = strlen(content);
	ALGraph *rt = (ALGraph*)malloc(sizeof(ALGraph));
	int letterNum = getLetterNum(content, clen);

	if( letterNum && rt ){
		rt->vertices = (Vertex*)malloc(letterNum * sizeof(Vertex));

		if( rt->vertices ){
			rt->vexnum = letterNum;
			letterNum = 0;
			for(size_t i = 0; i < clen; ++i){
				if( isalpha(content[i]) ){
					rt->vertices[letterNum].data = content[i];
					rt->vertices[letterNum].firstarc = NULL;
					++letterNum;
				}
			}
		}else{
			free(rt);
			rt = NULL;
		}
	}

	return rt;
}

//添加弧
void AddArcToALGraph(ALGraph *g,char head,char tail){
	int headpos = findVerPos(g, head),
		tailpos = findVerPos(g, tail);

	addArc(g->vertices,headpos,tailpos);
	addArc(g->vertices,tailpos,headpos);
}

//找到关节点
char* FindArticul(ALGraph *g){
}
