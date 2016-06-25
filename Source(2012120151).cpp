#include <stdio.h>
#include <stdlib.h>
#include <string.h> //strlen
#include <malloc.h>

enum COLOR {RED,BLACK};
typedef enum COLOR COLOR;
#define WHITE 0
#define GRAY  1 //�� ���� for BFS,RBtree
#define HASH_SIZE 10000  //HASH ũ��

struct List* UserData[HASH_SIZE]; //List + Hash(key)�� UserProfile Data����
struct RBTree* WordData;          //WordData
struct RBTree* null; 
struct Vertex* FriendData;        //FriendData

struct TreeNODE* UniUSER;
struct TreeNODE* UniFriend;       //�ߺ�Ȯ�� Data

typedef struct List               //List ��� ����
{
	int val;  

	char *key;
	char *data;
	char *data2;

	List* next;
}List;
List* ALLOC_NODE(char key[],char data[],char data2[]){
List* N = (List*)malloc(sizeof(List));
N->key = (char*)malloc(sizeof(char)*sizeof(key));
N->data = (char*)malloc(sizeof(char)*sizeof(data));
N->data2 = (char*)malloc(sizeof(char)*sizeof(data2));
N->key = NULL;
N->data = NULL;
N->data2 = NULL;
N->val = NULL;
N->next = NULL;
return N;
}//�ʱⰪ �� �����Ҵ� �Լ�
List* INSERT_NODE(List* list, int val,char key[],char data[],char data2[]){
List* N = ALLOC_NODE(key,data,data2);
N->val = val;
N->next = list;
N->key = key;
N->data = data;
N->data2 = data2;
return N;
} //�����Լ�
void FIND_ID(struct List* list, char key[])
{
	struct List* P;
	for(P = list; P != NULL; P = P->next){
		if(strcmp(P->key, key) == 0) 
		{
			printf("%s" ,P->data2);
			break;
		}
	}
} //key�� id�� ã���ִ� �Լ�

//List

int Hash(char key[])
{
 char str[10];
 int a = 0;
 for(int i = 0; i< strlen(key);i++)
 {
	 if(a < 10000000)
	 {
	 sprintf(str,"%d",key[i]);
	 a *= abs(atoi(str));
	 }else a += abs(atoi(str));
 }
 return a % HASH_SIZE;
} //Hash ���� #1
int Hashkey(char key[]){
	int A;
	A = atoi(key);
	return A % HASH_SIZE;
}  //Hash ���� #2
int WordHash(char word[]){
	char strA[10],strB[10],strC[10],strD[10];	
	int A,B,C,D;
	int key;
	sprintf(strA,"%d",word[0]);
	sprintf(strB,"%d",word[1]);
	sprintf(strC,"%d",word[strlen(word) - 2]);
	sprintf(strD,"%d",word[strlen(word) - 1]);
	A = abs(atoi(strA));
	B = abs(atoi(strD));
	C = abs(atoi(strB))*abs(atoi(strC));
	D = strlen(word);
	key = (A+B*C)*A*D+A*D*(A+B+C+D);
	return key;
} //����->�ƽ�Ű��ȯ
int NextNum(int key)
{
	if (key <1000000) key *= key % 10;
	else key += key % 100;
	return key;
}//÷��

//�ؽ�

