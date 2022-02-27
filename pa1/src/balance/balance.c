#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
struct Node{
    char value;
    struct Node *next;
}; 

struct Node*  push(struct Node* topNode, char v)
{   
    //printf("push %c\n", v);	
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->value = v;
    newNode->next  = NULL;

    if(topNode == NULL){
	newNode->next = NULL;
        topNode = newNode;
    }else{
        newNode->next = topNode;
        topNode = newNode;
    }

    return topNode;

}
struct Node* pop(struct Node* topNode){
    if(topNode == NULL){
        return NULL;
    }
    struct Node *temp = topNode;
    topNode = temp->next;
    free(temp);

    return topNode;
}

char top(struct Node *topNode){
    if(topNode == NULL){
        return ' ';
    }
    return topNode->value;

}
void freeStack(struct Node *stack){
    struct Node *temp = stack;
    while(temp){
        stack = temp->next;
        free(temp);
	temp = stack;

    }
}
void display(struct Node *topNode){
    struct Node *temp = topNode;
    while(temp){
        printf("%c" , temp->value);
	temp = temp->next;
    }

    printf("\n");
}
int size(struct Node *stack){
    struct Node *temp = stack;
    int i = 0;
    while(temp){
        i++;
	temp = temp->next;
    }
    return i;
}
struct Node* displayOpen(struct Node *stack){
    //struct Node *temp = stack;
    printf("open: ");
    while(stack){
        char c = top(stack);
        if(c == '('){
            printf(")"); 
        }else if(c == '{'){
            printf("}"); 
        }else if(c == '['){
            printf("]"); 
        }
        stack = pop(stack);
    }
    printf("\n");

   return stack; 
}
/*
bool isEmpty(struct Node* topNode)
{
    if(topNode == NULL){
        return true;
    }
    return false;
}
*/
int main(int argc, char** argv){
   if( argc <= 1 || strlen(argv[1]) < 1 ){
       return EXIT_FAILURE;
   }
   int exit_code = EXIT_SUCCESS;
   bool openStack = false;
   bool done = false;
   //char arg = argv[1];
   struct Node *stack = NULL;
   for(int i = 0; i< strlen(argv[1]); i++){
   
       char c = argv[1][i];
       //char topChar = top(stack);     
       if(c == '(' || c == '{' || c == '[') {
           stack = push(stack, c);
           openStack = true;
       }

       else if(c == ')' || c == '}' || c == ']') {
	   char topChar = top(stack);     
           openStack = false;
	   if(topChar == '(' && c == ')') {
               stack = pop(stack);
               
	   }
           else if(topChar == '{' && c == '}'){
               stack = pop(stack);
	   }
           else if(topChar == '[' && c == ']'){
               stack = pop(stack);
	   }
	   else{
               printf("%d: %c\n",i, c);
               exit_code = EXIT_FAILURE;
               openStack = false;
	       done = true;
	       break;

	   }
        }

   }

   bool isBal = (size(stack) == 0);
   
   if( !done && (openStack || !isBal )){
       stack = displayOpen(stack);
       exit_code = EXIT_FAILURE;
   }

   freeStack(stack);

   return exit_code;
  
}

