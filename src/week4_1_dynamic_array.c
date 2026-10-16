/*
 * week4_1_dynamic_array.c
 * Author: Raghav Joshi
 * Student ID: 251ADB004
 * Description:
 *   Demonstrates creation and usage of a dynamic array using malloc.
 *   Allocate memory for n integers, read them from the user,
 *   print their sum and average, and then free the memory.
 *
 *   Output must match the format in the Week 4 instructions exactly
 *   (it is checked by the autograder).
 */

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
  int n;
  int* arr = NULL;
  long long sum = 0;
  double average;

  printf("Enter number of elements: ");

  if (scanf("%d", &n) != 1 || n <= 0) {
    printf("Invalid size.\n");
    return 1;
  }

  // Allocate memory for n integers.
  arr = malloc((size_t)n * sizeof(int));

  // Stop if memory allocation fails.
  if (arr == NULL) {
    printf("Memory allocation failed.\n");
    return 1;
  }

  printf("Enter %d integers: ", n);

  // Read integers and calculate their sum.
  for (int i = 0; i < n; i++) {
    if (scanf("%d", &arr[i]) != 1) {
      printf("Invalid input.\n");
      free(arr);
      return 1;
    }
    sum += arr[i];
  }

  // Convert to floating point to avoid integer division.
  average = (double)sum / n;

  printf("Sum = %lld\n", sum);
  printf("Average = %.2f\n", average);

  // Release allocated memory.
  free(arr);

  return 0;
}