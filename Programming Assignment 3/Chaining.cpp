#ifndef CHAINING_CPP
#define CHAINING_CPP
#include "Chaining.h"
#include "hashfunctions.cpp"

HashC::HashC(int size){
tableSize=size;
hashTable= new LinkedList<string> [tableSize];

}
HashC::~HashC(){
    delete hashTable;
    tableSize=0;

}

unsigned long HashC :: hash(string input){
    return bitHash(input);


}

void HashC::insert(string word){
    unsigned long key= madCompression(hash(word),tableSize);
    hashTable[key].insertAtHead(word);

}

ListItem<string>* HashC :: lookup(string word){
    unsigned long key= madCompression(hash(word),tableSize);
    return hashTable[key].searchFor(word);

}

void HashC :: deleteWord(string word){
    unsigned long key= madCompression(hash(word),tableSize);
    hashTable[key].deleteElement(word);

}


#endif
