#include <stdio.h>  //표준 입출력
#include <stdlib.h> //atoi
#include <string.h> //strlen
#include <malloc.h>
#include <Windows.h>//유니코드

#define MAX_LENGTH 256
#define WORD_SIZE 50
#define HASH 1000

struct NODE* userlist[HASH];
//struct NODE* wordlist[HASH];
//#define MAX_NUM 1000000
//struct NODE* friendlist[MAX_NUM];
struct AdjNODE* friendlist;
struct AdjNODE* wordlist;
struct TreeNODE* Uniqueword; //트리노드 선언


////////////////////////////////////////////////////////////////////////////Hash Function


int Hash(char word[]){
	char string1[WORD_SIZE];
	char string2[WORD_SIZE];	
	int A = 0;
	for(int i = 0; i < strlen(word) / 2;i++)
	{
	sprintf(string1,"%d",word[i]);
	sprintf(string2,"%d",word[i+1]);
	A += abs(atoi(string1)) + abs(atoi(string2));
	}
	return A % HASH;
}

int Hashkey(char key[]){
	int A;
	A = atoi(key);
	return A % HASH;
}

int Ramdom(int key)
{
	key += 1;
	if (key <1000000)
	{
    key += 1000000;
	}
	return key;
}


int WordNum(char word[]){
	char string1[WORD_SIZE];
	char string2[WORD_SIZE];	
	int A = 0;
	for(int i = 0; i < strlen(word) / 2;i++)
	{
	sprintf(string1,"%d",word[i]);
	sprintf(string2,"%d",word[i+1]);
	A += abs(atoi(string1)) + abs(atoi(string2));
	}
	return A;
}
////////////////////////////////////////////////////////////////////////////tree

struct TreeNODE
{
TreeNODE* Left;
TreeNODE* Right;
int Data;
int count;
char *word;
} Node;

struct TreeNODE* CREATE_NODE(int data,char word[],int count)
{
TreeNODE* newNode = (TreeNODE*)malloc(sizeof(Node));
newNode->word = (char*)malloc(sizeof(char)*sizeof(word));
newNode->Left = NULL;
newNode->Right = NULL;
newNode->Data = data;
newNode->word = word;
newNode->count = count;


return newNode;
}

struct TreeNODE* SEARCH_NODE(TreeNODE* Tree, int findData,char word[])
{
if (Tree == NULL) {
	//Tree = CREATE_NODE(WordNum(word),word,1);
    //printf("%s\n","Tree Null");
	//printf("없어요");
    return NULL;
}
if (Tree->Data == findData)//이미 있으면
{
	if(strcmp(Tree->word,word) == 0){
	    Tree->count++;
		printf("%s\n",Tree->word);
		return Tree;
	}else{//우연히 겹쳤는데.. 아직 NULL인데.. 있는 것으로 인식..
		printf("%s 가 겹쳤어요",Tree->word);
    SEARCH_NODE(Tree, Ramdom(findData), word);
	}

}
else if (Tree->Data > findData)
SEARCH_NODE(Tree->Left, findData, word);
else
SEARCH_NODE(Tree->Right, findData, word);
}

void INSERT_TREENODE(TreeNODE* Tree, TreeNODE* newNode)
{

    if (newNode->Data > Tree->Data)
    {
    if (Tree->Right != NULL) INSERT_TREENODE(Tree->Right, newNode);
    else Tree->Right = newNode;
    }
    else if (newNode->Data < Tree->Data)
    {
    if (Tree->Left != NULL) INSERT_TREENODE(Tree->Left, newNode);
    else Tree->Left = newNode;
    }

}


TreeNODE* FIND_MIN(TreeNODE* Tree)
{
    if (Tree == NULL) return NULL;
    if (Tree->Left != NULL) return FIND_MIN(Tree->Left);
    else return Tree;
}
//TreeNODE* REMOVE_NODE(TreeNODE* Tree, int data)
TreeNODE* REMOVE_NODE(TreeNODE* Tree, int data, char word[])
{
 TreeNODE* TempNODE;
   if (Tree == NULL) printf("해당하는 노드를 찾을 수 없습니다.\n");
   else if (Tree->Data > data) Tree->Left = REMOVE_NODE(Tree->Left, data, word);
   else if (Tree->Data < data) Tree->Right = REMOVE_NODE(Tree->Right, data, word);
else
{
if (Tree->Left != NULL && Tree->Right != NULL)
{
   TempNODE = FIND_MIN(Tree->Right);
   Tree->Data = TempNODE->Data;
   //Tree->key = TempNODE->key;//add
   //Tree->date = TempNODE->date;
   Tree->word = TempNODE->word;
   Tree->Right = REMOVE_NODE(Tree->Right, TempNODE->Data, word);
}
else
{
   TempNODE = Tree;
     if (Tree->Left == NULL) Tree = Tree->Right;
     else if (Tree->Right == NULL) Tree = Tree->Left;
   free(TempNODE);
}
}
return Tree;
}

