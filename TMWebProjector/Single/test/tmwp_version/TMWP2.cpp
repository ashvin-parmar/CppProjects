#include<stdio.h>
#include<windows.h>
#include<iostream>
using namespace std;
typedef struct _request
{
char *resource;
char *method;
char isClientSideTechnologyResource;
char *mimeType;
}REQUEST;
int extensionEquals(const char *left,const char *right)
{
int a,b;
while(*left!='\0' && *right!='\0')
{
a=*left;
b=*right;
if(a>=65 && a<=90) a+=32;
if(b>=65 && b<=90) b+=32;
if(a!=b) return 0;
left++;
right++;
}
return *left==*right;
}
char isClientSideResource(const char *resource)
{
return 'Y';	//There are some changes have to be done later on
}
char * getMIMEType(char *resource)
{
char *mimeType;
mimeType=NULL;
cout<<"1"<<endl;
int len=strlen(resource);
int lastIndexOfDot=len-1;
for(;lastIndexOfDot>0 && resource[lastIndexOfDot]!='.';lastIndexOfDot--);
cout<<"lastIndexOfDot"<<lastIndexOfDot<<endl;
if(lastIndexOfDot==0) return mimeType;
if(extensionEquals(resource+lastIndexOfDot+1,"html"))
{
mimeType=(char *)malloc(sizeof(char)*10);
strcpy(mimeType,"text/html");
}
else if(extensionEquals(resource+lastIndexOfDot+1,"css"))
{
mimeType=(char *)malloc(sizeof(char)*9);
strcpy(mimeType,"text/css");
}else if(extensionEquals(resource+lastIndexOfDot+1,"js"))
{
mimeType=(char *)malloc(sizeof(char)*16);
strcpy(mimeType,"text/javascript");
}
return mimeType;
}
REQUEST * parseRequest(char *bytes)
{
char resource[1001];
char method[11];
int i,j;
int len=strlen(bytes);
for(i=0;bytes[i]!=' ' && bytes[i]!='\0';i++) method[i]=bytes[i];
method[i]='\0';
i+=2;
for(j=0;bytes[i]!=' ' && bytes[i]!='\0';j++,i++) resource[j]=bytes[i];
resource[j]='\0';
REQUEST *request=(REQUEST *)malloc(sizeof(REQUEST));
request->method=(char *)malloc(sizeof(char)*(strlen(method)+1));
strcpy(request->method,method);
if(resource[0]=='\0')
{
cout<<"if"<<endl;
request->resource=NULL;
request->isClientSideTechnologyResource=isClientSideResource(resource);
request->mimeType=NULL;
}
else
{
cout<<"else"<<endl;
request->resource=(char *)malloc(sizeof(char)*(strlen(resource)+1));
strcpy(request->resource,resource);
request->isClientSideTechnologyResource=isClientSideResource(resource);
request->mimeType=getMIMEType(resource);
}
//cout<<"method: ("<<method<<")"<<endl;
//cout<<"resource: ("<<resource<<")"<<endl;
//cout<<"mimeType: ("<<request->mimeType<<")"<<endl;
return request;
}
int main()
{
int length;
FILE *f;
WORD ver;
WSADATA wsaData;
int serverSocketDescriptor;
int clientSocketDescriptor;
struct sockaddr_in serverSocketInformation;
struct sockaddr_in clientSocketInformation;
int successCode,byteExtracted,len;
char requestBuffer[8193]; 	//8192=1024 * 8 and 1 space for '\0' (string terminator)
char responseBuffer[1025]; 	//1024 chunk of data is send in response and 1 space for string termination
ver=MAKEWORD(1,1);
WSAStartup(ver,&wsaData);
serverSocketDescriptor=socket(AF_INET,SOCK_STREAM,0);
if(serverSocketDescriptor<0)
{
printf("Unable to create socket\n");
WSACleanup();
return 0;
}
serverSocketInformation.sin_family=AF_INET;
serverSocketInformation.sin_port=htons(5050);
serverSocketInformation.sin_addr.s_addr=inet_addr("127.0.0.1");
successCode=bind(serverSocketDescriptor,(struct sockaddr *)&serverSocketInformation,sizeof(serverSocketInformation));
if(successCode<0)
{
printf("Unable to bind server\n");
closesocket(serverSocketDescriptor);
WSACleanup();
return 0;
}
listen(serverSocketDescriptor,10);
len=sizeof(clientSocketInformation);
while(1)
{
printf("TMServer is ready to accept request\n");
clientSocketDescriptor=accept(serverSocketDescriptor,(struct sockaddr *)&clientSocketInformation,&len);
if(clientSocketDescriptor<0)
{
printf("Unable to accept client request\n");
closesocket(serverSocketDescriptor);
WSACleanup();
return 0;
}
cout<<"recv"<<endl;
byteExtracted=recv(clientSocketDescriptor,requestBuffer,8193,0);
cout<<"Here stuck"<<endl;
if(byteExtracted<0)
{
cout<<"Something to done here, Implemeted later on"<<endl;
// Something to done here, Implemeted later on
}
else if(byteExtracted==0)
{
cout<<"Something to done here, Implemeted later on"<<endl;
//Something to done here, Implemeted later on
}
else 
{
cout<<"else part"<<endl;
requestBuffer[byteExtracted]='\0';
REQUEST *request=parseRequest(requestBuffer);
cout<<request->resource<<endl;
if(request->isClientSideTechnologyResource=='Y')
{
cout<<"clientSideTech"<<endl;
if(request->resource==NULL)
{
cout<<"resource Null"<<endl;

f=fopen("index.html","rb");
if(f==NULL)
{
f=fopen("index.htm","rb");
}
if(f==NULL)
{
strcpy(responseBuffer,"HTTP/1.1 200 OK\nContent-Type:text/html\nContent-Length:163\n\n<!DOCTYPE HTML><html lang='en'><head><meta charset='utf-8'><title>TM Web Projector</title></head><body><h2 style='color:red'>Resource / not found</h2></body></html>");
send(clientSocketDescriptor,responseBuffer,strlen(responseBuffer),0);
}
else
{
fseek(f,0,2);
length=ftell(f);
printf("Size of length: %d\n",length);
printf("Size is %d\n",length);
char header[5000];
strcpy(header,"HTTP/1.1 200 OK\n");
strcat(header,"Content-Type: text/html\n");
strcat(header,"Contant-Length: ");
char ll[11];
sprintf(ll,"%d\n",length);
strcat(header,ll);
strcat(header,"Keep-Alive: Timeout=5, max=1000\n");
strcat(header,"\n");
byteExtracted=send(clientSocketDescriptor,header,strlen(header)+1,0);
int t;
fseek(f,0,0);
while(1)
{
if(feof(f)) break;
t=ftell(f);
if(length-t<=0) break;
if(length-t<1024)
{
fread(responseBuffer,sizeof(char),length-t,f);
if(feof(f)) break;
}
else 
{
fread(responseBuffer,sizeof(char),1024,f);
if(feof(f)) break;
}
byteExtracted=send(clientSocketDescriptor,responseBuffer,strlen(responseBuffer),0);
}
fclose(f);
}
}
else		//if request->resource!=NULL
{
cout<<"resource Not Null"<<endl;

f=fopen(request->resource,"rb");
if(f==NULL)
{
char tmp[501];
sprintf(tmp,"<DOCTYPE HTML><html lang='en'><head><meta charset='utf-8'><title>TM Web Projector</title></head><body><h2 style='color:red'>Resource /%s not found</h2></body></html>",request->resource);
sprintf(responseBuffer,"HTTP/1.1 200 OK\nContent-Type:text/html\nContent-Length:%d\n\n",strlen(tmp));
strcat(responseBuffer,tmp);
send(clientSocketDescriptor,responseBuffer,strlen(responseBuffer),0);
}
else
{
fseek(f,0,2);
length=ftell(f);
printf("Size of length: %d\n",length);
printf("Size is %d\n",length);
char header[5000];
strcpy(header,"HTTP/1.1 200 OK\n");
strcat(header,"Content-Type: text/html\n");
strcat(header,"Contant-Length: ");
char ll[11];
sprintf(ll,"%d\n",length);
strcat(header,ll);
strcat(header,"Keep-Alive: Timeout=5, max=1000\n");
strcat(header,"\n");
byteExtracted=send(clientSocketDescriptor,header,strlen(header)+1,0);
int t;
fseek(f,0,0);
while(1)
{
if(feof(f)) break;
t=ftell(f);
if(length-t<=0) break;
if(length-t<1024)
{
fread(responseBuffer,sizeof(char),length-t,f);
if(feof(f)) break;
responseBuffer[length-t]='\0';
}
else 
{
fread(responseBuffer,sizeof(char),1024,f);
if(feof(f)) break;
responseBuffer[1024]='\0';
}
byteExtracted=send(clientSocketDescriptor,responseBuffer,strlen(responseBuffer),0);
}
fclose(f);
}
}
}
else
{
cout<<"serverSideResource"<<endl;

//server side resources
}
}//else part ends here
}// while loop ends

closesocket(clientSocketDescriptor);
closesocket(serverSocketDescriptor);
WSACleanup();
return 0;
}