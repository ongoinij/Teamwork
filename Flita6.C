#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define UNIQ 2147483647

void quicksort(int* array,int first,int last){
    int i, j, pivot, temp;
    if(first<last){
        pivot=first;
        i=first;
        j=last;
        while(i<j){

            while(array[i]<=array[pivot]&&i<last)
                i++;

            while(array[j]>array[pivot])
                j--;

            if(i<j){
                temp=array[i];
                array[i]=array[j];
                array[j]=temp;
            }

        }

        temp=array[pivot];
        array[pivot]=array[j];
        array[j]=temp;

        quicksort(array,first,j-1);
        quicksort(array,j+1,last);

    }

}
void  good_morning_vietnam(int numbers, int count){
    FILE *file_get  = fopen("array.txt","r");
    if (file_get == NULL){
        printf("Unhappy");
    }

    int* array = (int*) malloc(numbers * sizeof(int));
    int x,i=0;

    while(fscanf(file_get, "%d ", &x) != EOF){
        array[i]=x;
        i++;
    }
    fclose(file_get);

    double worktime;
    struct timespec start_time, end_time;
    clock_gettime(CLOCK_MONOTONIC, &start_time);
    quicksort(array,0,i-1);
    clock_gettime(CLOCK_MONOTONIC, &end_time);
    free(array);
    worktime = (end_time.tv_sec - start_time.tv_sec) + (end_time.tv_nsec - start_time.tv_nsec) / 1e9;

    FILE* file_out=fopen("info.txt","a+");
    fprintf(file_out,"%d %.7f",numbers, worktime);
    if(count != 7){
        fprintf(file_out, "\n");
    }
    fclose(file_out);
}

int main() {

    int numbers = 1771430;
    int file_number,count = 0;
    FILE* file = fopen("array.txt", "w");
    fclose(file);
    FILE* file_out=fopen("info.txt","w");
    fclose(file_out);

    for (int i =0 ; i<8;i++){
        file = fopen("array.txt", "w");
        srand(time(NULL));

        for(int i = 0; i < numbers; i++){
            file_number = rand() % UNIQ;
            fprintf(file, "%d ", file_number );
        }
        fclose(file);


        good_morning_vietnam(numbers, count);

        count++;
        numbers*=2;
    }
    system("gnuplot -e \"plot 'info.txt' u 1:2 with lines, '' u 1:2 with points; pause -1\"");
    return 0;
}