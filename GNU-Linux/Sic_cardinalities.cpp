/*
This program is collect cadinalities of strong I-contractible graphs and check misings runs.
*/

#include<stdio.h>
#include<string.h>
#include<math.h>

void GetNameIn_agc(int v, int e, char NameInM[30]){
    char Num[30];
    strcpy(NameInM,"sic/");
    sprintf(Num,"%d",v);strcat(NameInM,Num);strcat(NameInM,"v/#");
    sprintf(Num,"%d",v);strcat(NameInM,Num);strcat(NameInM,"v");
    sprintf(Num,"%d",e);strcat(NameInM,Num);strcat(NameInM,"e.dat");
}

void GetNameIn_agc(int v, int e, int M, char NameInM[30]){
    char Num[30];
    strcpy(NameInM,"sic/11v/11v");
    sprintf(Num,"%d",e);strcat(NameInM,Num);strcat(NameInM,"e/#11v");
    sprintf(Num,"%d",e);strcat(NameInM,Num);strcat(NameInM,"e");
    if(M<10) strcat(NameInM,"-00");
    if(M>=10 && M<100) strcat(NameInM,"-0");
    if(M>=100) strcat(NameInM,"-");
    sprintf(Num,"%d",M); strcat(NameInM,Num);strcat(NameInM,".dat");
}

int main(){
    FILE *OFv,*OFve,*IFve;
    FILE *IFc;
    int V,E,v,e,M,nM,i;
    long int g,ga;
    char NameIn_c[30];
    long int card, cardCGve;
    
    IFve=fopen("#cgVE.dat","r");
    
    OFv=fopen("#sicV.dat","w");
    OFve=fopen("#sicVE.dat","w");
    
    for(V=1;V<=10;V++){
        ga=0;
        g=0;
        for(E=V-1;E<=V*(V-1)/2;E++){
            GetNameIn_agc(V,E,NameIn_c);
            fscanf(IFve,"%d %d %ld", &v,&e,&cardCGve);
            IFc=fopen(NameIn_c,"r");
            if(IFc==NULL){
                printf("\nProblems with input file %s.",NameIn_c);
                printf("\nFile for v=%d and e=%d is missing.\n",V,E);
                getchar();
                return 1;
            }
            fscanf(IFc,"%ld",&card); 
            fclose(IFc);
            g+=card;
            fprintf(OFve,"%d %d %ld\n",V,E,card);
        }
        ga+=g;
        fprintf(OFv,"%d %ld\n",V,ga);
    }
    
    V=11;
    ga=0;
    for(E=V-1;E<=16;E++){
        g=0;
        GetNameIn_agc(V,E,NameIn_c);
        fscanf(IFve,"%d %d %ld", &v,&e,&cardCGve);
        IFc=fopen(NameIn_c,"r");
        if(IFc==NULL){
            printf("\nProblems with input file %s.",NameIn_c);
            printf("\nFile for v=%d and e=%d is missing.\n",V,E);
            getchar();
            return 1;
        }
        fscanf(IFc,"%ld",&card);
        fclose(IFc);
        g+=card;
        ga+=card;
        fprintf(OFve,"%d %d %ld\n",V,E,card);
    }
    
    for(E=17;E<=39;E++){
        g=0;
        fscanf(IFve,"%d %d %ld", &v,&e,&cardCGve);
        printf("Cardinality=%ld, ",cardCGve);
        nM=ceil(cardCGve/1000000.0);
        printf("V=%d,   E=%d,   M=%d\n",V,E,nM);
        for(M=1;M<=nM;M++){
            GetNameIn_agc(V,E,M,NameIn_c);
            IFc=fopen(NameIn_c,"r");
            if(IFc!=NULL){
                fscanf(IFc,"%ld",&card); 
                fclose(IFc);
                g+=card;
                ga+=card;
            }else{
                printf("\nProblems with input file %s.\n",NameIn_c);
                printf("\nFile for v=%d, e=%d and M=%d is missing.\n",V,E,M);
                getchar();
                return 1;
            }
        }
        fprintf(OFve,"%d %d %ld\n",V,E,g);
    }
    
    for(E=40;E<=V*(V-1)/2;E++){
        g=0;
        GetNameIn_agc(V,E,NameIn_c);
        IFc=fopen(NameIn_c,"r");
        if(IFc==NULL){
            printf("\nProblems with input file %s.\n", NameIn_c);
            getchar();
            return 1;
        }
        fscanf(IFc,"%ld",&card);
        fclose(IFc);
        g+=card;
        ga+=card;
        fprintf(OFve,"%d %d %ld\n",V,E,card);
    }
    fprintf(OFv,"%d %ld\n",V,ga);
    return 0;
}
