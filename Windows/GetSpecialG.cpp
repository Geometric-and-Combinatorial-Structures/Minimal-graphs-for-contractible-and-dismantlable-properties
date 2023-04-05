/*
This program runs over the family of acyclic graphs, up to 11 vertices, and find the graphs in SIC but not in SVIC.
*/


#include<stdio.h>
#include<math.h>
#include<string.h>
#include<time.h>
#define MaxV 11
FILE *IF,*OF;

void GetNameIn_ag(int v, int e,char NameInM[30]){
	char Num[30];
	strcpy(NameInM,"ag/");
	sprintf(Num,"%d",v);strcat(NameInM,Num);strcat(NameInM,"v/");
	sprintf(Num,"%d",v);strcat(NameInM,Num);strcat(NameInM,"v");
	sprintf(Num,"%d",e);strcat(NameInM,Num);strcat(NameInM,"e._g6");
}
void GetNameIn_ag(int v, int e,int M,char NameInM[30]){
	char Num[30];
	strcpy(NameInM,"ag/11v/11v");
	sprintf(Num,"%d",e);strcat(NameInM,Num);strcat(NameInM,"e/11v");
	sprintf(Num,"%d",e);strcat(NameInM,Num);strcat(NameInM,"e");
	if(M<10) strcat(NameInM,"-00"); 
	if(M>=10 && M<100) strcat(NameInM,"-0");
	if(M>=100) strcat(NameInM,"-"); 
	sprintf(Num,"%d",M); strcat(NameInM,Num);strcat(NameInM,"._g6");
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



//Calculate Open Neiborhood of vertex
void CalLk(int A[MaxV][MaxV],  int n, int k,
            int Lk[MaxV][MaxV], int *m){
	int i,j;
	int Isobre[MaxV];
	*m=0;
	for(j=0;j<n;j++) 
		if(A[k][j]==1) {
		  Isobre[*m]=j; //Survivor Vertex
		  (*m)++;
		}
	for(i=0;i<*m;i++)for(j=0;j<*m;j++)	Lk[i][j]=A[Isobre[i]][Isobre[j]];
}
//Delete vertex of graph
void DeleteVert(int A[MaxV][MaxV],  int n, int k,int B[MaxV][MaxV], int *m){
	int i,j;	
	(*m)=n-1;
	for(i=0;i<*m;i++){
		for(j=0;j<*m;j++){
			if(i<k && j<k) B[i][j]=A[i][j];
			if(!(i<k) && j<k) B[i][j]=A[i+1][j];
			if(i<k && !(j<k)) B[i][j]=A[i][j+1];
			if(!(i<k) && !(j<k)) B[i][j]=A[i+1][j+1];
		}
	}    
}
int BtoSICv(int G[MaxV][MaxV],int n){
	int i,j,m;
    int Lk[MaxV][MaxV],GmV[MaxV][MaxV];
    if(n==0 || n==1)  return n;	
    else{
        //Try to delete some vertex
        for(i=0;i<n;i++){
            //Calcuate neighborhood of v_i   
			CalLk(G,n,i,Lk,&m);
			if(BtoSICv(Lk,m)==1){
			  	  DeleteVert(G,n,i,GmV,&m);
			  	  return BtoSICv(GmV,m); // For express version (n<12)
				  //if(BtoSICv(GmV,m)==1) return 1; // Full version
		}	}	
	    return 0;
}	}	

//Calculate Open Neibourhood of edge
void CalLk( int A[MaxV][MaxV],  int n, int k1,int k2,
           int Lk[MaxV][MaxV], int *m){
	int i,j;
	int Isobre[MaxV];
	*m=0;
	for(j=0;j<n;j++) 
		if(A[k1][j]*A[k2][j]==1) {
		  Isobre[*m]=j; //Survivor Vertex
		  (*m)++;
		}
	for(i=0;i<*m;i++)for(j=0;j<*m;j++)	Lk[i][j]=A[Isobre[i]][Isobre[j]];
}
//Delete edge of graph
void DeleteEdge(int A[MaxV][MaxV],  int n, int k1,int k2,int B[MaxV][MaxV]){
	int i,j;	
	for(i=0;i<n;i++){
	   for(j=0;j<n;j++) B[i][j]=A[i][j];
	}    
	B[k1][k2]=0;B[k2][k1]=0;
}
int BtoSIC( int G[MaxV][MaxV],int n){ // Belongs to Strong I-contractible set
	int i,j,m,CanDE;
    int Lk[MaxV][MaxV],GmV[MaxV][MaxV],GmE[MaxV][MaxV];
    if(n==0 || n==1)  return n;	
    else{
        //Try to delete some vertex
        for(i=0;i<n;i++){
            //Calcuate neighborhood of v_i   
			CalLk(G,n,i,Lk,&m);
			if(BtoSIC(Lk,m)==1){
			  	  DeleteVert(G,n,i,GmV,&m);
			  	  return BtoSIC(GmV,m);          // Express version for n<12
				  //if(BtoSIC(GmV,m)==1) return 1; // Full version 
		}	}	
		//Try to delete edges
		for(i=0;i<n-1 ;i++){
			for(j=i+1;j<n  ;j++){
				if(G[i][j]==1){
					CalLk(G,n,i,j,Lk,&m); //Calcuate neighborhood of v_i   \cap v_j
					if(BtoSIC(Lk,m)==1){
						DeleteEdge(G,n,i,j,GmE); 			
						return BtoSIC(GmE,n); // Express version
						//if(BtoSIC(GmE,n)==1) return 1; // Full version 
		}   }   }	}
		return 0;
	}
}

void PrintGtoD(int k,int G[MaxV][MaxV],int V){
	int i,j;printf("\n%d\n",k);
	for(i=0;i<V;i++){
		for(j=0;j<V;j++) printf("%2d ",G[i][j]); printf("\n");
	} printf("\n");
}

void PrintGtoF(int k,int G[MaxV][MaxV],int V){
	int i,j;fprintf(OF,"\n%d\n",k);
	for(i=0;i<V;i++){
		 for(j=0;j<V;j++) fprintf(OF,"%2d ",G[i][j]); fprintf(OF,"\n");
	} fprintf(OF,"\n");
}


int main(){
    int G[MaxV][MaxV];
	int V,E,M,v,e;
	long int k,kk,g,ng,ngM,Tg=0;
	char NameIn[30],NameInc[30];
	int Binary[64][6],count=0;
    
	FILE *IFc,*IFcM;
	clock_t Begin = clock(),End;  double time_spent;


    GetBin(Binary);
    OF=fopen("SpecialG.dat","w");
    IFc=fopen("#agVE.dat","r");
    if(IFc==NULL){
    	printf("\nProblems with #agVE.dat\n<enter to exit>");getchar(); return 1;
	}
	for(V=1;V<=10;V++){
		for(E=V-1;E<=V*(V-1)/2;E++){	
			fscanf(IFc,"%d %d %ld",&v,&e,&ng); printf("\nV=%d E=%d ng=%ld",v,e,ng);//getchar();
		    GetNameIn_ag(V,E,NameIn);
			IF=fopen(NameIn,"r");
		
			if(IF==NULL){
				printf("\nProblems with input file %s",NameIn); getchar(); return 1;
			}
			for(k=1;k<=ng;k++){
				GetA_M(Binary,G,V); Tg++;
				if(BtoSIC(G,V)==1){
				    if(BtoSICv(G,V)==0){
				    	count++;
				    	printf("\nFound a graph SIC but not SICv");
				    	PrintGtoF(count,G, V);
				    	PrintGtoD(count,G, V);
					}
				}
		    }
		    fclose(IF);
		}
		
	}
    if(count==0) printf("\n Did not found any special graph with V<=10\n");	
	
	V=11;
    for(E=V-1;E<=16;E++){	
			fscanf(IFc,"%d %d %ld",&v,&e,&ng); printf("\nV=%d E=%d ng=%ld",v,e,ng);//getchar();
		    GetNameIn_ag(V,E,NameIn);
			IF=fopen(NameIn,"r");
		
			if(IF==NULL){
				printf("\nProblems with input file %s",NameIn); getchar(); return 1;
			}
			for(k=1;k<=ng;k++){
				GetA_M(Binary,G,V);Tg++;
				if(BtoSIC(G,V)==1){
				    if(BtoSICv(G,V)==0){
				    	count++;
				    	printf("\nFound a graph SIC but not SICv");
				    	PrintGtoF(count,G, V);
				    	PrintGtoD(count,G, V);
					}
				}
		    }
		    fclose(IF);
	}
    if(count==0) printf("\n Did not found any special graph with V=11 and E=10,11,..., 16\n");	
    
    for(E=17;E<=39;E++){	
			fscanf(IFc,"%d %d %ld",&v,&e,&ng); printf("\nV=%d E=%d ng=%ld  \n          M= 1 ",v,e,ng);
			M=1;
			
			GetNameIn_ag(V,E,M,NameIn);
			IF=fopen(NameIn,"r");
			if(IF==NULL){
					printf("\nProblems with input file %s",NameIn); getchar(); return 1;
			}
			GetNameIn_agc(V,E,M,NameInc);
			IFcM=fopen(NameInc,"r");
			if(IFcM==NULL){
					printf("\nProblems with input file %s",NameInc); getchar(); return 1;
			}			
			
			do{
				fscanf(IFcM,"%ld",&ngM);
				for(g=1;g<=ngM;g++){
						GetA_M(Binary,G,V);Tg++;
						if(BtoSIC(G,V)==1){
						    if(BtoSICv(G,V)==0){
						    	count++;
						    	printf("\nFound a graph SIC but not SICv     M=%d",M);
						    	PrintGtoF(count,G, V);
						    	PrintGtoD(count,G, V);printf("\n             ");
							}
						}
				}				
				M++;
				fclose(IF);fclose(IFcM);GetNameIn_ag(V,E,M,NameIn);  IF=fopen(NameIn,"r");
				                        GetNameIn_agc(V,E,M,NameInc);IFcM=fopen(NameInc,"r");
				if(IF!=NULL && IFcM!=NULL){

               			printf("%2d ",M);if(M%30==0) printf("\n            ");
				}                        
			}while(IF!=NULL && IFcM!=NULL);
	}    
    if(count>0) printf("\n %d special graphs were founded",count);
    
    for(E=40;E<=V*(V-1)/2;E++){	
			fscanf(IFc,"%d %d %ld",&v,&e,&g); printf("\nV=%d E=%d ng=%ld",v,e,g);//getchar();
		    GetNameIn_ag(V,E,NameIn);
			IF=fopen(NameIn,"r");
		
			if(IF==NULL){
				printf("\nProblems with input file %s",NameIn); getchar(); return 1;
			}
			for(k=1;k<=g;k++){
				GetA_M(Binary,G,V);Tg++;
				if(BtoSIC(G,V)==1){
				    if(BtoSICv(G,V)==0){
				    	count++;
				    	printf("\nFound a graph SIC but not SICv");
				    	PrintGtoF(count,G, V);
				    	PrintGtoD(count,G, V);
					}
				}
		    }
		    fclose(IF);
	}     
	fclose(OF);
    if(count==12) printf("\n No more special graphs were founded");
    End=clock();time_spent = (double)(End - Begin) / CLOCKS_PER_SEC;
    printf("\nExecution time %lf\n", time_spent);
    printf("\n%0.0lf graphs processed per second\n<Enter to exit>",Tg/time_spent);getchar();
    
	return 0;
}
