#include <iostream>
#include <ctime>
using namespace std;

//Selection
void selectionSort(int*, int);
unsigned long long selectionSort_step(int*, int);
void Measure_Time_Selection(int*, int, string, double&, unsigned long long&);

//MinMax Selection
void minMaxSelectionSort(int*,int);
unsigned long long min_max_selection_sort_steps(int[],int);
void Measure_Time_MinMaxSelection(int*, int, string, double&, unsigned long long&);

//Merge Sort
void Merge_sort(int[], int, int);
unsigned long long merge_steps(int [], int, int , int );
unsigned long long Merge_sort_steps(int[], int, int);
void Measure_Time_Merge(int*, int, string, double&, unsigned long long&);

//Merge-Insert Sort
void merge(int[],int,int,int);
void mergeInsertionSort(int[],int,int);
unsigned long long merge_insertion_sort_steps(int[],int,int);
void Measure_Time_Merge_insert(int*, int, string, double&, unsigned long long&);

void PrintArr(int[],int);
void randomize(int[],int);
void swap(int*,int*);


int main() {
    int sizes[] = {100,300,500,1000,3000,5000,10000,50000};
    int num_sizes = sizeof(sizes)/sizeof(int);
    cout << "--------------------------------selection Sort--------------------------------" << endl;
    for (int i = 0; i < num_sizes; i++) {
        int size = sizes[i];
        double  avg_time_random = 0;
        unsigned long long  avg_steps_random = 0;
        for (int j = 0; j < 50; j++) {
            int* arr = new int[size];
            for (int k = 0; k < size; k++) {
                arr[k] = k + 1;
            }
            randomize(arr, size);
            Measure_Time_Selection(arr, size, "random generated instance", avg_time_random, avg_steps_random);
            delete[] arr;
        }
        avg_time_random /= 50;
        avg_steps_random /= 50;
        cout << "For input data of size " << size << ":" << endl;
        cout << "  Average CPU time taken by program for random generated instance input is : " << avg_time_random << " microsec " << endl;
        cout << "  Average number of steps taken for random generated instance input is : " << avg_steps_random << endl;
        cout << "--------------------------------------------------------------------------------------" << endl;
    }

    cout << "-----------------------------------MinMaxselection Sort-----------------------------------" << endl;
    for (int i = 0; i < num_sizes; i++){
        int size = sizes[i];
        double  avg_time_random = 0;
        unsigned long long  avg_steps_random = 0;
        for (int j = 0; j < 3; j++){
            int *arr = new int[size];
            for (int k = 0; k < size; k++){
                arr[k] = k + 1 ;
            }
            randomize(arr, size);
            Measure_Time_MinMaxSelection(arr, size, "random generated instance", avg_time_random, avg_steps_random);
            delete[] arr;
        }     
        avg_time_random /= 50;
        avg_steps_random /= 50;
        cout << "For input data of size " << size << ":" << endl;
        cout << "  Average CPU time taken by program for random generated instance input is : "  << avg_time_random << " microsec " << endl;
        cout << "  Average number of steps taken for random generated instance input is : " << avg_steps_random << endl;
        cout << "--------------------------------------------------------------------------------------" << endl;
    }

    cout << "--------------------------------------Merge Sort--------------------------------------" << endl;
    for (int i = 0; i < num_sizes; i++) {
        int size = sizes[i];
        double  avg_time_random = 0;
        unsigned long long  avg_steps_random = 0;
        for (int j = 0; j < 50; j++) {
            int* arr = new int[size];
            for (int k = 0; k < size; k++) {
                arr[k] = k + 1;
            }
            randomize(arr, size);
            Measure_Time_Merge(arr, size, "random generated instance", avg_time_random, avg_steps_random);
            delete[] arr;
        }
        avg_time_random /= 50;
        avg_steps_random /= 50;
        cout << "For input data of size " << size << ":" << endl;
        cout << "  Average CPU time taken by program for random generated instance input is : " << avg_time_random << " microsec " << endl;
        cout << "  Average number of steps taken for random generated instance input is : " << avg_steps_random << endl;
        cout << "--------------------------------------------------------------------------------------" << endl;
    }

    cout << "----------------------------------Merge-Insert Sort-----------------------------------" << endl;
    for (int i = 0; i < num_sizes; i++){
        int size = sizes[i];
        double  avg_time_random = 0;
        unsigned long long  avg_steps_random = 0;
        for (int j = 0; j < 50; j++){
            int* arr = new int[size];
            for (int k = 0; k < size; k++){
                arr[k] = k + 1;
            }
            randomize(arr, size);
            Measure_Time_Merge_insert(arr, size, "random generated instance", avg_time_random, avg_steps_random);
            delete[] arr;
        }       
        avg_time_random /= 50;
        avg_steps_random /= 50;
        cout << "For input data of size " << size << ":" << endl;
        cout << "  Average CPU time taken by program for random generated instance input is : " <<  avg_time_random << " microsec " << endl;
        cout << "  Average number of steps taken for random generated instance input is : " << avg_steps_random << endl;
        cout << "--------------------------------------------------------------------------------------" << endl;
    }
    return 0;
}

