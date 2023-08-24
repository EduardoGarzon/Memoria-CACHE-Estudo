#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Funcao para imprimir matriz resultado
void printar(double **m, int l, int c)
{
    for (int i = 0; i < l; i++)
    {
        for (int j = 0; j < c; j++)
        {
            printf("%lf ", m[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// Funcao que cria as matrizes A e B
double **criar_matriz(int l, int c)
{
    double **matriz = malloc(l * sizeof(double *));
    for (int i = 0; i < l; i++)
    {
        matriz[i] = malloc(c * sizeof(double));
    }
    for (int i = 0; i < l; i++)
    {
        for (int j = 0; j < c; j++)
        {
            //matriz[i][j] = (double)(rand() % 10);
            matriz[i][j] = ((double)(rand() % RAND_MAX)) / ((double)(rand() % RAND_MAX));
        }
    }
    return matriz;
}

// Multiplicacao Original
double **multiplicaM1M2(double **m1, double **m2, int l1, int c1, int l2, int c2)
{
    double **matriz = malloc(l1 * sizeof(double *));
    for (int i = 0; i < l1; i++)
    {
        matriz[i] = malloc(c2 * sizeof(double));
    }

    for (int i = 0; i < l1; i++)
    {
        for (int j = 0; j < c2; j++)
        {
            double n = 0;
            for (int k = 0; k < c1; k++)
            {
                n += m1[i][k] * m2[k][j];
            }
            matriz[i][j] = n;
        }
    }
    return matriz;
}

// Funcao para transpor matriz B
double **transpor(double **m2, int l2, int c2)
{
    double **matriz = malloc(l2 * sizeof(double *));
    for (int i = 0; i < l2; i++)
    {
        matriz[i] = malloc(c2 * sizeof(double));
    }
    for (int i = 0; i < l2; i++)
    {
        for (int j = 0; j < c2; j++)
        {
            matriz[i][j] = m2[j][i];
        }
    }
    return matriz;
}

// Multiplicacao Transposta
double **multiplicaM1M2T(double **m1, double **matrizT, int l1, int c1, int lt, int ct)
{
    double **matriz = malloc(l1 * sizeof(double *));
    for (int i = 0; i < l1; i++)
    {
        matriz[i] = malloc(lt * sizeof(double));
    }

    for (int i = 0; i < l1; i++)
    {
        for (int j = 0; j < lt; j++)
        {
            double n = 0;
            for (int k = 0; k < c1; k++)
            {
                n += m1[i][k] * matrizT[j][k];
            }
            matriz[i][j] = n;
        }
    }
    return matriz;
}

int main(int argc[], char *argv[])
{
    srand(time(NULL));
    // tempo de execucao para original e transposta
    float timespent = 0.0;
    // tempo de execucao para M1M2T
    float timeM1M2T = 0.0;
    clock_t begin, end;

    // ./cache l1, c1, l2, c2, method, clock_type
    int l1 = atoi(argv[1]), c1 = atoi(argv[2]), l2 = atoi(argv[3]), c2 = atoi(argv[4]);
    char method = *argv[5], clock_type = *argv[6];
    if (l1 == c2)
    {
        double **m1 = criar_matriz(l1, c1);
        double **m2 = criar_matriz(l2, c2);
        if (clock_type == 'o' || clock_type == 't')
        {
            begin = clock();
        }

        if (method == 'o')
        {
            double **normal = multiplicaM1M2(m1, m2, l1, c1, l2, c2);
        }
        else if (method == 't')
        {
            double **matrizT = transpor(m2, l2, c2);
            if (clock_type == 'n')
            {
                begin = clock();
            }

            double **transposta = multiplicaM1M2T(m1, matrizT, l1, c1, l2, c2);
        }
        end = clock();
        timespent = (float)(((end - begin) + 0.0) / CLOCKS_PER_SEC);
        printf("Time: %fs\n", timespent);
    }
    else
    {
        printf("Parametros Invalidos\n");
    }

    return 0;
}