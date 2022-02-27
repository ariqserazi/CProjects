#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
void print(double **matrix,int r, int c){
  for(int i = 0; i < r; ++i){
        for(int j = 0; j < c; ++j){
            if(j==c-1){
               printf("%.0f", matrix[i][j]);
            }else{
               printf("%.0f ", matrix[i][j]);
            }
        }
        printf("\n");


  }  
}

double **identity(int n){
    
    double ** N = (double**) malloc(n*sizeof(double *));
    int i,j;
    for(i = 0; i < n; i++){
        N[i]  =(double *)malloc(n*sizeof(double));
    }
    for(i = 0; i<n;i++){
        for(j=0; j<n; j++){
	    if(i == j){
	        N[i][j] = 1;
	    }else{
	        N[i][j] = 0;
	    }
	}
    }
    return N;

}
double **inverse(double **M, int n){
     
    double ** N = identity(n);
   
    for(int p = 0; p < n; p++){
       double f = M[p][p];
     for(int j = 0; j<n; j++){
           M[p][j] = M[p][j]/f;
           N[p][j] = N[p][j]/f;
       } 	   
       for(int i = p+1; i<n;i++){
           f = M[i][p];
	   for(int j=0; j<n; j++){
               M[i][j] = M[i][j] - (M[p][j]*f);
	       N[i][j] = N[i][j] - (N[p][j]*f);
	   }
       }
    }

    for(int p = n-1; p>=0; p--){
        for(int i = p-1; i>=0;i--){
	    double f = M[i][p];
	    for(int j = 0; j<n; j++){
	        M[i][j] = M[i][j] - (M[p][j]*f);
		N[i][j] = N[i][j] - (N[p][j]*f);
	    
	    }
	}  
    }
    //print(M,n,n); 
    return N;
}

/*double **multiply(double ** X, int xRows, int xCols, double* Y, int yRows, int *resultRows, int *resultCols) {
     if(xCols != yRows){
         return NULL;
     }
}*/
double **multiply(double ** X, int xRows, int xCols, double ** Y, int yRows, int yCols, int *resultRows, int *resultCols) {
     if(xCols != yRows){
         //printf("not same\n");
         return NULL;
     }
     
    *resultRows = xRows;
    *resultCols = yCols;
    
    double ** temp = (double **) malloc(xRows * sizeof(double *));
    
    int i,j,k;
    for (i = 0; i < xRows; i++) {
        temp[i] = (double *) malloc(yCols * sizeof(double));
    }

    for (i = 0; i < xRows; i++) {
        for (j = 0; j < yCols; j++) {
            double sum = 0;  
            //temp[i][j] = 0;  
            for (k = 0; k < yRows; k++) {
                sum +=(X[i][k] * Y[k][j]);
            }
            temp[i][j] = sum;
            //sum = 0;
        }
    }
    
    return temp;
    
}

double ** transpose(double ** matrix,int rows,int columns) {
    //printf("rows:%d cols:%d\n", columns, rows);
    double ** temp = (double **)malloc(columns * sizeof(double *));
    int i,j;
    for (i = 0; i < columns; i++) {
        temp[i] = (double *) malloc(rows * sizeof(double));
    }

    for (i = 0; i < columns; i++) {
        for (j = 0; j < rows; j++) {
           temp[i][j] = matrix[j][i];
        }
    }
    
    return temp;
}

