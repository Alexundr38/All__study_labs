#include <stdio.h>
#include <regex.h>
#include <stdlib.h>
#include <string.h>

#define BLOCK 20
int scan(char ***massive){
	int flag=0;
        int csnt=0;
        int csmb=0;
	int n=1;
	char symbol;
        while (flag!=1){
                symbol=getchar();
                if (symbol=='\n' || symbol==EOF){
			(*massive)[csnt][csmb]='\n';
			(*massive)[csnt][csmb+1]='\0';
			csmb=0;
			n=1;
			if (strcmp((*massive)[csnt],"Fin.\n")==0){ flag=1; break; }
			csnt++;
			(*massive)=(char **)realloc((*massive),sizeof(char *)*(csnt+1));
			(*massive)[csnt]=(char *)malloc(BLOCK*sizeof(char));
                }else{
			if (strlen((*massive)[csnt])>=BLOCK*n){
				n+=1;
				(*massive)[csnt]=(char *)realloc((*massive)[csnt],BLOCK*n*sizeof(char));
			}
			(*massive)[csnt][csmb]=symbol;
			csmb++;
		}
        }
	return csnt;
}
int main(){
	regex_t reegex;
	char ** massive = (char **)malloc(sizeof(char*));
	massive[0]=(char *)malloc(BLOCK*sizeof(char));
	int csnt=scan(&massive);
	int value;
	value=regcomp(&reegex,"([A-Za-z0-9,_]+)@[A-Za-z0-9,_,-]+\\: ?\\~ ?\\# (.+)\n$",REG_EXTENDED);
	regmatch_t matches[3];
	for (int i=0; i<csnt; i++){
		value=regexec(&reegex,massive[i],3,matches,0);
		int namebeg,nameend,combeg,comend;
		if (value==0){
			namebeg=matches[1].rm_so;
			nameend=matches[1].rm_eo;
			combeg=matches[2].rm_so;
			comend=matches[2].rm_eo;
			printf("%.*s - %.*s\n", nameend-namebeg, massive[i]+namebeg, comend-combeg, massive[i]+combeg);
		}
	}
	regfree(&reegex);
}
