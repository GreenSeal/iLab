#include<stdio.h>
#include<stdlib.h>

int Calculate_R(int i, double* U,double* I, FILE *babka);

int Check_open (FILE *labka,FILE *babka);


int main(){
    double* U = (double*) calloc(36, sizeof(double*));
    double* I = (double*) calloc(36, sizeof(double*)); 
    int check = 2;
    
    FILE *labka=NULL; 
    FILE *babka=NULL;
    labka = fopen("labka.txt","r"); 
    babka = fopen("babka.csv","w");
    
    check = Check_open(labka,babka);
    
    if (check == 1){
        return 1;
    }
    
    
    
    for(int i=0;i<=35;i++){
        fscanf(labka,"%lf %lf",&U[i],&I[i]);
        
        
        Calculate_R(i,U,I,babka);
    }
    
    fclose(labka);                                     
    fclose(babka);
	return 0;
}
    

int Calculate_R(int i, double* U,double* I, FILE *babka){
    double d=0.035,L=1;
    const double Tolerance = 1e-6;
    
    if ((I[i] > 0.0-Tolerance) && (I[i] < 0.0+Tolerance)){
        printf("Read error\n");
        return 1;
        }
        
    if (i==0)                                       
           fprintf(babka,"L=20cm\n");
    
    if ((i>-1) && (i<=11)){                         
        L=20;
            
        fprintf(babka,"%f Om*cm\n",(U[i]/I[i])*d/L);
    }
    if (i==11)                                      
        fprintf(babka,"\n\nL=30cm\n");
            
    if ((i>11) && (i<=23)){                         
        L=30;
        
        fprintf(babka,"%f Om*cm\n",(U[i]/I[i])*d/L);
    }
        
    if (i==23)                                     
        fprintf(babka,"\n\nL=50cm\n");
            
    if ((i>23) && (i<=35)){                         
        L=50;
            
        fprintf(babka,"%f Om*cm\n",(U[i]/I[i])*d/L);
    }
    return 0;        
}

int Check_open (FILE *labka,FILE *babka){
    int error = 0;
    if (labka == NULL){
        printf("Could not open file labka");
        error = 1;
    }
        
        
    if (babka == NULL){
        printf("Could not open file babka");
        error = 1;
    }
    return error;
}

