# Análise e Comparação de Algoritmos de Ordenação em C

Este projeto, desenvolvido como parte de exercícios de uma disciplina, implementa e compara o desempenho de cinco algoritmos de ordenação clássicos: **Bubble Sort**, **Insertion Sort**, **Selection Sort**, **Merge Sort** e **Quick Sort**.

O programa foi projetado para medir métricas críticas (tempo de execução, número de comparações e número de trocas) sob diferentes cenários de entrada, salvando os resultados em um arquivo CSV para posterior análise e geração de gráficos.

---

## 🚀 Como Executar

1.  **Compilação:** Compile o código-fonte C (`nome_do_arquivo.c`) usando um compilador C (como GCC):

    ```bash
    gcc comparacoes.c -o nomedesuaescolha
    ```

2.  **Execução:** Execute o programa compilado:

    ```bash
    ./nomedasuaescolha
    ```

3.  **Resultado:** Após a execução, o programa irá gerar o arquivo **`resultados.csv`** no mesmo diretório.

---

## 📊 Estrutura e Saída de Dados

O programa avalia cada algoritmo para os seguintes tamanhos de vetor (`N`): **1000, 5000, 10000, 20000**.

### Cenários de Entrada

Os algoritmos são testados com três tipos de dados para simular diferentes complexidades:

1.  **`Aleatorio`**: Vetor preenchido com números aleatórios.
2.  **`Quase_Ordenado`**: Vetor inicialmente ordenado com pequenas desordens para simular entradas "quase ideais".
3.  **`Inverso`**: Vetor completamente ordenado de forma decrescente (pior caso para muitos algoritmos).

### Arquivo `resultados.csv`

O arquivo de saída contém uma linha para cada combinação de Algoritmo, Tamanho e Tipo de Dados, com as seguintes colunas:

| Coluna        | Descrição                                                              |
| :------------ | :--------------------------------------------------------------------- |
| `Tipo_Dado`   | Aleatorio, Quase_Ordenado ou Inverso.                                  |
| `Algoritmo`   | Bubble, Insertion, Selection, Merge ou Quick.                          |
| `Tamanho`     | Tamanho do vetor (N).                                                  |
| `Tempo(s)`    | Tempo de execução do processador em segundos, medido usando `clock_t`. |
| `Comparacoes` | Número total de comparações realizadas.                                |
| `Trocas`      | Número total de trocas/movimentações de elementos realizadas.          |

---

## 🛠️ Detalhes da Implementação

### Estrutura Central: `Metricas`

É utilizada uma estrutura para encapsular as métricas de desempenho de forma organizada:

```c
typedef struct
{
    long comparacoes;
    long trocas;
} Metricas;
```

## 🛠️ Algoritmos e Funções Auxiliares

### Algoritmos Implementados

O código inclui funções para os seguintes algoritmos de ordenação, todos recebendo o vetor, seu tamanho e um ponteiro para a estrutura `Metricas` para rastrear o desempenho:

- **`bubbleSort`**
- **`insertionSort`**
- **`selectionSort`**
- **`mergeSort`**
- **`quickSort`**

---

### Funções Auxiliares de Geração de Dados

Para garantir a consistência dos testes em diferentes cenários, o código utiliza funções específicas para criar os vetores base:

- **`gerarAleatorio(int *vet, int n)`**: Cria um vetor com valores totalmente aleatórios.
- **`gerarQuaseOrdenado(int *vet, int n)`**: Cria um vetor inicialmente ordenado com pequenas desordens.
- **`gerarInverso(int *vet, int n)`**: Cria um vetor ordenado em ordem decrescente (pior caso para muitos algoritmos).

## 👩‍🚀 Autor

Desenvolvido por Juliano Aureliano. 😊

> **Nota:** Este projeto foi feito para uma atividade prática da unidade
