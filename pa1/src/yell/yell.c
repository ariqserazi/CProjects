#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char **argv){
    if(argc>1 && strlen(argv[1])>0){
	char *str =(char *)malloc(sizeof(char)*strlen(argv[1])+1);
        for(int i = 0; i<strlen(argv[1]);i++){
	   str[i] =toupper(argv[1][i]);
	}
	str[strlen(argv[1])]= '\0';
       	printf("%s!!\n" , str);
	free(str);


    }
    return 0;

}
