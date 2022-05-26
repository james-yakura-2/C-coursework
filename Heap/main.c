#include <stdio.h>
void swap(int* a, int* b);
void fix_up(int a[], int index);
void fix_down(int a[], int size, int index);
void heapify(int a[], int size);
void heap_sort(int a[], int size);

int main() {
	int a[] = { 80,40,30,60,81,90,100,10 };
	int a1[] = { 80,40,30,60,81,90,100,10 };

	int i;
	for (i = 0; i < 8; ++i)
		printf("%d ", a[i]);
	printf("\n");
	printf("------------\n");
	for (i = 0; i < 8; ++i)
		fix_up(a, i);
	for (i = 0; i < 8; ++i)
		printf("%d ", a[i]);
	printf("\n");
	//heapify(a1, 8);
	heap_sort(a1, 8);
	printf("------------\n");
	for (i = 0; i < 8; ++i)
		printf("%d ", a1[i]);
	printf("\n");
	return 0;
}
void swap(int* a, int* b) {
	int tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}
void fix_up(int a[], int index) {
	int index_of_parent;
	if (index >= 1) {
		index_of_parent = (index - 1) / 2;
		if (a[index] > a[index_of_parent]) {
			swap(&a[index], &a[index_of_parent]);
			fix_up(a, index_of_parent);
		}
	}

}
void fix_down(int a[], int size, int index) {
	int left_child_index = 2 * index + 1;
	int right_child_index = 2 * index + 2;
	if (left_child_index < size) {
		if (right_child_index<size && a[right_child_index]>a[left_child_index]) {
			if (a[right_child_index] > a[index]) {
				swap(&a[right_child_index], &a[index]);
				fix_down(a, size, right_child_index);
			}
		}
		else {
			if (a[left_child_index] > a[index]) {
				swap(&a[left_child_index], &a[index]);
				fix_down(a, size, left_child_index);
			}
		}
	}
}
void heapify(int a[], int size) {
	int i;
	for (i = size / 2 - 1; i >= 0; i--)
		fix_down(a, size, i);
}
void heap_sort(int a[], int size) {
	int i, tmp;
	int tmp_size = size;
	heapify(a, size);
	for ( i = 0; i < size - 1; i++) {
		tmp = a[0];
		a[0] = a[tmp_size - 1];
		a[tmp_size - 1] = tmp;
		tmp_size--;
		fix_down(a, tmp_size, 0);
	}
}