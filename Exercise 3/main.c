/*
 * main.c
 *
 *  Created on: 16 Apr 2012
 *      Author: tamer
 */

#include <stdio.h>

#define arrSize 10

int main() {
	int a, i, arr[arrSize] = { 0 };

	for (i = 0; i < arrSize; i++) {
		printf("Please enter a number: ");
		scanf("%d", &a);
		arr[i] = a;
	}

	printf("[");
	for (i = 0; i < arrSize; i++) {
		printf("%d", arr[i]);
		if (i < arrSize - 1)
			printf(", ");
	}
	printf("]\n");

	int sum = 0;

	for (i = 0; i < arrSize; i++)
		sum += arr[i];

	float mean = ((float) sum) / ((float) arrSize);
	printf("Mean = %f\n", mean);

	int max = arr[0];
	int maxAt = 0;
	int duplicateAt[arrSize] = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };
	int duplicateValue[arrSize] = { 0 };
	int j = 0;

	for (i = 0; i < arrSize; i++) {
		if (max < arr[i]) {
			max = arr[i];
			maxAt = i;
			// resetting arrays
			for (j = 0; j < arrSize; j++) {
				duplicateAt[j] = -1;
				duplicateValue[j] = 0;
			}
			j = 0;
		} else if (max == arr[i]) {
			duplicateAt[j] = i;
			duplicateValue[j++] = arr[i];
		}
	}

	printf("Max at arr[%d]=%d\n", maxAt, arr[maxAt]);

	printf("Duplicates positions = [");
	for (i = 0; i < arrSize && duplicateAt[i] != -1; i++) {
		printf("%d", duplicateAt[i]);
		if (i < arrSize - 1 && duplicateAt[i] != -1)
			printf(", ");
	}
	printf("]\n");

	return 0;
}
