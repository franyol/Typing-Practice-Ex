#include <stdio.h>

int calculate_score(int *values, int size) {
    int score = 0;

    for (int i = 0; i < size; i++) {
        if (values[i] > 10) {
            score += values[i] * 2;
        } else if (values[i] > 5) {
            score += values[i];
        } else {
            score -= values[i];
        }
    }

    return score;
}

void print_results(int *values, int size) {
    int result = calculate_score(values, size);

    if (result > 50) {
        printf("High score: %d\n", result);
    } else if (result > 20) {
        printf("Medium score: %d\n", result);
    } else {
        printf("Low score: %d\n", result);
    }
}

int main() {
    int data[] = {3, 7, 12, 5, 20, 1};
    print_results(data, 6);
    return 0;
}
