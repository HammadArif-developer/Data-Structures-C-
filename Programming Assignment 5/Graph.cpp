#ifndef GRAPH__CPP
#define GRAPH__CPP
#include "Graph.h"
#include<fstream>
#include<bits/stdc++.h>


Graph::Graph(string file, bool isUnitLength=false)
{
	ifstream infile;
	infile.open(file);
	string name;
	getline(infile,name);
	int counter=0;
	while(counter<20)
	{
		getline(infile,name);
		istringstream ss(name);
		string n;
		ss>>n;
		node* temp=new node;
		temp->name=n;
		cities.push_back(temp);
		counter++;
	}
	string edges;
	getline(infile,edges);
	bool check=true;
	while(check)
	{
		getline(infile,edges);
		vector<string> sep;
		istringstream ss(edges);
		string w1,w2;
		float w;
		ss>>w1;
		ss>>w2;
		ss>>w;
		edge temp2;
		node* temp2_node;
		for(int i=0;i<cities.size();i++)
		{
			string ch=cities[i]->name;
			if(w1==ch)
			{
				temp2_node=cities[i];
				temp2.Origin=temp2_node;
			}
			else if(w2==ch)
			{
				temp2_node=cities[i];
				temp2.Dest=temp2_node;
			}
		}
		if(isUnitLength==false)
		{
			temp2.weight=w;
		}
		else
		{
			temp2.weight=1.00;	
		}
		arcs.push_back(temp2);
		if (w1=="Perry" && w2=="Ariana")
		{
			check=false;
		}
	}
	infile.close();
	for(int i=0;i<arcs.size();i++)
	{
		for(int j=0;j<cities.size();j++)
		{
			if(arcs[i].Origin->name==cities[j]->name)
			{
				cities[j]->edges.push_back(arcs[i]);
			}
			else if(arcs[i].Dest->name==cities[j]->name)
			{
				edge temp;
				temp.Origin=arcs[i].Dest;
				temp.Dest=arcs[i].Origin;
				cities[j]->edges.push_back(temp);
			}			
		}
	}

}

void Graph::display(node* temp)
{
	if(temp->visit)
		return;
	
	cout << "Person: " << temp->name;
	temp->visit = 1;
	for(int i=0; i< temp->edges.size(); i++)
	{
		if(!temp->edges[i].Origin->visit || !temp->edges[i].Dest->visit)
		cout << "->" << temp->edges[i].weight << endl;
		display(temp->edges[i].Origin);
		display(temp->edges[i].Dest);
	}
}

bool Graph::Reachable(string start, string dest)
{
//using bfs because the graph data provided sparse so less time complexity in finding path using breath first search.
bool check1=false,check2=false;
for(int i=0;i<cities.size();i++)
{
	if(cities[i]->name==start)
	{
		check1=true;
	}
	if(cities[i]->name==dest)
	{
		check2=true;
	}
}
if(check1==false || check2==false)
{
	return false;
}
if(start==dest)
{
	return true;
}
node* temp;
for(int i=0;i<cities.size();i++)
{
	if(cities[i]->name==start)
	{
		temp=cities[i];
	}
	cities[i]->visit=0;
}
temp->visit=1;
list<node*> queue;
queue.push_back(temp);
while(!queue.empty())
{
temp=queue.front();
queue.pop_front();
for(int i=0;i<temp->edges.size();i++)
{
	if(dest==temp->edges[i].Dest->name)
	{
		return true;
	}
	if(temp->edges[i].Dest->visit==0)
	{
		temp->edges[i].Dest->visit=1;
		queue.push_back(temp->edges[i].Dest);
	}
}
}
return false;
}

vector<node*> Graph::Prims()
{

}