int main(int argc, char **argv){
    
    FILE *file_handler;
    FILE *file_handler1;
    if(argv[1]<=0 || argc<1){
         return 0;
    }
    file_handler = fopen (argv[1], "r");
    file_handler1 = fopen (argv[2], "r");
    
    int r,c;
    char l[6];
    char l1[6];
    fscanf(file_handler,"%5s",l);

    if(strcmp(l,"train") != 0){
      printf("Error, Wrong File Type, it should be a Train type not a %s type\n", l);      
      return 0;
    }
    fscanf(file_handler1,"%4s",l1);
     if(strcmp(l1,"data") != 0){
      printf("Error, Wrong File Type, it should be a data type not a %s type\n", l);      
      return 0;
    }
    fscanf(file_handler,"%d", &c);
    fscanf(file_handler,"%d", &r); 
    //printf("row = %d col = %d\n",r,c);
    if(r<=0 || c<=0){
        printf("error, both row and col must be greater than 0\n");
        return 0;
    
    }
    // including 1st column always 1
    c = c+1;
    double **trX;
    double **XtX;
    double **invX;
    double **invXxT;
    double **res;
    
    double **matrix = (double **)malloc(r*sizeof(double*));
    double **matrix2 = (double **)malloc(r*sizeof(double*));
    for(int k =0; k<r;k++){
         matrix[k] = (double *)malloc(c*sizeof(double));
    }
    for(int k =0; k<r;k++){
         matrix2[k] = (double *)malloc(1*sizeof(double));
    }
    if (file_handler == NULL)
        return 0;

    for(int i = 0; i < r; i++)
    {
        matrix[i][0] = 1;
        for(int j = 1; j <=c; j++){
            if(j==c){
              fscanf(file_handler, "%lf", &matrix2[i][0]);
            } else {
            fscanf(file_handler, "%lf", &matrix[i][j]);
            
            }
            
        }
    }
    
     fclose(file_handler);
    /* print(matrix,r,c);
      printf("\n");
     print(matrix2,r,1);
     printf("\n");
     */
     trX = transpose(matrix,r,c);
     //print(trX,c,r);
     //printf("\n");
     int xtxRows = 0;
     int xtxCols = 0;
     XtX = multiply(trX, c, r, matrix, r ,c, &xtxRows, &xtxCols);
     if(XtX == NULL){
          return 0;
     }
     //printf("xtxrows: %d xtxCols: %d\n", xtxRows,xtxCols);
     //print(XtX,xtxRows,xtxCols);
     invX = inverse(XtX,xtxRows); 
     //printf("\n");
     //print(invX, xtxRows,xtxCols); 
     int xtxRows1 = 0;
     int xtxCols1 = 0;
      invXxT = multiply(invX, xtxRows, xtxRows, trX, c ,r, &xtxRows1, &xtxCols1);
     if(invXxT == NULL){
        return 0;
     }
     //printf("\n");
     //printf("xtxrows: %d xtxCols: %d\n", xtxRows1,xtxCols1);
     //print(invXxT,xtxRows1,xtxCols1);
     //printf("\n");
     int xtxRows2 = 0;
     int xtxCols2 = 0;
     int x = 1;
     res = multiply(invXxT, xtxRows1, xtxCols1, matrix2, r,x, &xtxRows2, &xtxCols2);
     if(res == NULL){
        return 0;
     }
     //printf("xtxrows: %d xtxCols: %d\n", xtxRows,xtxCols);
     //printf("row = %d col = %d\n",xtxRows1,xtxCols1);
     //print(res,xtxRows2,xtxCols2);
     
/**********************************************************************************************/     
     
     double **res1;
     int r1,c1;
     
    
    fscanf(file_handler1,"%d", &c1);
    fscanf(file_handler1,"%d", &r1); 
 
    if(r1<=0 || c1<=0){
        printf("error, both row and col must be greater than 0\n");
        return 0;
    
    }
    c1 = c1 + 1;
   if(c1 != c){
     return 0;
   }
     double **X = (double **)malloc(r1*sizeof(double*));
    for(int k =0; k<r1;k++){
         X[k] = (double *)malloc(c1*sizeof(double));
    }
     for(int i = 0; i < r1; i++){
        X[i][0] = 1;
        for(int j = 1; j <c1; j++){
            fscanf(file_handler1, "%lf", &X[i][j]);    
        }
    }
    
    fclose(file_handler1);    
    int xtxRows3 = 0;
    int xtxCols3 = 0;    
    res1 = multiply(X,r1,c1,res,xtxRows2,xtxCols2,&xtxRows3,&xtxCols3);
    if(res1 == NULL){
          return 0;
     }
    //printf("row = %d col = %d\n",xtxRows3,xtxCols3);  
    print(res1,xtxRows3,xtxCols3); 
     // free all the memory     
     for(int i = 0; i<r; i++){
          free(matrix[i]);
          free(matrix2[i]); 
          
      }
     for(int i = 0; i<r1;i++){
         free(X[i]);
     }
      free(matrix);
      free(matrix2);
      free(X);
      for(int i = 0; i<c; i++){
         free(trX[i]);
      }
      free(trX);
      for(int i = 0; i<xtxRows; i++){
          free(XtX[i]);
	  free(invX[i]); 
      }
      free(XtX);
      free(invX);
      for(int i = 0; i<xtxRows1; i++){
          free(invXxT[i]);
	 
      }
      free(invXxT);
      for(int i = 0; i<xtxRows2; i++){
          free(res[i]);
	 
      }
      free(res);
      for(int i = 0; i<xtxRows3; i++){
         free(res1[i]);
      }
      free(res1);
  
       
    return 0;

}
