#include<stdio.h>
#include<string.h>
#include<stdlib.h>
struct
{
    int spos;   //for denoting position and variable of passed variable
    char a;
}s[10];
void main()
{
    FILE *f1,*f2,*f3,*f4,*f5;
    int spos[20],x,n1=0,pos=1,index=1,sindex=1,st=0;
    for(x=0;x<20;x++) spos[x]=0;
    char mne[20],opnd[20],la[20],name[20],opnd1[20],la1[20],new2[20][20],store[20][20];;
    f1=fopen("input.txt","r");          //input file is opened
    f2=fopen("namtab.txt","w+");
    f3=fopen("deftab.txt","w+");
    f4=fopen("argtab.txt","w+");
    f5=fopen("output.txt","w+");
    fscanf(f1,"%s%s%s",la,mne,opnd);
    fprintf(f5,"%s\t%s\t%s",la,mne,opnd);
    while(strcmp(mne,"END")!=0)             //check until macro ends
    {
        if(strcmp(mne,"MACRO")==0)
        {   sindex=index;
            int i=1;
            index++;
            strcpy(la1,la);
            fprintf(f3,"%s\t%s\t%s\n",la,mne,opnd);
            for(x=0;x<strlen(opnd);x++)     
            {
                if(opnd[x]=='&')
                {
                s[i].a=opnd[x+1];   //spliting input into char array
                s[i].spos=i;        //finding positions of all variables used in macro defenition
                i++;
                }
            }
            fscanf(f1,"%s%s%s",la,mne,opnd);
            while(strcmp(mne,"MEND")!=0)    
            { index++;
                n1++;
                if(opnd[0]=='&')
                {
                    for(x=1;x<=i;x++)
                    {
                        if(opnd[1]==s[x].a)
                        {
                        fprintf(f3,"%s\t%s\t?%d\n",la,mne,s[x].spos);
                        }
                    }
                }
                strcpy(store[st],mne); st++;
                fscanf(f1,"%s%s%s",la,mne,opnd);
            }
            fprintf(f3,"%s\t%s\t%s\n",la,mne,opnd);
            fprintf(f2,"%s\t%d\t%d\n",la1,sindex,index);
            fscanf(f1,"%s%s%s",la,mne,opnd);
            while(strcmp(mne,la1)!=0)
            {
            	fprintf(f5,"\n%s\t%s\t%s",la,mne,opnd);
            	fscanf(f1,"%s%s%s",la,mne,opnd);
            }
        }
        if(strcmp(mne,la1)==0)      //la1 is name of macro 
        {
            int x,x1=0,x2=0;
            char new1[20][20];
            for(x=0;x<strlen(opnd);x++)
            {
                if(opnd[x]!=',')
                {
                new1[x1][x2]=opnd[x];x2++;
                }
                else
                {
                x2=0; x1++;
                }
            }
            for(x=0;x<=x1;x++)
            fprintf(f4,"%d\t%s\n",x+1,new1[x]);
            for(x=0;x<st;x++)
                fprintf(f5,"\n-\t%s\t%s",store[x],new1[x]);
        }
        if(strcmp(mne,"WORD")==0||strcmp(mne,"BYTE")==0||strcmp(mne,"RESB")==0||strcmp(mne,"RESW")==0)  //printing the declarations to uutput file
        {
            fprintf(f5,"\n%s\t%s\t%s",la,mne,opnd);
        }
        fscanf(f1,"%s%s%s",la,mne,opnd);
    }
}