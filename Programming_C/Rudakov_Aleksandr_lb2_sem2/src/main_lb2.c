#include <stdlib.h>
#include <stdio.h>
#include <string.h>


// Описание структуры MusicalComposition

typedef struct MusicalComposition{
    char* name;
    char* author;
    int year;
    struct MusicalComposition* next;
    struct MusicalComposition* previous;
}MusicalComposition;

// Создание структуры MusicalComposition

MusicalComposition* createMusicalComposition(char* name, char* author,int year){
    MusicalComposition* Composition = (MusicalComposition*)malloc(sizeof(MusicalComposition));
    Composition->name=name;
    Composition->author=author;
    Composition->year=year;
    return Composition;
}

// Функции для работы со списком MusicalComposition

MusicalComposition* createMusicalCompositionList(char** array_names, char** array_authors, int* array_years, int n){
    MusicalComposition* Composition;
    MusicalComposition* PreviousComposition;
    MusicalComposition* BeginComposition;
    for (int i=0; i<n; i++){
        Composition=createMusicalComposition(array_names[i],array_authors[i],array_years[i]);
        if (i==0){
            Composition->previous=NULL;
            BeginComposition=Composition;
        } else{
            Composition->previous=PreviousComposition;
            Composition->previous->next=Composition;
        }
        PreviousComposition=Composition;
    }
    Composition->next=NULL;
    return BeginComposition;
}

void push(MusicalComposition* head, MusicalComposition* element){
    MusicalComposition* tek=head;
    while (tek->next!=NULL){
        tek=tek->next;
    }
    tek->next=element;
    element->next=NULL;
    element->previous=tek;
}

void removeEl(MusicalComposition* head, char* name_for_remove){
    MusicalComposition* tek=head;
    MusicalComposition* tek2;
    while (tek!=NULL){
        if (strcmp(tek->name,name_for_remove)==0){
            if (tek->previous!=NULL){
                if (tek->next!=NULL){
                    tek->previous->next=tek->next;
                    tek->next->previous=tek->previous;
                } else {
                    tek->previous->next=NULL;
                }
            } else if (tek->next!=NULL){
                tek->next->previous=NULL;
            }
            tek2=tek;
            tek=tek->next;
            free(tek2);
        } else{
            tek=tek->next;
        }
    }
}

int count(MusicalComposition* head){
    int k=1;
    while (head->next!=NULL){
        head=head->next;
        k++;
    }
    return k;
}

void print_names(MusicalComposition* head){
    MusicalComposition* tek=head;
    while (tek!=NULL){
        puts(tek->name);
        tek=tek->next;
    }
}


int main(){
    int length;
    scanf("%d\n", &length);  

    char** names = (char**)malloc(sizeof(char*)*length);
    char** authors = (char**)malloc(sizeof(char*)*length);
    int* years = (int*)malloc(sizeof(int)*length);

    for (int i=0;i<length;i++)
    {
        char name[80];
        char author[80];

        fgets(name, 80, stdin);
        fgets(author, 80, stdin);
        fscanf(stdin, "%d\n", &years[i]);

        (*strstr(name,"\n"))=0;
        (*strstr(author,"\n"))=0;

        names[i] = (char*)malloc(sizeof(char*) * (strlen(name)+1));
        authors[i] = (char*)malloc(sizeof(char*) * (strlen(author)+1));

        strcpy(names[i], name);
        strcpy(authors[i], author);

    }
    MusicalComposition* head = createMusicalCompositionList(names, authors, years, length);
    char name_for_push[80];
    char author_for_push[80];
    int year_for_push;

    char name_for_remove[80];

    fgets(name_for_push, 80, stdin);
    fgets(author_for_push, 80, stdin);
    fscanf(stdin, "%d\n", &year_for_push);
    (*strstr(name_for_push,"\n"))=0;
    (*strstr(author_for_push,"\n"))=0;

    MusicalComposition* element_for_push = createMusicalComposition(name_for_push, author_for_push, year_for_push);

    fgets(name_for_remove, 80, stdin);
    (*strstr(name_for_remove,"\n"))=0;

    printf("%s %s %d\n", head->name, head->author, head->year);
    int k = count(head);

    printf("%d\n", k);
    push(head, element_for_push);

    k = count(head);
    printf("%d\n", k);

    removeEl(head, name_for_remove); 
    print_names(head);

    k = count(head);
    printf("%d\n", k);

    for (int i=0;i<length;i++){
        free(names[i]);
        free(authors[i]);
    }
    free(names);
    free(authors);
    free(years);
 
    return 0;

}
