#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<time.h>
/*
This program take simple graphs of      https://users.cecs.anu.edu.au/~bdm/data/graphs.html
and save in several files
depending of number of vertices and edges (v,e)  (to make easy parallel work).

Also eliminate N[n] of format .g6 of Mckey
to reduce a little size of files.                  the new format we will call ._g6

Number of vertices is part of the name of file.


During the process files and directories will be relocated

*/

//   CHOOSE an operative sistem     0 for   linux          1 for msdos/windows    
#define OS 1

  

#define MaxV 11
void Back(void){  
  int i; for(i=1;i<=11;i++) printf("%c",8);// Move 10 places left
}

void GetBin(int Binary[64][6], int Qones[64]){
  int i,j,k;
  for(i=0;i<64;i++){
     k=i;Qones[i]=0;
     for(j=5;j>=0;j--){
         Binary[i][j]=k%2; k/=2;  
         Qones[i]+=Binary[i][j];
   }
  }
}

void GetNameIn(int v, char NameIn[30]){
  char Num[30];
  strcpy(NameIn,"graph");
  sprintf(Num,"%d",v);strcat(NameIn,Num);
  if(v!=11) strcat(NameIn,"c.g6"); else strcat(NameIn,".g6");
}

void GetNameOut(int v, int e,char NameOut[30]){
  char Num[30];
  strcpy(NameOut,"");
  sprintf(Num,"%d",v);strcat(NameOut,Num);strcat(NameOut,"v"); 
  sprintf(Num,"%d",e);strcat(NameOut,Num);strcat(NameOut,"e._g6");
}
void GetNameOutM(int v, int e,int M,char NameOutM[30]){
  char Num[30];
  strcpy(NameOutM,"");
  sprintf(Num,"%d",v);strcat(NameOutM,Num);strcat(NameOutM,"v"); 
  sprintf(Num,"%d",e);strcat(NameOutM,Num);strcat(NameOutM,"e");
  if(M<10) strcat(NameOutM,"-00"); 
  if(M>=10 && M<100) strcat(NameOutM,"-0");
  if(M>=100) strcat(NameOutM,"-"); 
  sprintf(Num,"%d",M); strcat(NameOutM,Num);strcat(NameOutM,"._g6");
}

void MakeDirV(int v){// Create directory of V vertex
	char Num[30],Comm1[50];
	if(OS==0) strcpy(Comm1,"mkdir "); // linux
	else strcpy(Comm1,"md "); // msdos
    sprintf(Num,"%d",v);strcat(Comm1,Num);strcat(Comm1,"v"); 
    system(Comm1);     
}
void MakeDirVE(int v, int e){ // Create directory of V vertex and E edges
	char Num[30],Comm1[50];
	if(OS==0)strcpy(Comm1,"mkdir "); // linux
	else strcpy(Comm1,"md "); // msdos
    sprintf(Num,"%d",v);strcat(Comm1,Num);strcat(Comm1,"v"); 
    sprintf(Num,"%d",e);strcat(Comm1,Num);strcat(Comm1,"e");
    system(Comm1);     
}
void MoveToDir(int v){ // Move files of V vertices and any edges to correspondent directory
	char Num[30],Comm1[50],Name[30],NameT[30];
	strcpy(Name," ");sprintf(Num,"%d",v);strcat(Name,Num);strcat(Name,"v");  strcpy(NameT,Name);
	strcat(Name,"*._g6 ");
	if(OS==0)strcpy(Comm1,"mv "); // linux
	else strcpy(Comm1,"move ");   // msdos
		strcat(Comm1,Name); strcat(Comm1,NameT); system(Comm1); // Move Files
}
void CopyFile(int v, int e,char NameOut[30],char NameOutM[30]){// Copy Big and fractions files
	char Num[30],Comm[50], Name[30];
	if(OS==0)strcpy(Comm,"mv "); // linux
	else strcpy(Comm,"ren "); // msdos
	strcat(Comm,NameOut); strcat(Comm," "); strcat(Comm,NameOutM); system(Comm); 
	
	if(OS==0)strcpy(Comm,"mv "); // linux
	else strcpy(Comm,"move "); // msdos
	strcat(Comm,NameOutM); strcat(Comm," ");
    sprintf(Num,"%d",v);strcat(Comm,Num);strcat(Comm,"v"); 
    sprintf(Num,"%d",e);strcat(Comm,Num);strcat(Comm,"e"); system(Comm);
}
void MoveDirToDir(int v, int e){// Relocate diredctories
	char Num[30],Comm1[50],Name[30],NameT[30];
	strcpy(NameT," ");sprintf(Num,"%d",v);strcat(NameT,Num);strcat(NameT,"v"); strcpy(Name,NameT);
	sprintf(Num,"%d",e);strcat(Name,Num);strcat(Name,"e ");
	if(OS==0) strcpy(Comm1,"mv "); // linux
	else strcpy(Comm1,"move ");    // msdos
	 strcat(Comm1, Name); strcat(Comm1, NameT); system(Comm1); 
}

