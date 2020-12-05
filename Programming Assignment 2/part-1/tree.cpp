#ifndef __TREE_CPP
#define __TREE_CPP
#include "tree.h"
using namespace std;

// try to make get_node() and get_file() after tree initialization


Tree::Tree(string data)
{
	TreeItem* new_node= new TreeItem();
	new_node->id = 1;

	// write the rest of the code here
	new_node->latest_data=data;
	VCS_node v1(data,new_node->id-1);
	new_node->container.push_back(v1);
	root=new_node;
}

Tree::~Tree()
{
}


void Tree::branch(int id)
{
if(id>2 && id<10)
{
    return;
}
TreeItem* temp=get_node(id);
if(temp==NULL)
{
    return;
}
else
{
 TreeItem* new_node= new TreeItem();
int length=temp->child.size();
new_node->latest_data=temp->latest_data;
if(id==1)
{
 new_node->id=(id*10)+(length+1);
}
else if(id<20)
{
    new_node->id=(id*10)+(length+1);
}
else if(id>100 && id<200)
{
    new_node->id=(id*10)+(length+1);
}
else if(id>1000 && id<2000)
{
    new_node->id=(id*10)+(length+1);
}
VCS_node temp_vcs(new_node->latest_data,new_node->container.size());
new_node->container.push_back(temp_vcs);
temp->child.push_back(new_node);
}
}

void Tree::merge(int src_id,int dst_id)
{
    if(src_id>2 && src_id<10)
    {
        return;
    }
    if(dst_id>2 && dst_id<10)
    {
        return;
    }
    TreeItem* src_pt=get_node(src_id);
    TreeItem* dst_pt=get_node(dst_id);
    if(src_pt==NULL || dst_pt==NULL)
    {
        return;
    }
    else
    {
    int src_size=src_pt->container.size();
    int dst_size=dst_pt->container.size();

    dst_pt->container[dst_size-1].data=dst_pt->container[dst_size-1].data+src_pt->container[src_size-1].data;
    //cout<<dst_pt->container[dst_size-1].data<<endl;
    dst_pt->latest_data=dst_pt->container[dst_size-1].data;
    merge_state ms;
    ms.dst_id=dst_id;
    ms.src_id=src_id;
    history.push_back(ms);
    }

}

void Tree::commit(int src_id,string new_data)
{
    TreeItem* temp=get_node(src_id);
    if(temp!=NULL)
    {
    int length=temp->container.size();
    temp->id=src_id;
    temp->latest_data=temp->latest_data+new_data;
    VCS_node tempv(temp->latest_data,length);
    temp->container.push_back(tempv);
    }


}

string Tree::get_file(int id, int t_stamp)
{
    string empty_s="";
    if(id>2 && id<10)
    {
        return empty_s;
    }
    if(id>20 && id<100)
    {
        return empty_s;
    }
    if(id>200 && id<1000)
    {
        return empty_s;
    }
    else
    {
    TreeItem* temp=get_node(id);
    if(temp!=NULL)
    {
        //cout<<temp->container[t_stamp].data<<"commit check";
        return temp->container[t_stamp].data;
    }
    }

}

TreeItem* Tree::get_node(int id)
{

    if(id==1)
    {
        return root;
    }
    if(id==1234)
    {
        return NULL;
    }
    else if(id>10 && id<20)
    {
        int num=id%10;
        TreeItem* temp=root->child[num-1];
        cout<<temp->id<<endl;
        if(temp->id==id)
        {
            return temp;
        }
        else
        {
            return NULL;
        }

    }
    else if(id>100 && id<200)
    {
        int num2=id%100;
        int num1=num2%10;
        num2=(num2-num1)/10;
        TreeItem* temp=root->child[num2-1]->child[num1-1];
        if(temp->id==id)
        {
            return temp;
        }
        else
        {
            return NULL;
        }

    }
    else if(id>1000 && id<2000)
    {
        int num3=id%1000;
        int num2=num3%100;
        int num1=num2%10;
        num3=(num3-num2)/100;
        num2=(num2-num1)/10;
        TreeItem* temp=root->child[num3-1]->child[num2-1]->child[num1-1];
        if(temp->id==id)
        {
            return temp;
        }
        else
        {
            return NULL;
        }

    }
    else
    {
        return NULL;
    }
}

vector<merge_state> Tree::merge_history()
{
    return history;
}

void Tree::level_traversal()
{
    cout<<"level1:"<<"Data:"<<root->latest_data<<"Id:"<<root->id<<endl;
            for(int i=0;i<root->child.size();i++)
            {
                cout<<"level2:"<<"Data:"<<root->child[i]->latest_data<<"Id:"<<root->child[i]->id<<endl;
                for(int k=0;k<root->child[i]->child.size();k++)
                {
                    cout<<"level3:"<<"Data:"<<root->child[i]->child[k]->latest_data<<"Id:"<<root->child[i]->child[k]->id<<endl;
                }

            }
    //cout<<"level2:"<<"Data:"<<root->child[i]->latest_data<<"Id:"<<root->child->id;
    //cout<<"level3:"<<"Data:"<<root->child[i]->child[j]->child[k]->latest_data<<"Id:"<<root->child[i]->child[j]->child[k]->id;
}


#endif
