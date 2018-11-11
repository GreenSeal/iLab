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
        printf("dgagga");
        
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
            if (OneginStrAdd[count] == NULL || OneginStrAdd2[count] == NULL || OneginStrAdd3[count] == NULL)
                printf("Ti glupij");
            ++count;
        }
    }
    
   /* for(int i = 0; i<=500; i++) {
       printf("\n%s",OneginStrAdd2[i]);
    }*/
    
    qsort(OneginStrAdd2,count, sizeof(char**), cmp);
    
    for(int i = 0; i<=500; i++) {
       printf("%s",OneginStrAdd2[i]); 
    }
}

int cmp(const void * x1,const void * x2) {
    char* Str1 = *(char**)x1;
    char* Str2 = *(char**)x2;
    
    printf("Ti tupoy");
    char el1,el2;
    
    for(int i = 0;; i++) {
        el1 = Str1[i];
        el2 = Str2[i];
        if (el1 > el2) 
            return 1;
        if (el1 < el2)
            return -1;
        if (el1 == '\0' || el2 == '\0')
            return 0;
    }
}
