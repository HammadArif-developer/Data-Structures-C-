#ifndef HASHFUNCTIONS_CPP
#define HASHFUNCTIONS_CPP
#include <string>
#include <iostream>
#include <cmath>

using namespace std;
// this takes in a string and returns a 64bit hash.
unsigned long polyHash(std::string value,int a = 9){
    unsigned long result=0;
    int w_length= value.length();
    for(int i=0;i<w_length;i++)
    {
        result= result + (value[i]*pow(a,w_length-(1+i)));
    }
    return result;

}

//does some bitwise operation and generates a 64bit hash.
unsigned long bitHash(std::string value){
    unsigned long bitwise_hash=0;
    int w_length=value.length();
    for(int i=0;i<w_length;i++)
    {
        bitwise_hash^=(bitwise_hash<<5) + (bitwise_hash>>2) + value[i];
    }
    return bitwise_hash;
}
// Size is the size of array maintained by the hashtable.
unsigned long divCompression(unsigned long hash,long size){
return hash%(size);
}
// multiplication addition and division compression.
unsigned long madCompression(unsigned long hash,long size,int m = 1993,int a = 1637){
return ((a*hash)+m)%size;
}
#endif
// you may write your own program to test these functions.
/*int main()
{
    while (true)
    {
    string name;
    cin>>name;
    cout<<polyHash(name,9)<<endl;
    cout<<bitHash(name)<<endl;
    cout<<divCompression(polyHash(name,9),9)<<endl;
    cout<<madCompression(polyHash(name,9),9,1993,1637)<<endl;
    cout<<divCompression(bitHash(name),9)<<endl;
    cout<<madCompression(bitHash(name),9,1993,1637)<<endl;

    }

}*/
