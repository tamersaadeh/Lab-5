/*
 * main.c
 *
 *  Created on: 23 Apr 2012
 *      Author: tamer
 */

#include <stdio.h>

#define arrSize 10
#define DEBUG 1

int main() {
	int a, i = 0, j = 0, arr[arrSize] = { 0 };
	_Bool increasing = 1, decreasing = 1;

	do {
		printf("Please enter a number: ");
		scanf("%d", &a);
		arr[i++] = a;

		if (DEBUG) {
			printf("increasing=%d\tdecreasing=%d\n", increasing, decreasing);
		}

		_Bool rightLoop = i > (j + 1) && i < (j + 3);

		if (rightLoop && (decreasing && arr[i - 2] < arr[i - 1])) {
			if (DEBUG) {
				printf("arr[%d]=%d\tarr[%d]=%d\n", i - 2, arr[i - 2], i - 1,
						arr[i - 1]);

				puts("increasing!!!!!!");
			}

			decreasing = 0;
			increasing = 1;
		} else if (rightLoop && (increasing && arr[i - 2] > arr[i - 1])) {
			if (DEBUG) {
				printf("arr[%d]=%d\tarr[%d]=%d\n", i - 2, arr[i - 2], i - 1,
						arr[i - 1]);
				puts("decreasing!!!!!!");
			}

			increasing = 0;
			decreasing = 1;
		} else if (arr[i - 2] == arr[i - 1]) {
			j++;
		}
	} while ((i < arrSize)
			&& ((decreasing && arr[i - 2] >= arr[i - 1])
					|| (increasing && arr[i - 2] <= arr[i - 1])));

	printf("[");
	for (i = 0; i < arrSize; i++) {
		printf("%d", arr[i]);
		if (i < arrSize - 1)
			printf(", ");
	}
	printf("]\n");

	return 0;
}
