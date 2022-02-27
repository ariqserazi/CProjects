#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
int main(int argc, char** argv){
    if(argc<=1 || strlen(argv[1])<1) return 0;
   // printf("%s\n",argv[0]);    
    int counter = 1;
    char* inString = argv[1];
    char prevChar = inString[0];
    for(int k = 0; k<strlen(inString);k++){
        if(isdigit(inString[k])){
            printf("error\n");
	    return 0;
	}	
    }
    char* outString =(char *)malloc((sizeof(char)+sizeof(int))*strlen(inString) + 1);
    int outCount = 0;    
    for(int i = 1; i<strlen(inString);i++){
        if(prevChar == inString[i]){
	    counter++;
	} else {
	   outCount += sprintf(outString+outCount,"%c%d",prevChar,counter);
	    counter = 1;
	}
	prevChar = inString[i];
    }
    outCount += sprintf(outString+outCount,"%c%d\n",prevChar, counter);
    outString[outCount-1] = '\0';
    //printf("%lu %lu\n", strlen(outString),strlen(inString));
    if(strlen(outString)>strlen(inString)){
        printf("%s\n", inString);
    }else{
        printf("%s\n", outString);
    }

    free(outString);
    return 0;
}
