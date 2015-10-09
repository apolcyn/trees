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
   struct node *new_root = root, *temp_b = NULL;

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
	 root->right = addToTree(NULL, root, new_root->left);
	 new_root->left = addToTree(NULL, new_root, root);
	 new_root->parent = parent;
      }
      else {
         new_root = root->right->left;
         temp_b = root->right;
         root->right = addToTree(NULL, root, new_root->left);
         temp_b->left = addToTree(NULL, temp_b, new_root->right);
         new_root->left = addToTree(NULL, new_root, root);
         new_root->right = addToTree(NULL, new_root, temp_b); 
      }
   }
   else if(diff_heights(root) < -1) {
      printf("shouln't be here\n");
      exit(-1);
      if(diff_heights(root->left) <= 0) {
         // easy
      }
      else {
         // hardd::
      }
   }

   new_root->height = max(height(new_root->right), height(new_root->left)) + 1;
   return new_root;
}

void graphic(struct node *tree, int indent) {
   if(tree) {
      printf("%*d\n", indent, tree->val); 
      printf("%*s\n", indent, "left subtree:");
      graphic(tree->left, indent + 3);
      printf("%*s\n", indent, "right subtree:");
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
   
   fprintf(stderr, "enter a num\n");
   while(scanf("%d\b", &val) && !feof(stdin)) {
      temp = calloc(1, sizeof(struct node));
      temp->val = val;
      tree = addToTree(tree, NULL, temp);
      fprintf(stderr, "enter a num\n");
   }

   printInOrder(tree);
   graphic(tree, 0);
   return 0;
}
