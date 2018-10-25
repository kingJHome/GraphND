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

//访问图，并寻找关结点
void DFSArticul(ALGraph *g,int v,int *ct,int *min,int *visited){
	*ct += 1;
	int minl = *ct;
	visited[v] = *ct;

	for(ArcLink *p = g->vertices[v].firstarc; p; p = p->nextarc){
		if( !visited[p->adjvex] ){
			DFSArticul(g,p->adjvex,ct,min,visited);
			if( min[p->adjvex] < minl ){
				minl = min[p->adjvex];
			}
			if( min[p->adjvex] >= visited[v] ){
				printf("%c ", g->vertices[v].data);
			}
		}else if( visited[p->adjvex] < minl){
			minl = visited[p->adjvex];
		}
	}

	min[v] = minl;
}

//找到关节点
void FindArticul(ALGraph *g){
	if( g && g->vexnum ){
		int vt,
			count = 1,
			min[g->vexnum],
			visited[g->vexnum];
		ArcLink *p = g->vertices[0].firstarc;
		vt = p->adjvex;
	
		visited[0] = 1;
		for(int i = 1; i < g->vexnum; ++i){
			visited[i] = 0;
		}
		DFSArticul(g,vt,&count,min,visited);
		if(count < g->vexnum){
			printf("%c ", g->vertices[0].data);
			while(p->nextarc){
				p = p->nextarc;
				vt = p->adjvex;
				if( !visited[vt] ){
					DFSArticul(g,vt,&count,min,visited);
				}
			}
		}
	}
}
