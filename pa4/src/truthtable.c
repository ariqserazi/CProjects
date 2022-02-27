#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
 
typedef enum { AND, OR, NAND, NOR, XOR, NOT, PASS, DECODER, MULTIPLEXER } kind_t;
 
struct gate
{
    kind_t kind;
    int size; // indicates size of DECODER and MULTIPLEXER
    int paramCount;
    int *params; // length determined by kind and size;
    // includes inputs and outputs, indicated by variable numbers
};
typedef struct gate Gate;
 
Gate* createAndGate(){
    Gate* g = (Gate*)malloc(sizeof(Gate));
    g->kind = AND;
    g->size = 0;
    g->paramCount = 3;
    g->params = (int*)malloc(sizeof(int) * g->paramCount);
    return g;
}
Gate* createOrGate(){
    Gate* g = (Gate*)malloc(sizeof(Gate));
    g->kind = OR;
    g->size = 0;
     g->paramCount = 3;
    g->params = (int*)malloc(sizeof(int)*g->paramCount);
    return g;
}
Gate* createXorGate(){
    Gate* g = (Gate*)malloc(sizeof(Gate));
    g->kind = XOR;
    g->size = 0;
    g->paramCount = 3;
    g->params = (int*)malloc(sizeof(int) * g->paramCount);
    return g;
}
Gate* createNorGate(){
    Gate* g = (Gate*)malloc(sizeof(Gate));
    g->kind = NOR;
    g->size = 0;
    g->paramCount = 3;
    g->params = (int*)malloc(sizeof(int) * g->paramCount);
    return g;
}
Gate* createNandGate(){
    Gate* g = (Gate*)malloc(sizeof(Gate));
    g->kind = NAND;
    g->size = 0;
    g->paramCount = 3;
    g->params = (int*)malloc(sizeof(int) * g->paramCount);
    return g;
}
Gate* createNotGate(){
    Gate* g = (Gate*)malloc(sizeof(Gate));
    g->kind = NOT;
    g->size = 0;
    g->paramCount = 2;
    g->params = (int*)malloc(sizeof(int) * g->paramCount);
    return g;
}
 
Gate* createPassGate(){
    Gate* g = (Gate*)malloc(sizeof(Gate));
    g->kind = NOT;
    g->size = 0;
    g->paramCount = 2;
    g->params = (int*)malloc(sizeof(int) * g->paramCount);
    return g;
}
Gate* createDecoderGate(int size){
    Gate* g = (Gate*)malloc(sizeof(Gate));
    g->kind = DECODER;
    g->size = size;
    g->paramCount = size + pow(2, size);
    g->params = (int*)malloc(sizeof(int) * g->paramCount);
    return g;
}
Gate* createMultiplexerGate(int size){
    Gate* g = (Gate*)malloc(sizeof(Gate));
    g->kind = MULTIPLEXER;
    g->size = size;
    g->paramCount = pow(2, size) + size + 1;
    g->params = (int*)malloc( sizeof(int) * g->paramCount);
    return g;
}
 
 
 
void printGate(Gate* g)
{
    switch(g->kind) {
        case AND:
            printf("AND ");
            break;
        case OR:
            printf("OR ");
            break;
        case NOT:
            printf("NOT ");
            break;
        case NOR:
            printf("NOR ");
            break;
        case XOR:
            printf("XOR ");
            break;
        case NAND:
            printf("NAND ");
            break;
        case PASS:
            printf("PASS ");
            break;
        case DECODER:
            printf("DECODER ");
            break;
        case MULTIPLEXER:
            printf("MULTIPLEXER ");
            break;
        default:
            printf("%d ", g->kind);
    }
    printf("Size: %d ", g->size);
    printf("Params: ");
   
    for(int i = 0; i < g->paramCount; i++){
        if(i == g->paramCount-1){
            printf("%d", g->params[i]);
        }else{
            printf("%d ", g->params[i]);
        }
    }
    printf("\n");
}
void deleteGate(Gate* g){
    free(g->params);
    free(g);
}
struct circuit
{
    int numOfInputs;
    int numOfOutputs;
    char* params[100];
    int paramCount;
    int paramValues[100];
    int gateCount;  
    Gate* gates[50];
};
typedef struct circuit Circuit;
 
