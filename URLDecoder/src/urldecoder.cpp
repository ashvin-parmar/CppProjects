#include<urldecoder>
#include <iostream>
#include <string>
#include <cctype>
using namespace std;
using namespace urldecoder;
char URLDecoder::toHexDigit(char c) 
{
if (c >= '0' && c <= '9') 
{
return c - '0';
}
else if (c >= 'a' && c <= 'f') 
{
return c - 'a' + 10;
}
else if (c >= 'A' && c <= 'F') 
{
return c - 'A' + 10;
}
else
{
return -1;
}
}
char URLDecoder::toDigitHex(char c) 
{
if (c >= 0 && c <= 9) 
{
return '0' + c;
}
else if (c >= 10 && c <= 15) 
{
return 'A' + c - 10;
} 
else 
{
return -1;
}
}
URLDecoder::URLDecoder()
{
this->decodedURL="";
this->encodedURL="";
}
URLDecoder::URLDecoder(const string &encodedURL)
{
this->encodedURL=encodedURL;
this->decodedURL=decode(encodedURL);
}
URLDecoder::URLDecoder(const URLDecoder &other)
{
this->encodedURL=other.encodedURL;
this->decodedURL=other.decodedURL;
}
URLDecoder & URLDecoder::operator=(const URLDecoder &other)
{
this->encodedURL=other.encodedURL;
this->decodedURL=other.decodedURL;
return *this;
}
string URLDecoder::decode(const string &encodedURL)
{
string decodedURL;
decodedURL.reserve(encodedURL.size());
for (int i = 0; i < encodedURL.size();i++)
{
char c = encodedURL[i];
if(c=='%')
{
if(i+2<encodedURL.size())
{
char highNibble=(char)(toHexDigit(encodedURL[i + 1]));
char lowNibble=(char)(toHexDigit(encodedURL[i + 2]));
if (highNibble != -1 && lowNibble != -1)
{
decodedURL.push_back((char)((highNibble << 4) | lowNibble));	//left Shift along with oring operation
i += 2;
} 
else 
{
decodedURL.push_back('%');
}
}
else 
{
decodedURL.push_back('%');
}
} 
else if (c == '+') 
{
decodedURL.push_back('+');
} 
else 
{
decodedURL.push_back(c);
}
}
return decodedURL;
}
string URLDecoder::encode(const string &decodedURL)
{
string encodedURL;
for (char c : decodedURL) 
{
if(c == ' ') 
{
encodedURL.push_back('+');
}
else if(isxdigit(c)) 
{
encodedURL.push_back(c);
}
else 
{
encodedURL.push_back('%');
encodedURL.push_back(toDigitHex(static_cast<unsigned char>(c) >> 4));
encodedURL.push_back(toDigitHex(static_cast<unsigned char>(c) & 0x0F));
}
}
return encodedURL;
}
void URLDecoder::setEncodedURL(string &encodedURL)
{
this->encodedURL=encodedURL;
}
void URLDecoder::setDecodedURL(string &decodedURL)
{
this->decodedURL=decodedURL;
}
string URLDecoder::getEncodedURL()
{
return this->encodedURL;
}
string URLDecoder::getDecodedURL()
{
return this->decodedURL;
}