void randomize(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % n + 1;
    }
}

void PrintArr(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

void selectionSort(int* arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        int min = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min]) {
                min = j;
            }
        }
        swap(&arr[i], &arr[min]);
    }
}

unsigned long long selectionSort_step(int* arr, int n) {
    unsigned long long steps = 0;
    steps++;
    for (int i = 0; i < n - 1; i++) {
        int min = i;
        steps += 4;
        for (int j = i + 1; j < n; j++) {
            steps += 3;
            if (arr[j] < arr[min]) {
                min = j;
                steps += 1;
            }
        }
        swap(&arr[i], &arr[min]);
        steps += 3;
    }
    return steps;
}

void Measure_Time_Selection(int* arr, int size, string input_type, double& avg_time, unsigned long long& avg_steps) {
    unsigned long long steps = selectionSort_step(arr, size);
    avg_steps += steps;
    clock_t start = clock();
    selectionSort(arr, size);
    clock_t end = clock();
    double elapsed_time = (double)(end - start) / CLOCKS_PER_SEC;
    avg_time += elapsed_time * 1000000;
}

void minMaxSelectionSort(int* arr, int n){
    for(int i = 0; i < n / 2; i++){
        int min = i;
        int max = i;
        for(int j = i; j < n - i ; j++){
            if(arr[j] < arr[min]){
                min = j;
            }
            if(arr[j] > arr[max]){
                max = j;
            }
        }
        swap(&arr[i], &arr[min]);
        if(max == i){
            max = min;
        }
        swap(&arr[n - i - 1], &arr[max]);
    }
}

unsigned long long min_max_selection_sort_steps(int arr[], int n) {
    unsigned long long steps = 0;
    steps++;
    for (int i = 0; i < n / 2; i++) {
        int min = i;
        int max = i;
        steps += 5;
        for (int j = i; j < n - i; j++) {
            steps += 3;
            if (arr[j] < arr[min]) {
                min = j;
                steps++;
            }
            steps++;
            if (arr[j] > arr[max]) {
                max = j;
                steps += 1;
            }
        }
        swap(&arr[i], &arr[min]);
        steps += 4;
        if (max == i) {
            max = min;
            steps++;
        }
        swap(&arr[n - i - 1], &arr[max]);
        steps += 3;
    }
    return steps;
}

void Measure_Time_MinMaxSelection(int* arr, int size, string input_type, double& avg_time, unsigned long long& avg_steps){
    unsigned long long steps = min_max_selection_sort_steps(arr, size);
    avg_steps += steps;
    clock_t start = clock();
    minMaxSelectionSort(arr, size);
    clock_t end = clock();
    double elapsed_time = (double)(end - start) / CLOCKS_PER_SEC;
    avg_time += elapsed_time * 1000000;
}

