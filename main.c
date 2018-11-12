#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int cmp(const void * x1,const void * x2);

int main() {
    
    FILE* Onegin = NULL;
    FILE* Onegin_alf = NULL;
    FILE* Onegin_ryhm = NULL;
    Onegin = fopen("Onegin.txt","r");
    
    if(Onegin == NULL)
        printf("File couldn't open");
        
    Onegin_alf = fopen("Onegin_alf.txt","w");
    Onegin_ryhm = fopen("Onegin_ryhm.txt","w");
    
    char* OneginStr = (char*) calloc(500000,sizeof(char));
    char** OneginStrAdd = (char**) calloc (50000, sizeof(char*));
    char** OneginStrAdd2 = (char**) calloc (50000, sizeof(char*));
    char** OneginStrAdd3 = (char**) calloc (50000, sizeof(char*));
    
    fread(OneginStr,sizeof(char),500000, Onegin);
        
    int count = 0;
    
    for (int i = 0; i<= 500000; i++) {
        if (OneginStr[i] == '\n'){
            OneginStr[i] = '\0';
            OneginStrAdd[count] = OneginStr + i+1;
            OneginStrAdd2[count] = OneginStr + i+1;
            OneginStrAdd3[count] = OneginStr + i+1;
            ++count;
        }
    }
    
    qsort(OneginStrAdd2, count, sizeof(char**), cmp);
    
    for(int i = 0; i<=count; i++) {
       printf("\n%s",OneginStrAdd2[i]); 
    }
}

int cmp(const void * x1,const void * x2) {
    char* Str1 = *(char**)x1;
    char* Str2 = *(char**)x2;
    
    int count1 = 0;
    int count2 = 0;
    
    for(int i = 0;; i++) {
        
        for (;;){
            if (Str1[count1] == '`' || Str1[count1] == ' ')
                count1 ++;
            if (Str2[count2] == '`' || Str2[count2] == ' ')
                count2 ++;
            if (Str1[count1] != '`' && Str1[count1] != ' ' && Str2[count2] != '`' && Str2[count2] != ' ')
                break;
        }
        
        
        if (Str1[count1] > Str2[count2]) { 
            return 1;
        }
        if (Str1[count1] < Str2[count2]) {
            return -1;
        }
        
        if (Str1[count1] == '\0' || Str2[count2] == '\0') {
            if (Str1[count1 + 1] == 0)
                return 1;
            if (Str2[count2 + 1] == 0)
                return -1;
        }
        count1++; count2++;
    }
}
