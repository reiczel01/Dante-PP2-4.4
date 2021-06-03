#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct matrix_t {
	int** ptr;
	int width;
	int height;
};

void matrix_destroy(struct matrix_t* m) {
	if (m != NULL && m->height > 0) {
		if (m->ptr != NULL) {
			for (int i = 0; m->height > i; i++) {
				if (*(m->ptr + i) != NULL) {
					free(*(m->ptr + i));
				}
			}
		}
		free(m->ptr);
	}
}
int matrix_create(struct matrix_t* m, int width, int height) { //https://www.geeksforgeeks.org/dynamically-allocate-2d-array-c/
	if (m == NULL || width <= 0 || height <= 0) {
		return 1;
	}
	m->height = height;
	m->width = width;
	m->ptr = NULL;
	m->ptr = (int**)calloc(height, sizeof(int*)); //rzutownaie na wsakżnik na wskaźnik plus alokacaj pamięi dla kolejnych wierszy * ilość pamięci o wielkości wskażnika int
	if (m->ptr == NULL) {
		return 2;
	}
	for (int i = 0; height > i; i++) {
		*(m->ptr + i) = NULL;
		*(m->ptr + i) = calloc(width, sizeof(int));
		if (*(m->ptr + i) == NULL) {
			matrix_destroy(m);
			return 2;
		}
	}
	return 0;
}
int matrix_read(struct matrix_t* m) {
	if (m == NULL || m->height <= 0 || m->width <= 0 || m->ptr == NULL) {
		return 1;
	}
	printf("Podaj wartości: ");
	for (int i = 0; m->height > i; i++) {
		for (int j = 0; m->width > j; j++) {
			int temp;
			int check = scanf("%d", &temp);
			if (check != 1) {
				return 2;
			}
			*(*(m->ptr + i) + j) = temp;
		}
	}
	return 0;
}

void matrix_display(const struct matrix_t* m) {
	if (m == NULL || m->height <= 0 || m->width <= 0 || m->ptr == NULL) {
		return;
	}
	for (int i = 0; m->height > i; i++) {
		if (*(m->ptr + i) != NULL) {
			for (int j = 0; m->width > j; j++) {
				int temp = *(*(m->ptr + i) + j);
				printf("%d ", temp);
			}
			printf("\n");
		}
	}
}



int main()
{
	struct matrix_t matrix;
	int check = 0;
	int height = 0;
	int width = 0;
	printf("Podaj szerokość i wysokość: ");
	check = scanf("%d %d", &width, &height);
	if (check != 2) {
		printf("incorrect input");
		return 1;
	}

	//matrix.width = -3;
	//matrix.height = 7;
	
	check = matrix_create(&matrix, width, height);
	if (check == 1) {
		printf("incorrect input data");
		return 2;
	}
	else if (check == 2) {
		printf("Failed to allocate memory");
		return 8;
	}
	
	
	check = matrix_read(&matrix);
	if (check == 1) {
		printf("incorrect input data");
		matrix_destroy(&matrix);
		return 8;
	}
	else if (check == 2) {
		printf("incorrect input");
		matrix_destroy(&matrix);
		return 1;
	}

	matrix_display(&matrix);

	matrix_destroy(&matrix);
	return 0;
}
