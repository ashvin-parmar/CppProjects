#include<stdio.h>
#include<windows.h>
#include<string.h>
int main()
{
WORD ver;
WSADATA wsaData;
int serverSocketDescriptor;
int clientSocketDescriptor;
struct sockaddr_in serverSocketInformation;
struct sockaddr_in clientSocketInformation;
char request[5000];
char response[5000];
int len;
int successCode;

ver=MAKEWORD(1,1);		//Two byte version formate
WSAStartup(ver,&wsaData);	//Windows startup	(Intialize library)

serverSocketDescriptor=socket(AF_INET,SOCK_STREAM,0);
	//AF_INET: IPV4/IPV6 Best connection port
	//SOCK_STREAM: Most reliable stream to create socket
	// 0: set for TCP/IP Protocol
serverSocketInformation.sin_family=AF_INET;			//Set protocol (IPV4 protocol)
serverSocketInformation.sin_port=htons(5050);			//Set Port Number in sort form
serverSocketInformation.sin_addr.s_addr=htonl(INADDR_ANY);	//Set IP Address in long form
successCode=bind(serverSocketDescriptor,(struct sockaddr *)&serverSocketInformation,sizeof(serverSocketInformation));
//Bind socket with port

if(successCode<0)
{
printf("Unable to bind connection\n");
closesocket(serverSocketDescriptor);
WSACleanup();
return 0;
}
//Specify 10 server port
listen(serverSocketDescriptor,10);

printf("TMServer is ready to accept request on port 5050\n");

len=sizeof(clientSocketInformation);
clientSocketDescriptor=accept(serverSocketDescriptor,(struct sockaddr *)&clientSocketInformation,&len);	
//accept request from client to connect with server socket
if(clientSocketDescriptor<0)
{
printf("Unable to accept client connection\n");
closesocket(serverSocketDescriptor);
WSACleanup();
return 0;
}

successCode=recv(clientSocketDescriptor,request,sizeof(request),0); //Recieve request in recv
printf("Request: %s\n",request);

strcpy(response,"Welcome, Thinking Machine");
send(clientSocketDescriptor,response,sizeof(response),0); //send response using send function
printf("Response sent\n");

closesocket(clientSocketDescriptor);	//Close client socket first
closesocket(serverSocketDescriptor);	//Close server socket last
WSACleanup();	//Clean WSA
return 0;
}