struct TreeNODE  //Ʈ����� ����
{
List* list;
char* key;

TreeNODE* Left;
TreeNODE* Right;
TreeNODE* Parent;

int Val;
int count;
char *word;
} Node;
struct TreeNODE* CREATE_NODE(int data,char word[],int count, char key[])  //�ʱⰪ �� �����Ҵ�
{
TreeNODE* newNode = (TreeNODE*)malloc(sizeof(Node));
newNode->word = (char*)malloc(sizeof(char)*sizeof(word));
newNode->Left = NULL;
newNode->Right = NULL;
newNode->Parent = NULL;
newNode->Val = data;
newNode->word = word;
newNode->count = count;

newNode->key = (char*)malloc(sizeof(char)*sizeof(key));
newNode->key = key;

newNode->list = NULL;

return newNode;
}
TreeNODE* TREE_INSERT(TreeNODE* Root,TreeNODE* New)               //���� �Լ�
{
TreeNODE* M;
TreeNODE* N = Root;
while (N != NULL)//N�� NULL�� �� ����.. Root���� New�� ���� ���س����鼭... ���ϵ� ���� �̵�..
 {
	M = N; //M���� �ڳడ ���� ��� N�� �־��ش�.
	if (New->Val < N->Val) N = N->Left;
	else N = N->Right;
 }
New->Parent = M; //New�� �θ���� M�̴�.
if(M == NULL)    //�ڳడ ���� ��尡 ���� ���(Tree�� NULL)
	Root = New;  //Root��忡�� New�� �־��ش�.
else if (New->Val < M->Val) // New�� Val�� �θ� M�� Val���� ������..
	M->Left = New;          //M�� �����ڳ࿡�� New�� ����.
else M->Right = New;

return Root; //Root�� ��ȯ�Ѵ�.
}
TreeNODE* BST_SEARCH(TreeNODE* tree,int Val, char word[], char key[])    //�˻��Լ�
{
TreeNODE* root;
root = tree;
while (root != NULL && Val != root -> Val && (strcmp(root->word,word) != 0))//÷��
{
if (Val < root -> Val)
root = root -> Left;
else
root = root -> Right;
}

return root;
}
void BST_INORDER(TreeNODE* root)  //Ʈ�� ��ȸ
{

  
if (root != NULL)
{
BST_INORDER(root -> Left);
printf("%s  %d\n",root->key,root->count);
BST_INORDER(root -> Right);
}
}
TreeNODE* TRANSPLANT(TreeNODE* Root,TreeNODE* X,TreeNODE* Y)
{
	if (X->Parent == NULL) Root = Y; //X�� �θ� NULL�̸� ��Ʈ�� Y�̴�.
	else if(X == X->Parent->Left) X->Parent->Left = Y;//X�� �� �θ��� ���ڳ��̸�.. �׺θ��� ���ڳ� �ڸ����� Y�� �־��ش�.
	else X->Parent->Right = Y;
	if (Y != NULL) Y->Parent = X->Parent;//Y�� �θ𿡴� ����X�� �θ� �־��ش�.
	//TreeB->Parent = TreeA->Parent;
	return Root; //Root�� ��ȯ�Ѵ�.

}
TreeNODE* TREE_MINIMUM(TreeNODE* Root)
{
	TreeNODE* N = Root;
	while(N->Left !=NULL)
	{
		N = N->Left;
	}
	return N;
}
TreeNODE* TREE_DELETE(TreeNODE* Root, TreeNODE* X)
{
	if(X->Left == NULL)             //�����Ϸ��� X����� ������ �������..
		TRANSPLANT(Root,X,X->Right);        // X �ڸ��� ���� X�� �������� �÷��ش�.
	else if (X->Right == NULL)      //�ݴ��..
		TRANSPLANT(Root,X,X->Left);         // X �ڸ��� ���� x�� ������ �÷��ش�.
	else                            //X�� �ڳడ �Ѵ� ������...
	{
		TreeNODE* Y = TREE_MINIMUM(X->Right);   //Y���� X�� �������� �ּڰ�(Successor)�� �־��ش�.
		
		if(Y->Parent != X)                  //���� Y�� �θ� X�� �ƴ� ���..
		{
			TRANSPLANT(Root,Y,Y->Right);     //Y�ڸ��� Y�� �����ڳฦ �÷��ش�.
			Y->Right = X->Right;             //Y�� �����ڳ࿡�� X�� �����ڳฦ �־��ش�.
			Y->Right->Parent = Y;            //Y�� �����ڳ�, �� ���� X�� �����ڳ��� �θ� Y�� �����ش�.
		}

		TRANSPLANT(Root,X,Y);  //X�� �ڸ��� Y�� �÷��ش�.
		Y->Left = X->Left;          //Y�� ���ڳ� �ڸ����� ���� X�� ���ڳฦ �־��ش�.
		Y->Left->Parent = Y;        //Y�� ���ڳ� �ڸ��� ���� X�� ���ڳ��� �θ� Y�� �����ش�.

	}
	return Root; // Root�� ��ȯ�Ѵ�.
}

