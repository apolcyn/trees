#include<stdio.h>
#include<stdlib.h>

struct node {
   struct node *left;
   struct node *right;
   struct node *parent;
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

struct node* addToTree(struct node *root, struct node *parent, struct node *new_node) {
   struct node *new_root;

   fprintf(stderr, "calling\n");

   if(root == NULL) {
      new_node->parent = parent;
      return new_node;
   }
   else if(new_node->val > root->val) {
      root->right = addToTree(root->right, root, new_node);
   }
   else {
      root->left = addToTree(root->left, root, new_node);
   }

   if(diff_heights(root) > 1) {
      if(diff_heights(root->right) >= 0) {
	 new_root = root->right;
	 root->right = NULL;
	 new_root->left = addToTree(root, new_root, new_root->left);
	 new_root->parent = parent;
      }
      else {
	 printf("shouldn't be trying to add a new number here\n");
	 exit(-1);
      }
   }
   else if(diff_heights(root) < -1) {
      printf("shouln't be here\n");
      exit(-1);
      if(diff_heights(root->left) <= 0) {
         // easy
      }
      else {
         // hard
      }
   }

   new_root->height = max(height(new_root->right), height(new_root->left));
   return new_root;
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
   
   while(1) {
      fprintf(stderr, "enter a num\n");
      scanf("%d\n", &val);
      if(val < 0)
	 break;
      temp = calloc(1, sizeof(struct node));
      temp->val = val;
      tree = addToTree(tree, NULL, temp);
   }

   printInOrder(tree);
   return 0;
}
