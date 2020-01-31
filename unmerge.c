#include<stdio.h> 
#include <stdlib.h>
#define MAXCHAR 1000

void loadFiles2(FILE *f1, int numReads, bool change, char* newName)
{
    FILE *forward = fopen("forward.fq", "w"); // write only 
    FILE *reverse = fopen("reverse.fq", "w"); // write only 
    FILE  *files[2]={forward, reverse};
    FILE  *output=files[0];
    char str1[MAXCHAR];
    int i=0, j=0;
    //printf("Reading files\n");
     while (fgets(str1, MAXCHAR, f1) != NULL)
    {   
        //printf("%d%c%d%c",i,'@',j,'\n');
        if(i==0)
        {
            fprintf(output,"%s%d%c",newName,j/2,'\n');
        }
        else
            fprintf(output,"%s",str1);

        i++;
        if((i%4)==0)
        {
            j++;
            i=0;
            output=files[j%2];
        }
        
        if(j==(2*numReads))//because each read contains forward and reverse
            break;
    }
        
    fclose(f1); 
    fclose(forward);
    fclose(reverse); 
}


void loadFiles(FILE *f1, bool change, char* newName)
{
    FILE *forward = fopen("forward.fq", "w"); // write only 
    FILE *reverse = fopen("reverse.fq", "w"); // write only 
    FILE  *files[2]={forward, reverse};
    FILE  *output=files[0];
    char str1[MAXCHAR];
    int i=0, j=0;
    //printf("Reading files\n");
    while (fgets(str1, MAXCHAR, f1) != NULL)
    {   
        //printf("%d%c%d%c",i,'@',j,'\n');
        if(i==0)
        {
            fprintf(output,"%s%d%c",newName,j/2,'\n');
        }
        else
            fprintf(output,"%s",str1);

        i++;
        if((i%4)==0)
        {
            j++;
            i=0;
            output=files[j%2];
        }
    }
        
    fclose(f1); 
    fclose(forward);
    fclose(reverse); 
}

int main(int argc,char* argv[]) 
{ 
    int counter; 
    int numReads=0;
    bool change=false;
    char* newName;
    
    if( argc > 5 || argc <3) 
    {
        printf("Use: umerge file header [numReads: optional to extract n reads]\n");
        printf("file: fastq file <mandatory>\n");
        printf("header: read name <mandatory>\n");
        printf("numReads: extract only n reads <optional>\n");
        exit(1);
    }
    
    
    FILE *f1 = fopen(argv[1],"r"); 
    change=true;     
    newName=argv[2];
    
    if(f1 == NULL)
        printf("File doesn´t exits\n"),  exit(1);
    
    if (argc==4)
        loadFiles2(f1, atoi(argv[3]),change, newName);
    else
        loadFiles(f1,change, newName);
    
    return 0; 
}
