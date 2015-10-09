#include<stdio.h>
#include<stdlib.h>

struct node {
   struct node *left;
   struct node *right;
   int val;
   int height;
   struct node *prev;
   struct node *next;
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

void update_median(struct node *new_node, struct node **high_median, struct node **low_median) {
   if(*high_median == NULL && *low_median == NULL) {
      *high_median = *low_median = new_node;
   }
   else if(*high_median == *low_median) {
      if(new_node->val >= (*high_median)->val) {
         *high_median = (*high_median)->next;
      }
      else {
	 *low_median = (*low_median)->prev;
      }
   }
   else {
      if(new_node->val >= (*high_median)->val) {
         *low_median = *high_median;
      }
      else if(new_node->val > (*low_median)->val && new_node->val < (*high_median)->val) {
	 *high_median = *low_median = new_node;
      }
      else {
	 *high_median = *low_median;
      }
   }
}

void update_height(struct node *node) {
   node->height = max(height(node->left), height(node->right)) + 1;
}
	 

// takes in a balanced tree, returns a balanced tree after the new node added to it
struct node* addToTree(struct node *root, struct node *new_node, struct node *prev, struct node *next) {
   struct node *new_root = root;

   fprintf(stderr, "calling\n");

   if(root == NULL) {
      new_node->next = next;
      next->prev = new_node;
      new_node->prev = prev;
      prev->next = new_node;
      return new_node;
   }
   else if(new_node->val > root->val) {
      root->right = addToTree(root->right, new_node, root, root->next);
   }
   else {
      root->left = addToTree(root->left, new_node, root->prev, root);
   }

   if(diff_heights(root) > 1) {
      if(diff_heights(root->right) >= 0) {
	 new_root = root->right;
	 root->right = new_root->left;
	 new_root->left = root;
	 update_height(root);
      }
      else {
	 new_root = root->right->left;
	 root->right->left = new_root->right;
	 new_root->right = root->right;
	 root->right = new_root->left;
	 new_root->left = root;
	 update_height(new_root->right);
	 update_height(new_root->left);
      }
   }
   else if(diff_heights(root) < -1) {
      if(diff_heights(root->left) <= 0) {
         new_root = root->left;
	 root->left = new_root->right;
	 new_root->right = root;
	 update_height(root);
      }
      else {
	 new_root = root->left->right;
	 root->left->right = new_root->left;
	 new_root->left = root->left;
	 root->left = new_root->right;
	 new_root->right = root;
	 update_height(new_root->right);
	 update_height(new_root->left);
      }
   }

   update_height(new_root);
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

void printList(struct node *head) {
   struct node *cur = head->next;
   printf("list print out\n");

   while(cur != head) {
      printf("%d\n", cur->val);
      cur = cur->next;
   }
   printf("-----\n");
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
   struct node *list = calloc(1, sizeof(struct node));
   struct node *high_median = NULL, *low_median = NULL;
   list->prev = list;
   list->next = list;
   fprintf(stderr, "enter a num\n");
   
   while(scanf("%d\n", &val) && !feof(stdin)) {
      temp = calloc(1, sizeof(struct node));
      temp->val = val;
      temp->height = 0;
      tree = addToTree(tree, temp, list->prev, list->next);
      update_median(temp, &high_median, &low_median);
      printf("median = %lf\n", ((double)high_median->val + (double)low_median->val) / 2);
      fprintf(stderr, "enter a num\n");
   }

   printInOrder(tree);
   graphic(tree, 0);
   printList(list);
   return 0;
}
