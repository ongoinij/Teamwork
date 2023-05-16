#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void  counting_sort(int numbers, int count, int UNIQ){
    FILE *file_get  = fopen("array.txt","r");
    if (file_get == NULL){
        printf("Unhappy");
    }
    int **range_array = (int**) malloc(2*sizeof(int*)); 
    for (int i = 0; i <2; i++){ 
        range_array[i] = (int*) malloc(UNIQ*sizeof(int)); 
    }

    for (int i = 0; i < 2; i++){
        for(int j = 0; j < UNIQ; j++){
            range_array[i][j] = 0;
        }
    }
    int *main_array = (int*) malloc(numbers*sizeof(int));
    int x;
    int i = 0;
    while(fscanf(file_get, "%d ", &x) != EOF){
        main_array[i] = x;
        i++;
    }
    int place = 0;

    for (int i = 0 ; i<UNIQ;i++)
        range_array[1][i] = i;
    double worktime;
    struct timespec start_time, end_time;
    clock_gettime(CLOCK_MONOTONIC, &start_time);
    for (int i = 0 ; i<numbers;i++){
        range_array[0][main_array[i]]++;
    }


    for (int i = 0; i<UNIQ;i++){
        for (int j = 0 ; j<range_array[0][i];j++){
            main_array[place]=range_array[1][i];
            place++;
        }
    }
    clock_gettime(CLOCK_MONOTONIC, &end_time);
    worktime = (end_time.tv_sec - start_time.tv_sec) + (end_time.tv_nsec - start_time.tv_nsec) / 1e9;
    printf("%.7f", worktime);
    printf("\n\n");
    fclose(file_get);
    FILE* file_out=fopen("info.txt","a+");
    fprintf(file_out,"%d %.7f",numbers, worktime);
    if(count != 9){
        fprintf(file_out, "\n");
    }
    free(range_array);
    free(main_array);
    fclose(file_out);
}

int main() {
    int numbers = 900000;
    int UNIQ = 100;
    int number, count = 0;
    FILE* file = fopen("array.txt", "w");
    fclose(file);
    FILE* file_out=fopen("info.txt","w");
    fclose(file_out);
    for (int i =0 ; i<10;i++){
        file = fopen("array.txt", "w");
        srand(time(NULL));

        for(int i = 0; i < numbers; i++){
            number = rand() % UNIQ;
            fprintf(file, "%d ", number);
        }
        fclose(file);
        counting_sort(numbers, count, UNIQ);
        count++;
        UNIQ *=2;
        numbers*=2;
    }
    system("gnuplot -e \"plot 'info.txt' u 1:2 with lines, '' u 1:2 with points; pause -1\" && echo Plot generated successfully");
    return 0;
}