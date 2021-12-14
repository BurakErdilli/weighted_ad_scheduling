
#define MAX 500
#include <stdio.h>
#include <stdlib.h>

struct Advertisement {
    int id;
    int StartTime;
    int Duration;
    int Profit;
};
int max(int a, int b);
int findMaxProfit(struct Advertisement A[], int n);
int cmpfunc(const void *a, const void *b);
int collisionsBinarySearchCheck(struct Advertisement Ads[], int index);

int collisionsBinarySearchCheck(struct Advertisement Ads[], int index) {
    int lo = 0;
    int hi = index - 1;
    int mid;

    while (lo <= hi) {
        mid = (lo + hi) / 2;
        if ((Ads[mid].StartTime + Ads[mid].Duration) <= (Ads[index].StartTime)) {
            if ((Ads[mid + 1].StartTime + Ads[mid + 1].Duration) <= (Ads[index].StartTime)) {
                lo = mid + 1;
            } else {
                return mid;
            }
        } else {
            hi = mid - 1;
        }
    }
    return -1;
}

int cmpfunc(const void *a, const void *b) {
    struct Advertisement *p_a;
    struct Advertisement *p_b;
    p_a = (struct Advertisement *) a;
    p_b = (struct Advertisement *) b;
    return (p_a->StartTime + p_a->Duration - (p_b->StartTime + p_b->Duration));
}

int max(int a, int b) {
    return a > b ? a : b;
}

int findMaxProfit(struct Advertisement *A, int n) {
    qsort(A, n, sizeof(struct Advertisement), cmpfunc);
    int table[n];
    int i, l, inclProf, result, j;
    int data[n][n];
    int index_count[n];
    int check;
    int index;
    table[0] = A[0].Profit;
    index_count[0] = 1;
    data[0][0] = A[0].id;

    for (i = 1; i < n; i++) {
        check = 0;
        inclProf = A[i].Profit;
        l = collisionsBinarySearchCheck(A, i);
        if (l != -1) {
            inclProf += table[l];
            check = 1;
        }

        if (check != 1) {
            index_count[i] = 1;
            data[i][0] = A[i].id;
        }
        else {

            for (j = 0; j < index_count[l]; j++) {
                data[i][j] = data[l][j];
            }
            data[i][j] = A[i].id;
            index_count[i] = j + 1;
        }

        table[i] = max(inclProf, table[i - 1]);
        if (table[i] == inclProf) {
            index = i;
        }
    }

    result = table[i - 1];
    printf("\nAdvertisement indexes that are chosen: ");
    for (i = 0; i < index_count[index]; i++) {
        printf("%d ", data[index][i]);
    }
    return result;
}



int main() {
    struct Advertisement A[MAX];
    char filename[20] = "Sample.txt";
    FILE *fp;
    fp = fopen(filename, "r");
    int i = 0;
    int j;
    if (fp == NULL) {
        printf("unable to open the file");
        return -1;
    } else {
        printf("All the data in the file->> %s  \n\n", filename);
        while (3 == fscanf(fp, "%d %d %d", &A[i].StartTime, &A[i].Duration, &A[i].Profit)) {
            printf("Advertisement %d ---> (StartTime ,Duration ,Profit)  (%d , %d ,%d)  \n", i + 1, A[i].StartTime,
                   A[i].Duration, A[i].Profit);
            A[i].id = i + 1;
            i++;
        }
        fclose(fp);
        printf("\n\nSorting by finishTimes.. \n\n");
        qsort(A, i, sizeof(struct Advertisement), cmpfunc);
        for (j = 0; j < i; ++j) {
            printf("id:%d \t%d \t%d \t%d \n", A[j].id, A[j].StartTime, A[j].Duration, A[j].Profit);
        }
        printf("\n\nMaximum profit: %d.\n ", findMaxProfit(A, i));
        return 0;
    }
}