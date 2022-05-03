#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int **matrix;
int linha = 0, coluna = 0, matrix_size;
int sum_all, max_line = 0;
void *line_sum(void *arg);

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; 

int main() {
    int linha = 0, coluna = 0;

    printf("Matrix Size: ");
    scanf("%d",&matrix_size);

    matrix = malloc(sizeof(int*) * matrix_size);
    
    for(int i = 0; i < matrix_size; i++){
      matrix[i] = malloc(sizeof(int) * matrix_size);
    }
    printf("Matrix Values:\n");
    for(coluna = 0; coluna < matrix_size; coluna++){
      for(linha = 0; linha < matrix_size; linha++){
          scanf("%d",&matrix[coluna][linha]);
        }
    }

  pthread_t threads[linha];
	for(int i = 0; i < matrix_size; i++){
		if(pthread_create(&(threads[i]), NULL, line_sum, NULL)){
			printf("A thread %d não foi criada", i);
		}
  }
    
  for(int i = 0; i < matrix_size; i++){
		pthread_join(threads[i], NULL);
	}

  printf("Sum: %d\n", sum_all);
  
    return 0;
}

void *line_sum(void *arg){
  int line_value = 0;
  
  pthread_mutex_lock(&mutex);
  
  for (int i = 0; i < matrix_size; i++){
    line_value += matrix[max_line][i];
  }

  sum_all = sum_all + line_value;
  max_line++;

	pthread_mutex_unlock(&mutex);

  return arg;
}
