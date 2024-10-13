// To find length of characters in file
//ftell(f) reads all characters including '\r' 
//meanwhile fgetc()--> ignore '\r' character (Which is used with '\n' or ENTER)thats why use binary mode to get rid of this problem(eg1_1.c [Solution of eg1.c]) 

#include<stdio.h>
int main()
{
FILE *f;
char g;
int cn;
int ln;
int backSlashnCount=0;
f=fopen("index.html","r");
fseek(f,0,2);
ln=ftell(f);
printf("Length of file: %d\n",ln);
fseek(f,0,0);
cn=0;
while(1)
{
g=fgetc(f);
if(feof(f)) break;
if(g=='\n') backSlashnCount++;
cn++; 
}
fclose(f);
printf("Size of file: %d\n",cn);
printf("Size of blacSlash n count: %d\n",backSlashnCount);
return 0;
}