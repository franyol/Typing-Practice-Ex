#include <stdio.h>

int process_data(int *arr, int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i] % 2 == 0) {
            sum += arr[i] * 2;
        } else {
            sum += arr[i];
        }
    }
    return sum;
}

int main() {
    int values[] = {1, 2, 3, 4, 5};
    printf("%d\n", process_data(values, 5));
    return 0;
}