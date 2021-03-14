#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void remove_star(char * line, char outline[])
{
    char * chr;
    char * id;
    char * pos;
    char * ref;
    char * alt;
    char * h1;
    char * h2;
    chr = strtok(line, " ");
    strcat(outline, chr);
    id = strtok(NULL, " ");
    strcat(outline, "\t");
    strcat(outline, id);
    pos = strtok(NULL, " ");
    strcat(outline, "\t");
    strcat(outline, pos);
    ref = strtok(NULL, " ");
    strcat(outline, "\t");
    strcat(outline, ref);
    alt = strtok(NULL, " ");
    strcat(outline, "\t");
    strcat(outline, alt);
    h1 = strtok(NULL, " ");
    while(h1!=NULL)
    {
        h2 = strtok(NULL, " ");
        if(strcmp(h1,h2)==0 & strlen(h1)>1)
        {
            strcat(outline,"\t");
            strncat(outline,h1,1);
            strcat(outline,"\t");
            strncat(outline,h2,1);
        }
        // change *0 *1 to ? ?
        else if (strcmp(h1,h2)!=0 & strlen(h1) > 1)
        {
            strcat(outline,"\t");
            strcat(outline,"?");
            strcat(outline,"\t");
            strcat(outline,"?");
        } 
        else
        {
            strcat(outline,"\t");
            strcat(outline,h1);
            strcat(outline,"\t");
            strcat(outline,h2);   
        }
        h1 = strtok(NULL, " "); 
    }

}



int main(int argc, char * argv[])
{
    char line[1024]; 
    FILE *f = fopen(argv[1],"r");
    FILE *fout = fopen(argv[2],"w");
    if(!f){printf("Input file error!"); exit -1;}
    while(fgets(line, sizeof(line),f)!=NULL)
    {
        char outline[1024];
        memset(outline, 0, strlen(outline));
        char * field;
        char * line_no_return = strtok(line,"\n");
        // remove homo stars
        char buffer[1024];
        memset(buffer, 0, strlen(buffer));
        remove_star(line_no_return, buffer);
        // printf("%s\n",buffer);
        field = strtok(buffer,"\t");
        strcat(outline, field); 
        // process first 5 columns
        for(int i=1; i<5; i++)
        {
            strcat(outline,"\t");
            field = strtok(NULL, "\t");
            strcat(outline,field);
            
        }
        // printf("%s\n", outline);
        char * f1 = strtok(NULL, "\t");
        char * f2 = strtok(NULL, "\t");
        char * m1 = strtok(NULL, "\t");
        char * m2 = strtok(NULL, "\t");
        strcat(outline,"\t");
        strcat(outline,f1);
        strcat(outline,"\t");
        strcat(outline,f2);
        strcat(outline,"\t");
        strcat(outline,m1);
        strcat(outline,"\t");
        strcat(outline,m2);
        // check if parents are both homozygous
        // 0 0 0 0
        // 0 0 1 1
        // 1 1 0 0
        // 1 1 1 1
        if(strcmp(f1,f2)==0 & strcmp(m1,m2)==0) continue;
        if(strcmp(f1, "?") == 0 | strcmp(f2, "?") == 0 | strcmp(m1, "?") == 0  | strcmp(m2, "?") == 0 ) continue;
        // check if parents are both heterozygous
        // 0 1 0 1
        // 0 1 1 0
        // 1 0 1 0
        // 1 0 0 1
        if(strcmp(f1,f2)!=0 & strcmp(m1,m2)!=0)
        {
            // There must a homo for offspring and valid
            char * h1 = strtok(NULL, "\t");
            int homo_count = 0;
            while(h1!=NULL)
            {
                char * h2 = strtok(NULL, "\t");
                if(strcmp(h1,h2)==0 & strcmp(h1,"?")!=0) homo_count++;
                strcat(outline,"\t");
                strcat(outline,h1);
                strcat(outline,"\t");
                strcat(outline,h2);
                h1 = strtok(NULL,"\t");
            }
            if(homo_count==0)continue;
            //printf("%s\n",outline);
            fprintf(fout, "%s\n", outline);
        }
        // 0 0 1 0
        // 1 0 0 0
        // ... 
        else
        {
            // all offspring valid
            char * h1 = strtok(NULL, "\t");
            int valid_phased = 0;
            while(h1!=NULL)
            {
                char * h2 = strtok(NULL, "\t");
                if(strcmp(h1,"?") != 0 & strcmp(h2,"?")!=0) valid_phased++;
                strcat(outline,"\t");
                strcat(outline,h1);
                strcat(outline,"\t");
                strcat(outline,h2);
                h1 = strtok(NULL,"\t");               
            }
            if(valid_phased==0)continue;
            //printf("%s\n", outline);
            fprintf(fout, "%s\n", outline);
        }
    }
    fclose(f);
    fclose(fout);
    return 0;
}
