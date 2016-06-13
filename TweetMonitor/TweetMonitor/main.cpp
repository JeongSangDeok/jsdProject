
#include <stdio.h>      // 표준 입출력 header
#include <malloc.h>
#include <stdlib.h>

struct Usernode
{
	int val;
	char key[9];
	char registerdate[30]; 
	char id[30];
	struct Usernode* leftchild;
	struct Usernode* rightchild;

};

struct Usernode* BST_ALLOC(char key[],char registerdate[],char id[])
{
	char str[10];
	sprintf(str,"%d",id[0]);
	
	struct Usernode* N = (struct Usernode*)malloc(sizeof(struct Usernode));
    N->val = atoi(str);
	N->key[9] = key[sizeof(key)];
	N->registerdate[sizeof(registerdate)] = registerdate[sizeof(registerdate)];
	N->id[sizeof(id)] = id[sizeof(id)];
	N->leftchild = NULL;
	N->rightchild = NULL;
};

struct Usernode* BST_INSERT(struct Usernode* tree, struct Usernode* child)
{
if(tree == NULL)
{
	tree = child;
}
else
{
	if(child->




}

}






int main(){

char str[256];
int Cnt = 1;
int usernumber = 0;
int friendsnumber = 0;
int tweetnumber = 0;

FILE *fp_user = fopen("user.txt","r");
FILE *fp_friend = fopen("friend.txt","r");
FILE *fp_word = fopen("word.txt","r");

if(fp_user == NULL ){
	printf("user 파일열기실패\n");
}else if(fp_friend == NULL){
	printf("friend 파일열기실패\n");
}else if(fp_word == NULL){
	printf("word 파일열기실패\n");
}

while(Cnt > 0)
{
 if(fgets(str,sizeof(str),fp_user) != NULL){
 usernumber++;   
 }else if(fgets(str,sizeof(str),fp_friend) != NULL){
 friendsnumber++;
 }else if(fgets(str,sizeof(str),fp_word) != NULL){
 tweetnumber++;
 }else{
 Cnt = 0;
 }   
}



printf(">>DATA INFO<<\n");
printf("Total users: %d\n", usernumber/4);
printf("Total friendship records: %d\n", friendsnumber/3);
printf("Total tweets: %d\n", tweetnumber/4);
printf(">>Select Menu<<\n");
printf("1.display statistics\n");
printf("2.Top 5 most tweeted words\n");
printf("3.Top 5 most tweeted users\n");
printf("4.Find users who tweeted a word\n");
printf("5.Find all people who are friends of the above users\n");
printf("6.Delete all mention of a word\n");
printf("7.Delete all users who mentioned a word\n");
printf("8.Find strongly connected components\n");
printf("9.Find shortest path from a given user\n");
printf(">>Choose one(1~9)!<<\n");

int Input;
scanf("%d", &Input);


return 0;

}