void printCircuit(Circuit *c)
{
    printf("=====================================\n");
    printf("numOfInputs=%d\n",  c->numOfInputs);
    printf("numOfOutputs=%d\n", c->numOfOutputs);
    printf("paramCount=%d\n",   c->paramCount);
    printf("paramValues [");
    for(int i = 0; i < c->paramCount; i++) {
        printf("%d ", c->paramValues[i]);
    }
    printf("]");
    printf("\n");
    for(int i = 0; i < c->gateCount; i++) {
        printGate(c->gates[i]);
    }
}
 
void addGate(Circuit *c, Gate *g){
    c->gates[c->gateCount] = g;
    c->gateCount++;
}
 
int addParam(Circuit* c, char* p)
{
    int paramLoc = c->paramCount;
    c->params[paramLoc] = (char*)malloc(strlen(p) + 1);
    strcpy(c->params[paramLoc], p);
    c->paramCount++;
    return paramLoc;
}
void deleteCircuit(Circuit* c){
     for(int i = 0; i<c->paramCount;i++){
         free(c->params[i]);
     }
     for(int i = 0; i<c->gateCount;i++){
         deleteGate(c->gates[i]);
     }
}
int findParam(Circuit* c, char* p)
{
    for(int i = 0; i < c->paramCount; i++){
        if(strcmp(c->params[i], p) == 0){
           return i;
        }
    }
    return -1;    
}
 
void resetParamValues(Circuit* c){
    for(int i = 0; i< c->numOfInputs + c->numOfOutputs; i++){
        c->paramValues[i] = 0;
    }
}
 
void and(int * values, int inIndex1, int inIndex2, int outIndex)
{
    values[outIndex]  = values[inIndex1] && values[inIndex2];
}
 
void nand(int * values, int inIndex1, int inIndex2, int outIndex)
{
    values[outIndex]  = !(values[inIndex1] && values[inIndex2]);
}
 
void or(int * values, int inIndex1, int inIndex2, int outIndex)
{
    values[outIndex]  = values[inIndex1] || values[inIndex2];
}
 
void nor(int * values, int inIndex1, int inIndex2, int outIndex)
{
    values[outIndex]  = !(values[inIndex1] || values[inIndex2]);
}
 
void xor(int * values, int inIndex1, int inIndex2, int outIndex)
{
    values[outIndex]  = values[inIndex1] ^ values[inIndex2];
}
 
void not(int * values, int inIndex, int outIndex)
{
    values[outIndex]  = !values[inIndex];
}
 
void pass(int * values, int inIndex, int outIndex)
{
    values[outIndex]  = values[inIndex];
}
 
void decode(int *values, int size, int *inIndex, int *outIndex) {
    int sum = 0;
   
    for (int i = 0; i < pow(2, size); i++) {
        //printf("outIndex[] %d %d\n", i, outIndex[i]);
        values[outIndex[i]] = 0;
    }
    for (int i = 0; i < size; i++) {
        sum += values[inIndex[i]] * pow(2, size - i - 1);
        //printf("SUM=%d\n", sum);
    }
   
    values[outIndex[sum]] = 1;
}
 
void multiplex(int *values, int size, int *inIndex, int *selectorIndex, int outIndex) {
    int sum = 0;
   
    for (int i = 0; i < size; i++) {
        sum += values[selectorIndex[i]] * pow(2, size - i - 1);
       
    }
    //printf("SUM=%d inIndex[sum]=%d values[inIndex[sum]]%d\n", sum, inIndex[sum], values[inIndex[sum]]);  
    values[inIndex[outIndex]] = values[inIndex[sum]];
}
 
