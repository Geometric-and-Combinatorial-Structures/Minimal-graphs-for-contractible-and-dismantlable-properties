/*
This program take connected graphs up to 8 vertices
and say which one are 1 diamatables but no 0 dismantable

*/

#include<string.h>
#include<stdio.h>
#include<math.h>

//Maximun number of vertices 
#define MaxV 8

FILE *IF,*OF,*IFc;

void GetNameIn(int v, int e,char NameIn[30]){
	char Num[30];
	strcpy(NameIn,"ag/");
	sprintf(Num,"%d",v);strcat(NameIn,Num);strcat(NameIn,"v/");
	sprintf(Num,"%d",v);strcat(NameIn,Num);strcat(NameIn,"v");
	sprintf(Num,"%d",e);strcat(NameIn,Num);strcat(NameIn,"e._g6");
}

void GetBin(int Binary[64][6]){
  int i,j,k;
  for(i=0;i<64;i++){
  	 k=i; for(j=5;j>=0;j--){ Binary[i][j]=k%2; k/=2;	}
  }
}

void GetA_M(int Binary[64][6],int G[MaxV][MaxV],int V){
	int nB=ceil(V*(V-1)/2.0/6),i,j,k; 	int OnesZ[6*nB]; char Num[12];
	// Get 0-1 chain
	for(k=0;k<nB;k++){
	   fscanf(IF,"%c",&Num[k]); 	
	   for(j=0;j<6;j++) OnesZ[6*k+j]=Binary[Num[k]-63][j];// By ._g6 format
	}fscanf(IF,"%c",&Num[k]);	
	
	k=0;// Put 0-1 in their places of G
	for(j=1;j<V;j++){
		for(i=0;i<j;i++){
			G[i][j]=OnesZ[k];k++;
			G[j][i]=G[i][j];
		}G[j-1][j-1]=0;
	}G[V-1][V-1]=0; //Last one element of diagonal
}

int IsCone( int G[MaxV][MaxV],int v){
   	 int Degre[MaxV];
   	int i,j;
   	for(i=0;i<v;i++){
   		Degre[i]=0;
   		for(j=0;j<v;j++){
   		 	Degre[i]+=G[i][j];
		}
		if(Degre[i]==v-1) return 1;
	}
	return 0;
}

//Calcuate neigbourhood of v_i  
void CalLk(int A[MaxV][MaxV],  int n, int k,
           int Lk[MaxV][MaxV], int *m){
	int i,j;
	int Isobre[MaxV];
	int Cont=0;
	
	for(j=0;j<n;j++) {
		if(A[k][j]==1) {
		  Isobre[Cont]=j;
		  Cont++;	
		}
	}
	*m=Cont;
	
	for(i=0;i<*m;i++){
		for(j=0;j<*m;j++){
			Lk[i][j]=A[Isobre[i]][Isobre[j]];
		}
	}
}



void DeleteVert( int A[MaxV][MaxV],  int n, int k,int B[MaxV][MaxV], int *m){
	int i,j;	
	*m=n-1;
	for(i=0;i<*m;i++){
		for(j=0;j<*m;j++){
			if(i<k && j<k) B[i][j]=A[i][j];
			if(!(i<k) && j<k) B[i][j]=A[i+1][j];
			if(i<k && !(j<k)) B[i][j]=A[i][j+1];
			if(!(i<k) && !(j<k)) B[i][j]=A[i+1][j+1];
		}
	}    
}

// Recursive function to verify if G is 0-dismantable
int Is0Dis(int G[MaxV][MaxV],int n){
	int Lk[MaxV][MaxV],GmV[MaxV][MaxV];
	int i,m;
	if(n==1) return 1;
	else{
		for(i=0;i<n;i++){
			//Calcuate neighborhood of v_i   
			CalLk(G,n,i,Lk,&m);
			if(IsCone(Lk,m)==1){
				DeleteVert(G,n,i,GmV,&m);
				return Is0Dis(GmV,m);
			}
	    }
	    return 0;
	}
}

// Recursive function to verify if G is 1-dismantable
int Is1Dis(int G[MaxV][MaxV],int n){
	int Lk[MaxV][MaxV],GmV[MaxV][MaxV];
	int i,m;
	if(n==1) return 1;
	else{
		for(i=0;i<n;i++){
			//Calcuate neighborhood of v_i   
			CalLk(G,n,i,Lk,&m);
			if(Is0Dis(Lk,m)==1){
				DeleteVert(G,n,i,GmV,&m);
				return Is1Dis(GmV,m);
			}
	    }
	    return 0;
	}
}

void PrintGtoD(int k,int G[MaxV][MaxV],int V){
	int i,j;printf("\ng%d\n",k);
	for(i=0;i<V;i++){
		for(j=0;j<V;j++) printf("%2d ",G[i][j]); printf("\n");
	} printf("\n");
}

void PrintGtoF(int k,int G[MaxV][MaxV],int V){
	int i,j;fprintf(OF,"\ng%d\n",k);
	for(i=0;i<V;i++){
		 for(j=0;j<V;j++) fprintf(OF,"%2d ",G[i][j]); fprintf(OF,"\n");
	} fprintf(OF,"\n");
}

int main(){
	char NameIn[20],Num[12];
	int G[MaxV][MaxV],Lk[MaxV][MaxV];
    
    int V,E;
    int v,e;
    int i,j,k,kk,kkk,m;
    long int Cant,Cont=0;
    int Vert;
    int Binary[64][6];
    
    GetBin(Binary);
    IFc=fopen("#agVE.dat","r");
    OF=fopen("ag_Not0Dis.dat","w");
    Cont=0;
    for(V=1;V<=8;V++){
    	for(E=V-1;E<=V*(V-1)/2;E++){
    		GetNameIn(V,E,NameIn);//printf("File opened %s\n",NameIn);
    		IF=fopen(NameIn,"r");
    		fscanf(IFc,"%d %d %ld",&v,&e,&Cant); 
    		for(kk=1;kk<=Cant;kk++){
    		   GetA_M(Binary,G,V); 	
	  	  	   if(Is0Dis(G,V)==0){
	  	  	   	   	Cont++;
	  	  	   	   	printf("\n v=%d e=%d ",V,E);
	  	  	   	   	fprintf(OF,"\n v=%d e=%d ",V,E);
	  	  	   	   	PrintGtoD(Cont,G,V);
	  	  	   	   	PrintGtoF(Cont,G,V);
			   }
		    }
	    }   
    	fclose(IF);
	}
    fclose(IFc);fclose(OF);

    
    return 0;
    
}
