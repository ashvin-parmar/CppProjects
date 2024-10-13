#include<windows.h>
#include<stdio.h>
#include<string.h>
int main()
{
WSADATA wsaData;
int clientSocketDescriptor;
struct sockaddr_in serverSocketInformation;
char response[5000];
char request[5000];

WSAStartup(MAKEWORD(1,1),&wsaData);

clientSocketDescriptor=socket(AF_INET,SOCK_STREAM,0);
if(clientSocketDescriptor<0)
{
printf("Unable to create socket\n");
WSACleanup();
return 0;
}
serverSocketInformation.sin_family=AF_INET;
serverSocketInformation.sin_port=htons(5050);
serverSocketInformation.sin_addr.s_addr=inet_addr("127.0.0.1");
connect(clientSocketDescriptor,(struct sockaddr *)&serverSocketInformation,sizeof(serverSocketInformation));
strcpy(request,"Hello Thinking Machine, I have inrolled for a course");
send(clientSocketDescriptor,request,sizeof(request),0);
printf("Request sent\n");
recv(clientSocketDescriptor,response,sizeof(response),0);
printf("%s\n",response);
recv(clientSocketDescriptor,response,sizeof(response),0);
printf("%s\n",response);

WSACleanup();
return 0;
}