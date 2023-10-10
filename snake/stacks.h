typedef struct Node{
  int x;
  int y;
  struct Node *next;
} node;
void add_head(node **head);
void gotoxy(int x,int y);
void loadSnake(node *head);
int collisionSnake(int x, int y, node *head);
void move(node *head, char direction);
