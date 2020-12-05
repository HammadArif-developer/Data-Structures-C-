#ifndef __DICTIONARY_CPP
#define __DICTIONARY_CPP
#include "dictionary.h"
#include <time.h>
#include <stdio.h>
#include<fstream>

Dictionary::Dictionary() {
	wordsTree = NULL;
}

Dictionary::~Dictionary(){
    delete wordsTree;
}

void Dictionary::initialize(string wordsFile) {
    ifstream fread;
    int count=0;
    string temp;
    wordsTree=new BST<string>;
    fread.open((wordsFile+".txt").c_str());
    while(count<50000)
    {
        //cout<<temp<<" ";
        fread>>temp;
        wordsTree->insert(temp,temp);
        count++;
    }
    fread.close();
}

bool Dictionary::deleteWord(string word) {
    node<string>* temp=findWord(word);
    if(temp==NULL)
	return false;
	else
    {
        wordsTree->delete_node(word);
        return true;
    }
}
bool Dictionary::editWord(string oldWord, string newWord) {
    node<string>* temp=findWord(oldWord);
    if(temp==NULL)
        return false;
    else
    {
        deleteWord(oldWord);
        insertWord(newWord);
        return true;
    }
}
bool Dictionary::insertWord(string word) {
    if(wordsTree==NULL)
    {
        wordsTree=new BST<string>;
        wordsTree->insert(word,word);
        return true;
    }
    node<string>* temp=findWord(word);
    if(temp==NULL)
        return false;
    else
    {
        wordsTree->insert(word,word);
        return true;
    }

}
node<string>* Dictionary::findWord(string word) {
	clock_t t;
    t = clock();
    // TODO your code here
    node<string>* temp = wordsTree->search(word);
    t = clock() - t;
    double time_taken = ((double)t) / CLOCKS_PER_SEC; // in seconds
    cout << "findWord() took " << time_taken << "sec to search for " << word << endl;
    return temp; // TODO
}

#endif

int main() {
	Dictionary dic;
    dic.initialize("words");
	ifstream ofile;
	ofile.open("word2.txt");
	string temp;
	while(ofile>>temp)
    {
    dic.findWord(temp);
    }
    ofile.close();
    return 0;
}
