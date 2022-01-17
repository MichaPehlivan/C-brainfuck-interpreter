#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARRAYSIZE 30000

unsigned char tape[ARRAYSIZE] = {0};
unsigned char *ptr = tape;

//searches forward for matching bracket
int findbracket(char *commands, int currentpos){
    int lb = 0;
    int rb = 0;

    for(int i = currentpos; i < strlen(commands); ++i){
        if(commands[i] == '[') ++lb;
        if(commands[i] == ']') ++rb;

        if(lb == rb){
            return i;
        }
    }
}

//executes brainfuck commands in a string
void interpret(char *commands){

    int stack[10];
    int *pStack = stack;

    for(int i = 0; i < strlen(commands); ++i){
        char command = commands[i];
        
        if(command == '>'){
            ++ptr;
        }
        else if(command == '<'){
            --ptr;
        }
        else if(command == '+'){
            ++*ptr;
        }
        else if(command == '-'){
            --*ptr;
        }
        else if(command == '.'){
            putchar(*ptr);
        }
        else if(command == ','){
            *ptr = getchar();
        }
        else if(command == '['){
            if(*ptr == 0){
                i = findbracket(commands, i);
            }
            else{
                ++pStack;
                *pStack = i;
            }
        }
        else if(command == ']'){
            if(*ptr != 0){
                i = *pStack;
            }
            else{
                --pStack;
            }
        }
    }
}

int main(){
    printf("file to interpret: ");
    char path[21];
    scanf("%20s", &path);
    
    FILE *file = fopen(path, "r");

    if(file == NULL){
        printf("could not open file\n");
        return 1;
    }

    int n = 0;
    char *content = (char *)malloc(n *sizeof(char));

    if(content == NULL){
        printf("out of memory\n");
        return 1;
    }

    int c;
    while((c = getc(file)) != EOF){
        content[n] = c;
        ++n;
        content = realloc(content, n * sizeof(char));
        
        if(content == NULL){
            printf("out of memory\n");
            return 1;
        }
    }

    interpret(content);

    fclose(file);
    free(content);

    return 0;
}
