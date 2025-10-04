#include <stdio.h>
#include <stdlib.h>
#include <time.h> // usado para medir os tempos de duração do processador
#include <string.h>
// praticamente todos os codigos foram feitos em aula (slides) e exercícios da matéria

// estrutura para métricas
typedef struct
{
    long comparacoes;
    long trocas;
} Metricas;

// funções auxiliares
void trocar(int *a, int *b, Metricas *m)
{
    int temp = *a;
    *a = *b;
    *b = temp;
    m->trocas++;
}

void copiarArray(int *origem, int *destino, int n)
{
    for (int i = 0; i < n; i++)
        destino[i] = origem[i];
}

// bubble Sort
void bubbleSort(int *vet, int n, Metricas *m)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            m->comparacoes++;
            if (vet[j] > vet[j + 1])
            {
                trocar(&vet[j], &vet[j + 1], m);
            }
        }
    }
}

// insertion Sort
void insertionSort(int *vet, int n, Metricas *m)
{
    for (int i = 1; i < n; i++)
    {
        int chave = vet[i];
        int j = i - 1;
        while (j >= 0)
        {
            m->comparacoes++;
            if (vet[j] > chave)
            {
                vet[j + 1] = vet[j];
                m->trocas++;
                j--;
            }
            else
                break;
        }
        vet[j + 1] = chave;
    }
}

// selection Sort
void selectionSort(int *vet, int n, Metricas *m)
{
    for (int i = 0; i < n - 1; i++)
    {
        int min = i;
        for (int j = i + 1; j < n; j++)
        {
            m->comparacoes++;
            if (vet[j] < vet[min])
                min = j;
        }
        if (min != i)
            trocar(&vet[i], &vet[min], m);
    }
}

// merge Sort
void merge(int *vet, int inicio, int meio, int fim, Metricas *m)
{
    int n1 = meio - inicio + 1;
    int n2 = fim - meio;
    int L[n1], R[n2];

    for (int i = 0; i < n1; i++)
        L[i] = vet[inicio + i];
    for (int j = 0; j < n2; j++)
        R[j] = vet[meio + 1 + j];

    int i = 0, j = 0, k = inicio;
    while (i < n1 && j < n2)
    {
        m->comparacoes++;
        if (L[i] <= R[j])
            vet[k++] = L[i++];
        else
        {
            vet[k++] = R[j++];
            m->trocas++;
        }
    }
    while (i < n1)
        vet[k++] = L[i++];
    while (j < n2)
        vet[k++] = R[j++];
}

void mergeSort(int *vet, int inicio, int fim, Metricas *m)
{
    if (inicio < fim)
    {
        int meio = inicio + (fim - inicio) / 2;
        mergeSort(vet, inicio, meio, m);
        mergeSort(vet, meio + 1, fim, m);
        merge(vet, inicio, meio, fim, m);
    }
}

// quick Sort
int particiona(int *vet, int baixo, int alto, Metricas *m)
{
    int pivo = vet[alto];
    int i = baixo - 1;
    for (int j = baixo; j < alto; j++)
    {
        m->comparacoes++;
        if (vet[j] < pivo)
        {
            i++;
            trocar(&vet[i], &vet[j], m);
        }
    }
    trocar(&vet[i + 1], &vet[alto], m);
    return i + 1;
}

void quickSort(int *vet, int baixo, int alto, Metricas *m)
{
    if (baixo < alto)
    {
        int pi = particiona(vet, baixo, alto, m);
        quickSort(vet, baixo, pi - 1, m);
        quickSort(vet, pi + 1, alto, m);
    }
}

// geração de vetores
void gerarAleatorio(int *vet, int n)
{
    for (int i = 0; i < n; i++)
        vet[i] = rand() % (n * 10);
}

