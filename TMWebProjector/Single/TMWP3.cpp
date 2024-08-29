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
int len=strlen(resource);
int lastIndexOfDot=len-1;
for(;lastIndexOfDot>0 && resource[lastIndexOfDot]!='.';lastIndexOfDot--);
if(lastIndexOfDot==0) return mimeType;
if(extensionEquals(resource+lastIndexOfDot+1,"html"))
{
mimeType=(char *)malloc(sizeof(char)*10);
strcpy(mimeType,"text/html");
}
if(extensionEquals(resource+lastIndexOfDot+1,"css"))
{
mimeType=(char *)malloc(sizeof(char)*9);
strcpy(mimeType,"text/css");
}
if(extensionEquals(resource+lastIndexOfDot+1,"js"))
{
mimeType=(char *)malloc(sizeof(char)*16);
strcpy(mimeType,"text/javascript");
}
if(extensionEquals(resource+lastIndexOfDot+1,"jpg"))
{
mimeType=(char *)malloc(sizeof(char)*11);
strcpy(mimeType,"image/jpeg");
}
if(extensionEquals(resource+lastIndexOfDot+1,"jpeg"))
{
mimeType=(char *)malloc(sizeof(char)*11);
strcpy(mimeType,"image/jpeg");
}
if(extensionEquals(resource+lastIndexOfDot+1,"png"))
{
mimeType=(char *)malloc(sizeof(char)*10);
strcpy(mimeType,"image/png");
}
if(extensionEquals(resource+lastIndexOfDot+1,"ico"))
{
mimeType=(char *)malloc(sizeof(char)*13);
strcpy(mimeType,"image/x-icon");
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
request->resource=NULL;
request->isClientSideTechnologyResource=isClientSideResource(resource);
request->mimeType=NULL;
}
else
{
request->resource=(char *)malloc(sizeof(char)*(strlen(resource)+1));
strcpy(request->resource,resource);
request->isClientSideTechnologyResource=isClientSideResource(resource);
request->mimeType=getMIMEType(resource);
}
printf("Request arrived: (%s)\n",resource);
//cout<<"method: ("<<method<<")"<<endl;
//cout<<"resource: ("<<resource<<")"<<endl;
//cout<<"mimeType: ("<<request->mimeType<<")"<<endl;
return request;
}
int main()
{
int length;
int cn,rc;
FILE *f;
WORD ver;
WSADATA wsaData;
int serverSocketDescriptor;
int clientSocketDescriptor;
struct sockaddr_in serverSocketInformation;
struct sockaddr_in clientSocketInformation;
int successCode,byteExtracted,len;
char requestBuffer[8192]; 	//8192=1024 * 8 
char responseBuffer[1024]; 	//1024 chunk of data 
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
clientSocketDescriptor=accept(serverSocketDescriptor,(struct sockaddr *)&clientSocketInformation,&len);
printf("TMServer is ready to accept request\n");
printf("Client Socket Descriptor: %d\n",clientSocketDescriptor);
if(clientSocketDescriptor==0) continue;
if(clientSocketDescriptor<0)
{
printf("Unable to accept client request\n");
closesocket(serverSocketDescriptor);
WSACleanup();
return 0;
}
byteExtracted=recv(clientSocketDescriptor,requestBuffer,8192,0);
printf("Request Byte Extracted : %d\n",byteExtracted);
if(byteExtracted<0)
{
// Something to done here, Implemeted later on
}
else if(byteExtracted==0)
{
//Something to done here, Implemeted later on
}
else 
{
requestBuffer[byteExtracted]='\0';	//Request taken from browser are not contain termination
REQUEST *request=parseRequest(requestBuffer);
if(request->isClientSideTechnologyResource=='Y')
{
cout<<"clientSideTech"<<endl;
if(request->resource==NULL)
{
cout<<"Resource Null"<<endl;
f=fopen("index.html","rb");
if(f==NULL)
{
f=fopen("index.htm","rb");
}
if(f==NULL)
{
printf("Sending 404 page\n");
strcpy(responseBuffer,"HTTP/1.1 200 OK\nContent-Type:text/html\nContent-Length:163\n\n<!DOCTYPE HTML><html lang='en'><head><meta charset='utf-8'><title>TM Web Projector</title></head><body><h2 style='color:red'>Resource / not found</h2></body></html>");
send(clientSocketDescriptor,responseBuffer,strlen(responseBuffer),0);
closesocket(clientSocketDescriptor);
}
else
{
fseek(f,0,2);
length=ftell(f);
fseek(f,0,0);
printf("Size of length: %d\n",length);
sprintf(responseBuffer,"HTTP/1.1 200 OK\nContent-Type:text/html\nContent-Length: %d\nKeep-Alive: Timeout=5, max=1000\n\n",length);
byteExtracted=send(clientSocketDescriptor,responseBuffer,strlen(responseBuffer),0);
cn=0;
while(cn<length)
{
rc=length-cn;
if(rc>1024) rc=1024;
fread(responseBuffer,rc,1,f);
if(feof(f)) break;
byteExtracted=send(clientSocketDescriptor,responseBuffer,rc,0);
cn+=rc;
}
fclose(f);
closesocket(clientSocketDescriptor);
}
}
else		//if request->resource!=NULL
{
printf("Resource not null\n");
f=fopen(request->resource,"rb");
if(f==NULL)
{
printf("Sending 404 page\n");
char tmp[501];
sprintf(tmp,"<!DOCTYPE HTML><html lang='en'><head><meta charset='utf-8'><title>TM Web Projector</title></head><body><h2 style='color:red'>Resource /%s not found</h2></body></html>",request->resource);
sprintf(responseBuffer,"HTTP/1.1 200 OK\nContent-Type:text/html\nContent-Length:%d\n\n",strlen(tmp));
strcat(responseBuffer,tmp);
send(clientSocketDescriptor,responseBuffer,strlen(responseBuffer),0);
closesocket(clientSocketDescriptor);
}
else
{
fseek(f,0,2);
length=ftell(f);
fseek(f,0,0);
printf("Size of length: %d\n",length);
sprintf(responseBuffer,"HTTP/1.1 200 OK\nContent-Type: %s\nContent-Length: %d\nKeep-Alive: Timeout=5, max=1000\n\n",request->mimeType,length);
byteExtracted=send(clientSocketDescriptor,responseBuffer,strlen(responseBuffer),0);
cn=0;
while(cn<length)
{
rc=length-cn;
if(rc>1024) rc=1024;
fread(responseBuffer,rc,1,f);
if(feof(f)) break;
byteExtracted=send(clientSocketDescriptor,responseBuffer,rc,0);
cn+=rc;
}
fclose(f);
closesocket(clientSocketDescriptor);
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
closesocket(serverSocketDescriptor);
WSACleanup();
return 0;
}