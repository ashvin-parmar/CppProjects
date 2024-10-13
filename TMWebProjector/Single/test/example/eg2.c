// To find length of characters in file

#include<stdio.h>
int main()
{
FILE *f;
char g;
int cn;
int ln,rc;
char response[1024];
f=fopen("index.html","rb");
fseek(f,0,2);
ln=ftell(f);
printf("Length of file: %d\n",ln);
fseek(f,0,0);
cn=0;
while(cn<ln)
{
if(ln-cn>1024) rc=1024; 
else rc=ln-cn;
fread(response,rc,1,f);
if(feof(f)) break;
cn+=rc;
}
fclose(f);
printf("Size of file: %d\n",cn);

return 0;
}