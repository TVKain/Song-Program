#include "mgraphics.h"

#include <string.h>
#include <stdio.h>

void print_block(size_t size, char *a[size], size_t length, size_t padding, ALIGN opt) 
{
	int n;
	int l;

	switch (opt) {
		case CENTER:
			print_pad(padding);

			printf(" "); 
			print_symbol(length, '-');
			printf(" \n");

			for (size_t j = 0; j < size; ++j) {

				l = strlen(a[j]);
				n = (length - l) / 2;

				print_pad(padding);
				printf("|");
				print_pad(n);

				printf("%s", a[j]);
				if (strlen(a[j]) % 2 == 1) 
					n += 1;
				print_pad(n);
				printf("|\n");
			}
			print_pad(padding);
			printf(" "); 
			print_symbol(length, '-');
			printf(" \n");
			break;
		case LEFT:
			print_pad(padding);
			printf(" "); 
			print_symbol(length, '-');
			printf(" \n");

			for (size_t j = 0; j < size; ++j) {

				l = strlen(a[j]);
				n = length - strlen(a[j]) - 1;

				print_pad(padding);
				printf("| %s", a[j]);
				print_pad(n);
				printf("|\n");
			}
			printf(" "); 
			print_pad(padding);
			print_symbol(length, '-'); 
			printf(" \n");
			break;
		default: printf("Invalid option!\n"); break; 
	}
}

void print_error_block(size_t size, char *a[size], size_t length, size_t padding) 
{	
	int n;
	int l;
	char *msg = "Error";

	print_symbol(length, '.'); 
	printf("\n");
	printf(". %s", msg);
	print_pad(length - strlen(msg) - 3);
	printf(".\n");
	for (size_t j = 0; j < size; ++j) {
		l = strlen(a[j]);
		n = (length - l) / 2 - 1;

		printf(".");
		print_pad(n);

		if (l % 2 == 1)
			n += 1;

		printf("%s", a[j]);

		print_pad(n);
		printf(".\n");
	}
	print_symbol(length, '.');
	printf("\n");


	return;
}