void gerarQuaseOrdenado(int *vet, int n)
{
    for (int i = 0; i < n; i++)
        vet[i] = i;
    for (int i = 0; i < n / 10; i++)
    { // pequenas desordens
        int a = rand() % n;
        int b = rand() % n;
        int temp = vet[a];
        vet[a] = vet[b];
        vet[b] = temp;
    }
}

void gerarInverso(int *vet, int n)
{
    for (int i = 0; i < n; i++)
        vet[i] = n - i;
}

// função principal
int main()
{
    srand(time(NULL));
    FILE *arquivo = fopen("resultados.csv", "w"); // salvar os resultados em um arquivo para as criações dos gráficos
    if (!arquivo)
    {
        printf("Erro ao criar o arquivo CSV.\n");
        return 1;
    }

    fprintf(arquivo, "Tipo_Dado,Algoritmo,Tamanho,Tempo(s),Comparacoes,Trocas\n");

    int tamanhos[] = {1000, 5000, 10000, 20000};
    int numTamanhos = sizeof(tamanhos) / sizeof(tamanhos[0]);

    char *tipos[] = {"Aleatorio", "Quase_Ordenado", "Inverso"};

    for (int t = 0; t < 3; t++)
    {
        for (int k = 0; k < numTamanhos; k++)
        {
            int n = tamanhos[k];
            int *base = (int *)malloc(n * sizeof(int));

            // geração do vetor base
            if (strcmp(tipos[t], "Aleatorio") == 0)
                gerarAleatorio(base, n);
            else if (strcmp(tipos[t], "Quase_Ordenado") == 0)
                gerarQuaseOrdenado(base, n);
            else
                gerarInverso(base, n);

            int *copia = (int *)malloc(n * sizeof(int));
            Metricas m;
            clock_t inicio, fim;

            // teste Bubble
            copiarArray(base, copia, n);
            m.comparacoes = m.trocas = 0;
            inicio = clock();
            bubbleSort(copia, n, &m);
            fim = clock();
            fprintf(arquivo, "%s,Bubble,%d,%.6f,%ld,%ld\n", tipos[t], n, (double)(fim - inicio) / CLOCKS_PER_SEC, m.comparacoes, m.trocas);

            // teste Insertion
            copiarArray(base, copia, n);
            m.comparacoes = m.trocas = 0;
            inicio = clock();
            insertionSort(copia, n, &m);
            fim = clock();
            fprintf(arquivo, "%s,Insertion,%d,%.6f,%ld,%ld\n", tipos[t], n, (double)(fim - inicio) / CLOCKS_PER_SEC, m.comparacoes, m.trocas);

            // teste Selection
            copiarArray(base, copia, n);
            m.comparacoes = m.trocas = 0;
            inicio = clock();
            selectionSort(copia, n, &m);
            fim = clock();
            fprintf(arquivo, "%s,Selection,%d,%.6f,%ld,%ld\n", tipos[t], n, (double)(fim - inicio) / CLOCKS_PER_SEC, m.comparacoes, m.trocas);

            // teste Merge
            copiarArray(base, copia, n);
            m.comparacoes = m.trocas = 0;
            inicio = clock();
            mergeSort(copia, 0, n - 1, &m);
            fim = clock();
            fprintf(arquivo, "%s,Merge,%d,%.6f,%ld,%ld\n", tipos[t], n, (double)(fim - inicio) / CLOCKS_PER_SEC, m.comparacoes, m.trocas);

            // teste Quick
            copiarArray(base, copia, n);
            m.comparacoes = m.trocas = 0;
            inicio = clock();
            quickSort(copia, 0, n - 1, &m);
            fim = clock();
            fprintf(arquivo, "%s,Quick,%d,%.6f,%ld,%ld\n", tipos[t], n, (double)(fim - inicio) / CLOCKS_PER_SEC, m.comparacoes, m.trocas);

            free(base);
            free(copia);
        }
    }

    fclose(arquivo);
    printf("Resultados salvos em 'resultados.csv'\n");
    return 0;
}
