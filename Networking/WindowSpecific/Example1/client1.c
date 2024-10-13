#include<stdio.h>
#include<windows.h>
int main()
{
WORD ver;
WSADATA wsaData;
int clientSocketDescriptor;
struct sockaddr_in serverSocketInformation;
char request[5000];
char response[5000];

ver=MAKEWORD(1,1);
WSAStartup(ver,&wsaData);

clientSocketDescriptor=socket(AF_INET,SOCK_STREAM,0); //Craete socket

serverSocketInformation.sin_family=AF_INET;	//Set IPV4
serverSocketInformation.sin_port=htons(5050);	//Set port number
serverSocketInformation.sin_addr.s_addr=inet_addr("127.0.0.1");	 
//Set IP Address of server to connect client(Used inet_addr("") to send address in string form and convert it in long form)

connect(clientSocketDescriptor,(struct sockaddr *)&serverSocketInformation,sizeof(serverSocketInformation));
//Connect request from client to server

strcpy(request,"Hello thinking machine, I have registered for a course");
send(clientSocketDescriptor,request,sizeof(request),0);
printf("Request send\n");

recv(clientSocketDescriptor,response,sizeof(response),0);	//take response data using recv
printf("Response: %s\n",response);

WSACleanup();	//Clean WSA
return 0;
}