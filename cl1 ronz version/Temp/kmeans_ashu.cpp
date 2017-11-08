#include <iostream>
#include<math.h>
using namespace std;

class node
{
	float x,y,cluster;
public:
	node() {cluster = 0; x = 0; y = 0;}
	void setdata(float,float);
	float getx();
	float gety();
	void setcluster(float);
	float getcluster();
};

float node :: getcluster()
{
	return cluster;
}

void node :: setcluster(float c)
{
	cluster = c;
}

void node :: setdata(float x1, float y1)
{
	x = x1;
	y = y1;
}

float node :: getx()
{
	return x;
}

float node :: gety()
{
	return y;
}

float distance(node n1, float x, float y)
{
	return sqrt(((n1.getx()-x)*(n1.getx()-x)) + ((n1.gety()-y)*(n1.gety()-y)));
}

int main()
{
	//declaration
	int n,num,k;
	float x,y,min;

	//get data
	cout << "Enter the no. of nodes (less than 20)" << endl;
	cin >> n;
	node p[n];
	for(int i = 0; i < n; i++)
	{
		cout << "For node " << i << endl << "\tEnter the x-cordinate" << endl << "	";
		cin >> x;
		cout << "\tEnter the y-cordinate" << endl << "	";
		cin >> y;
		p[i].setdata(x,y);
	}
	cout << "Enter the no. of clusters" << endl;
	cin >> k;

	//check feasibility (optional)
	if(n < k || k <= 1)
	{
		cout << "Invalid input" << endl;
		return 0;
	}
	else if(n == k)
	{
		cout << "Every node is a cluster" << endl;
		return 0;
	}

	float x1[k],y1[k];				//to store cluster centers
	float checkx[k],checky[k];			//to store cluster centers of previous iteration of while loop

	//select random cluster points (first k points)
	for(int i = 0; i < k; i++)
	{
		p[i].setcluster(i);
		x1[i] = p[i].getx();
		y1[i] = p[i].gety();
		checkx[i] = p[i].getx();
		checky[i] = p[i].gety();
	}

	while(true)
	{
		//calc. distances from each to cluster center and accordingly assign clusters to points
		for(int i = 0; i < n; i++)
		{
			min = 99;
			for(int j = 0; j < k; j++)
			{
				if(min > distance(p[i],x1[j],y1[j]))
				{
					min = distance(p[i],x1[j],y1[j]);
					p[i].setcluster(j);
				}
			}
		}

		//get center of clusters as avg. of all points in that cluster
		for(int i = 0; i < k; i++)
		{
			x = 0;
			y = 0;
			num = 0;
			for(int j = 0; j < n; j++)
				if(p[j].getcluster() == i)
				{
					x += p[j].getx();
					y += p[j].gety();
					num++;
				}
			x1[i] = x/num; 
			y1[i] = y/num;
		}

		//check repeat condition (if old center of cluster and new are same or not)
		bool done = true;
		for(int i = 0; i < k; i++)
		{
			if(x1[i] != checkx[i] || y1[i] != checky[i])
				done = false;
			checkx[i] = x1[i];
			checky[i] = y1[i];
		}

		if(done)
			break;
	}

	// display all node clusters
	for(int i = 0; i < n; i++)
		cout << "x = " << p[i].getx() << ";  y = " << p[i].gety() << ";  cluster = " << p[i].getcluster() << endl;

	return 0;
}
