#ifndef DOUBLEHASH_CPP
#define DOUBLEHASH_CPP
#include "doubleHash.h"
#include "hashfunctions.cpp"
HashD::HashD(){
    tableSize = 10000; // you cant change this
    count=0;
    hashTable = new block*[tableSize];
    for(int i=0;i<tableSize;i++)
    {
    	hashTable[i]=NULL;
    }

}

HashD::~HashD(){
for (int i=0; i<tableSize; i++)
{
	delete hashTable[i];
}
delete hashTable;	


}
unsigned long HashD::hash1(string value)
{
return divCompression(bitHash(value), tableSize);
}




unsigned long HashD::hash2(string value)
{
return madCompression(polyHash(value),tableSize);
}

void HashD::resizeTable(){
int oldsize = tableSize;
tableSize = tableSize * 5.5;

block** hashTable2 = new block*[tableSize];
for (int i=0; i<tableSize; i++)
{
	hashTable2[i] = NULL;
}

string* allvalues= new string[oldsize];

for (int i=0; i<oldsize; i++)
{
	if (hashTable[i] == NULL || hashTable[i]->key == -1)
		allvalues[i] = "value deleted";
	else		
		allvalues[i] = hashTable[i]->value;
}

for (int i=0; i<oldsize; i++)
{
	delete hashTable[i];
}
delete hashTable;

hashTable = hashTable2;
count = 0; 
for (int i=0; i<oldsize; i++)
{
	if (allvalues[i] != "value deleted")
	{
		insert(allvalues[i]);
	}
}

}

void HashD::insert(string value){
unsigned long key1 = hash1(value);

double temp= count;
double temp2= tableSize;
double loadfactor = temp/temp2;
if (loadfactor>=0.2)
{
	resizeTable();
}
if (hashTable[key1] == NULL || hashTable[key1]->key == -1)
	{
		hashTable[key1] = new block(key1, value);
	    count=count+1;
	}

else
{
	int i=1;
	int index = 0;
	unsigned long key2 = hash2(value);
	index = (key1 + key2*i) % tableSize;
	while(hashTable[index] != NULL && hashTable[index]->key != -1)
	{
		i++;
		index=(key1 + key2*i) % tableSize;
	}
	hashTable[index] = new block(key1, value);
	count=count+1;
}


  
}

void HashD::deleteWord(string value){
block* temp = lookup(value);
	if (temp != NULL)
	{
		temp->key = -1;
		temp->value = "value deleted";
		count=count+1;
	}
}

block* HashD::lookup(string value){

unsigned long key1 = hash1(value);

if (hashTable[key1]!= NULL && hashTable[key1]->value == value && hashTable[key1]->key == key1)
{
		return hashTable[key1];
}

else
{
	int i=0;
	int index = 0;	
	unsigned long key2 = hash2(value);
	index = (key1 + key2*i) % tableSize;
	while(hashTable[index]->value != value || hashTable[index]->key !=key1)
	{
		i++;
		index = (key1 + key2*i) % tableSize;	

		if (i>=tableSize) //not found
			return NULL;
		if (hashTable[index] == NULL)
			return NULL;		
	}
	return hashTable[index];

}
}

#endif