void PRINT_TREE(TreeNODE* Tree)
{
if (Tree == NULL) return;
PRINT_TREE(Tree->Left);
//printf("%d ", Tree->Data);
if(Tree->count != 0) printf("count : %d word : %s", Tree->count, Tree->word);//printf("%s ", Tree->word);
PRINT_TREE(Tree->Right);
}

////////////////////////////////////////////////////////////////////////////Singly Linked List
struct AdjNODE
{
	int Val;  //추가 변수
	struct NODE* List;
	struct AdjNODE* Next;
};

struct AdjNODE* ALLOC_AdjNODE(){
struct AdjNODE* N = (struct AdjNODE*)malloc(sizeof(struct AdjNODE*));
N->List = (struct NODE*)malloc(sizeof(struct NODE*));; 
N->List = NULL;
N->Val = NULL;
N->Next = NULL;
return N;
}

struct AdjNODE* INSERT_AdjNODE(struct AdjNODE* list, struct NODE* Li,int Val){
struct AdjNODE* N = ALLOC_AdjNODE();
N->List = Li;
N->Val = Val;
N->Next = list;
return N;
}
////////////////////////////////////////////////////////////////////////////Singly Linked List
struct NODE
{
	int val;  //추가 변수

	char *key;
	char *data1;
	char *data2;

	struct NODE* next;
};

struct NODE* ALLOC_NODE(char key[],char data1[],char data2[]){
struct NODE* N = (struct NODE*)malloc(sizeof(struct NODE*));
N->key = (char*)malloc(sizeof(char)*sizeof(key));
N->data1 = (char*)malloc(sizeof(char)*sizeof(data1));
N->data2 = (char*)malloc(sizeof(char)*sizeof(data2));
N->key = NULL;
N->data1 = NULL;
N->data2 = NULL;
N->val = NULL;
N->next = NULL;
return N;
}//사실상 INSERT와 같이 쓰여야 의미있음.

struct NODE* INSERT_NODE(struct NODE* list, int val,char key[],char data1[],char data2[]){
struct NODE* N = ALLOC_NODE(key,data1,data2);
N->val = val;
N->next = list;
N->key = key;
N->data1 = data1;
N->data2 = data2;
return N;
}

struct NODE* DELETE_FIRST(struct NODE* list){
struct NODE* N = list;
list = N->next;
free(N);
return list;
}


void PRINT_LIST(struct NODE* list)
{
	for(struct NODE* P = list; P != NULL; P = P->next){
	printf("%d\n",P->val);
	}
}
////////////////////////////////////////////////////////////////////////////

void DeleteData(struct NODE *head,char word[]) 
{ 
   int n = 0; 
   NODE *p = head, *del; 
   while(p->next) 
   { 
	  if(strcmp(p->data2, word) == 0)
      { 
         del = p->next; 
         p->next = p->next->next; 
         free(del); 
		 free(del->data1);
		 free(del->data2);
		 free(del->key);
         return; 
      } 
      p = p->next; 
      n++; 
   } 
} 

void DELETE_WORD_NODE(char word[])
{
  //DeleteData(wordlist[Hash(word)],word);
}
////////////////////////////////////////////////////////////////////////////
void FIND_USER_NODE(struct NODE* list, char key[])
{
	struct NODE* P;
	for(P = list; P != NULL; P = P->next){
	 if(strcmp(P->key, key) == 0) printf("%s\n",P->data2);
	}

}

void FIND_WORD_NODE(struct NODE* list, char word[])
{
	struct NODE* P;
	for(P = list; P != NULL; P = P->next){
	    if(strcmp(P->data2, word) == 0) 
		{
		FIND_USER_NODE(userlist[Hashkey(P->key)],P->key);
		}
	}
}

