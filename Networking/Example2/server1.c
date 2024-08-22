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
serverSocketInformation.sin_addr.s_addr=inet_addr("127.0.0.1");
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
if(byteCount<0)
{
printf("Unable to get request\n");
}

strcpy(response,"<!DOCTYPE HTML>");
strcat(response,"<html lang='en'>");
strcat(response,"<head>");
strcat(response,"<meta charset='utf-8'>");
strcat(response,"<title>Whatever</title>");
strcat(response,"</head>");
strcat(response,"<body>");
strcat(response,"<h1>Welcome To Thinking Machine</h1>");
strcat(response,"</body>");
strcat(response,"</html>");

char header[5000];
strcpy(header,"HTTP/1.1 200 OK\n");			//Here all things are '\n' seperated
strcat(header,"Content-Type: text/html\n");		//Here all things are '\n' seperated
strcat(header,"Content-Length: ");
char responseLength[11];
sprintf(responseLength,"%d\n",strlen(response)+1);	//Here all things are '\n' seperated
strcat(header,responseLength);
strcat(header,"\n"); 					//one line gap

byteCount=send(clientSocketDescriptor,header,strlen(header)+1,0);
byteCount=send(clientSocketDescriptor,response,strlen(response)+1,0);
printf("Response send\n");

closesocket(clientSocketDescriptor);
closesocket(serverSocketDescriptor);
WSACleanup();
return 0;
}