#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>


int cmp(const void * x1,const void * x2);
int WriteDownAdd(char* Str, char** StrAdd, char** StrAdd2, char** StrAdd3, int SizeAdd);
int CountSymbols(FILE* file, int* size);

int main() {
    
    FILE* Onegin = NULL;
    FILE* Onegin_alf = NULL;
    FILE* Onegin_ryhm = NULL;
    Onegin = fopen("Onegin.txt","r");
    Onegin_alf = fopen("Onegin_alf.txt","w");
    Onegin_ryhm = fopen("Onegin_ryhm.txt","w");
    
    if (Onegin == NULL)
        printf ("File on read couldn't open");
    if (Onegin_alf == NULL)
        printf ("File to sort by alphabet couldn't open");
    if (Onegin_ryhm == NULL)
        printf ("File to sort by ryhms couldn't open");
        
    int size2 = 0;
    int size = CountSymbols(Onegin, &size2);
    
    char* OneginStr = (char*) calloc(size+1,sizeof(char));
    char** OneginStrAdd = (char**) calloc (size2+1, sizeof(char*));
    char** OneginStrAdd2 = (char**) calloc (size2+1, sizeof(char*));
    char** OneginStrAdd3 = (char**) calloc (size2 +1, sizeof(char*));
    
    fread(OneginStr,sizeof(char), size+1, Onegin);
    
    int count = WriteDownAdd(OneginStr, OneginStrAdd, OneginStrAdd2, OneginStrAdd3, size+1);
    
    
    qsort(OneginStrAdd2, count+1, sizeof(char**), cmp);
    
    for(int i = 0; i<=count; i++) {
       printf("%s\n",OneginStrAdd2[i]); 
    }
    fclose(Onegin);
}

int cmp(const void * x1,const void * x2) {
    char* Str1 = *(char**)x1;
    char* Str2 = *(char**)x2;
    
    int count1 = 0;
    int count2 = 0;
    
    for(;;) {
        
        for (;;){
            if (Str1[count1] == '`' || Str1[count1] == ' ' || Str1[count1] == '}' 
            || Str1[count1] == '{' || isdigit(Str1[count1]) != 0 || Str1[count1] == '<' 
            || Str1[count1] == '"')
                count1 ++;
            else if (Str2[count2] == '`' || Str2[count2] == ' ' || Str2[count2] == '}' 
                || Str2[count2] == '{' || isdigit(Str2[count2]) != 0 || Str2[count2] == '<' 
                || Str2[count2] == '"')
                count2 ++;
                 else break;
        }
        
        char el1 = Str1[count1];
        char el2 = Str2[count2];
        
        if (el1 >= 'A' && el1 <= 'Z')
           el1 = tolower(el1);
            
        if (el2 >= 'A' && el2 <= 'Z')
            el2 = tolower(el2);
        
        if (el1 > el2) { 
            return 1;
        }
        if (el1 < el2) {
            return -1;
        }
        
        if (el1 == '\0' || el2 == '\0') {
           return 0;
        }
        count1++; count2++;
    }
}

int WriteDownAdd(char* Str, char** StrAdd, char** StrAdd2, char** StrAdd3, int SizeAdd) {
    printf("%d", SizeAdd);
    int count = 0;
    
    for (int i = 0; i<= SizeAdd; i++) {
        if (Str[i] == '\n') {
            Str[i] = '\0';
            StrAdd[count] = Str + i + 1;
            StrAdd2[count] = Str + i + 1;
            StrAdd3[count] = Str + i + 1;
            
            if (StrAdd[count] == 0)
                printf ("Address don't writedown in massive 1");
            if (StrAdd2[count] == 0)
                printf ("Address don't writedown in massive 2");
            if (StrAdd3[count] == 0)
                printf ("Address don't writedown in massive 3");
           
            ++count;
        }
    }
    return count;
}

int CountSymbols(FILE* file, int* size) {
    
    int count1 = 0;
    char buf = 0;
    
    fseek(file, 0, SEEK_SET);
    
    while(feof(file) == 0) {
        
        fscanf(file, "%c", &buf);
        
        count1 ++;
        
        if ( buf == '\0' || buf == '\n')
            count1 ++;
        
        if ( buf == '\n') {
            (*size) ++;
        }
    }
    fseek(file, 0, SEEK_SET);
    return count1;
}