vector<node*> Graph::Kruskal()
{
// vector<node*> result;
// vector<edge> set;
// for (int i=0;i<arcs.size();i++)
// {
// 	for(int j=i+1;j<arcs.size();j++)
// 	{
// 		if(arcs[i]->weight>arcs[j]->weight)
// 		{
// 			edge temp;
// 			temp=arcs[i];
// 			arcs[i]=arcs[j];
// 			arcs[j]=temp;
// 		}
// 	}
// }
// int i=0;
// while(i<arcs.size())
// {

// }
for(int i=0;i<cities.size();i++)
{
	node* n=new node;
	n->name=cities[i]->name;
	cities[i]->visit=1;
	float minimum_weight=INT_MAX;
	int index=0;
	for(int j=0;j<cities[i]->edges.size();j++)
	{
		if(cities[i]->edges[j].Dest->visit==0)
		{
			if(cities[i]->edges[j].weight<minimum_weight)
			{
				minimum_weight=cities[i]->edges[j].weight;
				index=j;
			}
		}
	}
	n->edges.push_back(cities[i]->edges[index]);
	temp.push_back(n);
}
return temp;
}

vector<string> Graph::Dijkstra(string start, string dest, float &d)
{
node* temp;
for(int i=0;i<cities.size();i++)
{
	if(cities[i]->name==start)
	{
		temp=cities[i];
	}
	cities[i]->visit=0;
}
temp->visit=1;
vector<pair<node*,float>> dist;
vector<string> result;
for(int i=0;i<cities.size();i++)
{
	dist.push_back(make_pair(cities[i],INT_MAX));
}
class comparer{public: float operator ()(const pair<node*, float>&p1 , const pair<node*, float>&p2){return p1.second>p2.second;}};
priority_queue<pair<node*,float>,vector<pair<node*,float>>, comparer> p;
p.push(make_pair(temp,0));
for(int i=0;i<cities.size();i++)
{
	if(cities[i]->name==start)
	{
		dist[i].second=0;
	}
}
while(!p.empty())
{
	// for(int i=0;i<p.size();i++)
	// {
	// 	cout<<"lol ";
	// 	cout<<p[i].first->name<<p[i].second<<endl;
	// }
	node* temp=p.top().first;
	float w1=p.top().second;
	p.pop();
	cout<<temp->name<<" "<<w1<<endl;
	result.push_back(temp->name);
	for(int i=0;i<temp->edges.size();i++)
	{
		node *temp2=temp->edges[i].Dest;
		float w2=temp->edges[i].weight;
		int index;
		for(int i=0;i<cities.size();i++)
		{
			if(cities[i]->name==temp2->name)
			{
			d=dist[i].second;
			index=i;
			}
		}
		if(d>w1+w2)
		{
			dist[index].second=w1+w2;
			p.push(make_pair(temp2,dist[index].second));
		}
		if(temp2->name==dest)
		{
			result.push_back(temp2->name);
			d=dist[index].second;
			return result;
		}
		// else if(temp->edges[i].Dest->visit==0)
		// {
		// 	temp->edges[i].Dest->visit=1;
		// 	float d;
		// 	int index;
		// 	for(int j=0;j<dist.size();j++)
		// 	{
		// 		if(dist[j].first->name==temp->edges[i].Dest->name)
		// 		{
		// 			d=dist[j].second;
		// 			index=j;
		// 		}
		// 	}
		// 	if(d>w+temp->edges[i].weight)
		// 	{
		// 		dist[index].second=w+temp->edges[i].weight;
		// 		p.push(make_pair(temp->edges[i].Dest,dist[index].second));
		// 	}
		// }
	}
}
// return result;
}

int main()
{
	cout<<"Initialize your graph in main!"<<endl;
	// write code for part 6 here
	Graph g("friends.txt",false);
	g.display(g.cities[0]);
	cout<<endl<<"Mannan "<<"Ali "<<"Reachability "<<g.Reachable("Mannan","Ali")<<endl;
	cout<<endl<<"Mannan "<<"Trump "<<"Reachability "<<g.Reachable("Mannan","Trump")<<endl;
	cout<<endl<<"Ali "<<"Trump "<<"Reachability "<<g.Reachable("Ali","Trump")<<endl;
	float d;
	// vector<string> result=g.Dijkstra("Babar","Trump",d);
	vector<node*> result=g.Kruskal();
	for(int i=0;i<result.size();i++)
	{
		cout<<result[i]->name<<" "<<result[i]->edges[0].Dest->name<<" "<<endl;
	}
	//part 6
	// 1) all three Reachable
	// 2) 2hops
	// 3) 3hops
	// 4) Mannan
	// 5) yes there can be another minimum spanning tree because there are more than same weight edges.
}

#endif
