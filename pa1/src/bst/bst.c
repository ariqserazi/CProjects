#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
 
struct node {
    int val;
    struct node *left, *right;
};

void freeTree(struct node *newNode){
    //printf("freeTree");
    if(newNode == NULL){
       return;
    }
    //printf("free node value = %d",newNode->val);
    if(newNode->right != NULL){
       freeTree(newNode->right);
    }
    if(newNode->left != NULL){
        freeTree(newNode->left);
    }
    free(newNode);

    
}

struct node *makeNewNode(int v)
{
    struct node *newNode = (struct node *)malloc(sizeof(struct node));
    newNode->val = v;
    newNode->left =NULL;
    newNode->right = NULL;
    return newNode;
}
struct node* insertNewNode(struct node* aNode, int v)
{
    //struct node* newNode = (struct node*)malloc(sizeof(struct node));
    if(aNode == NULL){
        /*newNode->val = v;
        newNode->left = NULL;
        newNode->right = NULL;
        printf("inserted\n");
        return newNode; */
        printf("inserted\n");
        return makeNewNode(v);
    }
    if(aNode->val == v){
        printf("not inserted\n");
        return aNode;
    }
    else if (aNode->val > v){
        aNode->left  = insertNewNode(aNode->left, v);
    }
    else if (aNode->val < v){
        aNode->right = insertNewNode(aNode->right, v);
    }
    return aNode;
}
void treeSearch(struct node *newNode, int v){
    if(newNode==NULL){
        printf("absent\n");
    }
    else if(newNode->val==v){
        printf("present\n");
    }

    else if (newNode->val > v){
        treeSearch(newNode->left, v);
    }
    else if (newNode->val < v){
        treeSearch(newNode->right, v);
    }

}

struct node *delete(struct node *newNode, int v, bool check){
    if (newNode == NULL){
      printf("absent\n");
      return newNode;
    }
    
    if (v< newNode->val){
        newNode->left = delete(newNode->left, v, check);
    }
    else if (v > newNode->val){
        newNode->right = delete(newNode->right, v, check);
    }else{
        if(check){
            printf("deleted\n");
	}
      
      if (newNode->left == NULL){
          struct node* standIn = newNode->right;
          free(newNode);
          return standIn;
      }
      else if (newNode->right == NULL){
         struct node* standIn = newNode->left;
          free(newNode);
          return standIn;
      }
      struct node* standIn = newNode->right;
      while(standIn->left != NULL){
	  standIn = standIn->left;
      } 
      newNode->val= standIn->val;
      newNode->right = delete(newNode->right, standIn->val,false);
    }
    return newNode;
}
void printTree(struct node *newNode)
{
    if (newNode != NULL)
    {
        printf("(");
        printTree(newNode->left);
        printf("%d", newNode->val);
        printTree(newNode->right);
        printf(")");
    }
}
int main(void){
   char input; 
   int n;
   struct node* newNode = NULL;
   do{
       int rc = scanf(" %c", &input);
       if(rc == EOF){
           break;
       }
       
       if(input !='i' && input != 'd' && input != 's' && input != 'p'){
           break;
       }
       if(input ==  'i'){
            scanf(" %d", &n);
          /*if(bc == EOF){
           break;
           } */
           newNode = insertNewNode(newNode,n);
       } else if(input == 'd'){
       scanf(" %d", &n);
          /*if(bc == EOF){
           break;
           } */
           newNode = delete(newNode,n,true);
       } else if(input=='s'){
scanf(" %d", &n);
          /*if(bc == EOF){
           break;
           } */
          treeSearch(newNode,n);
       }
        else if(input=='p'){
        
            printTree(newNode);
            printf("\n");
       }


   } while(input =='i' || input == 'd' || input == 's' || input == 'p');
   //printf("hello\n");
   freeTree(newNode);
   return EXIT_SUCCESS; 
}