void BST_TRANSITION(TreeNODE* root,TreeNODE* X)   //������ BST�� count�� �������� ���ο� BST�� �����.
{
if (root != NULL)
{
BST_TRANSITION(root -> Left,X);
if(root->count >2){
X = TREE_INSERT(X , CREATE_NODE(root->count,root->word,1,root->key));
}
BST_TRANSITION(root -> Right,X);
}
}	
void INSERT_TREENODE(TreeNODE* Tree, TreeNODE* newNode)
{

    if (newNode->Val > Tree->Val)
    {
    if (Tree->Right != NULL) INSERT_TREENODE(Tree->Right, newNode);
    else Tree->Right = newNode;
    }
    else if (newNode->Val < Tree->Val)
    {
    if (Tree->Left != NULL) INSERT_TREENODE(Tree->Left, newNode);
    else Tree->Left = newNode;
    }

}
int SEARCH_NODE_F(TreeNODE* Tree, int findData,char word[]) // Tree�� �ش� word�� ������.. word�� �ƽ�Ű���� ������ NULL�� ��ȯ
{
     if (Tree == NULL) {
         return findData;
     }
     if (Tree->Val == findData)    //�̹� ������........
     {
	 if(strcmp(Tree->word,word) == 0){//Tree->word���� key���� ����ִ�.
	    Tree->count++;
		return NULL;
	 }else{                     //�˻��ܾ��� �ش� ���ڴ� �̹� ������,�׷��� �� �ܾ�� ���ο� �ܾ� �̹Ƿ� �߰����־����..
		SEARCH_NODE_F(Tree ->Right, NextNum(findData), word); //�ӽ� ����
	 }
     }
     else if (Tree->Val > findData) SEARCH_NODE_F(Tree->Left, findData, word);
     else SEARCH_NODE_F(Tree->Right, findData, word);
}//÷��
void BST_TRANSITION_F(TreeNODE* tree,TreeNODE* X) { //������ BST�� count�� �������� ���ο� BST�� �����.
	if (tree) {
	INSERT_TREENODE(X, CREATE_NODE(tree->count,tree->word,1,tree->key));
	}
	if(tree ->Left){ 
	BST_TRANSITION_F(tree->Left,X);
	}
	if (tree ->Right){ 
	BST_TRANSITION_F(tree->Right,X);
	}
}

//BST

