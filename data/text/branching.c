#include <stdio.h>

int adjust_value(int value) {
    if (value > 50) {
        return value - 10;
    } else if (value > 20) {
        return value + 5;
    }
    return value * 2;
}

int compute_total(int *arr, int size) {
    int total = 0;

    for (int i = 0; i < size; i++) {
        int adjusted = adjust_value(arr[i]);

        if (adjusted % 2 == 0) {
            total += adjusted;
        } else {
            total -= adjusted;
        }
    }

    return total;
}

void print_summary(int total) {
    if (total > 100) {
        printf("Large total: %d\n", total);
    } else if (total > 50) {
        printf("Medium total: %d\n", total);
    } else {
        printf("Small total: %d\n", total);
    }
}

int main() {
    int values[] = {10, 25, 60, 5, 80};
    int total = compute_total(values, 5);
    print_summary(total);
    return 0;
}