void swap(int* a,int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void merge(int arr[], int l, int m, int r){
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
    int* L = new int[n1];
    int* R = new int[n2];
    for(i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for(j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];
    i = 0;
    j = 0;
    k = l;
    while(i < n1 && j < n2){
        if(L[i] <= R[j]){
            arr[k] = L[i];
            i++;
        }
        else{
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while(i < n1){
        arr[k] = L[i];
        i++;
        k++;
    }
    while(j < n2){
        arr[k] = R[j];
        j++;
        k++;
    }
    delete[] L;
    delete[] R;
}

unsigned long long merge_steps(int arr[], int l, int m, int r) {
    unsigned long long steps = 0;
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
    steps += 5;
    int* L = new int[n1];
    int* R = new int[n2];
    steps += 3;
    for (i = 0; i < n1; i++) {
        L[i] = arr[l + i];
        steps += 4;
    }
    for (j = 0; j < n2; j++) {
        R[j] = arr[m + 1 + j];
        steps += 3;
    }
    i = 0;
    j = 0;
    k = l;
    steps += 3;
    while (i < n1 && j < n2) {
        steps += 3;
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
            steps += 2;
        }
        else {
            arr[k] = R[j];
            j++;
            steps += 2;
        }
        k++;
        steps++;
    }
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
        steps += 4;
    }
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
        steps += 4;
    }
    delete[] L;
    delete[] R;
    steps += 2;

    return steps;
}

void mergeInsertionSort(int arr[], int l, int r) {
    if (r - l + 1 <= 10) {
        int i, j, key;
        for (i = l + 1; i <= r; i++) {
            key = arr[i];
            j = i - 1;
            while (j >= l && arr[j] > key) {
                arr[j + 1] = arr[j];
                j = j - 1;
            }
            arr[j + 1] = key;
        }
    }
    else {
        int mid = (l + r) / 2;
        mergeInsertionSort(arr, l, mid);
        mergeInsertionSort(arr, mid + 1, r);
        merge(arr, l, mid, r);
    }
}

unsigned long long merge_insertion_sort_steps(int arr[], int l, int r) {
    unsigned long long steps = 0;
    steps += 1;
    if (r - l + 1 <= 10) {
        int i, j, key;
        steps += 4;
        for (i = l + 1; i <= r; i++) {
            key = arr[i];
            j = i - 1;
            steps += 4;
            while (j >= l && arr[j] > key) {
                arr[j + 1] = arr[j];
                j = j - 1;
                steps += 4;
            }
            arr[j + 1] = key;
            steps += 1;
        }
    }
    else {
        int mid = (l + r) / 2;
        steps++;
        steps += merge_insertion_sort_steps(arr, l, mid);
        steps += merge_insertion_sort_steps(arr, mid + 1, r);
        steps += merge_steps(arr, l, mid, r);
    }
    return steps;
}

void Measure_Time_Merge_insert(int* arr, int size, string input_type, double& avg_time, unsigned long long& avg_steps){
    unsigned long long steps = merge_insertion_sort_steps(arr, 0, size - 1);
    avg_steps += steps;
    clock_t start = clock();
    mergeInsertionSort(arr, 0, size - 1);
    clock_t end = clock();
    double elapsed_time = (double)(end - start) / CLOCKS_PER_SEC;
    avg_time += elapsed_time * 1000000;
}

void Merge_sort(int arr[], int l, int r) {
    if (l < r) {
        int mid = (l + r) / 2;
        Merge_sort(arr, l, mid);
        Merge_sort(arr, mid + 1, r);
        merge(arr, l, mid, r);
    }
}

unsigned long long Merge_sort_steps(int arr[], int l, int r) {
    unsigned long long steps = 0;
    steps += 1;
    if (l < r) {
        int mid = (l + r) / 2;
        steps += 1;
        steps += Merge_sort_steps(arr, l, mid);
        steps += Merge_sort_steps(arr, mid + 1, r);
        steps += merge_steps(arr, l, mid, r);
    }
    return steps;
}

void Measure_Time_Merge(int* arr, int size, string input_type, double& avg_time, unsigned long long& avg_steps) {
    unsigned long long steps = Merge_sort_steps(arr, 0, size - 1);
    avg_steps += steps;
    clock_t start = clock();
    Merge_sort(arr, 0, size - 1);
    clock_t end = clock();
    double elapsed_time = (double)(end - start) / CLOCKS_PER_SEC;
    avg_time += elapsed_time * 1000000;
}