struct RBTree          //Red-Black Node ����
{
int            key;
COLOR           color;

struct List* First;
char *datakey;
char *data; //������
int Cnt;

struct RBTree   *Left;
struct RBTree   *Right;
struct RBTree   *p;
};
typedef struct RBTree*  RBTREE;
RBTREE LEFT_ROTATE(RBTREE tree, RBTREE X, RBTREE null)
{
RBTREE y = X -> Right;
X -> Right = y -> Left;
if (y -> Left != null)
y -> Left -> p = X;
y -> p = X -> p;
if (X -> p == null)
tree = y;
else if (X == X -> p -> Left)
X -> p -> Left = y;
else
X -> p -> Right = y;
y -> Left = X;
X -> p = y;
return tree;
}
RBTREE RIGHT_ROTATE(RBTREE tree, RBTREE X, RBTREE null)
{
RBTREE y = X -> Left;
X -> Left = y -> Right;
if (y -> Right != null)
y -> Right -> p = X;
y ->p = X -> p;
if (X -> p == null)
tree = y;
else if (X == X -> p -> Right)
X -> p -> Right = y;
else
X -> p -> Left = y;
y -> Right = X;
X -> p = y;
return tree;
}
RBTREE RB_INSERT_FIXUP(RBTREE tree, RBTREE New, RBTREE null)
{
RBTREE y;
while ( New -> p -> color == RED)
{
if( (New -> p) == (New -> p -> p -> Left))
{
y = New -> p -> p -> Right;
if (y -> color == RED)
{
New -> p -> color = BLACK;
y -> color = BLACK;
New -> p -> p -> color = RED;
New = New -> p -> p;
}
else
{
if ( New == New -> p -> Right)
{
New = New -> p;
tree = LEFT_ROTATE(tree,New,null);
}
New -> p -> color = BLACK;
New -> p -> p -> color = RED;
tree = RIGHT_ROTATE(tree,New->p->p,null);
}
}
else
{
y = New -> p -> p -> Left;
if (y -> color == RED)
{
New -> p -> color = BLACK;
y -> color = BLACK;
New -> p -> p -> color = RED;
New = New -> p -> p;
}
else
{
if ( New == New -> p -> Left)
{
New = New -> p;
tree = RIGHT_ROTATE(tree,New,null);
}
New -> p -> color = BLACK;
New -> p -> p -> color = RED;
tree = LEFT_ROTATE(tree,New->p->p,null);
}
}
}

tree -> color = BLACK;
return tree;
}
RBTREE RB_INSERT(RBTREE tree, RBTREE New, RBTREE null)
{
RBTREE y = null;
RBTREE x = tree;
while (x != null)
{
y = x;
if ((New -> key) < (x -> key))
x = x -> Left;
else
x = x -> Right;
}
New -> p = y;
if (y == null)
tree = New;
else if ((New -> key) < (y -> key))
y -> Left = New;
else
y -> Right = New;
New -> Left = null;
New -> Right = null;
New -> color = RED;
return RB_INSERT_FIXUP(tree,New,null);
}
RBTREE MAKE_NODE(int New ,RBTREE null,char datakey[],char data[],int Cnt)
{
RBTREE tmp;
tmp =  (struct RBTree*)malloc(sizeof(RBTree));

tmp->datakey = (char*)malloc(sizeof(char)*strlen(datakey));
tmp->data =  (char*)malloc(sizeof(char)*strlen(data));
tmp->data = data;
tmp->datakey = datakey;
tmp->Cnt = Cnt;
tmp->First = NULL;

tmp ->key = New;
tmp ->Left = null;
tmp -> Right = null;
tmp ->p = null;
return tmp;
}
RBTREE MAKE_NULL()
{
RBTREE tmp;
tmp = (struct RBTree*)malloc(sizeof(RBTree));

tmp -> datakey = (char*)malloc(sizeof(char)*50);
tmp -> data =  (char*)malloc(sizeof(char)*50);
tmp -> data = NULL;
tmp -> datakey = NULL;
tmp->Cnt = 0;
tmp->First = NULL;

tmp -> key = 0;
tmp ->Left = NULL;
tmp -> Right = NULL;
tmp ->p = NULL;
tmp ->color = BLACK;
return tmp;
}
void INORDER(RBTREE root, RBTREE nil)
{

  
if (root != nil)
{
INORDER(root -> Left,nil);
printf("%s  %d\n",root->data,root->Cnt);
INORDER(root -> Right,nil);
}
}
RBTREE TREE_MINIMUM(RBTREE root, RBTREE null)
{
RBTREE tmp = root;
while (tmp -> Left != null)
{
tmp = tmp -> Left;
}
return tmp;
}
RBTREE TREE_SUCCESSOR(RBTREE root, RBTREE null)
{
RBTREE tmp;
if (root -> Right != null)
return TREE_MINIMUM(root -> Right,null);
tmp = root->p;
while((tmp != null) && (root == tmp->Right))
{
root = tmp;
tmp = tmp -> p;
}
return tmp;
}
RBTREE RB_DELETE_FIXUP(RBTREE tree, RBTREE put, RBTREE null)
{
RBTREE w;
while((put != tree) &&(put -> color == BLACK))
{
if(put == put -> p -> Left)
{
w = put -> p -> Right;
if (w -> color == RED)
{
w -> color = BLACK;
put -> p -> color = RED;
tree = LEFT_ROTATE(tree,put->p,null);
w = put -> p -> Right;
}
if ((w->Left->color == BLACK)&&(w->Right->color == BLACK))
{
w -> color = RED;
put = put -> p;
}
else
{
if(w -> Right -> color == BLACK)
{
w->Left->color = BLACK;
w-> color = RED;
tree = RIGHT_ROTATE(tree,w,null);
w = put->p->Right;
}
w -> color = put -> p -> color;
put -> p -> color = BLACK;
w -> Right -> color = BLACK;
tree = LEFT_ROTATE(tree,put->p,null);
put = tree;
}
}
else
{
w = put -> p -> Left;
if (w -> color == RED)
{
w -> color = BLACK;
put -> p -> color = RED;
tree = RIGHT_ROTATE(tree,put->p,null);
w = put -> p -> Left;
}
if ((w->Right->color == BLACK)&&(w->Left->color == BLACK))
{
w -> color = RED;
put = put -> p;
}
else
{
if(w -> Left -> color == BLACK)
{
w->Right->color = BLACK;
w-> color = RED;
tree = LEFT_ROTATE(tree,w,null);
w = put->p->Left;
}
w -> color = put -> p -> color;
put -> p -> color = BLACK;
w -> Left -> color = BLACK;
tree = RIGHT_ROTATE(tree,put->p,null);
put = tree;
}
}
}
put -> color = BLACK;
return tree;
}
RBTREE RB_DELETE(RBTREE tree, RBTREE put, RBTREE null)
{
RBTREE y;
RBTREE x;
if ((put -> Left == null)||(put->Right == null))
y = put;

else
y = TREE_SUCCESSOR(put,null);
if(put -> Left != null)
x = y -> Left;
else
x = y -> Right;
 
x->p = y->p;
 
if (y -> p == null)
tree = x;
else
{
if (y == y -> p -> Left)
y -> p -> Left = x;
else
y -> p -> Right = x;
}
if ( y != put)
put -> key = y -> key;
if (y -> color == BLACK)
tree = RB_DELETE_FIXUP(tree,x,null);
return tree;
}
int Count = 0;
RBTREE TREE_SEARCH(RBTREE tree, int d, char word[],RBTREE null)
{
RBTREE root;
root = tree;
while ((root != null) && (d != root -> key) && (strcmp(root->data,word) != 0))//÷��
{
if (d < root -> key)
root = root -> Left;
else
root = root -> Right;
}

return root;
}
//RBtree
void TRANSITION(RBTREE root, TreeNODE* X, RBTREE nil)
{
if (root != nil)
{
TRANSITION(root -> Left,X,nil);
if(root->Cnt >2){
X = TREE_INSERT(X, CREATE_NODE(root->Cnt,root->data,1,root->datakey));
}
TRANSITION(root -> Right,X,nil);
}
} //Red-BlackƮ������ count���� �������� BST�� �������..


