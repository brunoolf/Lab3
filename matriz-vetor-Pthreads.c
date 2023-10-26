// Raul Vilhora Cardoso Matias - 32267274
// Bruno Lauand Ferrão - 32217994

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int m, n, thread_count;
int** A;
int* x;
int* y;

void *Pth_mat_vect(void *rank) {
    long my_rank = (long) rank;
    int i, j;
    int local_m = m / thread_count;
    int my_first_row = my_rank * local_m;
    int my_last_row = (my_rank + 1) * local_m - 1;

    for (i = my_first_row; i <= my_last_row; i++) {
        y[i] = 0;
        for (j = 0; j < n; j++) {
            y[i] += A[i][j] * x[j];
        }
    }

    return NULL;
}

int main() {
    printf("Número de threads: ");
    scanf("%d", &thread_count);

    printf("Tamanho de m (número de linhas de A): ");
    scanf("%d", &m);

    printf("Tamanho de n (número de colunas de A e tamanho de X): ");
    scanf("%d", &n);

    A = (int **) malloc(m * sizeof(int *));
    for (int i = 0; i < m; i++) {
        A[i] = (int *) malloc(n * sizeof(int));
        for (int j = 0; j < n; j++) {
            printf("Valor de A[%d][%d]: ", i, j);
            scanf("%d", &A[i][j]);
        }
    }

    x = (int *) malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        printf("Valor de X[%d]: ", i);
        scanf("%d", &x[i]);
    }

    y = (int *) malloc(m * sizeof(int));

    pthread_t *thread_handles;
    thread_handles = (pthread_t *) malloc(thread_count * sizeof(pthread_t));

    for (long thread = 0; thread < thread_count; thread++) {
        pthread_create(&thread_handles[thread], NULL, Pth_mat_vect, (void *) thread);
    }

    for (long thread = 0; thread < thread_count; thread++) {
        pthread_join(thread_handles[thread], NULL);
    }

    printf("\nMatriz A:\n");
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d\t", A[i][j]);
        }
        printf("\n");
    }

    printf("\nMatriz X:\n");
    for (int i = 0; i < n; i++) {
        printf("%d\n", x[i]);
    }

    printf("\nMultiplicação da matriz Y:\n");
    for (int i = 0; i < m; i++) {
        printf("%d\n", y[i]);
    }

    free(thread_handles);
    for (int i = 0; i < m; i++) {
        free(A[i]);
    }
    free(A);
    free(x);
    free(y);

    return 0;
}
