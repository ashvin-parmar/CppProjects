#include<stdio.h>
#include<urldecoder>
using namespace urldecoder;
using namespace std;

int main() {
    URLDecoder encode;

    string decodedURL1="http://localhost:8080/register?nm=Ashvin~????What_is_your-name-^%&$*#(%#(#)@*$(%*$-=><:?:{}|+:>&ct=432423MEDFMEOg?";
cout<<"Encoded URL 1: "<<decodedURL1<<endl;	
    std::string encodedURL1= encode.encode(decodedURL1);
    std::cout << "Encoded URL 1: " << encodedURL1<< std::endl;
    std::string decodedURL2;
cout<<"Enter Your URL: ";
getline(cin,decodedURL2);

    std::string encodedURL2 = encode.encode(decodedURL2);
    std::cout << "Decoded URL 2: " <<encodedURL2<< std::endl;

    return 0;
}