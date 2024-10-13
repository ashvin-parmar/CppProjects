#include<sys/socket.h>
#include<stdio.h>
#include<string.h>
#include<arpa/inet.h>
#include<unistd.h>
int main()
{	
	char response[5000];
	char request[5000];
	int serverSocketDescriptor;
	int clientSocketDescriptor;
	struct sockaddr_in serverSocketInformation;
	struct sockaddr_in clientSocketInformation;
	int successCode;
	int len;
	int count;
	serverSocketDescriptor=socket(AF_INET,SOCK_STREAM,0);
	if(serverSocketDescriptor<0)
	{
		printf("Unable to create socket");
		return 0;
	}
	serverSocketInformation.sin_family=AF_INET;
	serverSocketInformation.sin_port=htons(5050);
	serverSocketInformation.sin_addr.s_addr=htonl(INADDR_ANY);
	successCode=bind(serverSocketDescriptor,(struct sockaddr *)&serverSocketInformation,sizeof(serverSocketInformation));
	if(successCode<0)
	{
		printf("Unable to bind socket to port 5050\n");
		return 0;
	}
	listen(serverSocketDescriptor,10);
	printf("TMWebServer is ready to accept request on port 5050\n");
	len=sizeof(clientSocketInformation);
	clientSocketDescriptor=accept(serverSocketDescriptor,(struct sockaddr *)&clientSocketInformation,&len);
	if(clientSocketDescriptor<0)
	{
		printf("Unable to accept client connection\n");
		close(serverSocketDescriptor);
		return 0;
	}
	successCode=recv(clientSocketDescriptor,request,sizeof(request),0);
	if(successCode>0)
	{
		printf("Request arrived\n");
		printf("Request : %s\n",request);
	}
	else
	{
		printf("Request not arrived\n");
	}
	strcpy(response,"Welcome to Ashvin Linux Project");
	count=0;
	while(1)
	{
	successCode=send(clientSocketDescriptor,response,strlen(response)+1,0);
	count+=successCode;
	if(count>=strlen(response)) break;
	}
	printf("Response send\n");
	close(clientSocketDescriptor);
	close(serverSocketDescriptor);
	return 0;
}
