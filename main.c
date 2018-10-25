#include <stdio.h>
#include <string.h>
#include "graph.h"

int main(int argc,char *argv[]){
	FILE *fp = fopen("graph.txt","r");

	if( fp ){
		char head,tail,*articuls = NULL;
		ALGraph *algra = NULL;
		char content[100];

		while( fgets(content, 100, fp) ){
			if( strstr(content,"Vertex") == content ){
				algra = CreateALGraph( strchr(content,':')+1 );
			}else if( strstr(content,"Arc") == content ){
				char *temp = strchr(content,':') + 1;
				sscanf(temp,"%c %c\n", &head, &tail);
				AddArcToALGraph(algra, head, tail);
				break;
			}
		}

		while( fscanf(fp,"%c %c\n", &head, &tail) > 0 ){
			AddArcToALGraph(algra, head, tail);
		}
		
		fclose(fp);
		articuls = FindArticul(algra);
		if( articuls ){
			printf("%s\n", articuls);
		}else{
			printf("there is no articuls\n");
		}
	}

	return 0;
}
