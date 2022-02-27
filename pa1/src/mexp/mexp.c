#include <stdio.h>

#include <stdlib.h>

int main(int argc, char *argv[]){
    FILE *file_Handle;
    
    file_Handle = fopen(argv[1], "r");
    if(file_Handle == NULL){
    	printf("error\n");
    	return 0;
    }
    int r1;
    int num;
    
    
    fscanf(file_Handle, "%d", &num);
    int **matrixOne = (int **)malloc(num*sizeof(int *));
    int **matrixTwo = (int **)malloc(num*sizeof(int *));
    int **solution = (int **)malloc(num*sizeof(int *));
    for(r1 = 0; r1<num; r1++){
    	matrixOne[r1] = (int *)malloc(num*sizeof(int));
    	matrixTwo[r1] = (int *)malloc(num*sizeof(int));
    	solution[r1] = (int *)malloc(num*sizeof(int));
    }
    int c1;
     for(r1 = 0; r1<num; r1++){
     	for(c1 = 0; c1<num; c1++){
     	     fscanf(file_Handle, "%d", &matrixOne[r1][c1]);
     	     matrixTwo[r1][c1] = matrixOne[r1][c1];
     	}
     }
     int r3,c3,x;
     fscanf(file_Handle, "%d", &x);
     if(x == 0){
     	for(r3 = 0; r3<num; r3++){
     	    for(c3 = 0; c3<num; c3++){
     	        if(r3!=c3){
     	            solution[r3][c3] = 0;
     	        } else{
     	            solution[r3][c3] = 1;
     	        }
     	}
     }
  }  
  int c2;
  int r2;
  for(c2 = 0; c2<x-1; c2++){
      for(r1 = 0; r1<num; r1++){
          for(c1 = 0; c1<num; c1++){
              solution[r1][c1] = 0;
              for(r2 = 0; r2<num; r2++){
                  solution[r1][c1] = solution[r1][c1] + (matrixOne[r1][r2] * matrixTwo[r2][c1]);
              }
          }
      }
          for(r1 = 0; r1<num; r1++){
              for(c1 = 0; c1<num; c1++){
                  matrixTwo[r1][c1] = solution[r1][c1];
              }
          }
   }
      
    int r;
    int c;
    for(r = 0; r<num; r++){
     	for(c = 0; c<num; c++){
     	    if(c == num-1){
                printf("%d", solution[r][c]);     	
     	    }else{
     	       printf("%d ", solution[r][c]);
     	    }
     	}
     	printf("\n");
     }
      
      
      fclose(file_Handle);
      for(r1 = 0; r1<num; r1++){
          free(matrixOne[r1]);
          free(matrixTwo[r1]);
          free(solution[r1]);
      }
      free(matrixOne);
      free(matrixTwo);
      free(solution);
      return EXIT_SUCCESS;
  
  
    
}
