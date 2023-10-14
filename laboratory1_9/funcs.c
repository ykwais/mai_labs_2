#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "enum.h"

bool is_number(char *str) {
    char *result;
    long number = strtol(str, &result, 10);

    if (*result != '\0') {
        return false;
    }

    return true;
}

enum input_status_code analysis(int argc, char **argv) {
    if (argc != 3) {
        return isc_bad_input;
    } else if (!is_number(argv[1]) || !is_number(argv[2])) {
        return isc_not_a_number;
    } else {
        return isc_well;
    }
}

int random_value(int a, int b) {
    if (a <= b) {
        return a + rand() % (b - a + 1);
    } else {
        return b + rand() % (a - b + 1);
    }
}

void filling_the_array(int a, int b, int *mass, int length) {
    for (int i = 0; i < length; i++) {
        mass[i] = random_value(a, b);
    }
}

void print_array(int *mass, int length) {
    for (int i = 0; i < length; i++) {
        printf("[%d]: %d  ", i, mass[i]);
    }
    printf("\n\n");
}

void min_max_element_by_one_pass(int *mass, int length) {
    int min_element = INT_MAX;
    int max_element = INT_MIN;
    int max_i = 0;
    int min_i = 0;
    for (int i = 0; i < length; i++) {
        if (mass[i] > max_element) {
            max_element = mass[i];
            max_i = i;
        }
        if (mass[i] < min_element) {
            min_element = mass[i];
            min_i = i;
        }
    }
    int tmp = mass[max_i];
    mass[max_i] = mass[min_i];
    mass[min_i] = tmp;
}

int little_sort_Lomuto(int *mass, int start, int end) {
    int left_pointer = start;
    for (int current_pointer = start; current_pointer < end; current_pointer++) {
        if (mass[current_pointer] < mass[end]) {
            int tmp = mass[left_pointer];
            mass[left_pointer] = mass[current_pointer];
            mass[current_pointer] = tmp;
            left_pointer++;
        }
    }
    int tmp = mass[left_pointer];
    mass[left_pointer] = mass[end];
    mass[end] = tmp;
    return left_pointer;
}

void fast_sort_Lomuto(int *mass, int start, int end) {
    if (start >= end) {
        return;
    }
    int begin_right_subarray = little_sort_Lomuto(mass, start, end);
    fast_sort_Lomuto(mass, start, begin_right_subarray - 1);
    fast_sort_Lomuto(mass, begin_right_subarray + 1, end);
}

void fast_sort_Lomuto_begin(int *mass, int length) {

    fast_sort_Lomuto(mass, 0, length - 1);
}


int bin_search_in_array(int *mass, int length, int required) {
    int left = 0;
    int right = length - 1;
    int middle = 0;
    while (left < right-1) {
        middle = (left + right) / 2;

        if(mass[middle] > required) {
            right = middle;
        } else  {
            left = middle;
        }
    }
    return (abs(mass[left] - required) < abs(mass[right] - required)) ?  mass[left] :  mass[right];
}

int c_value(int *mass_b, int length_b, int required) {
    if (required < mass_b[0]) {
        return mass_b[0];
    }
    if (required > mass_b[length_b - 1]) {
        return mass_b[length_b - 1];
    }
    return bin_search_in_array(mass_b, length_b, required);


}