void GetA_M(int Binary[64][6],char Num[12],int G[MaxV][MaxV],int V){
  int nB=ceil(V*(V-1)/2.0/6),i,j=0,k;
  int Ones[6*nB];
  for(k=1;k<=nB;k++)  for(j=0;j<6;j++) Ones[6*(k-1)+j]=Binary[Num[k]-63][j];// For .g6 format
  k=0;
  for(j=1;j<V;j++){
    for(i=0;i<j;i++){
      G[i][j]=Ones[k];k++; 
      G[j][i]=G[i][j];
    }G[j-1][j-1]=0;
  }G[V-1][V-1]=0; //Last one element of diagonal
}

int ExistV_isolated(int G[MaxV][MaxV],int V){ // Is equivant to see that E<V-1
  int Sum,i,j;
  for(i=0;i<V ;i++){
    Sum=0; for(j=0;j<V;j++)Sum+=G[i][j]; if(Sum==0) return 1;
  }
  return 0;
}
int IsJreg(int j,int Mark[MaxV],int nM){
  int i;
  for(i=0;i<nM;i++) if(j==Mark[i]) return 1;
  return 0;
}
int IsConnected(int G[MaxV][MaxV],int V){
  int j,k,Sum,Mark[MaxV],nM,RespnM;
  //Search insolated vertex 
  if(ExistV_isolated(G,V)==1) return 0;
  
  // Put marks to Vertex 0 and their Neighbours
  Mark[0]=0;nM=1; for(j=1;j<V;j++) if(G[0][j]==1){ Mark[nM]=j;nM++;}  if(nM==V) return 1;
  
  // Mark any vertex no marked   neighbour of each marked vertex (except mark[0])
  for(k=1;k<nM;k++){
    // Search neighbours   j     of vertex=Mark[k]
    RespnM=nM;
    for(j=0;j<V;j++){
      if(G[Mark[k]][j]==1){ // find a neighbour j
        if(IsJreg(j,Mark,nM)==0){  // is not vertex j registred?
           Mark[nM]=j; nM++; 
           if(nM==V) return 1;
          }
        }
      }
    }
  if(RespnM==nM) return 0; // dont found more  new vertices to mark
  return 0;
}

void PrintGtoD(int k,int G[MaxV][MaxV],int V){
  int i,j;printf("%d\n    ",k);
  for(j=0;j<V;j++) printf("%2d ",j);printf("\n");
  for(i=0;i<V-1;i++){
    printf("%2d  ",i); for(j=0;j<=i;j++) printf("---"); for(j=i+1;j<V;j++) printf("%2d ",G[i][j]); printf("\n");
  } printf("\n");
}

