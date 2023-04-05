/*
  This program run over the connected graphs, in format ._g6. 
  Then, the output is the family of Strong I-Contractible graphs
  and are saved in the directory ./sic.

  Use as:
  ./sic             : V and E will be requested after
  ./sic V           : graphs with V vertices and E=V-1,V,V+1,..., V(V-1)/2 will be processeed
  ./sic V E         : graphs with V vertices and E edges will be processeed
  ./sic V E n1      : graphs with V vertices, E edges and n1-th million will be processeed (by big files)
  ./sic V E n1 n2   : graphs with V vertices, E edges and n1_th to n1_th (millions will be processeed)
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctime>
#include<math.h>

#define MaxV 11

FILE *IF,*OF;

void MakeDirS(void){
    FILE *F;
    int flag;
    F=fopen("FlagSic.dat","r");
    if(F==NULL){
        printf("File FlagSic.dat not found. Press enter to continue.\n");
        getchar();
    }
    fscanf(F,"%d",&flag); fclose(F);
    if(flag==0){
        system("mkdir sic");
        system("mkdir 1v");
        system("mkdir 2v");
        system("mkdir 3v");
        system("mkdir 4v");
        system("mkdir 5v");
        system("mkdir 6v");
        system("mkdir 7v");
        system("mkdir 8v");
        system("mkdir 9v");
        system("mkdir 10v");
        system("mkdir 11v");
        system("mkdir 11v17e");
        system("mkdir 11v18e");
        system("mkdir 11v19e");
        system("mkdir 11v20e");
        system("mkdir 11v21e");
        system("mkdir 11v22e");
        system("mkdir 11v23e");
        system("mkdir 11v24e");
        system("mkdir 11v25e");
        system("mkdir 11v26e");
        system("mkdir 11v27e");
        system("mkdir 11v28e");
        system("mkdir 11v29e");
        system("mkdir 11v30e");
        system("mkdir 11v31e");
        system("mkdir 11v32e");
        system("mkdir 11v33e");
        system("mkdir 11v34e");
        system("mkdir 11v35e");
        system("mkdir 11v36e");
        system("mkdir 11v37e");
        system("mkdir 11v38e");
        system("mkdir 11v39e");
        system("mv 11v17e 11v");
        system("mv 11v18e 11v");
        system("mv 11v19e 11v");
        system("mv 11v20e 11v");
        system("mv 11v21e 11v");
        system("mv 11v22e 11v");
        system("mv 11v23e 11v");
        system("mv 11v24e 11v");
        system("mv 11v25e 11v");
        system("mv 11v26e 11v");
        system("mv 11v27e 11v");
        system("mv 11v28e 11v");
        system("mv 11v29e 11v");
        system("mv 11v30e 11v");
        system("mv 11v31e 11v");
        system("mv 11v32e 11v");
        system("mv 11v33e 11v");
        system("mv 11v34e 11v");
        system("mv 11v35e 11v");
        system("mv 11v36e 11v");
        system("mv 11v37e 11v");
        system("mv 11v38e 11v");
        system("mv 11v39e 11v");
        system("mv 1v sic");
        system("mv 2v sic");
        system("mv 3v sic");
        system("mv 4v sic");
        system("mv 5v sic");
        system("mv 6v sic");
        system("mv 7v sic");
        system("mv 8v sic");
        system("mv 9v sic");
        system("mv 10v sic");
        system("mv 11v sic");
        flag=1;
        F=fopen("FlagSic.dat","w");
        fprintf(F,"%d",flag);
        fclose(F);
    }
}

void GetNameIn(int v, int e, char NameIn[30]){
    char Num[30];
    strcpy(NameIn,"cg/");
    sprintf(Num,"%d",v); strcat(NameIn,Num); strcat(NameIn,"v/");
    sprintf(Num,"%d",v); strcat(NameIn,Num); strcat(NameIn,"v");
    sprintf(Num,"%d",e); strcat(NameIn,Num); strcat(NameIn,"e._g6");
}

void GetNameIn(int v, int e, int M, char NameInM[30]){
    char Num[30];
    strcpy(NameInM, "cg/");
    sprintf(Num,"%d",v); strcat(NameInM,Num); strcat(NameInM,"v/");
    sprintf(Num,"%d",v); strcat(NameInM,Num); strcat(NameInM,"v");
    sprintf(Num,"%d",e); strcat(NameInM,Num); strcat(NameInM,"e/");
    sprintf(Num,"%d",v); strcat(NameInM,Num); strcat(NameInM,"v");
    sprintf(Num,"%d",e); strcat(NameInM,Num); strcat(NameInM,"e");
    if(M<10) strcat(NameInM,"-00");
    if(M>=10 && M<100) strcat(NameInM,"-0");
    if(M>=100) strcat(NameInM,"-");
    sprintf(Num,"%d",M); strcat(NameInM,Num); strcat(NameInM,"._g6");
}

void GetNameOut(int v, int e, char NameOut[30]){
    char Num[30];
    strcpy(NameOut,"sic/");
    sprintf(Num,"%d",v); strcat(NameOut,Num); strcat(NameOut,"v/");
    sprintf(Num,"%d",v); strcat(NameOut,Num); strcat(NameOut,"v");
    sprintf(Num,"%d",e); strcat(NameOut,Num); strcat(NameOut,"e._g6");
}

void GetNameOut(int v, int e, int M, char NameOutM[30]){
    char Num[30];
    strcpy(NameOutM,"sic/");
    sprintf(Num,"%d",v); strcat(NameOutM,Num); strcat(NameOutM,"v/");
    sprintf(Num,"%d",v); strcat(NameOutM,Num); strcat(NameOutM,"v");
    sprintf(Num,"%d",e); strcat(NameOutM,Num); strcat(NameOutM,"e/");
    sprintf(Num,"%d",v); strcat(NameOutM,Num); strcat(NameOutM,"v");
    sprintf(Num,"%d",e); strcat(NameOutM,Num); strcat(NameOutM,"e");
    if(M<10) strcat(NameOutM,"-00");
    if(M>=10 && M<100) strcat(NameOutM,"-0");
    if(M>=100) strcat(NameOutM,"-");
    sprintf(Num,"%d",M); strcat(NameOutM,Num); strcat(NameOutM,"._g6");
}

void GetNameOut_C(int v, int e, int M, char NameOutM[30]){
    char Num[30];
    strcpy(NameOutM,"sic/");
    sprintf(Num,"%d",v); strcat(NameOutM,Num); strcat(NameOutM,"v/");
    sprintf(Num,"%d",v); strcat(NameOutM,Num); strcat(NameOutM,"v");
    sprintf(Num,"%d",e); strcat(NameOutM,Num); strcat(NameOutM,"e/#");
    sprintf(Num,"%d",v); strcat(NameOutM,Num); strcat(NameOutM,"v");
    sprintf(Num,"%d",e); strcat(NameOutM,Num); strcat(NameOutM,"e");
    if(M<10) strcat(NameOutM,"-00");
    if(M>=10 && M<100) strcat(NameOutM,"-0");
    if(M>=100) strcat(NameOutM,"-");
    sprintf(Num,"%d",M); strcat(NameOutM,Num); strcat(NameOutM,".dat");
}

void GetNameOut_C(int v, int e, char NameOutM[30]){
    char Num[30];
    strcpy(NameOutM,"sic/");
    sprintf(Num,"%d",v); strcat(NameOutM,Num); strcat(NameOutM,"v/#");
    sprintf(Num,"%d",v); strcat(NameOutM,Num); strcat(NameOutM,"v");
    sprintf(Num,"%d",e); strcat(NameOutM,Num); strcat(NameOutM,"e.dat");
}

void GetBin(int Binary[64][6]){
    int i,j,k;
    for(i=0;i<64;i++){
        k=i; for(j=5;j>=0;j--){ Binary[i][j]=k%2; k/=2;}
    }
}

void Back(void){
    int i; for(i=1;i<=11;i++) printf("%c",8);// Move 10 places left
}

// Compute the open neighborhood of a vertex
void CalLk(int A[MaxV][MaxV],  int n, int k, int Lk[MaxV][MaxV], int *m){
    int i,j;
    int Isobre[MaxV];
    *m=0;
    for(j=0;j<n;j++)
        if(A[k][j]==1) {
            Isobre[*m]=j; //Survivor vertex
            (*m)++;
        }
        for(i=0;i<*m;i++) for(j=0;j<*m;j++) Lk[i][j]=A[Isobre[i]][Isobre[j]];
}

//Delete a vertex from the graph
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

//Compute the open join neighborhood of an edge
void CalLk(int A[MaxV][MaxV], int n, int k1, int k2, int Lk[MaxV][MaxV], int *m){
    int i,j;
    int Isobre[MaxV];
    *m=0;
    for(j=0;j<n;j++){
        if(A[k1][j]*A[k2][j]==1) {
            Isobre[*m]=j; //Survivor vertex
            (*m)++;
        }
    }
    for(i=0;i<*m;i++) for(j=0;j<*m;j++) Lk[i][j]=A[Isobre[i]][Isobre[j]];
}

//Delete an edge from a graph
void DeleteEdge(int A[MaxV][MaxV], int n, int k1, int k2, int B[MaxV][MaxV]){
    int i,j;
    for(i=0;i<n;i++){
        for(j=0;j<n;j++) B[i][j]=A[i][j];
    }
    B[k1][k2]=0;B[k2][k1]=0;
}

int BtoSIC( int G[MaxV][MaxV], int n){ // Check if a graph belongs to the Strong I-Contractible family
    int i,j,m,CanDE;
    int Lk[MaxV][MaxV],GmV[MaxV][MaxV],GmE[MaxV][MaxV];
    if(n==0 || n==1) return n;
    else{
        //Try to delete any vertex
        for(i=0;i<n;i++){
            //Compujte the neighborhood of the vertex v_i
            CalLk(G,n,i,Lk,&m);
            if(BtoSIC(Lk,m)==1){
                DeleteVert(G,n,i,GmV,&m);
                return BtoSIC(GmV,m);
            }
        }
        //Try to delete edges
        for(i=0;i<n-1 ;i++){
            for(j=i+1;j<n  ;j++){
                if(G[i][j]==1){
                    CalLk(G,n,i,j,Lk,&m); //Compute the join neighborhood of v_i and v_j
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

int main(int argc, char* argv[]) {
    char *n;
    int numVertices,V;
    int numEdges,E,kk;
    char Name_F_G_in[30],Name_F_G_out[30],Name_F_G_in_c[30],Name_F_G_out_c[30],Num[12];
    FILE *IF_c,*OF_c;
    int i,j,rv,re,n1,n2;
    long int Card,ii,ngSIC=0;
    int G[MaxV][MaxV],ene,ng;
    clock_t Begin = clock(),End;
    double time_spent;
    long int Quant;
    char NameDir[30],NameDir2[30],Comm[30];
    int Binary[64][6];
    
    // Make directories structure
    MakeDirS();
    GetBin(Binary);
    
    if(argc==1){// User will enter V and E  after run
        printf("\nNumber of vertices, from V=1 to V=11. V = "); scanf("%d",&V);
        printf("\nNumber of edges, from E=%d to E=%d. E = ",V-1,V*(V-1)/2); scanf("%d",&E);
    }
    if(argc==2){// User will enter V from command line and E=V-1,V,V+1,V+1,...,V(V-1)/2
        V=atoi(*(argv+1));
    }
    if(argc==3){// User will enter V and E from command line
        V=atoi(*(argv+1));
        E=atoi(*(argv+2));
    }
    if(argc==4){// User will enter V and E from command line
        V=atoi(*(argv+1));
        E=atoi(*(argv+2));
        n1=atoi(*(argv+3));
    }
    if(argc==5){// User will enter V and E from command line
        V=atoi(*(argv+1));
        E=atoi(*(argv+2));
        n1=atoi(*(argv+3));
        n2=atoi(*(argv+4));
    }
    
    if(argc==1 || argc==3){
        if(V<11 || (V==11)&&(E<=16 || E>=40)){
            Quant=0;
            printf("\nV=%d, E=%d\n",V,E);
            numVertices=V;
            numEdges=E;
            // Search cardinality of the family of connected graphs
            IF_c=fopen("#cgVE.dat","r");
            if(IF_c==NULL){
                printf("\nFile #cgVE.dat not found. Please check.\nPress enter to continue.\n");getchar();return 1;
            }
            i=0;
            do{
                fscanf(IF_c,"%d %d %ld",&rv,&re,&Card); i++;
            }while((rv!=V || re!=E) && i<1000);
            if(i>=1000){ printf("\nIssues found with V-E pair.\nPress enter to continue.\n");getchar(); return 1;}
            printf("\n%ld graphs to check.\n",Card);
            GetNameIn(V,E,Name_F_G_in); IF=fopen(Name_F_G_in,"r");
            GetNameOut(V,E,Name_F_G_out); OF=fopen(Name_F_G_out,"w");
            if(IF==NULL) {
                printf("\nProblems with input file %s.\nPress enter to continue.\n",Name_F_G_in); getchar();return 1;
            }
            for(ii=1;ii<=Card;ii++){
                int nB=ceil(V*(V-1)/2.0/6),i,j,k;
                int OnesZ[6*nB];
                for(k=0;k<nB;k++){
                    fscanf(IF,"%c",&Num[k]);
                    for(j=0;j<6;j++) {
                        OnesZ[6*k+j]=Binary[Num[k]-63][j];
                    }
                }fscanf(IF,"%c",&Num[k]);
                kk=0;// Put 0-1 in their places of G
                for(j=1;j<V;j++){
                    for(i=0;i<j;i++){
                        G[i][j]=OnesZ[kk]; G[j][i]=G[i][j];
                        kk++;
                    }
                    G[j-1][j-1]=0;
                }
                G[V-1][V-1]=0; // PrintGtoD(ii,G,V);getchar();
                if(BtoSIC(G,V)==1){
                    ngSIC++;
                    for(k=0;k<=nB;k++) fprintf(OF,"%c",Num[k]);  // Write to file
                }
                if(ii==10000) printf("\n10,000 graphs of [%d,%d]  have been revised.\n",V,E);
                if(ii%10000==0 && ii>10000) printf("%ld ",ii);  Back();
                Quant++;
            }
            fclose(IF);
            fclose(OF);
            GetNameOut_C(V,E,Name_F_G_out_c); OF_c=fopen(Name_F_G_out_c,"w");
            if(OF_c==NULL){
                printf("\nProblems with file counter %s.\n",Name_F_G_out_c);
            }
            fprintf(OF_c,"%ld",ngSIC);
            printf("\n%ld graphs with V=%d and E=%d are in SIC family.",ngSIC,V,E);
            fclose(OF_c);
        }else{
            printf("\nInstead of use ./Sic 11");
            printf("\nuse ./Sic 11 E");
            printf("\nwith E=1,2,...,16 and");
            printf("\nwith E=40,41,...,55.");
            printf("\nFor E=17,18,..39");
            printf("\nuse ./Sic 11 E M");
            printf("\nwhere M indicate what M-th million corrresponds (see #sicVE.dat file).");
            printf("\nPress enter to exit.\n");
            getchar();
            return 0;
        }
    }
    
    if(argc==2){
        if(V<11){
            Quant=0;
            for(E=V-1;E<=V*(V-1)/2;E++){
                ngSIC=0;
                printf("\nV=%d, E=%d\n",V,E);
                numVertices=V;
                numEdges=E;
                double * graph = new double[(int)V*(V-1)/2];
                // Search cardinality of the connected graphs family.
                IF_c=fopen("#cgVE.dat","r");
                if(IF_c==NULL){
                    printf("File cardVE.dat not found.\nPress enter to continue.\n");
                    getchar();
                    return 1;
                }
                i=0;
                do{
                    fscanf(IF_c,"%d %d %ld",&rv,&re,&Card); i++;
                }while((rv!=V || re!=E) && i<1000);
                if(i>=1000){
                    printf("\nIssues found with V-E pair.\n Press enter to continue.\n");
                    getchar();
                    return 1;
                }
                printf("\n%ld graphs to check.\n",Card);
                GetNameIn(V,E,Name_F_G_in);
                IF=fopen(Name_F_G_in,"r");
                GetNameOut(V,E,Name_F_G_out);
                OF=fopen(Name_F_G_out,"w");
                if(IF==NULL) {
                    printf("\nProblems with input file %s.\nPress enter to continue.\n",Name_F_G_in);
                    getchar();
                    return 1;
                }
                for(ii=1;ii<=Card;ii++){
                    int nB=ceil(V*(V-1)/2.0/6),i,j,k;
                    int OnesZ[6*nB];
                    for(k=0;k<nB;k++){
                        fscanf(IF,"%c",&Num[k]);
                        for(j=0;j<6;j++) {
                            OnesZ[6*k+j]=Binary[Num[k]-63][j];
                        }
                    }fscanf(IF,"%c",&Num[k]);
                    kk=0;// Put 0-1 in their places of G
                    for(j=1;j<V;j++){
                        for(i=0;i<j;i++){
                            G[i][j]=OnesZ[kk]; G[j][i]=G[i][j];
                            kk++;
                        }
                        G[j-1][j-1]=0;
                    }
                    G[V-1][V-1]=0;
                    if(BtoSIC(G,V)==1){
                        ngSIC++;
                        for(k=0;k<=nB;k++){
                            fprintf(OF,"%c",Num[k]);  // Write to file
                        }
                    }
                    if(ii==100000) printf("\n100,000 graphs of [%d,%d]  have been revised.\n",V,E);
                    if(ii%100000==0 && ii>100000) printf("%ld ",ii);
                    Back();
                    Quant++;
                }
                fclose(IF);
                fclose(OF);
                GetNameOut_C(V,E,Name_F_G_out_c);
                OF_c=fopen(Name_F_G_out_c,"w");
                if(OF_c==NULL){
                    printf("\nProblems with file counter %s.\n",Name_F_G_out_c);
                }
                fprintf(OF_c,"%ld",ngSIC);
                printf("\n%ld graphs with V=%d and E=%d are in SIC family.\n",ngSIC,V,E);
                fclose(OF_c);
            }
        }else{
            printf("\nInstead of use ./Sic 11");
            printf("\nuse ./Sic 11 E");
            printf("\nwith E=1,2,...,16 and");
            printf("\nwith E=40,41,...,55");
            printf("\nFor E=17,18,..39");
            printf("\nuse ./Sic 11  E  M");
            printf("\nwhere M indicate the M-th million (see #sicVE.dat file)");
            printf("\nPress enter to exit.\n");
            getchar();
            return 0;
        }
    }
    
    if(argc==4 || argc==5){
        if( V==11 && E>=17 && E<=39){
            Quant=0;
            if(argc==4) printf("\n\nV=%d E=%d, %d-th million\n",V,E,n1);
            if(argc==5) printf("\n\nV=%d E=%d, %d-th to %d-th millions\n",V,E,n1,n2);
            if(argc==4) n2=n1;
            numVertices=V;
            numEdges=E;
            // Search cardinality of the family of connected graphs.
            IF_c=fopen("#cgVE.dat","r");
            if(IF_c==NULL){
                printf("File #cgVE.dat not found.\nPress enter to continue.\n");
                getchar();
                return 1;
            }
            i=0;
            do{
                fscanf(IF_c,"%d %d %ld",&rv,&re,&Card); i++;
            }while((rv!=V || re!=E) && i<1000);
            if(i>=1000){
                printf("\nIssues found with V-E pair.\nPress enter to continue.\n");
                getchar();
                return 1;
            }
            for(ene=n1;ene<=n2;ene++){
                ngSIC=0;
                if(ene < ceil(Card/1000000.0)){
                    printf("\n%d graphs to check\n",ng=1000000);
                }else{
                    printf("\n%d graphs to check\n",ng=Card%1000000);
                }
                GetNameIn(V,E,ene,Name_F_G_in); IF=fopen(Name_F_G_in,"r");
                GetNameOut(V,E,ene,Name_F_G_out); OF=fopen(Name_F_G_out,"w");
                if(IF==NULL) {
                    printf("\nProblems with input file %s.\nPress enter to continue.\n",Name_F_G_in);
                    getchar();
                    return 1;
                }
                for(ii=1;ii<=ng;ii++){
                    int nB=ceil(V*(V-1)/2.0/6),i,j,k;
                    int OnesZ[6*nB];
                    for(k=0;k<nB;k++){
                        fscanf(IF,"%c",&Num[k]);
                        for(j=0;j<6;j++) {
                            OnesZ[6*k+j]=Binary[Num[k]-63][j];
                        }
                    }fscanf(IF,"%c",&Num[k]);
                    kk=0;// Put 0-1 in their places of G
                    for(j=1;j<V;j++){
                        for(i=0;i<j;i++){
                            G[i][j]=OnesZ[kk]; G[j][i]=G[i][j];
                            kk++;
                        }
                        G[j-1][j-1]=0;
                    }
                    G[V-1][V-1]=0;
                    if(BtoSIC(G,V)==1){
                        ngSIC++;
                        for(k=0;k<=nB;k++) fprintf(OF,"%c",Num[k]);  // Write to file
                    }
                    if(ii==1000) printf("\n1,000 graphs of [%d,%d] have been revised.\n",V,E);
                    if(ii%1000==0 && ii>1000) printf("%ld ",ii);  Back();
                    Quant++;
                }
                fclose(IF);
                fclose(OF);
                GetNameOut_C(V,E,ene,Name_F_G_out_c);
                OF_c=fopen(Name_F_G_out_c,"w");
                fprintf(OF_c,"%ld",ngSIC);
                printf("\n%ld graphs with V=%d, E=%d, of %d-th million are in SIC family.\n",ngSIC,V,E,ene);
                fclose(OF_c);
            }
        }else{
            printf("\nThis opcion is only for V=11 and E=17,18,..., 39.\n");
            printf("\nPress enter to exit.\n");
            getchar();
            return 1;
        }
    }
    if(V>=8){
        End=clock();
        time_spent = (double)(End - Begin) / CLOCKS_PER_SEC;
        printf("\nExecution time: %lf seconds.", time_spent);
        printf("\n%0.0lf graphs processed per second.\nPress enter to exit.\n",Quant/time_spent);
    }
    return 0;
}
