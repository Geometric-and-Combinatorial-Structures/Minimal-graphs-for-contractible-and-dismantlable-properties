/*
    This program run under the connected graphs database, in format ._g6,
    searching the graphs that contradicts the Ivashchenko's axiom. 
    The output of this script are two graphs on 8 vertices (called g3 and g7)
    in the paper, and 133 graphs on 9 vertices. See Proposition 26 from the article.
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


#define MaxV 9

FILE *IF,*OF;

void GetNameIn(int v, int e, char NameIn[30]){
    char Num[30];
    strcpy(NameIn,"cg/");
    sprintf(Num,"%d",v); strcat(NameIn,Num); strcat(NameIn,"v/");
    sprintf(Num,"%d",v); strcat(NameIn,Num); strcat(NameIn,"v");
    sprintf(Num,"%d",e); strcat(NameIn,Num); strcat(NameIn,"e._g6");
    }

void GetBin(int Binary[64][6]){
    int i,j,k;
    for(i=0;i<64;i++){
        k=i; 
        for(j=5;j>=0;j--){
            Binary[i][j]=k%2;
            k/=2;
        }
    }
}

void PrintGtoD(int k, int G[MaxV][MaxV], int V){
    int i,j;
    printf("\n%d\n",k);
    for(i=0;i<V;i++){
        for(j=0;j<V;j++){
            printf("%2d ",G[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void PrintGtoF(int k, int G[MaxV][MaxV], int V){
    int i,j;
    fprintf(OF,"\n%d\n",k);
    for(i=0;i<V;i++){
        for(j=0;j<V;j++){
            fprintf(OF,"%2d ",G[i][j]);
        }
        fprintf(OF,"\n");
    }
    fprintf(OF,"\n");
}

// Compute the open neighborhood of a vertex
void CalLk(int A[MaxV][MaxV], int n, int k, int Lk[MaxV][MaxV], int *m){
    int i,j;
    int Isobre[MaxV];
    *m=0;
    for(j=0;j<n;j++){
        if(A[k][j]==1){
            Isobre[*m]=j; //Survivor vertex
            (*m)++;
        }
    }
    for(i=0;i<*m;i++){
        for(j=0;j<*m;j++){
            Lk[i][j]=A[Isobre[i]][Isobre[j]];
        }
    }
}

//Delete a vertex from a graph
void DeleteVert(int A[MaxV][MaxV], int n, int k, int B[MaxV][MaxV], int *m){
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

int BtoSICv(int G[MaxV][MaxV], int n){
    int i,j,m;
    int Lk[MaxV][MaxV],GmV[MaxV][MaxV];
    if(n==0 || n==1) return n;
    else{
        //Try to delete any vertex
        for(i=0;i<n;i++){
            //Compute the neighborhood of v_i
            CalLk(G,n,i,Lk,&m);
            if(BtoSICv(Lk,m)==1){
                DeleteVert(G,n,i,GmV,&m);
                return BtoSICv(GmV,m);
            }
        }
        return 0;
    }
}

//Compute the open neighborhood of an edge:
void CalLk( int A[MaxV][MaxV], int n, int k1, int k2, int Lk[MaxV][MaxV], int *m){
    int i,j;
    int Isobre[MaxV];
    *m=0;
    for(j=0;j<n;j++){
        if(A[k1][j]*A[k2][j]==1) {
            Isobre[*m]=j; //Survivor vertex
            (*m)++;
        }
    }
    for(i=0;i<*m;i++){
        for(j=0;j<*m;j++){
            Lk[i][j]=A[Isobre[i]][Isobre[j]];
        }
    }
}

//Delete an edge from a graph
void DeleteEdge(int A[MaxV][MaxV], int n, int k1, int k2, int B[MaxV][MaxV]){
    int i,j;
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            B[i][j]=A[i][j];
        }
    }
    B[k1][k2]=0;B[k2][k1]=0;
}

int BtoSIC(int G[MaxV][MaxV], int n){ // Check if a graph belongs to the Strong I-Contractible family.
    int i,j,m,CanDE;
    int Lk[MaxV][MaxV],GmV[MaxV][MaxV],GmE[MaxV][MaxV];
    if(n==0 || n==1) return n;
    else{
        //Try to delete any vertex
        for(i=0;i<n;i++){
            //Compute the neighborhood of v_i
            CalLk(G,n,i,Lk,&m);
            if(BtoSIC(Lk,m)==1){
                DeleteVert(G,n,i,GmV,&m);
                return BtoSIC(GmV,m);
            }
        }
        //Try to delete an edge:
        for(i=0;i<n-1; i++){
            for(j=i+1; j<n; j++){
                if(G[i][j]==1){
                    CalLk(G,n,i,j,Lk,&m); //Compute the join neighborhood of v_i and v_j:
                    if(BtoSIC(Lk,m)==1){
                        DeleteEdge(G,n,i,j,GmE);
                        return BtoSIC(GmE,n);
                    }
                }
            }
        }
        return 0;
    }
}

int CanAddE(int G[MaxV][MaxV], int V, int i, int j){
    int m;
    int Lk[MaxV][MaxV];
    CalLk(G,V,i,j,Lk,&m); //Compute the join neighborhood of v_i and v_j
    if(BtoSIC(Lk,m)==1){
        return 1;
    }else return 0;
}

int Vaxm(int G[MaxV][MaxV], int V){
    int VA;
    int VNC[MaxV],nVNC; // Non universal vertex
    int grado,i,j,k;
    
    //Detect non-universal vertices
    nVNC=0;
    for(i=0;i<V;i++){
        grado=0;
        for(j=0;j<V;j++) if(G[i][j]==1) grado++;
        if(grado<V-1){ // Is not universal
            VNC[nVNC]=i;
            nVNC++;
        }
    }
    VA=0;
    for(i=0;i<nVNC && VA==0;i++){
        int CanAddany=0;
        for(j=0;j<i;j++){
            if(G[VNC[i]][VNC[j]]==0){ // Is not connected
                if(CanAddE(G,V,VNC[i],VNC[j])==1) CanAddany=1;
            }
        }
        for(j=i+1;j<nVNC;j++){
            if(G[VNC[i]][VNC[j]]==0){ // Is not connected
                if(CanAddE(G,V,VNC[i],VNC[j])==1) CanAddany=1;
            }
        }
        if(CanAddany==0) {
            VA=1;
            fprintf(OF,"The vertex V=%d contradicts the Ivashchenko's axiom. #V = %d, ",VNC[i]+1,V);
        }
    }
    return VA;
}

int main(){
    char NameIn[30],Num[12];
    FILE *IF_c;
    int g,i,j,k,V,E,v,e,ng=0;
    int Binary[64][6];
    long int Card;
    int G[MaxV][MaxV];
    
    GetBin(Binary);
    IF_c=fopen("#cgVE.dat","r");
    if(IF_c==NULL){
        printf("File #cgVE.dat is missing, please check.\nPress enter to exit.\n");
        getchar();
        return 1;
    }
    OF=fopen("CheckAxiom.dat","w");
    
    for(V=1;V<=9;V++){
        if(V == 9){
            printf("\ng3 and g7 graphs from Proposition 26, on 8 vertices.\nPress enter to obtain the other 133 graphs on 9 vertices pointed out in the proposition.\nThe output will be saved in the file CheckAxiom.dat.\n");
            getchar();
        }
        for(E=V-1;E<=V*(V-1)/2;E++){
            fscanf(IF_c,"%d %d %ld",&v,&e,&Card);
            GetNameIn(V,E,NameIn);
            IF=fopen(NameIn,"r");
            if(IF==NULL){
                printf("\nProblems with input file %s.\nPress enter to exit.\n",NameIn); 
                getchar();
                return 1;
            }
            for(g=1;g<=Card;g++){
                int nB=ceil(V*(V-1)/2.0/6);
                int OnesZ[6*nB];
                for(k=0;k<nB;k++){
                    fscanf(IF,"%c",&Num[k]);
                    for(j=0;j<6;j++) {
                        OnesZ[6*k+j]=Binary[Num[k]-63][j];
                    }
                }
                fscanf(IF,"%c",&Num[k]);
                k=0;// Put 0-1 in their places of G
                for(j=1;j<V;j++){
                    for(i=0;i<j;i++){
                        G[i][j]=OnesZ[k]; G[j][i]=G[i][j];
                        k++;
                    }
                    G[j-1][j-1]=0;
                }
                G[V-1][V-1]=0; 
                if(BtoSIC(G,V)==1){
                    if(Vaxm(G,V)==1) {
                        ng++;
                        printf("#E = %d.",E);
                        fprintf(OF,"#E = %d.",E);
                        PrintGtoD(ng,G,V);
                        PrintGtoF(ng,G,V);
                    }
                }
            }
        }
        fclose(IF);
    }
    fclose(OF);
    fclose(IF_c);
    return 0;
}
