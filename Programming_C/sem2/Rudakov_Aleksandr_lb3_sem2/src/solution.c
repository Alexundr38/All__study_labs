#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <regex.h>

#define BLOCK 20

typedef struct nameList{
    char *name;
    struct nameList *next;
    struct nameList *previous;
} nameList;

nameList *createPath(char *name, nameList *next, nameList *previous){
    nameList *new_dir=(nameList *)malloc(sizeof(nameList));
    new_dir->name=name;
    new_dir->next=next;
    new_dir->previous=previous;
    return new_dir;
}

nameList *appendPath(char *name, nameList *next, nameList *previous){
    nameList *new_dir=(nameList *)malloc(sizeof(nameList));
    new_dir->name=name;
    new_dir->next=next;
    new_dir->previous=previous;
    new_dir->previous->next=new_dir;
    return new_dir;
}

nameList *removeDir(nameList *directory){
    directory=directory->previous;
    free(directory->next);
    directory->next=NULL;
    return directory;
}

char *create_path(nameList *file_path){
    while (file_path->previous!=NULL){
        file_path=file_path->previous;
    }
    
    char *output=NULL;
    int size=0;
    
    while (file_path!=NULL){
        if (output==NULL){
            size=strlen(file_path->name)+2;
            output=(char *)malloc(sizeof(char)*size);
            strcpy(output,file_path->name);
        } else {
            size=strlen(output)+strlen(file_path->name)+2;
            output=(char *)realloc(output,sizeof(char)*size);
            strcat(output,file_path->name);
        }
        output[size-2]='/';
        output[size-1]='\0';
        file_path=file_path->next;
    }

    output[size-2]='\0';
    return output;
}

void find_file(char letter, DIR *dp, nameList *file_path, int *flag, FILE * output_file){
    struct dirent *dirp;
    
    regex_t reegex;
    int value = regcomp(&reegex, "(.+)\\.txt$",REG_EXTENDED);
    regmatch_t matches[2];
    
    int flag1=0;
    
    while(flag1==0 && *flag==0){
        dirp=readdir(dp);
        if (dirp==NULL){
            flag1=1;
            break;
        }

        if ((strcmp(dirp->d_name, ".") != 0 && strcmp(dirp->d_name, "..") != 0)){
            value=regexec(&reegex,dirp->d_name,2,matches,0);
            if (value==0){
                if ((matches[1].rm_eo-matches[1].rm_so)==1){
                    if (letter==dirp->d_name[0]){
                        file_path=appendPath(dirp->d_name,NULL,file_path);
                        fprintf(output_file,"%s\n",create_path(file_path));
                        *flag=1;
                    }
                }
            } else{
                file_path=appendPath(dirp->d_name,NULL,file_path);
                
                char *directory=create_path(file_path);
                DIR *dp1;
                
                dp1=opendir(directory);
                find_file(letter,dp1,file_path,flag,output_file);
                
                closedir(dp1);
                file_path=removeDir(file_path);
            }
        }
    }
}

int main(){
    DIR *dp;
    char *directory=(char *)malloc(sizeof(char)*5);
    directory="./tmp";
    dp=opendir(directory);
    
    nameList *file_path=createPath(directory, NULL, NULL);
    
    char *input=malloc(sizeof(char)*BLOCK);
    char c='0';
    int count=0;
    
    while ((c!='\n') && (c!=EOF)){
        c=getchar();
        if (count%BLOCK==BLOCK-1){
            input=(char *)realloc(input,sizeof(char)*(count+1+BLOCK));
        }
        input[count]=c;
        count++;
    }
    count--;
    input[count]='\0';
    
    FILE* output_file;
    output_file=fopen("result.txt","w");

    int f=0;
    int *flag=&f;
    
    for (int i=0; i<count; i++){
        find_file(input[i],dp,file_path,flag,output_file);
        closedir(dp);
        *flag=0;
        dp=opendir(directory);
    }
}