void runCircuit(Circuit *c, int *inputs){
   
    for(int i = 0; i < c->numOfInputs;i++){
        c->paramValues[i] = inputs[i];
    }
 
    for(int i = 0; i < c->gateCount; i++){
        Gate* g = c->gates[i];
        if(g->kind == AND){
            and(c->paramValues, g->params[0], g->params[1], g->params[2]);
        }
        else if(g->kind == OR){
            or(c->paramValues, g->params[0], g->params[1], g->params[2]);
        }
        else if(g->kind == NOT){
            not(c->paramValues, g->params[0], g->params[1]);
        }
        else if(g->kind == NAND){
            nand(c->paramValues, g->params[0], g->params[1], g->params[2]);
        }
        else if(g->kind == NOR){
            nor(c->paramValues, g->params[0], g->params[1], g->params[2]);
        }
        else if(g->kind == XOR){
             xor(c->paramValues, g->params[0], g->params[1], g->params[2]);
        }
        else if(g->kind == PASS){
            pass(c->paramValues, g->params[0], g->params[1]);
        }
        else if(g->kind == DECODER){
            decode(c->paramValues, g->size, g->params, g->params + g->size);
        }
        else if(g->kind == MULTIPLEXER){
            int inputSize = (int)pow(2, g->size);
            multiplex(c->paramValues, g->size, g->params, g->params + inputSize , g->paramCount - 1);
        }
    }
 
}
void printTruthTable(Circuit *c)
{
    int nInput  = c->numOfInputs;
    int nOutput = c->numOfOutputs;
    int *inputs = (int *)malloc(sizeof(int) * nInput);
 
    for(int i = 0; i < pow(2, nInput); i++){
        // reset all inputs
        for(int i = 0; i < nInput; i++){
            inputs[i] = 0;
        }
       
        int temp = i;
        for(int j = 0; j < nInput; j++){
            inputs[nInput - j - 1] = temp%2;
            temp /= 2;
        }
 
        runCircuit(c, inputs);
        //printCircuit(c);
        int i = 0;
        for(i = 0; i < nInput; i++){
            printf("%d ", c->paramValues[i]);        
        }
        printf("| ");
        for(; i < nInput + nOutput; i++){
           printf("%d", c->paramValues[i]);
           if(i != nInput + nOutput-1){
                printf(" ");
           }
        } 
        
        printf("\n");
 
        resetParamValues(c);
    }
    free(inputs);
}
 
 
 
int main(int argc, char **argv){
    Circuit cir;
    cir.gateCount  = 0;
    cir.paramCount = 0;
    FILE *file_handler;
    file_handler = fopen (argv[1], "r");
    if(!file_handler){
        printf("Error opening file %s\n", argv[0]);
        return 0;
    }
    char type[17];
    int numOfInputs;
    int numOfOutputs;
    fscanf(file_handler,"%16s",type);
    //printf("%s\n",type);
    fscanf(file_handler,"%d",&numOfInputs);
    //printf("%d\n",numOfInputs);
    cir.numOfInputs = numOfInputs;
    char name[25];
   
    for(int i = 0; i<numOfInputs; i++){
        fscanf(file_handler,"%16s", name);
        addParam(&cir, name);
        //printf("%s\n", name);
    }
   
    fscanf(file_handler,"%16s",type);
    //printf("%s\n",type);
    fscanf(file_handler,"%d",&numOfOutputs);
    cir.numOfOutputs = numOfOutputs;
    //printf("%d\n",numOfOutputs);
 
    for(int i = 0; i<numOfOutputs; i++){
        fscanf(file_handler,"%16s", name);
        addParam(&cir, name);
        //printf("%s\n", name);
    }
 
    int n = 0;
    while((n = fscanf(file_handler,"%16s",type)) > 0){
        Gate* g = NULL;
 
        if(strcmp(type, "AND")     == 0){
            g = createAndGate();
        }else if(strcmp(type,"OR") == 0){
            g = createOrGate();
        }else if(strcmp(type,"XOR") == 0){
            g = createXorGate();
        }else if(strcmp(type,"NOR") == 0){
            g = createNorGate();
        }else if(strcmp(type,"NOT") == 0){
            g = createNotGate();
        }else if(strcmp(type,"NAND")==0){
            g = createNandGate();
        }else if(strcmp(type,"MULTIPLEXER") == 0){
            int input_size = 0;
            fscanf(file_handler,"%d", &input_size);
            g = createMultiplexerGate(input_size);      
        }
        else if(strcmp(type, "DECODER") == 0){
            int input_size = 0;
            fscanf(file_handler,"%d", &input_size);
            g = createDecoderGate(input_size);          
        }
        else if(strcmp(type,"PASS") == 0){
            g = createPassGate();
        }
        if(g != NULL){
            // int size = g->size;
            // if(g->kind == DECODER) {
            //     size += pow(2, size);
            // }
            for(int i = 0; i< g->paramCount;i++){
                fscanf(file_handler,"%16s", name);
                int loc = findParam(&cir, name);
                if(loc < 0){
                    loc = addParam(&cir,name);
                }
                g->params[i] = loc;
                if(strcmp(name, "0") == 0){
                    cir.paramValues[loc]= 0;
                }
                else if(strcmp(name, "1") == 0){
                    cir.paramValues[loc]= 1;
                }
               
            }
            addGate(&cir,g);
        }
    }
 
    fclose(file_handler);
 
    //printCircuit(&cir);
    printTruthTable(&cir);
    deleteCircuit(&cir);
 
   return 0;
 
}


