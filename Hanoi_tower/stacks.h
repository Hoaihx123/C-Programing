typedef struct Node{
  int data;
  struct Node *next;
} node;
void push(node **stack, int data);
int is_empty(node *stack);
int pop(node **stack);
int top(node *stack);
void drop(node **stack);
void list(node *stack);