void SEARCH_WORD_NODE(char word[])
{
 // FIND_WORD_NODE(wordlist,word);
}
////////////////////////////////////////////////////////////////////////////
int LoadData_user(){                                                      //해쉬
FILE *fp = fopen("user.txt","r");

if(fp == NULL ){
printf("파일열기실패\n");
}

int number = 0;
char line[MAX_LENGTH];
char *key;
char *signupdate;
char *id;


while(!feof(fp))
  {
  fgets(line,sizeof(line),fp);
  if (number % 4 == 0){
  key =(char*)malloc(strlen(line)-1);
  sprintf(key,"%s",line);

  }else if(number % 4 == 1){
  signupdate =(char*)malloc(strlen(line)-1);
  sprintf(signupdate,"%s",line);

  }else if(number % 4 == 2){
  id =(char*)malloc(strlen(line)-1);
  sprintf(id,"%s",line);

  }else if(strcmp(line,"\n") == 0)
  {
  userlist[Hashkey(key)] = INSERT_NODE(userlist[Hashkey(key)],Hashkey(key),key,signupdate,id);
  }
  number++;
  }
fclose(fp); 

return number / 4;
}

int LoadData_friend(){//리스트
FILE *fp = fopen("friend.txt","r");

if(fp == NULL ){
printf("파일열기실패\n");
}

int number = 0;
char line[MAX_LENGTH];
char *key;
char *friendkey;
char *data;
//
int Val = 0;
friendlist = NULL;
//
int keyvalue = 0;
int keycount = 0;
int friendCnt = 0;

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

  if(atoi(key) != keyvalue)
  {
  keycount++;
  friendCnt = 0;
  struct NODE* Flist = NULL;
  friendlist = INSERT_AdjNODE(friendlist,Flist,Val);
  Val++;
  }
  keyvalue = atoi(key);
  friendCnt++;
  //friendlist[keycount-1] = INSERT_NODE(friendlist[keycount-1],friendCnt,key,friendkey,friendkey);
  friendlist->List = INSERT_NODE(friendlist->List,friendCnt,key,friendkey,friendkey);

  }
  number++;
  }

fclose(fp); 

return number / 3;
}

int LoadData_word(){

FILE *fp = fopen("word.txt","r");

if(fp == NULL ){
printf("파일열기실패\n");
}

int number = 0;
char line[MAX_LENGTH];

char *key;
char *time;
char *word;

Uniqueword = CREATE_NODE(0,"0",0);
int Val = 0;
//wordlist = NULL;

 for(int i = 0; i < 3; i++){
  fgets(line,sizeof(line),fp);
  if(strcmp(line,"\n") != 0 && i == 0){
  key =(char*)malloc(strlen(line)-1);
  sprintf(key,"%s",line);
  }else if(strcmp(line,"\n") != 0 && i == 1){
  time =(char*)malloc(strlen(line)-1);
  sprintf(time,"%s",line);
  }else if(strcmp(line,"\n") != 0 && i == 2){
  word =(char*)malloc(strlen(line)-1);
  sprintf(word,"%s",line);
  number++;
  }else break;
  }
  struct NODE* Flist = NULL;
  wordlist = INSERT_AdjNODE(wordlist,Flist,Val);
  //Uniqueword = CREATE_NODE(WordNum(word),word,1);

while(!feof(fp))
  {
  fgets(line,sizeof(line),fp);
  if(strcmp(line,"\n") == 0)
  {
    if(SEARCH_NODE(Uniqueword,WordNum(word),word)==NULL)
    {
    INSERT_TREENODE(Uniqueword, CREATE_NODE(WordNum(word),word,1));
    struct NODE* Flist = NULL;
    wordlist = INSERT_AdjNODE(wordlist,Flist,Val);
    Val++;
    }
	wordlist->List = INSERT_NODE(wordlist->List,WordNum(word),key,time,word);
  for(int i = 0; i < 3; i++){
  fgets(line,sizeof(line),fp);
  if(strcmp(line,"\n") != 0 && i == 0){
  key =(char*)malloc(strlen(line)-1);
  sprintf(key,"%s",line);
  }else if(strcmp(line,"\n") != 0 && i == 1){
  time =(char*)malloc(strlen(line)-1);
  sprintf(time,"%s",line);
  }else if(strcmp(line,"\n") != 0 && i == 2){
  word =(char*)malloc(strlen(line)-1);
  sprintf(word,"%s",line);
  number++;
  }else break;
  }
  
  }

  }

fclose(fp); 

return number;

}


