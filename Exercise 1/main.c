/*
 * main.c
 *
 *  Created on: 23 Apr 2012
 *      Author: tamer
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define _size(type) (pow(2, sizeof (type) * 8 - 1) - 1)

#define maxbitsize 32

void inputbinary(int *nbit, int number[]) {

	int n, i;

	do {
		printf("Enter the number N of bit of the binary number (0>N<=32):");
		scanf("%d", &n);
		if (n <= 0 || n > 32) {
			printf("Error: N must be greater then 0\n");
		}
	} while (n <= 0 || n > 32);

	*nbit = n;

	for (i = *nbit - 1; i >= 0; i--) {
		do {
			printf("Enter bit number %d:", i);
			scanf("%d", &number[i]);

			if (number[i] != 0 && number[i] != 1) {
				printf("Error: value not allowd\n");
			}

		} while (number[i] != 0 && number[i] != 1);
	}

}

int binary2decimal(int nbit, int number[]) {

	int result = 0;
	int i;
	int twopower = 1;

	for (i = 0; i < nbit; i++) {
		result = result + number[i] * twopower;
		twopower = twopower * 2;
	}

	return result;
}

int signandmagnitude2decimal(int nbit, int number[]) {
	int result;

	result = binary2decimal(nbit - 1, number);

	if (number[nbit - 1] == 1) {
		result = result * -1;
	}

	return result;
}

int binaryadd(int nbit, int n1[], int n2[], int result[]) {
	int i;
	int carry = 0;

	for (i = 0; i < nbit; i++) {

		result[i] = n1[i] + n2[i] + carry;

		carry = result[i] / 2;

		result[i] = result[i] % 2;
	}

	return carry;
}

int twocomplement2decimal(int nbit, int number[]) {
	int result, i;

	int flippednumber[maxbitsize];
	int tmpnumber1[maxbitsize];
	int tmpnumber[maxbitsize] = { 0 };
	tmpnumber[0] = 1;

	int overflow;

	if (number[nbit - 1] == 0) {
		return binary2decimal(nbit, number);
	} else {
		for (i = 0; i < nbit; i++) {
			if (number[i] == 0) {
				flippednumber[i] = 1;
			} else {
				flippednumber[i] = 0;
			}
		}
		overflow = binaryadd(nbit, flippednumber, tmpnumber, tmpnumber1);

		result = -1 * binary2decimal(nbit, tmpnumber1);
	}

	return result;

}

void printbinary(int nbit, int number[]) {

	int i;
	for (i = 0; i < nbit; i++) {
		printf("%d", number[i]);
	}
	printf("\n");
}

void inputDecimal(int *decimal) {
	int d;

	do {

		printf("Enter the number to convert: ");
		scanf("%d", &d);

		if (*decimal <= -_size(int) || *decimal > _size(int)) {
			printf("Error: number too big, please use a smaller number\n");
		}
	} while (*decimal <= -_size(int) || *decimal > _size(int));
	*decimal = d;
}

void toBinarySNM(int decimal, int binary[], int *size) {
	// variables
	int k = 0, n = 0;
	int negative = 0;
	int remain;
	int temp[maxbitsize];

	// take care of negative input
	if (decimal < 0) {
		decimal = -decimal;
		negative = 1;
	}

	while (decimal > 0) {
		remain = decimal % 2;
		decimal = decimal / 2;
		temp[k++] = remain;
	}

	// using sign and magnitude

	if (negative)
		temp[k++] = 1;
	else
		temp[k++] = 0;

	*size = k;

	// reverse the spelling
	while (k >= 0)
		binary[n++] = temp[--k];

	binary[n - 1] = 0;
}

void flip(int n1[], int result[], int nbit) {
	int i;
	for (i = 0; i < nbit; i++) {
		if (n1[i] == 1)
			result[i] = 0;
		else
			result[i] = 1;
	}
}

// assumes decimal is a negative number!
void negative2C(int decimal, int result[], int *nbit) {
	int temp[maxbitsize], temp2[maxbitsize], s;
	toBinarySNM(-decimal, temp, &s);

	*nbit = s;
	int one[maxbitsize] = { 0 };
	one[s - 1] = 1;

	flip(temp, temp2, s);

	int overflow = binaryadd(s, temp2, one, result);
	if (overflow) {
		printf("Error: overflow encountered!\n");
		return;
	}
}

void toBinary2C(int decimal, int binary[], int *size) {
	// variables
	int s = *size;
	int temp[maxbitsize];
	if (decimal < 0) {
		negative2C(decimal, binary, &s);
		*size = s;
	} else {
		toBinarySNM(decimal, binary, &s);
		*size = s;
	}
}

void addOrSubtract2C(int addition, int n1[], int n2[], int result[]) {
	int size, size2;
	printf("First binary number: ");
	inputbinary(&size, n1);

	printf("Second binary number: ");
	inputbinary(&size2, n2);

	// check that the two numbers are of the the same bit length
	if (size != size2)
		return;
	else {
		if (addition) {
			int overflow = binaryadd(size, n1, n2, result);
			if (overflow) {
				printf("Error: overflow encountered!\n");
				return;
			}

			printf("The addition of the two numbers is: ");
		} else {
			int tmp[maxbitsize], tmp2[maxbitsize];
			flip(n2, tmp, size);
			int one[maxbitsize] = { 0 };
			one[size - 1] = 1;

			int overflow = binaryadd(size, tmp, one, tmp2);
			if (overflow) {
				printf("Error: overflow encountered!\n");
				return;
			}

			overflow = binaryadd(size, n1, tmp2, result);
			if (overflow) {
				printf("Error: overflow encountered!\n");
				return;
			}

			printf("The subtraction of the two numbers is: ");
		}
		printbinary(size, result);
	}
}

int main() {

	int n1[maxbitsize], n2[maxbitsize], result[maxbitsize];
	int size, decimalconversion, choice, decimal;

	printf("Binary numbers for dummies \n");
	printf("=============================");
	printf(
			"This program helps you practicing with binary numbers conversions and operations \n\n");
	printf("You can choose one of the following options \n");
	printf("1) Pure binary to decimal conversion\n");
	printf("2) S&M to decimal conversion\n");
	printf("3) Two'sC to decimal conversion\n");
	printf("4) Decimal to sign and magnitude binary\n");
	printf("5) Decimal to two's complement\n");
	printf("6) Addtion of two's complement\n");
	printf("7) Subtraction of two's complement\n");

	printf("\n\nENTER YOUR CHOICE:");
	scanf("%d", &choice);

	switch (choice) {

	case 1:
		inputbinary(&size, n1);
		decimalconversion = binary2decimal(size, n1);

		printf("The pure binary number: ");
		printbinary(size, n1);
		printf(" converted to decimal is equal to %d\n", decimalconversion);

		break;
	case 2:
		inputbinary(&size, n1);
		decimalconversion = signandmagnitude2decimal(size, n1);

		printf("The S&M  number: ");
		printbinary(size, n1);
		printf(" converted to decimal is equal to %d\n", decimalconversion);

		break;
	case 3:
		inputbinary(&size, n1);
		decimalconversion = twocomplement2decimal(size, n1);

		printf("The Two'sC  number: ");
		printbinary(size, n1);
		printf(" converted to decimal is equal to %d\n", decimalconversion);
		break;
	case 4:
		inputDecimal(&decimal);
		toBinarySNM(decimal, n1, &size);

		printf("The decimal number: %d", decimal);

		printf(" converted to binary in sign and magnitude is equal to: ");
		printbinary(size, n1);
		break;
	case 5:
		inputDecimal(&decimal);
		toBinary2C(decimal, n1, &size);

		printf("size=%d\n", size);

		printf("The decimal number: %d", decimal);

		printf(" converted to binary in two's complement is equal to: ");
		printbinary(size, n1);
		break;
	case 6:
		addOrSubtract2C(1, n1, n2, result);
		break;
	case 7:
		addOrSubtract2C(0, n1, n2, result);
		break;
	}

	return 0;
}
