#ifndef VCS_CPP
#define VCS_CPP
#include "VCS.h"
#include<iostream>
#include <sstream>
#include<string>
using namespace std;
//I used Stack as my Data Structure in VCS because we need to shift the top item of both containers and Stack has lowest Time complexity which O(1) to remove or push first element.   
//base constructor, init
VCS::VCS(string fname)
{
	curr_size=0;
	filename=fname;
}

//destructor
VCS::~VCS()
{
curr_size=0;
}


//time to commit
void VCS::commit(string msg)
{
    ifstream oread;
    ofstream rread;
    string temp;
    string ntemp="";
    ostringstream str1;
    str1<<curr_size;
    string filename_time_stamp=filename+str1.str()+".txt";
    oread.open((filename+".txt").c_str());
    rread.open(filename_time_stamp.c_str());
    oread>>temp;
    rread<<temp;
    oread.close();
    rread.close();
    VCS_node temp1(msg,curr_size);
    container1.push(temp1);
    curr_size++;

}

//print status of every version
void VCS::status()
{

    VCS_node temp1=container1.pop();
    cout<<"messages:"<<temp1.message<<endl<<"time_stamp:"<<temp1.time_stamp<<""<<endl;
    VCS_node temp2=container1.pop();
    cout<<"messages:"<<temp2.message<<endl<<"time_stamp:"<<temp2.time_stamp<<""<<endl;
    VCS_node temp3=container1.pop();
    cout<<"messages:"<<temp3.message<<endl<<"time_stamp:"<<temp3.time_stamp<<""<<endl;
    VCS_node temp4=container1.pop();
    cout<<"messages:"<<temp4.message<<endl<<"time_stamp:"<<temp4.time_stamp<<""<<endl;
    VCS_node temp5=container1.pop();
    cout<<"messages:"<<temp5.message<<endl<<"time_stamp:"<<temp5.time_stamp<<""<<endl;

    container1.push(temp1);
    container1.push(temp2);
    container1.push(temp3);
    container1.push(temp4);
    container1.push(temp5);
}

//goes one step back
string VCS::undo()
{
    container2.push(container1.pop());
    VCS_node tempnod=container1.top();
    ifstream oread;
    ofstream rread;
    string temp;
    ostringstream str1;
    str1<<tempnod.time_stamp;
    string filename_time_stamp=filename+str1.str()+".txt";
    oread.open(filename_time_stamp.c_str());
    rread.open((filename+".txt").c_str());
    //string temp2;
    oread>>temp;
    /*while(oread>>temp)
    {
        temp2=temp2+temp;
    }*/
    rread<<temp;
    oread.close();
    rread.close();
    return temp;

}

//one step ahead
string VCS::redo()
{
    container1.push(container2.pop());
    VCS_node tempnod=container1.top();
    ifstream oread;
    ofstream rread;
    string temp;
    ostringstream str1;
    str1<<tempnod.time_stamp;
    string filename_time_stamp=filename+str1.str()+".txt";
    oread.open(filename_time_stamp.c_str());
    rread.open((filename+".txt").c_str());
    string temp2;
    while(oread>>temp)
    {
        temp2=temp2+temp;
    }
    rread<<temp2;
    oread.close();
    rread.close();
    return temp2;
}

//goes t_stamp step back or ahead
string VCS::revert(int t_stamp)
{
    /*ifstream oread;
    string temp;
    ostringstream str1;
    str1<<t_stamp;
    string filename_time_stamp=filename+str1.str()+".txt";
    oread.open(filename_time_stamp.c_str());
    string temp2;
    while(oread>>temp)
    {
        temp2=temp2+temp;
    }
    oread.close();
    
    /*if(t_stamp<0 || t_stamp>curr_size)
    {
        return rtemp;
    }*/
    /*int counter=container1.length()-1;
    if(t_stamp==container1.length()-1)
    {
      return temp2;
    }
    if(t_stamp<container1.length()-1)
    {
        for(int i=0;i<(container1.length()-t_stamp-1);i++)
        {
         undo();
        }
        return temp2;
    }
    else
    {
        t_stamp=t_stamp-container1.length()+1;
        for(int i=0;i<t_stamp;i++)
        {
            redo();
        }
        return temp2;
    }*/
 VCS_node temp=container1.top();
 string line;
if(temp.time_stamp>t_stamp)
{
while(temp.time_stamp!=t_stamp)
{
line=undo();
temp=container1.top();
}
}
else
{
	while(temp.time_stamp!=t_stamp)
	{
	line=redo();
	temp=container1.top();
	}
}
return line;
}

#endif