typedef struct Adj { //��������Ʈ ����ü ����(for Edge)
  int n;
  char *key;
  struct Adj* next;
} Adj;
void Adj_init(Adj* self) { //Adj ����ü �ʱⰪ ����(���� �Ҵ�x), �̹� �Ҵ���� Adj��带 �Է¹���
  self->n = 0;
  self->next = NULL;
}
typedef struct Vertex{  //��� ����ü ����(for DFSVertex)
  int color;  
  int parent;   //�θ� index
  char name[10];
  int n;        //index
  Adj* first;   //��������Ʈ�� �Ӹ� ����;

  char *user;
  char *friends;
  Vertex* Next;  //��������Ʈ ����
  
  int d, f;
} Vertex;
Vertex* Vertex_make(char user[],char friends[]) { //Vertex����ü �ʱⰪ ����,�̹� �����Ҵ���� Vertex��带 �Է¹���
  Vertex* self = (Vertex*)malloc(sizeof(Vertex));
  self->Next = (Vertex*)malloc(sizeof(Vertex));
  self->Next = NULL;
  self->user = (char*)malloc(sizeof(char)*strlen(user));
  self->friends = (char*)malloc(sizeof(char)*strlen(friends));
  self->user = user;
  self->friends = friends;
  self->color = 0;
  self->parent = -1;
  strcpy(self->name, "(none)");
  self->n = 0;
  self->first = NULL;

  self->d = 0;
  self->f = 0;
  return self;
}
Vertex* Vertex_init() { //Vertex����ü �ʱⰪ ����,�̹� �����Ҵ���� Vertex��带 �Է¹���
  Vertex* self = (Vertex*)malloc(sizeof(Vertex));
  self->Next = (Vertex*)malloc(sizeof(Vertex));
  self->Next = NULL;
  self->user = (char*)malloc(sizeof(char)*50);
  self->friends = (char*)malloc(sizeof(char)*50);
  self->user = NULL;
  self->friends = NULL;
  self->color = 0;
  self->parent = -1;
  strcpy(self->name, "(none)");
  self->n = 0;
  self->first = NULL;

  self->d = 0;
  self->f = 0;
  return self;
}
Vertex* INSERT_LIST(Vertex* list, Vertex* X)
{
Vertex* N = X;
N->Next = list;
return N;
}
void Vertex_add(Vertex* self, Vertex* v) {  //Vertex �� Adj����ü �����Ҵ� �� ��������Ʈ �߰�
  Adj* a = (Adj *)malloc(sizeof(Adj)); 
  a->key = (char*)malloc(sizeof(v->user));
  a->n = v->n;
  a->key = v->user;
  a->next = self->first;
  self->first = a; //�߰��Ǿ� list�� �ٲ�..
} // �߿�!!!!

void Print_Friend(Vertex* list)
{
    Adj* P;
	for(P = list->first; P != NULL; P = P->next){
		printf("%s \n" ,P->key);
	}
} 
void FIND_Friend(Vertex* list, char key[])
{
    Vertex* P;
	for(P = list; P != NULL; P = P->Next){
		if(strcmp(P->user, key) == 0) 
		{
			//printf("%d \n" ,P->n);
			Print_Friend(P);
			break;
		}
	}
} 


typedef struct {
  int* Arr;
  int front;
  int rear;
  int sz;//�־�ߵ�..
} Queue; // ť����
void Queue_init(Queue* self) //����� Queue ����ü �ϳ��� �Է� �޾�.. �ʱⰪ ����..
{
  self->front = 0;
  self->rear = 0;
  self->sz = 0;
  self->Arr = NULL;
}
void Queue_create(Queue* self, int sz) {
  self->sz = sz;
  self->Arr = (int*)malloc(sizeof(int)*sz);
}
void Queue_enqueue(Queue* self, int val) {
  self->Arr[self->rear] = val;
  self->rear = (self->rear + 1) % self->sz;
}
int Queue_dequeue(Queue* self) {
  int res = self->Arr[self->front];
  self->front = (self->front + 1) % self->sz;
  return res;
}
int Queue_is_empty(Queue* self) {
  return self->front == self->rear;
}

int dfs_time = 0;

