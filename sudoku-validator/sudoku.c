#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/types.h>

#define SIZE 9

int sudoku[SIZE][SIZE] = {
    {5,3,4,6,7,8,9,1,2},
    {6,7,2,1,9,5,3,4,8},
    {1,9,8,3,4,2,5,6,7},
    {8,5,9,7,6,1,4,2,3},
    {4,2,6,8,5,3,7,9,1},
    {7,1,3,9,2,4,8,5,6},
    {9,6,1,5,3,7,2,8,4},
    {2,8,7,4,1,9,6,3,5},
    {3,4,5,2,8,6,1,7,9}
};

int valid[27];

typedef struct{
    int row;
    int col;
    int index;
} Parameters;

void* checkRow(void* arg){
    Parameters*  data = (Parameters*) arg;
    
    int r = data->row;
    int c = data->col;
    int ind = data->index;
    int vis[10] = {0};
    for(int i = 0 ; i < SIZE ; i++){
        int val = sudoku[r][i];
        if(val <= 0 || val > 9 || vis[val]){
            valid[ind] = 0;
            pthread_exit(NULL); 
        }
        vis[val] = 1;
    }
    valid[ind] = 1;
    pthread_exit(NULL);
}

void* checkCol(void *arg){
    Parameters* data = (Parameters*) arg;
    
    int r = data->row;
    int c = data->col;
    int ind = data->index;
    int vis[10] = {0};
    for(int i = 0 ; i < SIZE ; i++){
        int val = sudoku[i][c];
        if(val <= 0 || val > 9 || vis[val]){
            valid[ind] = 0;
            pthread_exit(NULL);
        }
        vis[val] = 1;
    }
    valid[ind] = 1;
    pthread_exit(NULL);
}

void* checkGrid(void *arg){
    Parameters* data = (Parameters*) arg;

    int r = data->row;
    int c = data->col;
    int ind = data->index;
    int vis[10] = {0};
    for(int i = r ; i < r+3 ; i++){
        for(int j = c ; j < c+3 ; j++){
            int val = sudoku[i][j];
            if(val <= 0 || val > 9 || vis[val]){
                valid[ind] = 0;
                pthread_exit(NULL);
            }
            vis[val] = 1;
        }
    }
    valid[ind] = 1;
    pthread_exit(NULL);
}

int main(int argc, char* argv[]){
    pthread_t threads[27];
    int threadNo = 0;
    //ROWS
    for(int i = 0 ; i < SIZE ; i++){
        Parameters* data = malloc(sizeof(Parameters));
        data->row = i;
        data->index = threadNo;
        pthread_create(&threads[threadNo], NULL, checkRow, (void*) data);
        threadNo++;
    }
    //COLUMN
    for(int i = 0 ; i < SIZE ; i++){
        Parameters* data = malloc(sizeof(Parameters));
        data->col = i;
        data->index = threadNo;
        pthread_create(&threads[threadNo], NULL, checkCol, (void*) data);
        threadNo++;
    }
    //GRID
    for(int r = 0 ; r < SIZE ; r+= 3){
        for(int c = 0 ; c < SIZE ; c+=3){
        Parameters* data = malloc(sizeof(Parameters));
        data->row = r;
        data->col = c;
        data->index = threadNo;
        pthread_create(&threads[threadNo], NULL, checkGrid, (void*) data);
        threadNo++;
        }
    }

    //Lets wait till the threads complete
    for(int i = 0 ; i < 27 ; i++){
        pthread_join(threads[i],NULL);
    }

    //Checking for Result
    for(int i = 0 ; i < 27 ; i++){
        if(valid[i] == 0){
            printf("Sudoku is Invalid 😁\n");
            return 0;
        }
    }
    printf("Sudoku is Valid 😘\n");
    return 0;
}