#include<stdio.h>
#include<stdlib.h>

struct node {
   struct node *left;
   struct node *right;
   int val;
   int height;
};

int max(int a, int b) {
   if(a > b)
      return a;
   return b;
}

int height(struct node *node) {
   if(node)
      return node->height;
   return -1;
}

int diff_heights(struct node *root) {
   return height(root->right) - height(root->left);
}

// takes in a balanced tree, returns a balanced tree after the new node added to it
struct node* addToTree(struct node *root, struct node *new_node) {
   struct node *new_root = root;

   fprintf(stderr, "calling\n");

   if(root == NULL) {
      return new_node;
   }
   else if(new_node->val > root->val) {
      root->right = addToTree(root->right, new_node);
   }
   else {
      root->left = addToTree(root->left, new_node);
   }

   if(diff_heights(root) > 1) {
      if(diff_heights(root->right) >= 0) {
	 new_root = root->right;
	 root->right = new_root->left;
	 new_root->left = root;
      }
      else {
	 new_root = root->right->left;
	 root->right->left = new_root->right;
	 new_root->right = root->right;
	 root->right = new_root->left;
	 new_root->left = root;
      }
   }
   else if(diff_heights(root) < -1) {
      if(diff_heights(root->left) <= 0) {
         new_root = root->left;
	 root->left = new_root->right;
	 new_root->right = root;
      }
      else {
	 new_root = root->left->right;
	 root->left->right = new_root->left;
	 new_root->left = root->left;
	 root->left = new_root->right;
	 new_root->right = root;
      }
   }

   new_root->height = max(height(new_root->right), height(new_root->left)) + 1;
   return new_root;
}

void print_spaces(int count) {
   while(count--)
      printf(" ");
}

void graphic(struct node *tree, int indent) {
   if(tree) {
      print_spaces(indent);
      printf("left subtree:\n");  
      graphic(tree->left, indent + 3);
      print_spaces(indent);
      printf("%d\n", tree->val);  
      print_spaces(indent);
      printf("right subtree:\n");  
      graphic(tree->right, indent + 3);
   }
}

void printInOrder(struct node *tree) {
   if(tree) {
      printInOrder(tree->left);
      fprintf(stderr, "%d\n", tree->val);
      printInOrder(tree->right);
   }
}

int main(char **argv, int argc) {
   int val = 0;
   struct node *tree = NULL;
   struct node *temp = NULL;
   
   while(scanf("%d\n", &val) && !feof(stdin)) {
      fprintf(stderr, "enter a num\n");
      temp = calloc(1, sizeof(struct node));
      temp->val = val;
      temp->height = 0;
      tree = addToTree(tree, temp);
   }

   printInOrder(tree);
   graphic(tree, 0);
   return 0;
}