void Dfs_visit(Vertex* vertices, int nelem, int u) {//u��° Vertex�� ���Ͽ�..
  dfs_time++;
  vertices[u].d = dfs_time;  //dfs_visit�Լ��� �����ϴ� ī��Ʈ�� �����ش�.
  vertices[u].color = GRAY; // ȸ������ ������ְ�..
  for (Adj* v = vertices[u].first; v; v = v->next) //u�� ��������Ʈ�� index���� �о�鼭..
  {
    if (vertices[v->n].color == WHITE) {//���߿� n��°�� vertex�� ���� �Ͼ���̸�..
      vertices[v->n].parent = u;        // �θ��ε����� u�� �������ְ�..
      Dfs_visit(vertices, nelem, v->n);       // n�� ���Ͽ� ����� ������ ���ش�..
    }
  }
  vertices[u].color = BLACK;//���� Ư����忡 ���Ͽ�.. ������ index�� �߿� �Ͼ���� �����ٸ�.. �ش���� ������ó��
  dfs_time++;
  vertices[u].f = dfs_time;
}
void Dfs(Vertex* vertices, int nelem) {
  for(int u = 0; u < nelem; u++) {
    vertices[u].color = WHITE;
    vertices[u].parent = -1;
  }//�ʱ�ȭ..
  dfs_time = 0;
  for(int u = 0; u < nelem; u++) { //��� index�� �ش��ϴ� vertex�鿡 ���Ͽ�..visit�� ����.
    if (vertices[u].color == WHITE) {//���� 0���� white�̸�.
      Dfs_visit(vertices, nelem, u);
    }
  }
}
#define NELEM 10000
void Transpose_dfs(Vertex* vertices)
{
  Adj* vertices_first[NELEM];
  for(int i=0; i< NELEM; i++){
    vertices_first[i]=vertices[i].first;
  }
  for(int i = 0; i < NELEM; i++) {
    vertices[i].d=0;
    vertices[i].f=0;
    vertices[i].color=0;
    vertices[i].parent=-1;
    vertices[i].first=NULL;
  }
  for(int i=0; i<NELEM; i++)
  {
    for(Adj* p=vertices_first[i];p;p=p->next)
    {
          Vertex_add(&vertices[p->n],&vertices[i]);
    }
  }
}
//DFS

int LOAD_DATA_F(){//����Ʈ
FILE *fp = fopen("friend.txt","r");

if(fp == NULL ){
printf("���Ͽ������\n");
}

int number = 0;
char line[256];
char *key;
char *friendkey;
char *data;

UniFriend = CREATE_NODE(0,"0",0,"0");//÷��
FriendData = Vertex_init();

int N;
int index = 0;
while(!feof(fp))
  {
  fgets(line,sizeof(line),fp);
  if (number % 3 == 0){
  key =(char*)malloc(strlen(line)-1);
  sprintf(key,"%s",line);

  }else if(number % 3 == 1){
  friendkey =(char*)malloc(strlen(line)-1);
  sprintf(friendkey,"%s",line);

  }else if(strcmp(line,"\n") == 0)
  {
	N = SEARCH_NODE_F(UniFriend,Hashkey(key),key);
	Vertex* New = Vertex_make(key,friendkey);
   
	if(N != NULL)//���ο� key
    {
	INSERT_TREENODE(UniFriend, CREATE_NODE(N,key,1,friendkey));
	New->n = index; 
	index++;
	FriendData = INSERT_LIST(FriendData,New);
	//friendCnt = 0;
	}
	Vertex_add(FriendData,New);
    //friendCnt++;
   }
  number++;
  }

fclose(fp); 
return number / 3;
}
int LOAD_DATA(char name[],int num)//"user.txt" 4,"friend.txt" 3,"word.txt" 4
{

FILE *fp = fopen( name ,"r");

if(fp == NULL ){
printf("���Ͽ������\n");
}
//�ʱ� ���� �Ҵ�
RBTREE val;
null = MAKE_NULL();
WordData = null;


UniUSER = CREATE_NODE(0,"0",0,"0");

//
int number = 0;
int Cnt = 0;
char line[50];
int FKEY = 0;

char *key;
char *data;//������ Or ģ��key
char *data2;//���̵� Or �ܾ�


while(!feof(fp))
  {
  fgets(line,sizeof(line),fp);
	 if(strcmp(line,"\n") != 0)
	 {
          if (number % num == 0){
          key =(char*)malloc(strlen(line)-1);
          sprintf(key,"%s",line);
          }else if(number % num == 1){
          data =(char*)malloc(strlen(line)-1);
          sprintf(data,"%s",line);
		  }else if(number % num == 2 && num == 4){
          data2 =(char*)malloc(strlen(line)-1);
          sprintf(data2,"%s",line);
          }
     number++;
	 }
     else
     {
		 number = 0;

		 if(strcmp(name,"user.txt") == 0){
		 
			 UserData[Hashkey(key)] = INSERT_NODE(UserData[Hashkey(key)],Hashkey(key),key,data,data2);//key�� date,id�� ��´�.

		 }
		 else if(strcmp(name,"friend.txt") == 0){
			 /*
		     Vertex* New = Vertex_make(key,data);
		     Vertex_add(FriendData,New);
		     FriendData = INSERT_LIST(FriendData,New);
		     */
		 }
		 else{
		   if(Cnt == 0) // ó������?
		   {
		   val = MAKE_NODE(WordHash(data2),null,key,data2,1);
		   WordData = RB_INSERT(WordData,val,null);
		   UniUSER = TREE_INSERT(UniUSER , CREATE_NODE(Hashkey(key),key,1,key));
		   }
		   RBTREE N = TREE_SEARCH(WordData,WordHash(data2),data2,null);//�˻��ϰ�..	 
		   TreeNODE* K = BST_SEARCH(UniUSER ,Hashkey(key),data2,key);

		   if(N == null && Cnt != 0)
		   {
		   val = MAKE_NODE(WordHash(data2),null,key,data2,1);
		   WordData = RB_INSERT(WordData,val,null);
		   }
		   else
		   {
		   N->First = INSERT_NODE(N->First,0,key,data,data2);
	       N->Cnt++;
		   }

		   if(K == NULL && Cnt != 0)
		   {
		   UniUSER = TREE_INSERT(UniUSER , CREATE_NODE(Hashkey(key),key,1,key));
		   }
		   else
		   {
	       K->count++;
		   }
		 }
	 Cnt++;
     }

  }

fclose(fp); 

return Cnt;
}

