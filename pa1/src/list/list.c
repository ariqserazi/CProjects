#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

struct Node{
    int value;
    struct Node *next;
};
bool contains(struct Node *front, int val){
    struct Node *currentNode = front;
    while(currentNode != NULL){
        if(currentNode->value == val){
	    return true;
	}
	currentNode = currentNode->next;
    }
    return false;
}
struct Node* insert(struct Node *front, int val){
    if(contains(front,val)){
        return front;
    }
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if(newNode!=NULL){
        newNode->value = val;
	newNode->next = NULL;
    
        if(front == NULL){
	    front = newNode;
        }else{
	    struct Node* currentNode = front;
	    struct Node* tempNode = NULL;
	    while(currentNode != NULL){
		if(currentNode->value > newNode->value){
	            if(tempNode == NULL){
	                newNode->next = front;
		        front = newNode;
	            } else{
	                newNode->next = currentNode;
			tempNode->next = newNode;
		    }
		    return front;
		}
		tempNode = currentNode;
		currentNode = currentNode->next;
	    }
	    tempNode->next = newNode;
       	}
    }
    return front;
}
struct Node* delete(struct Node *front, int val){
    if(!contains(front,val)){
        return front;   
    }
    if(front != NULL){
        if(front->value == val){
	    struct Node* tempNode = front;
	    front = front->next;
	    free(tempNode);
	}else{
	    struct Node* currentNode = front;
	    struct Node* tempNode2 = NULL;
	    while(currentNode != NULL){
	        if(currentNode->value == val){
		    tempNode2->next = currentNode->next;
		    free(currentNode);
		    return front;
		}	
		tempNode2 = currentNode;
		currentNode = currentNode->next;

	    }


	}

    }
    return front;    
}
void freeList (struct Node* front){
    struct Node* temp;
    while(front != NULL){
        temp = front->next;
        //free(front->value);
	free(front);
	front = temp;
    }
}
int length(struct Node* front){
    int count = 0;
    struct Node* currentNode = front;
    while(currentNode != NULL){
        count++;
	currentNode = currentNode->next;
    }
    return count;
}
//This is for the insert so we can check if the n is already present
void display(struct Node* front){
 struct Node* node = front;
       while(node != NULL){
          if(node->next == NULL){
	       printf("%d", node->value);
	  }else{
	       printf("%d ", node->value);
	  }
	   
	   node = node->next;
       }
       
}
int main(void){
    struct Node* front = NULL; 
    int value;
    char input;
    do{
     
       int rc = scanf(" %c %d", &input, &value);
       if(rc == EOF){
           break;
       }
       //printf("input = %c value = %d\n" , input,value);
       if(input != 'i' && input != 'd'){
           break;
       } 
       if(input == 'i'){
          front = insert(front,value); 
       }
       else if(input == 'd'){
           front = delete(front,value);
       }
       int size = length(front);
       if(size==0){
           printf("%d :", size);
       } else {
       printf("%d : ", size);
       }
       display(front);
       printf("\n");
    }while(input == 'i'||input == 'd');
    freeList(front);
    return EXIT_SUCCESS;


}
