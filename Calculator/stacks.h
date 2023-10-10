typedef struct Node1{
  float data;
  struct Node1 *next;
} node1;

typedef struct Node2{
  char c;
  struct Node2 *next;
} node2;

void push(node1 **stack, float data);
int is_empty(node1 *stack);
float pop(node1 **stack);
float top(node1 *stack);
void drop(node1 **stack);

void push2(node2 **stack, char c);
int is_empty2(node2 *stack);
char pop2(node2 **stack);
char top2(node2 *stack);
void drop2(node2 **stack);
