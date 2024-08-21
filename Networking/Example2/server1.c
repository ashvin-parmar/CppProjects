#include<stdio.h>
#include<string.h>
#include<windows.h>
int main()
{
WORD ver;
WSADATA wsaData;
int serverSocketDescriptor;
int clientSocketDescriptor;
struct sockaddr_in serverSocketInformation;
struct sockaddr_in clientSocketInformation;
int successCode;
int byteCount;
int len;
char request[5000];
char response[5000];

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
serverSocketInformation.sin_addr.s_addr=htonl(INADDR_ANY);
successCode=bind(serverSocketDescriptor,(struct sockaddr *)&serverSocketInformation,sizeof(serverSocketInformation));
if(successCode<0)
{
printf("Unable to bind socket with port");
closesocket(serverSocketDescriptor);
WSACleanup();
return 0;
}
listen(serverSocketDescriptor,10);
printf("TMServer is ready to accept request from client\n");
len=sizeof(clientSocketInformation);
clientSocketDescriptor=accept(serverSocketDescriptor,(struct sockaddr *)&clientSocketInformation,&len);
if(clientSocketDescriptor<0)
{
printf("Unable to accept client request");
closesocket(serverSocketDescriptor);
WSACleanup();
return 0;
}
byteCount=recv(clientSocketDescriptor,request,sizeof(request),0);
printf("%s\n",request);
strcpy(response,"Welcome to Thinking Machine");
byteCount=send(clientSocketDescriptor,response,sizeof(response),0);
printf("Response send");
closesocket(clientSocketDescriptor);
closesocket(serverSocketDescriptor);
WSACleanup();
return 0;
}