int main(){
   int Binary[64][6],Qones[64];
   int i,j,k,V,E,Nones;
   long int countV[MaxV+1],countVE[MaxV+1][MaxV*(MaxV-1)/2 +1],Tg=0;
   char Num[12],NameIn[30],NameOut[30],NameOutM[30];           // 12 must change for V>11
   char Comm1[50],Comm2[50],Comm3[50];
   FILE *IF,*OF,*OFc,*OFcV;
   int NumFopen;
   int G[MaxV][MaxV];
   clock_t Begin = clock(),End;  double time_spent;
   int M;
   
   GetBin(Binary,Qones);
   
   GetNameOut(1,0,NameOut);OF=fopen(NameOut,"w");fclose(OF);// V=1
   //MakeDirV(1);MoveToDir(1);
   if(OS==0){
   	   system("mkdir 1v");system("mv 1v0e._g6 1v");
     }else{
   	   system("md 1v");system("move 1v0e._g6 1v");
   }
   
   OFc=fopen("#cgVE.dat","w"); 
   OFcV=fopen("#cgV.dat","w"); 
   for(V=1;V<=11;V++){
      for(E=V-1;E<=V*(V-1)/2;E++) countVE[V][E]=0;countV[V]=0; 
   }
   countVE[1][0]=1;countV[1]=1; // V=1
   
   for(V=2;V<=10;V++){
      printf("\nV=%d  E=",V);
      for(E=V-1;E<=V*(V-1)/2;E++){
	       printf("%d ",E);
	       GetNameIn(V,NameIn);IF=fopen(NameIn,"r");if(IF==NULL){
	              printf("\nProblems with input file %s",NameIn); getchar(); return 1;
	       }
	       GetNameOut(V,E,NameOut);OF=fopen(NameOut,"w");
	       k=0;fscanf(IF,"%c",&Num[k]);// To ignore
           do{
		        Nones=0; // Number of edges
		        do{
		            k++; fscanf(IF,"%c",&Num[k]);
		            if(Num[k]!='\n') Nones+=Qones[Num[k]-63];
		       }while(Num[k]!='\n');
		       if(Nones==E){
	                for(j=1;j<=k;j++) fprintf(OF,"%c",Num[j]); 
	                countVE[V][E]++;countV[V]++;
		       }
		      k=0;fscanf(IF,"%c",&Num[k]);// To ignore
            }while(!feof(IF) );
	        fclose(IF);fclose(OF);
      }
      MakeDirV(V);MoveToDir(V);
   }
   
    
// Special tratament for V=11
   
   printf("\nV=11   \n");
    V=11; 
    GetNameIn(V,NameIn);IF=fopen(NameIn,"r"); 
	if(IF==NULL){
		printf("\nProblems with %s file",NameIn); getchar();return 1;
	}
    for(E=V-1;E<=V*(V-1)/2;E++) {//Clean output files
        GetNameOut(V,E,NameOut);remove(NameOut);
    }
    GetNameOut(V,V-1,NameOut);OF=fopen(NameOut,"a");NumFopen=V-1; 
    k=0;fscanf(IF,"%c",&Num[k]);// To ignore
    do{
        Nones=0; // Number of edges
        do{
            k++; fscanf(IF,"%c",&Num[k]);
            if(Num[k]!='\n') Nones+=Qones[Num[k]-63];
        }while(Num[k]!='\n');
        E=Nones;
        if(V-1<=E && E<=V*(V-1)/2){
           GetA_M(Binary,Num,G,V);
           if(IsConnected(G,V)==1) {
                if(E!=NumFopen){
                  fclose(OF);
                  GetNameOut(V,E,NameOut);OF=fopen(NameOut,"a");NumFopen=E;
                }
                for(j=1;j<=k;j++) fprintf(OF,"%c",Num[j]); 
                countV[V]++;countVE[V][E]++;
                if(countVE[V][E]%1000000==0){// for "BIG" files
                      M=countVE[V][E]/1000000; GetNameOutM(V,E,M,NameOutM);
                      if(M==1){   // Make new directory
                          MakeDirVE(V,E);
                      }
                      fclose(OF);
                      CopyFile(V,E,NameOut,NameOutM);// Move file with million graphs to a directory
                      OF=fopen(NameOut,"a"); // To empty file
                }
          }
       }
       k=0;fscanf(IF,"%c",&Num[k]);// To ignore
       Tg++;
       if(Tg==100000) printf("\n    100000 graphs of  11v have been revised \n"); 
       if(Tg%1000000==0 && Tg>100000) {printf("%10ld ",Tg); Back();}
    }while(!feof(IF) );
    fclose(IF);fclose(OF); 
    
    MakeDirV(V);
    for (E=V-1;E<=V*(V-1)/2;E++){  	
	    if(countVE[V][E]>1000000){
	      GetNameOut(V,E,NameOut); M=countVE[V][E]/1000000+1; GetNameOutM(V,E,M,NameOutM);
	      CopyFile(V,E,NameOut,NameOutM);
	      MoveDirToDir(V,E);    //Move directory (with big files) to directory
	    }
    }
    MoveToDir(V); // Move small files
   
   for(V=1;V<=11;V++){// Save cardinalities
      fprintf(OFcV,"%d %ld\n",V,countV[V]);
      for(E=V-1;E<=V*(V-1)/2;E++) fprintf(OFc,"%d %d %ld\n",V,E,countVE[V][E]);
   }
   fclose(OFc);
   fclose(OFcV);
   

   if(OS==0){
   	      system("mkdir cg");
   	      system("mv 1v cg");
   	      system("mv 2v cg");
   	      system("mv 3v cg");
   	      system("mv 4v cg");
   	      system("mv 5v cg");
   	      system("mv 6v cg");
   	      system("mv 7v cg");
   	      system("mv 8v cg");
   	      system("mv 9v cg");
   	      system("mv 10v cg");
   	      system("mv 11v cg");
      }else{
      	  system("md cg"); 
   	   	  system("move 1v cg");
   	      system("move 2v cg");
   	      system("move 3v cg");
   	      system("move 4v cg");
   	      system("move 5v cg");
   	      system("move 6v cg");
   	      system("move 7v cg");
   	      system("move 8v cg");
   	      system("move 9v cg");
   	      system("move 10v cg");
   	      system("move 11v cg");
   }

   End=clock();time_spent = (double)(End - Begin) / CLOCKS_PER_SEC;
   printf("\nExecution time %lf\n", time_spent);
   printf("\n%0.0lf graphs processed per second",Tg/time_spent);getchar();
   
   return 0;
}


