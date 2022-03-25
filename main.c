#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 30

typedef struct Graph{
    struct Node* head[N];
}GRAPH;

typedef struct Node{
    char destination[15];
    struct Node* next;
}NODE;

typedef struct Edge {
    char source[15];
    char destination[15];
    int id;
    int hour;
    int minute;
    int price;
    int src_id;
    int dest_id;
}EDGE;

typedef struct City {
    int id;
    char name[15];
}CITY;

int dosyadanOku(EDGE*);
int sehirID(EDGE*, CITY*, int);
GRAPH* createGraph(EDGE*, int);
void printGraph(GRAPH*, int);
//int ucusListele(EDGE *edges, int, int, int, int ,int[20][20], int, int); //uncomment

int ucusListele(EDGE *edges, int n, int k, int s_id, int d_id, int rapor[20][20], int x, int y){

    int i = 0;
    int j = 0;
    while(i < n && k > 0){
        if(edges[i].src_id == s_id){
            rapor[x][y] = edges[i].id;
            printf("%d-> ", rapor[x][y]);
            if(edges[i].dest_id == d_id){
                x = 0;
                return y++;
            }else{
                y = ucusListele(edges, n, k-1, edges[i].dest_id, d_id, rapor[20][20], x+1, y);
            }
        }
        i++;
    }
    if(k == 0){
        while(i < n){
            if(edges[i].src_id == s_id && edges[i].dest_id == d_id ){
                rapor[x][y] = edges[i].id;
                printf("%d-> ", rapor[x][y]);
                return y++;
            }else{
                i++;
            }
        }
        return y;
    }
}

int main(void){

    int i=0, j;
    int n;
    int city_number;

    EDGE edges[50];

    n = dosyadanOku(edges);
    CITY cities[2*n];

    city_number = sehirID(edges, cities, n);
    GRAPH *graph = createGraph(edges, n);

    printf("\nSehirler ve ID'leri (Isim-ID)\n----------------------------\n");
    for(i = 0; i < city_number; i++){
        printf("%s-%d \n",
               cities[i].name, cities[i].id);
    }

    printf("\nUcuslar ve Bilgileri\n-------------------------\n");
    for (i = 0; i < n; i++) {
        printf("%d No'lu Ucus --->"
               "(%s, %s, %d saat,  %d dakika, %d tl, %d nolu sehirden, %d nolu sehire)  \n", i + 1,
               edges[i].source, edges[i].destination, edges[i].hour,
               edges[i].minute,edges[i].price,
               edges[i].src_id,edges[i].dest_id);
    }

    printGraph(graph, n);

     int k = 2;
     int s_id=0;
     int d_id=2;
     int x=0, y=0;
     int rapor[n][n];
     ucusListele(edges, n, k, s_id, d_id, rapor, x, y);
     for(i = 0; i < n; i++){
         for(j = 0; j < n; j++){
             if(rapor[j][i] != NULL){
                 printf("%s ",edges[rapor[j][i]].destination);
             }
         }

     }

    return 0;
}


int dosyadanOku(EDGE *edges){

    int i = 0;
    char filename[20] = "Sample.txt";
    FILE *fp;
    fp = fopen(filename, "r");
    if (fp != NULL){
        while (5 == fscanf(fp, "%s %s %d %d %d ", &edges[i].source, &edges[i].destination, &edges[i].hour,&edges[i].minute ,&edges[i].price)) {
            edges[i].id = i;
            i++;
        }
        return i;
    }else{
        printf("\nDosya acilamadi!");
        fclose(fp);
        free(fp);
        return -1;
    }
}


int sehirID(EDGE *edges, CITY *cities , int n){

    int i = 0;
    int j = 0;
    int check = 0;
    int count1 = 1;
    int count2 = 2;

    strcpy(cities[0].name, edges[0].source);
    strcpy(cities[1].name, edges[0].destination);

    for(i=0; i < 2; i++)
        cities[i].id = i;

    edges[0].src_id=0;
    edges[0].dest_id=1;
    for(i = 1; i < n; i++){
        while(j < count2){
            if(strcmp(cities[j].name, edges[count1].source) == 0){
                check = 1;
                edges[count1].src_id = cities[j].id;
                j = count2;
            }
            j++;
        }
        if(check == 0){
            strcpy(cities[count2].name, edges[count1].source);
            cities[count2].id = count2;
            edges[count1].src_id = cities[count2].id;
            count2++;
        }
        count1++;
        check = 0;
        j = 0;
    }
    count1 = 1;
    for(i = 1; i < n; i++){
        while(j < count2){
            if(strcmp(cities[j].name, edges[count1].destination) == 0){
                check = 1;
                edges[count1].dest_id = cities[j].id;
                j = count2;
            }
            j++;
        }
        if(check == 0){
            strcpy(cities[count2].name, edges[count1].destination);
            cities[count2].id = count2;
            edges[count1].dest_id = cities[count2].id;
            count2++;
        }
        count1++;
        check = 0;
        j = 0;
    }
    return count2;
}


GRAPH* createGraph(EDGE edges[], int n){
    int i;
    char source[15];
    char destination[15];
    GRAPH* graph = (GRAPH*)malloc(sizeof(GRAPH));

    for (i = 0; i < n; i++) {
        graph->head[i] = NULL;
    }

    for (i = 0; i < n; i++)
    {
        strcpy(source, edges[i].source);
        strcpy(destination, edges[i].destination);

        NODE* newNode = (NODE*)malloc(sizeof(NODE));
        strcpy(newNode->destination, destination);

        newNode->next = graph->head[edges[i].src_id];

        graph->head[edges[i].src_id] = newNode;
    }

    return graph;
}

void printGraph(GRAPH* graph, int n){
    int i;
    for (i = 0; i < n; i++){
        NODE* ptr = graph->head[i];
        while (ptr != NULL){
            printf("\n(%d nolu sehirden-> %s)", i, ptr->destination);
            ptr = ptr->next;
        }
        printf("\n");
    }
}

