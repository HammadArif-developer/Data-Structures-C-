#ifndef LINEARPROBING_CPP
#define LINEARPROBING_CPP

#include "linearProbing.h"
#include "hashfunctions.cpp"


HashL::HashL(){
    tableSize = 1000; // you cant change this
    count=0;
    hashTable = new block*[tableSize];
    for(int i=0;i<tableSize;i++)
    {
    	hashTable[i]=NULL;
    }

}

HashL::~HashL(){
for (int i=0; i<tableSize; i++)
{
	delete hashTable[i];
}
delete hashTable;

}

unsigned long HashL :: hash(string value){
	unsigned long key = madCompression(bitHash(value),tableSize);
	return key;
	// return bitHash(value);


}

void HashL::resizeTable(){
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
			if (hashTable[i] == NULL)
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

void HashL::insert(string value){
	double temp= count;
	double temp2= tableSize;
	double loadfactor = temp/temp2;
	if(loadfactor > 0.4)
	{
		resizeTable();
	}		
	   unsigned long key = hash(value);
		while(hashTable[key]!=NULL)
		{
			key=key+1;
			key=key%tableSize;
		}
		if(hashTable[key]==NULL)
		{
		count=count+1;
		hashTable[key] = new block(key,value);
		}

}

void HashL::deleteWord(string value){
	unsigned long key = hash(value);
	while (hashTable[key] != NULL)
		{
			if ( hashTable[key]->value == value)
				{
					hashTable[key]->value="-1";
					count--;
					// break;
				}

				
			key++;
			key%=tableSize;
		}
}

block* HashL::lookup(string value){
	unsigned long key = hash(value);
	while( hashTable[key] != NULL)
		{
			if (hashTable[key]->value == value)
			return hashTable[key];

			key++;
			key%=tableSize;
		}

	return NULL;

}
#endif
