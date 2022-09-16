/*
This program is to collect cardinaties of acyclic graphs
*/


#include<stdio.h>
#include<string.h>

void GetNameIn_agc(int v, int e,char NameInM[30]){
	char Num[30];
	strcpy(NameInM,"ag/");
	sprintf(Num,"%d",v);strcat(NameInM,Num);strcat(NameInM,"v/#");
	sprintf(Num,"%d",v);strcat(NameInM,Num);strcat(NameInM,"v");
	sprintf(Num,"%d",e);strcat(NameInM,Num);strcat(NameInM,"e.dat");
}
void GetNameIn_agc(int v, int e,int M,char NameInM[30]){
	char Num[30];
	strcpy(NameInM,"ag/11v/11v");
	sprintf(Num,"%d",e);strcat(NameInM,Num);strcat(NameInM,"e/#11v");
	sprintf(Num,"%d",e);strcat(NameInM,Num);strcat(NameInM,"e");
	if(M<10) strcat(NameInM,"-00"); 
	if(M>=10 && M<100) strcat(NameInM,"-0");
	if(M>=100) strcat(NameInM,"-"); 
	sprintf(Num,"%d",M); strcat(NameInM,Num);strcat(NameInM,".dat");
}


int main(){
	FILE *OFv,*OFve;
	FILE *IFc;
	int V,E,M;
	long int g,ga;
	char NameIn_c[30];
	long int card;
	
	OFv=fopen("#agV.dat","w");
	OFve=fopen("#agVE.dat","w");
	for(V=1;V<=10;V++){
		ga=0;
		g=0;
		for(E=V-1;E<=V*(V-1)/2;E++){	
		    GetNameIn_agc(V,E,NameIn_c);
			IFc=fopen(NameIn_c,"r");
			if(IFc==NULL){
				printf("\nProblems with input file %s",NameIn_c); getchar(); return 1;
			}
			fscanf(IFc,"%d",&card); fclose(IFc);
			g+=card;
			fprintf(OFve,"%d %d %ld\n",V,E,card);
		}
		ga+=g;
		fprintf(OFv,"%d %ld\n",V,ga);
	}
	
	
	V=11;	
	ga=0;
	g=0;
	for(E=V-1;E<=16;E++){
		GetNameIn_agc(V,E,NameIn_c);
		IFc=fopen(NameIn_c,"r");
		if(IFc==NULL){
			printf("\nProblems with input file %s",NameIn_c); getchar(); return 1;
		}
		fscanf(IFc,"%d",&card);fclose(IFc);
		g+=card;
		fprintf(OFve,"%d %d %ld\n",V,E,card);
	}
	ga+=g;


	for(E=17;E<=39;E++){
		g=0;
		M=1;
		do{
			GetNameIn_agc(V,E,M,NameIn_c);
			IFc=fopen(NameIn_c,"r");
			if(IFc!=NULL){
				fscanf(IFc,"%d",&card); fclose(IFc);
				g+=card;
				M++;				
			}
		}while(IFc!=NULL);
	    fprintf(OFve,"%d %d %ld\n",V,E,g);
	    ga+=g;
	}
		

	g=0;
	for(E=40;E<=V*(V-1)/2;E++){
		GetNameIn_agc(V,E,NameIn_c);
		IFc=fopen(NameIn_c,"r");
		if(IFc==NULL){
			printf("\nProblems with input file %s", NameIn_c); getchar(); return 1;
		}
		fscanf(IFc,"%d",&card);fclose(IFc);
		g+=card;
		fprintf(OFve,"%d %d %d\n",V,E,card);
	}
	ga+=g;
	fprintf(OFv,"%d %ld\n",V,ga);	
	
	return 0;
}
