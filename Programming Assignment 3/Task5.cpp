#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "hashfunctions.cpp"
#include <thread>
#include <chrono>
#include <future>
// bool timeOut;
using namespace std::chrono;


using namespace std;
class block{
    public:
        unsigned long key;
        string value;
        block(unsigned long _key,string _value){
            this->key = _key;
            this->value = _value;
        }
};


class HashL{
    private:
        block** hashTable;
        long tableSize;
        unsigned long hash(string value)
        {
        	unsigned long key = madCompression(bitHash(value),tableSize);
			return key;
        } // return the corresponding key of the value
        long count; // keeps a count of the number of entries in the table.
        // void resizeTable();
    public:
        HashL()
        {
        	tableSize = 1000; // you cant change this
		    count=0;
		    hashTable = new block*[tableSize];
		    for(int i=0;i<tableSize;i++)
		    {
		    	hashTable[i]=NULL;
		    }
        }
        ~HashL()
        {
        		for (int i=0; i<tableSize; i++)
				{
					delete hashTable[i];
				}
				delete hashTable;
        }
        void insert(string value, string a)
        {
        		unsigned long key = hash(value);
        		unsigned long index=key;
				while(hashTable[index]!=NULL)
				{
					index=index+1;
					index=index%tableSize;
				}
				if(hashTable[index]==NULL)
				{
					count=count+1;
					hashTable[index] = new block(key,a);
				}
        }
		void deleteWord(string value)
		{
				unsigned long key = hash(value);
				unsigned long index = key;
				while (hashTable[index] != NULL)
					{
						if ( hashTable[index]->key == key)
							{
								hashTable[index]->value="-1";
								count--;
								// break;
							}

							
						index++;
						index%=tableSize;
					}
		}
		block* lookup(string value)
		{
				// unsigned long key = hash(a);
				// while( hashTable[key] != NULL)
				// 	{
				// 		if (hashTable[key]->key == a)
				// 			return hashTable[key];

				// 		key++;
				// 		key%=tableSize;
				// 	}
        		unsigned long key = hash(value);
        		unsigned long index=key;
				while(hashTable[index]!=NULL)
				{
					if (hashTable[index]->key == key)
						return hashTable[index];					
					index=index+1;
					index=index%tableSize;
				}

				return NULL;
		}
};
int main()
{
	high_resolution_clock::time_point timeStart = high_resolution_clock::now();
	vector<string> allWords;
	vector<string> Dictionary;
	HashL* cache= new HashL();
    ifstream file1;
    file1.open("secret1.txt");
    cout << "LOADING THE FILE1" << endl;
    string temp;
    int temp2;
    while(!file1.eof()){
        file1>>temp;
        temp2=temp.length();
        temp=temp.substr(0,temp2-1);
        allWords.push_back(temp);
        cout<<temp<<endl;
    }
    file1.close();
    ifstream file2;
    file2.open("secret2.txt");
    cout << "LOADING THE FILE2" << endl;
    while(!file2.eof()){
        file2 >> temp;
        temp2=temp.length();
        temp=temp.substr(0,temp2-1);
        allWords.push_back(temp);
        cout<<temp<<endl;
    }
    file2.close();
    ifstream file3;
    file3.open("secret3.txt");
    cout << "LOADING THE FILE3" << endl;
    while(!file3.eof()){
        file3 >> temp;
        temp2=temp.length();
        temp=temp.substr(0,temp2-1);
        allWords.push_back(temp);
        cout<<temp<<endl;
    }
    file3.close();
    for(int i=0;i<1000;i++)
    {
    ifstream dic;
    dic.open("dictionary.txt");
    cout << "LOADING THE Dictionary:" << endl;
    string rem;
    int counter=0;
    if(cache->lookup(allWords[i])!=NULL)
    {
    	cout<<"from cache:"cache->lookup(allWords[i])->value<<endl;
    }
    else
    {
    	while(!dic.eof())
    	{
    	dic>>rem;
        dic>>temp;
        temp2=temp.length();
        temp=temp.substr(0,temp2-1);
       	if(rem==allWords[i])
       	{
       		cache->insert(rem,temp);
       		cout<<"from Dictionary:"<<temp<<endl;
       		break;
       	}
        }
    dic.close();
    }    	

    }
    // ifstream dic;
    // dic.open("dictionary.txt");
    // cout << "LOADING THE Dictionary:" << endl;
    // string rem;
    // int counter=0;
    // while(!dic.eof()){
    // 	dic>>rem;
    //     dic>>temp;
    //     temp2=temp.length();
    //     temp=temp.substr(0,temp2-1);
    //     Dictionary.push_back(temp);
    //     cout<<temp<<endl;
    //     counter++;
    //     if(counter>1000)
    //     {
    //     	break;
    //     }
    // }
    // dic.close();
    // for(int i=0;i<Dictionary.size();i++){
    //     cache->insert(Dictionary[i]);
    // }
        // done_future.set_value(true);
    high_resolution_clock::time_point timeEnd = high_resolution_clock::now();;
    duration<double> totalTime = duration_cast<duration<double>>(timeEnd - timeStart);
    cout << "TEST PASSED IN : " << totalTime.count() << " SECONDS."<<endl;
}