/*
how to play?
----make----
---./mastermind---


*/


#include <stdio.h>
#include<stdlib.h> 
#include<time.h> 
#include <string.h> 
#include <stdbool.h>


int box(char arr[],char x){
    for(int i=0;i<4;i++){
        if(arr[i]==x){
            return 1;
        }
    }
    return 0;
}

char* randomCode(){
   srand(time(NULL)); 
   char* res = malloc(16);
   for(int i=0;i<4;){
       char temp= rand()%7+'0';
       if( box(res,temp)==0){
           res[i]=temp;
           i++;
       }
   }
   return res;
}

int compare(char arr1[],char arr2[]){
    for(size_t i = 0;i<strlen(arr1);i++){
        if(arr1[i] !=arr2[i]){
            return 0;
        }
    }
    return 1;
}

int isCorrect(char arr[]){
    if (strlen(arr)> 4 || strlen(arr)<4){
        return 0;
    }

    for(int i=0; i < 4;i++){
        if(arr[i] > 47 || arr[i]< 58){
            return 1;
        }
        return 0;
    }

    for(int i = 0;i < 4;i++){
        for(int j = 0; i < 4;j++){
            if(arr[i]==arr[j]){
                return 0;
            }
        }
    }
    return 1;
}


bool is_repeat(char* str) {
    for (int i =0; i < 4; i++) {
        for (int m=0; m < 4; m++) {
            if (i == m) continue;
            if (str[i] == str[m]) return true;
        }
    }
    return false;
}

bool wrong_input(char* t) {
    if (strlen(t) != 4) return true;
    for(int i=0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            if ((t[i] > '7' || t[i] < '0') || is_repeat(t)) return true;
        }
    }
    return false;
}

int main(int argc, char* argv[]){
    char* code = malloc(20) ;
    int atremps = 10, round = 0;
    int wp = 0;
    int mp = 0;
    int t = 0;
    int c = 0;
    
    for(int i = 1;i < argc;i++){
        if(compare(argv[i],"-c")){
            c = i + 1;
        }
        if(compare(argv[i],"-t")){
            t = i + 1;
            atremps = atoi(argv[t]);
        }

    }
    
    if(c == 0){
        strcpy(code, randomCode());
    }
    else{
        for(int i = 0; i < 4;i++){
            code[i]=argv[c][i];
        }
    }

    printf("Will you find the secret code?\n---\n");

    while(round < atremps){
        printf("Raund %d\n",round);
        // int corectInp = 1;
        char *input = malloc(20);
        wp = 0;
        mp = 0;
        start:
        printf(" >");     scanf("%s",input);
        if (wrong_input(input))
        {
           printf("Wrong input!\n");
           goto start;
        }
        // else
        // {
        //     corectInp = 0;
        //     printf("Wrong input!");
        // }

        for(int j =0;j< 4;j++){
            if(code[j]==input[j]){
                wp++;
            }
            else if(box(code,input[j]) && code[j] != input[round]){
                mp++;
            }
        }
        if(wp == 4){
            printf("Congratz! You did it!\n");
            break;
        }
        else{
            printf("Well placed pieces: %d\n", wp); 
            printf("Misplaced pieces: %d\n", mp); 
            
        }
        round++;

    }
}

