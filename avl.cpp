#include <stdio.h>
#include <malloc.h>

int max(int a, int b) {
	return a > b ? a : b;
}

struct data {
	int value;
	int height;
	struct data* left;
	struct data* right;
};

int getHeight(struct data* data) {
	if(data == NULL) return 0;
	return data->height;
}

void updateHeight(struct data* data) {
	data->height =
		max(
			getHeight(data->left),
			getHeight(data->right)
		) + 1;
}

int getBalanceFactor(data* data) {
	return getHeight(data->left) - getHeight(data->right);
}

struct data* newData(int value) {
	data* newData = (data*) malloc(sizeof(data));
	newData->value = value;
	newData->height = 1;
	newData->left = newData->right = NULL;
	return newData;
}

data* leftRotate(data* root) {
	data* child = root->right;
	data* subTree = child->left;
	
	root->right = subTree;
	child->left = root;
	
	updateHeight(root);
	updateHeight(child);
	
	return child;
}

data* rightRotate(data* root) {
	data* child = root->left;
	data* subTree = child->right;
	
	root->left = subTree;
	child->right = root;
	
	updateHeight(root);
	updateHeight(child);
	
	return child;
}

data* pushData(data* root, data* newData) {
	if(root == NULL)
		return newData;
	int key = newData->value;
	if(key < root->value)
		root->left = pushData(root->left, newData);
	if(key > root->value)
		root->right = pushData(root->right, newData);
		
	updateHeight(root);
	int bftor = getBalanceFactor(root);
	
	if(bftor > 1) {
		if(key > root->left->value)
			root->left = leftRotate(root->left);
		return rightRotate(root);
	}
	if(bftor < -1) {
		if(key < root->right->value)
			root->right = rightRotate(root->right);
		return leftRotate(root);
	}
	return root;
}

void inOrder(data* root) {
	if(root == NULL) return;
	inOrder(root->left);
	printf(" %d ", root->value);
	inOrder(root->right);
}

void search(data* root, int searchValue){
	if(root == NULL) return;
	if(searchValue > root->value) search(root->right, searchValue);
	if(searchValue < root->value) search(root->left, searchValue);
	if(searchValue == root->value){
		printf("[Found] value: %d\n", root->value);
	}
}

int main() {
	data* root = NULL;
	
	// 0  1  2  10  12  31  35  40  120
	root = pushData(root, newData(10));
	root = pushData(root, newData(12));
	root = pushData(root, newData(31));
	root = pushData(root, newData(40));
	root = pushData(root, newData(35));
	root = pushData(root, newData(0));
	root = pushData(root, newData(120));
	root = pushData(root, newData(2));
	root = pushData(root, newData(1));
		
	inOrder(root);
	printf("\n");
	search(root, 35);
	
	return 0;
}
