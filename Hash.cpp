#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "Node.cpp"

//#define N 1

typedef struct List_ List;

struct List_ {
    Node* head = NULL;
    int size;
};

int BaseOfData (List* Table);
int HashTable(unsigned long long tel_number, List* Table);
int HashFunction1 (unsigned long long tel_number);
int HashFunction2 (unsigned long long tel_number);
int HashFunction3 (unsigned long long tel_number);
int HashFunction4 (unsigned long long tel_number);
int HashFunction5 (unsigned long long tel_number);

const int SizeTable = 1000;
const int SizeNumber = 12;

int main() {
    srand(time(NULL));
    
    List* Table = new List [SizeTable];
    int i = 0;
   
    for(i = 0; i <= SizeTable-1; i++)
        Table[i].size = 0;
        
    BaseOfData(Table);
    
    FILE* Hash = NULL;
    Hash = fopen("Hash5.csv", "w");
    
    if (Hash == NULL)
        printf("File couldn't open\n");
   
    for (i = 0; i <= SizeTable-1; i++) {
        
        fprintf(Hash, "%d ; %d\n", i, Table[i].size);
        //printf("%d %d\n", i,  Table[i].size);
    }
    
    fclose(Hash);
    
	return 0;
}

int BaseOfData (List* Table) {
    
    int i = 0, j = 0;
    for (i = 0; i <= (SizeTable - 1)*100; i++) {
        
        unsigned long long tel_number = 0;
        
        for (j = 0; j <= SizeNumber - 2; j++)
            tel_number = tel_number*10 + rand()%10;                                                                                //Создаю Рандомный телефонный номер
            //printf("%llu ", tel_number);
            HashTable(tel_number, Table);
        }
    return 0;
    }

int HashTable(unsigned long long tel_number, List* Table) {
    
    int num = HashFunction5(tel_number);                                                                                        //Вычисляю номер, в который закинуть номер
    
    if (Table[num].head == NULL) {                                                                                              //Если еще нет узла под Listом, создаю
        Node* AddNewNode = Create(tel_number);
        Link(NULL, (Table + num) -> head, AddNewNode);
        Table[num].head = AddNewNode;
        Table[num].size++;
        return 0;
    }
            
        Node* buf = Table[num].head;
        
        while(buf != NULL) {                                                                                                       //Проверка на совпадение
            
            if (buf -> data == tel_number){
                //printf("Already add");
                return 0;
            }
            
            buf = buf -> next;
        }
        
        buf = Table[num].head;
        
        while(buf -> next != NULL)                                                                                                  //Запись в конец
            buf = buf -> next;
                
        Node *AddNewNode = Create(tel_number);
        Link(NULL, buf, AddNewNode);
        (Table[num].size)++;
        
    return 0;
}
    
int HashFunction1(unsigned long long tel_number) {                                                                                                   //Все в один
    
    int num = 0;
    return num;
}

int HashFunction2(unsigned long long tel_number) {                                                                                               // По первой цифре
    
    int num = tel_number/(pow(10, SizeNumber - 3));
    //printf("%llu  ", tel_number);
    return num;
}

int HashFunction3 (unsigned long long tel_number) {                                                                                             // По сумме цифр
    
    int sum = 0, buf = 0;
    int i = 0;
    for (i = 0; i <= SizeNumber - 2; i++) {                                                                                         // -2 из-за счёта с нуля и размера номера
        buf = tel_number%10;
        sum = sum + buf;
        tel_number = (tel_number - buf)/10;
    }
    
    return sum;
}

int HashFunction4 (unsigned long long tel_number) {                                                                                              //Побитовое смещение
    
    int val1 = (tel_number >> (SizeNumber - 2)) & 1u;
    int val2 = (tel_number >> 0) & 1u;
    if (val1 == 1)
        tel_number = tel_number | (1u << (SizeNumber - 2));
    if (val1 == 0)
        tel_number = tel_number & ~(1u << (SizeNumber - 2));
    if (val2 == 1)
        tel_number = tel_number | (1u);
    if (val2 == 0)
        tel_number = tel_number & ~(1u);
        
    return tel_number%SizeTable;
}

int HashFunction5 (unsigned long long tel_number) {                                                                                                 //Долден быть Пуассон
    
    unsigned long start = 7, sum = start, buf = 0;
    int i = 0;
    for(i = 0; i <= (SizeNumber - 2); i++) {
        //printf("%d  ", sum);
        buf = tel_number%10;
        sum = sum*2 + buf;
        tel_number = (tel_number - buf)/10;
    }
    
    return sum%SizeTable;
}

