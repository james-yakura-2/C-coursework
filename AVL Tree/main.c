#include <stdio.h>
#include <stdlib.h>

struct node;
typedef struct node Node;
struct node {
	int data;
	Node* left;
	Node* right;
	int balance_factor;
};

int insert_report_taller(Node** pRoot, int value);
void traversal_in_order(Node* root);
void check_balance(Node** pRoot);
void rotate_left_right(Node** pRoot);

int main() {
	Node* root = NULL;
	int taller;
	//insert root
	insert_report_taller(&root, 42);
	insert_report_taller(&root, 21);
	taller = insert_report_taller(&root, 33);
	traversal_in_order(root);
	printf("-------------\n");
	if (taller)
		check_balance(&root);
	traversal_in_order(root);
	return 0;
}

int insert_report_taller(Node** pRoot, int value) {
	//if pRoot = NULL
	// create a new node -> root
	// insert node on left or right
	int old_balance_factor;
	if (*pRoot == NULL) {
		*pRoot = (Node*)malloc(sizeof(Node));
		if (*pRoot == NULL) {
			printf("error\n");
			exit(1);
		}
		(*pRoot)->data = value;
		(*pRoot)->left = NULL;
		(*pRoot)->right = NULL;
		(*pRoot)->balance_factor = 0;
	}
	else {
		old_balance_factor = (*pRoot)->balance_factor;
		if (value < (*pRoot)->data) {
			//if tree is taller 
			if (insert_report_taller(&((*pRoot)->left), value)) {
				(*pRoot)->balance_factor++;
					if((*pRoot)->balance_factor> old_balance_factor)
						return 1;
					else
						return 0;
			}
		}
		else if (value > (*pRoot)->data) {
			//if tree is taller 
			if (insert_report_taller(&((*pRoot)->right), value)) {
				(*pRoot)->balance_factor--;
					if ((*pRoot)->balance_factor < old_balance_factor)
						return 1;
					else
						return 0;
			}
		}
		else 
				return 0;
	}

	return 1;
}
void traversal_in_order(Node* root) {
	if (root != NULL) {
		traversal_in_order(root->left);
		printf("value = %d\tbalance_factor = %d\n", root->data, root->balance_factor);
		traversal_in_order(root->right);
	}
}
void check_balance(Node** pRoot) {
	if ((*pRoot)->balance_factor == 2) { //parent is left-heavy
		if (((*pRoot)->left)->balance_factor == 1) {
			//do something here
		}
		else
			rotate_left_right(&(*pRoot));
	}
	//return NULL;
}
void rotate_left_right(Node** pRoot) {
	Node* tmp_root = *pRoot;
	Node* tmp_left = (*pRoot)->left;
	Node* tmp_right = ((*pRoot)->left)->right;
	//rotate child left
	tmp_root->left = tmp_right;  //left child is 33
	tmp_left->right = NULL;   
	tmp_right->left = tmp_left;   //take 21 as a child
	tmp_left->balance_factor++;   //balance factor of 33 is 1
	//rotate parent right
	*pRoot = tmp_right;   //root is 33 now
	tmp_right->right = tmp_root; //making 33 right child of 33
	(tmp_right->right)->left = NULL;
	(tmp_right->right)->balance_factor = 0;
//	return NULL;
}