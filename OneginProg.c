#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>


int cmp(const void * x1,const void * x2);
int WriteDownAdd(char* Str, char** StrAdd, char** StrAdd2, char** StrAdd3, const int size);
int CountSymbols(FILE* file, int* size);
int Check_open(FILE* File1,FILE* File2,FILE* File3);
int FreeAndClose (FILE* File1, FILE* File2, FILE* File3,char* Str,char** AddStr1,char** AddStr2,char** AddStr3);

int main() {
    FILE* Onegin = NULL;
    FILE* Onegin_alf = NULL;
    FILE* Onegin_ryhm = NULL;
    
    Onegin = fopen("Onegin.txt","r");
    Onegin_alf = fopen("Onegin_alf.txt","w");
    Onegin_ryhm = fopen("Onegin_ryhm.txt","w");
    
    const int size = 237568, addsize = 7200;
    
    int error = 0;
    
    error = Check_open(Onegin, Onegin_alf, Onegin_ryhm);
    if (error == 1)
        return 1;
        
    int size2 = 0;
    int size1 = CountSymbols(Onegin, &size2);
    printf("%d %d\n", size1, size2);
    
    char* OneginStr = (char*) calloc(size,sizeof(char));
    char** OneginStrAdd = (char**) calloc (addsize, sizeof(char*));
    char** OneginStrAdd2 = (char**) calloc (addsize, sizeof(char*));
    char** OneginStrAdd3 = (char**) calloc (addsize, sizeof(char*));
    
    fread(OneginStr,sizeof(char), size, Onegin);
    
    int count = WriteDownAdd(OneginStr, OneginStrAdd, OneginStrAdd2, OneginStrAdd3, size);
    
    printf("%d", count);
    
    qsort(OneginStrAdd2, count, sizeof(char**), cmp);
    
    int start = 0, mem = 0;
    
    for (int i = 0;; i++) {       
       for (int j = 0; OneginStrAdd2[i][j] != '\0'; j++) {
           if (OneginStrAdd2[i][j] == 'A'){
                start = i;
                mem = j;
                break;
           }
        }
     if (OneginStrAdd2[i][mem] == 'A')
         break;
    }
    
    for(int i = start; i <= count; i++) {
    fprintf(Onegin_alf, "%s\n", OneginStrAdd2[i]);
    }
    
    FreeAndClose(Onegin, Onegin_alf, Onegin_ryhm, OneginStr, OneginStrAdd, OneginStrAdd2, OneginStrAdd3);
}

int cmp(const void * x1,const void * x2) {
    char* Str1 = *(char**)x1;
    char* Str2 = *(char**)x2;
    
    int count1 = 0, count2 = 0;
    
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

int WriteDownAdd(char* Str, char** StrAdd, char** StrAdd2, char** StrAdd3, const int size) {
    
    int count = 0;
    
    for (int i = 0; i<= size; i++) {
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

int Check_open(FILE* File1,FILE* File2,FILE* File3) {
    
    int error = 0;
    
    if (File1 == NULL) {
        printf ("File on read couldn't open");
        error = 1;
    }
    if (File2 == NULL) {
        printf ("File to sort by alphabet couldn't open");
        error = 1;
    }
    if (File3 == NULL) {
        printf ("File to sort by ryhms couldn't open");
        error = 1;
    }
    return error;
}

int FreeAndClose (FILE* File1, FILE* File2, FILE* File3,char* Str,char** AddStr1,char** AddStr2,char** AddStr3) {
    fclose(File1);
    fclose(File2);
    fclose(File3);
    
    free(Str);
    free(AddStr1);
    free(AddStr2);
    free(AddStr3);
    
    return 0;
}