#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef char elementtype[5];

typedef struct Node_type
{
  elementtype element;
  struct Node_type* left, *right;
} NodeType;

typedef NodeType *TreeType;

void MakeNullTree (TreeType *T)
{
        (*T) = NULL;
}

int isEmptyTree (TreeType T)
{
        return T == NULL;
}

TreeType LeftChild (TreeType n)
{
        if (n != NULL) return n->left;
        else return NULL;
}

TreeType RightChild (TreeType n)
{
        if (n != NULL) return n->right;
        else return NULL;
}

NodeType* CreateNode (elementtype NewData)
{
        NodeType* N = (NodeType*)malloc(sizeof(NodeType));
        if (N != NULL)
        {
                N->left = NULL;
                N->right = NULL;
                strcpy(N->element, NewData);
        }
        return N;
}

int isLeaf (TreeType n)
{
        if (n != NULL) return (LeftChild(n)==NULL)&&(RightChild(n)==NULL);
        else return -1;
}

int nb_nodes (TreeType T) //count the number of nodes in a binary tree
{
        if (isEmptyTree(T)) return 0;
        else return 1 + nb_nodes(LeftChild(T)) + nb_nodes(RightChild(T));
}

TreeType CreateFrom2 (elementtype v, TreeType l, TreeType r)
{
        //create a binary tree from 2 binary trees
        TreeType N = (NodeType*)malloc(sizeof(NodeType));
        strcpy(N->element, v);
        N->left = l;
        N->right = r;
        return N;
}

TreeType AddLeft (TreeType *Tree, elementtype NewData)
{
        NodeType *NewNode = CreateNode(NewData);
        if (NewNode == NULL) return NewNode;
        if (*Tree == NULL) *Tree = NewNode;
        else
        {
                NodeType *Lnode = *Tree;
                while (Lnode->left != NULL) Lnode = Lnode->left;
                Lnode->left = NewNode;
        }
        return NewNode;
}

TreeType AddRight (TreeType *Tree, elementtype NewData)
{
        NodeType *NewNode = CreateNode(NewData);
        if (NewNode == NULL) return NewNode;
        if (*Tree == NULL) *Tree = NewNode;
        else
        {
                NodeType *Rnode = *Tree;
                while (Rnode->right != NULL) Rnode = Rnode->right;
                Rnode->right = NewNode;
        }
        return NewNode;
}

int height (TreeType T)
{
    if (T == NULL) return 0;
    else
    {
        //compute the height of each subtree
        int lheight = height(T->left);
        int rheight = height(T->right);

        //use the larger one
        if (lheight > rheight) return lheight+1;
        else return rheight+1;
    }
}

void freeTree(TreeType T)
{
  if(T != NULL)
  {
      freeTree(T->left);
      freeTree(T->right);
      free(T);
  }
}

typedef TreeType elementType;
typedef struct Node
{
  elementType element;
  struct Node* next;
} Node;
typedef Node* Position;
typedef struct
{
  Position front;
  Position rear;
} Queue;

void MakeNullQueue (Queue *Q)
{
  Position header = (Node*)malloc(sizeof(Node));
  header->next = NULL;
  Q->front = header;
  Q->rear = header;
}

int isEmptyQueue (Queue Q)
{
  return (Q.front == Q.rear);
}

void EnQueue (elementType x, Queue *Q) //InsertAtTail
{
  Q->rear->next = (Node*)malloc(sizeof(Node));
  Q->rear = Q->rear->next;
  Q->rear->element = x;
  Q->rear->next = NULL;
}

void DeQueue (Queue *Q) //DeleteAtHead
{
  if (!isEmptyQueue(*Q))
    {
      Position T;
      T = Q->front;
      Q->front = Q->front->next;
      free(T);
    }
  else printf("\nError: Queue is empty.\n");
}

int count_elements_Queue (Queue *Q)
{
        if (isEmptyQueue(*Q)) return 0;
        int count=0;
        Position tmp = Q->front->next;
        while (tmp != NULL)
        {
                count++;
                tmp = tmp->next;
        }
        return count;
}

void freeQueue (Queue *Q)
{
  Position to_free;
  while ((to_free=Q->front) != NULL)
    {
      Q->front = Q->front->next;
      free(to_free);
    }
}

void readfile (FILE *f, Queue *Q)
{
        f = fopen("USopen.txt","r");
        if (f == NULL)
        {
                printf("Cannot open file USopen.txt!\n");
                return;
        }
        while (!feof(f))
        {
                elementtype team;
                TreeType tree;
                MakeNullTree(&tree);
                fscanf(f, "%s ", team);
                AddLeft(&tree, team);
                EnQueue(tree, Q);
        }
        fclose(f);
}

void game (Queue *Q, int numteam)
{
        if (numteam == 1) return;
        for (int i=1; i<=numteam/2; i++)
        {
                elementtype team1, team2;
                TreeType tree1 = Q->front->next->element;
                strcpy(team1, tree1->element);
                DeQueue(Q);
                TreeType tree2 = Q->front->next->element;
                strcpy(team2, tree2->element);
                DeQueue(Q);

                int winner = 1 + rand()%(2-1+1); //random from 1 to 2
                TreeType wintree;
                if (winner == 1) wintree = CreateFrom2(team1, tree1, tree2);
                else if (winner == 2) wintree = CreateFrom2(team2, tree1, tree2);
                EnQueue(wintree, Q);
        }
        game(Q, numteam/2);
}

int maxspace = 0;
void print_result (TreeType T, int space)
{
    if (T == NULL)
    {
            maxspace = space;
            return;
    }

    space += 10;

    print_result(T->left, space);

    for (int i=space; i<maxspace; i++) printf(" ");
    printf("%s\n", T->element);

    print_result(T->right, space);
}

void printGivenLevel (TreeType T, int level, FILE *f) //Print nodes at a given level
{
    if (T == NULL) return;
    if (level == 1)
    {
            char s[80];
            sprintf(s, "\t%4s - %-4s ---> %s\n", T->left->element, T->right->element, T->element);
            fputs(s, f);
            //puts(s);
    }
    else if (level > 1)
    {
        printGivenLevel(T->left, level-1, f);
        printGivenLevel(T->right, level-1, f);
    }
}

void save_result_to_file (TreeType T, FILE *f)
{
    //function to print REVERSE level order traversal a tree to file f
    f = fopen("treegame.txt","w+");
    if (f == NULL)
    {
            printf("Cannot open file treegame.txt!\n");
            return;
    }

    int h = height(T)-1;
    for (int i=h; i>=1; i--)
    {
            if (i == 4) fputs("VONG LOAI:\n", f);
            if (i == 3) fputs("\nTU KET:\n", f);
            if (i == 2) fputs("\nBAN KET:\n", f);
            if (i == 1) fputs("\nCHUNG KET:\n", f);
            printGivenLevel(T, i, f);
    }
    fclose(f);
}

int main()
{
  srand(time(NULL));
  FILE *f;

  Queue *Q;
  MakeNullQueue(Q);

  readfile(f, Q);
  game(Q, 16);

  print_result(Q->front->next->element, 0);
  save_result_to_file(Q->front->next->element, f);

  freeTree(Q->front->next->element);
  freeQueue(Q);
  return 0;
}