void PRINT_DATAINFO(){
printf("           >>DATA INFO<<\n");
printf("+++++++++++++++++++++++++++++++++++++++++++\n");
printf("Total users: %d\n", LoadData_user());
printf("Total friendship records: %d\n", LoadData_friend());
printf("Total tweets: %d\n", LoadData_word());
printf("+++++++++++++++++++++++++++++++++++++++++++\n");
}
void PRINT_USER(){
   
   char word[MAX_LENGTH];
   printf("검색할 단어 : ");
   scanf("%s", &word);
   printf("+++++++++++++++++++++++++++++++++++++++++++\n");
   sprintf(word,"%s\n",word);
   SEARCH_NODE(Uniqueword,WordNum(word),word);
   //SEARCH_NODE(wordlist->Right,Hash(word),word);
   //SEARCH_WORD_NODE(word);
}


int main(){
PRINT_DATAINFO();
printf("           >>STATISTICS<<\n");
printf("+++++++++++++++++++++++++++++++++++++++++++\n");
printf("Average tweets per user : xxx\n");
printf("Min tweets per user : xxx\n");
printf("Max tweets per user : xxx\n");
printf("Q.Top 5 most tweeted words??\n");
printf("1.%s 2.%s 3.%s 4.%s 5.%s\n","z","z","z","z","z");
printf("Q.Top 5 most tweeted users??\n");
printf("1.%s 2.%s 3.%s 4.%s 5.%s\n","z","z","z","z","z");
printf("+++++++++++++++++++++++++++++++++++++++++++\n");
printf("           >>Select Menu<<\n");
printf("+++++++++++++++++++++++++++++++++++++++++++\n");
printf("1.Find users who tweeted a word\n");
printf("2.Find all people who are friends of the above users\n");
printf("3.Delete all mention of a word\n");
printf("4.Delete all users who mentioned a word\n");
printf("5.Find strongly connected components\n");
printf("6.Find shortest path from a given user\n");


ANSWER:
printf("+++++++++++++++++++++++++++++++++++++++++++\n");
printf("원하는 메뉴를 고르시오(0~6) : ");
int Answer;
scanf("%d", &Answer);
printf("+++++++++++++++++++++++++++++++++++++++++++\n");

/*

for(int i=0;i < HASH;i++){
	printf("%d 번째 user list\n",i);

	PRINT_LIST(userlist[i]);
	//PRINT_LIST(friendlist[i]);
	PRINT_LIST(wordlist[i]);
}


int Max = 0;
int Min = 100000;
int UserNum = 0;
int Cnt = 0;
int Sum = 0;
int count = 0;
for(struct AdjNODE* P = wordlist; P ->Next !=NULL;P = P->Next){
	printf("%s\n", P->List->data2);
	UserNum++;
	Cnt = 0;
	for(struct NODE* L = P->List;L->next !=NULL;L = L->next)
	{
	Cnt++;
	count++;
		//printf("%s\n",L->data1);
	}
	Sum += Cnt;
	if(Max <= Cnt) Max = Cnt;
	if(Min >= Cnt) Min = Cnt;
}
printf("Max : %d \n",Max);
printf("Min : %d \n",Min);
printf("Avg : %d \n",Sum / UserNum);
printf("총 노드 개수 : %d \n",count);

goto ANSWER;

	*/

   if(Answer == 0 ){

   }else if(Answer == 1)
   {
   PRINT_USER();
   goto ANSWER;
   }else if(Answer==2)
   {
   char word[MAX_LENGTH];
   printf("지울 단어 : ");
   scanf("%s", &word);
   printf("+++++++++++++++++++++++++++++++++++++++++++\n");
   sprintf(word,"%s\n",word);
   //DELETE_WORD_NODE(word);
   goto ANSWER;
   }else if(Answer==3)
   {
	int val = 0;
	PRINT_TREE(Uniqueword); printf("\n");
	goto ANSWER;
   }else if(Answer==4)
   {
	SEARCH_NODE(Uniqueword,Hash("ㅋㅋ"),"ㅋㅋ");
    goto ANSWER;
   }else if(Answer==5)
   {
   REMOVE_NODE(Uniqueword,Hash("ㅋㅋ"),"ㅋㅋ\n");
   goto ANSWER;
   }else if(Answer==6)
   {

   }else
   {
   printf("0~6번까지에서만 골라주세요!!\n");
   printf("+++++++++++++++++++++++++++++++++++++++++++\n");
   goto ANSWER;
   }

 return 0;
}
