#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// função para trocar os valores de dois elementos
void troca(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Selection Sort
void selectionSort(int arr[], int n) {
    // percorre o array até o penúltimo elemento
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;  // defini o menor elemento seja o atual
        // encontra o menor elemento na parte não ordenada
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIdx]) {
                minIdx = j;
            }
        }
        troca(&arr[minIdx], &arr[i]); // troca o menor elemento encontrado com o primeiro elemento da sublista
    }
}

// Insertion Sort
void insertionSort(int arr[], int n) {
    // percorre cada elemento a partir do segundo
    for (int i = 1; i < n; i++) {
        int atual = arr[i]; // guarda o valor atual
        int j = i - 1;
        // Move os elementos maiores que o atual uma posição pra frente
        while (j >= 0 && arr[j] > atual) {
            arr[j + 1] = arr[j];
            j--;
        }
        // insere o atual na posição correta
        arr[j + 1] = atual;
    }
}

// Bubble Sort
void bubbleSort(int arr[], int n) {
    // passa pelo array n-1 vezes
    for (int i = 0; i < n - 1; i++) {
        // move o maior elemento para o final da sublista não ordenada
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                troca(&arr[j], &arr[j + 1]);
            }
        }
    }
}

// juntar duas metades do array, parte do merge sort
void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1; // tamanho do array da esquerda
    int n2 = right - mid;    // tamanho do array da direita
    int L[n1], R[n2];        // arrays temporários

    // copia os elementos do array original para os arrays temporários
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int i = 0; i < n2; i++)
        R[i] = arr[mid + 1 + i];

    // junta os dois arrays temporários de volta para o array original
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // copia os elementos restantes, do array esquerdo
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // copia os elementos restantes, do array direito
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// Merge Sort 
void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        // divide o array em duas metades e ordena recursivamente
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        // junta as duas metades ordenadas
        merge(arr, left, mid, right);
    }
}

// particionar o array em volta de um pivo, para utilizar no quicksort
int partition(int arr[], int low, int high) {
    int pivot = arr[high]; // escolhe o último elemento como pivo
    int i = (low - 1);     // indice do menor elemento

    for (int j = low; j < high; j++) {
        // se o elemento atual é menor que o pivo move o elemento para a posição correta
        if (arr[j] < pivot) { 
            i++;
            troca(&arr[i], &arr[j]); 
        }
    }
    troca(&arr[i + 1], &arr[high]); // coloca o pivo na posição correta
    return (i + 1);
}

// Quick Sort 
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high); // divide o array e pega o indice do pivo
        quickSort(arr, low, pi - 1);        // ordena a sublista da esquerda do pivo
        quickSort(arr, pi + 1, high);       // ordena a sublista da direita do pivo
    }
}

// wrapper para funcionar o quicksort com array inteiro
void quickSortWrapper(int arr[], int n) {
    quickSort(arr, 0, n - 1);
}

// criar um heap máximo
void heapify(int arr[], int n, int i) {
    int largest = i;          // inicializa o maior como raiz
    int left = 2 * i + 1;     // filho da esquerda
    int right = 2 * i + 2;    // filho da direita

    // verifica se o filho da esquerda é maior que a raiz
    if (left < n && arr[left] > arr[largest])
        largest = left;

    // verifica se o filho da direita é maior que o maior atual
    if (right < n && arr[right] > arr[largest])
        largest = right;

    // se o maior não é a raiz, troca e continua ajustando
    if (largest != i) {
        troca(&arr[i], &arr[largest]);
        heapify(arr, n, largest); // recursivamente aplica heapify na subarvores
    }
}

// Heap Sort
void heapSort(int arr[], int n) {
    // faz um heap máximo
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // extrai elementos do heap um por um
    for (int i = n - 1; i >= 0; i--) {
        troca(&arr[0], &arr[i]); // move a raiz para o final do array
        heapify(arr, i, 0);      // aplica heapify na subarvore reduzida
    }
}



void gerarArrayAleatorio(int arr[], int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        arr[i] = rand();
    }
}

void imprimirArray(int arr[], int tamanho) {
    printf("[");
    for (int i = 0; i < tamanho; i++) {
        printf("%d", arr[i]);
        if (i < tamanho - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}

// medir e exibir o tempo de execução de um algoritmo de ordenação
void medirTempo(void (*algoritmo)(int[], int), int arr[], int tamanho, const char *nomeAlgoritmo) {
    int *arrCopia = malloc(tamanho * sizeof(int));
    if (arrCopia == NULL) {
        fprintf(stderr, "Erro ao alocar memória para a cópia do array.\n");
        return;
    }

    for (int i = 0; i < tamanho; i++) arrCopia[i] = arr[i];

    clock_t inicio = clock();
    algoritmo(arrCopia, tamanho);
    clock_t fim = clock();

    double tempoExecucao = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    printf("Tempo de execução do %s para %d elementos: %f segundos\n", nomeAlgoritmo, tamanho, tempoExecucao);

    free(arrCopia);
}

// medir o tempo de execução do Merge Sort, porque que usa parâmetros diferentes
void medirTempoMergeSort(int arr[], int tamanho) {
    int *arrCopia = malloc(tamanho * sizeof(int));
    if (arrCopia == NULL) {
        fprintf(stderr, "Erro ao alocar memória para a cópia do array.\n");
        return;
    }

    for (int i = 0; i < tamanho; i++) arrCopia[i] = arr[i];

    clock_t inicio = clock();
    mergeSort(arrCopia, 0, tamanho - 1);
    clock_t fim = clock();

    double tempoExecucao = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    printf("Tempo de execução do Merge Sort para %d elementos: %f segundos\n", tamanho, tempoExecucao);

    free(arrCopia);
}


int main() {
    srand(time(NULL));

    int tamanhos[5] = {100, 1000, 10000, 50000, 100000};
    for (int i = 0; i < 5; i++) {
        int tamanho = tamanhos[i];
        int *arr = malloc(tamanho * sizeof(int));
        if (arr == NULL) {
            fprintf(stderr, "Erro ao alocar memória para o array de %d elementos.\n", tamanho);
            return 1;
        }

        gerarArrayAleatorio(arr, tamanho);
        printf("\n--- Teste para %d elementos ---\n", tamanho);

        medirTempo(selectionSort, arr, tamanho, "Selection Sort");
        medirTempo(insertionSort, arr, tamanho, "Insertion Sort");
        medirTempo(bubbleSort, arr, tamanho, "Bubble Sort");
        medirTempoMergeSort(arr, tamanho);
        medirTempo(quickSortWrapper, arr, tamanho, "Quick Sort");
        medirTempo(heapSort, arr, tamanho, "Heap Sort");

        free(arr);
    }

    return 0;
}
