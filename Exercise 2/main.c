/*
 * main.c
 *
 *  Created on: 23 Apr 2012
 *      Author: tamer
 */

#include <stdio.h>

#define arrSize 10

int main() {
	int v1[arrSize] = { 0 };
	int v2[arrSize] = { 0 };
	int a;
	int i = 0;
	int j = 0;

	do {
		printf("Please enter a number: ");
		scanf("%d", &a);
		if (a != 0) {
			if (a % 3 == 0) {
				v1[i] = a;
				i++;
			} else {
				if (a % 2 != 0) {
					v2[j] = a;
					j++;
				}
			}
		}
	} while (i < arrSize && j < arrSize);

	printf("V1\t\tV2\n");

	int k;
	int min = (i > j) ? j : i;
	for (k = 0; k < arrSize; k++) {
		printf("%d\t\t%d\n", v1[k], v2[k]);

	}

	return 0;
}