bool SW = true;
void PRINT_MIN(TreeNODE* Tree,bool choice)// true : friends, false : tweets
{
if (Tree == NULL) return;
PRINT_MIN(Tree->Left,choice);
if(Tree->count != 0&& SW == true){

    if(choice == true) printf("Minimum # of friends : %d �� \n",Tree->Val);
	else printf("Minimum tweets per user : %d �� \n",Tree->Val);

SW = false; 
}
PRINT_MIN(Tree->Right,choice);
} //statistic
void PRINT_MAX(TreeNODE* Tree,bool choice)// true : friends, false : tweets
{
if (Tree == NULL) return;
PRINT_MAX(Tree->Right, choice);
if(Tree->count != 0 && SW == true){
	if(choice == true) printf("Maximum # of friends : %d �� \n",Tree->Val);
	else printf("Maximum tweets per user : %d �� \n",Tree->Val);
	SW = false; 
}
PRINT_MAX(Tree->Left, choice);
} //statistic
int SUM = 0;
int COUNT =0;
void CALC_AVG(TreeNODE* Tree)
{
if (Tree == NULL) return;
CALC_AVG(Tree->Right);
if(Tree->count != 0){
    SUM += Tree->count;
	COUNT++;
}
CALC_AVG(Tree->Left);
} //statistic
void PRINT_AVG(TreeNODE* Tree,bool choice)// true : friends, false : tweets
{
CALC_AVG(Tree);
    if(choice == true) printf("Average # of friends : %d �� \n",SUM / COUNT);
    else printf("Average tweets per user : %d �� \n",SUM / COUNT);
} //statistic
void FIND_USER(){
   
   char word[50];
   printf(">�˻��� �ܾ� : ");
   scanf("%s", &word);
   printf("+++++++++++++++++++++++++++++++++++++++++++\n");
   sprintf(word,"%s\n",word);
   RBTREE N = TREE_SEARCH(WordData,WordHash(word),word,null);
   if(N->First){
		for(struct List* P = N->First; P->next != NULL; P = P->next)
		{
			//printf("%s" ,P->key);
			FIND_ID(UserData[Hashkey(P->key)],P->key);
			//FIND_Friend(FriendData,P->key);
		}
	}

} //����� �˻�
void Init()
{
printf("           >>DATA INFO<<\n");
printf("+++++++++++++++++++++++++++++++++++++++++++\n");
printf("Total users: %d\n", LOAD_DATA("user.txt",4));
printf("Total friendship records: %d\n", LOAD_DATA_F());
printf("Total tweets: %d\n", LOAD_DATA("word.txt",4));
printf("+++++++++++++++++++++++++++++++++++++++++++\n");
printf("           >>Select Menu<<\n");
printf("+++++++++++++++++++++++++++++++++++++++++++\n");
printf("1.Show Statistics\n");
printf("2.Show Top 5 most tweeted words\n");
printf("3.Show Top 5 most tweeted users\n");
printf("4.Find users who tweeted a word\n");
printf("5.Delete all mention & users related to a word\n");
printf("99.Quit\n");

}
int Maxcount = 0;
void PRINT_TOP5_WORD(TreeNODE* Tree)
{
if (Tree == NULL) return;
PRINT_TOP5_WORD(Tree->Right);
if(Tree->count != 0){
	char temp[256];
	strcpy(temp,Tree->word);
	temp[strlen(Tree->word) - 1] = NULL;
	if(Maxcount == 0) printf("Q. Top Five most tweeted words??\n");
	if(Maxcount < 5) printf("%d��° -> %s (%d��) \n",Maxcount + 1, temp, Tree->Val);
	Maxcount++;
}
PRINT_TOP5_WORD(Tree->Left);
}
void PRINT_TOP5_USER(TreeNODE* Tree)
{
if (Tree == NULL) return;
PRINT_TOP5_USER(Tree->Right);
if(Tree->count != 0){
	char temp[256];
	strcpy(temp,Tree->word);
	temp[strlen(Tree->word) - 1] = NULL;
	if(Maxcount == 0) printf("Q. Top Five most tweeted users??\n");
	if(Maxcount < 5) printf("%d��° -> %s (%d��) \n",Maxcount + 1, temp, Tree->Val);
	Maxcount++;
}
PRINT_TOP5_USER(Tree->Left);
}


void Show_Statistic()
{ 
TreeNODE* UniUSER_Cnt = CREATE_NODE(0,"0",0,"0");
TreeNODE* UniFriend_Cnt = CREATE_NODE(0,"0",0,"0");

BST_TRANSITION(UniUSER,UniUSER_Cnt);
BST_TRANSITION_F(UniFriend,UniFriend_Cnt);


SW = true;
PRINT_MIN(UniFriend_Cnt,true);
SW = true;
PRINT_MAX(UniFriend_Cnt,true);
SUM = 0;
COUNT = 0;
PRINT_AVG(UniFriend,true);
printf("\n");

SW = true;
PRINT_MIN(UniUSER_Cnt,false);
SW = true;
PRINT_MAX(UniUSER_Cnt,false);
SUM = 0;
COUNT = 0;
PRINT_AVG(UniUSER,false);
printf("\n");

}
int main(void)
{
Init(); // �ʱ� ȭ��
ANSWER:
printf("+++++++++++++++++++++++++++++++++++++++++++\n");
printf("���ϴ� �޴��� ���ÿ�(0~6) : ");
int Answer;
scanf("%d", &Answer);
printf("\n+++++++++++++++++++++++++++++++++++++++++++\n");

 if(Answer == 1 ){          //���
    Show_Statistic();
	goto ANSWER;
   }
 
   else if(Answer == 2)    //Top 5 words
   {
	TreeNODE* UniWORD_Cnt = CREATE_NODE(0,"0",0,"0");
	TRANSITION(WordData,UniWORD_Cnt,null);
    Maxcount = 0;
    PRINT_TOP5_WORD(UniWORD_Cnt);
   goto ANSWER;
   }
   
   else if(Answer == 3)     //Top 5 users
   {
    TreeNODE* UniUSER_Cnt = CREATE_NODE(0,"0",0,"0");
    BST_TRANSITION(UniUSER,UniUSER_Cnt);
	Maxcount = 0;
    PRINT_TOP5_USER(UniUSER_Cnt);
   goto ANSWER;
   }
   
   else if(Answer == 4)     //Find User related to a word
   {
    FIND_USER();
   goto ANSWER;
   }
   
   else if(Answer == 5)      // Delete the word & users
   {
   char word[256];
   printf(">���� �ܾ� : ");
   scanf("%s", &word);
   printf("+++++++++++++++++++++++++++++++++++++++++++\n");
   sprintf(word,"%s\n",word);
   TreeNODE* R;
   RBTREE N = TREE_SEARCH(WordData,WordHash(word),word,null);
   N->Cnt = 0;
   N->First = NULL;
   WordData = RB_DELETE(WordData,N,null);
   printf("\n>�ش� �ܾ�� ���õ� ��� ����� �����߽��ϴ�.");
   printf("\n>�ش� �ܾ ����� ����ڸ� ��� �����߽��ϴ�.\n\n");
   goto ANSWER;
   }
   else if(Answer == 99)  //Quit
   {
   return 0;
   }
   
   else
   {
   printf("\n1~5������������ ����ּ���!!\n\n");
   printf("+++++++++++++++++++++++++++++++++++++++++++\n");
   goto ANSWER;
   }
return 0;
}