#include <iostream>
#include <vector>

using namespace std;


struct treeNode 
{
	int value;
	vector <treeNode*> *children;

	static vector<treeNode*> DEFAULT_VECTOR;
	treeNode(int value,  vector <treeNode*> *children =NULL)
	{
		this->value = value; this->children = children;
	}
	
};

void dfs(treeNode* root)
{
	if(root!=NULL )
	{
		cout<<root->value;
		cout<<endl;
	}

	
	if (root->children!=NULL)
	{
		
		for (vector<treeNode*>::iterator it = (*root->children).begin() ; it != (*root->children).end(); ++it)
		 {
			 
			 dfs (*it);
		}
		cout<<endl;
	}
}


int main ()
{

	treeNode* l1 = new treeNode (2);
	treeNode* l2 = new treeNode (10);
	treeNode* l3 = new treeNode (7);
	treeNode* l4 = new treeNode (1);
	treeNode* l5 = new treeNode (5);
	treeNode* l6 = new treeNode (8);

	vector <treeNode*> end1;
	end1.push_back(l1);
	end1.push_back(l2);
	end1.push_back(l3);

	vector <treeNode*> end2 ;
	end2.push_back(l4);
	end2.push_back(l5);
	end2.push_back(l6);

	treeNode* middle1 = new treeNode (4,&end1);
	treeNode* middle2 = new treeNode (12,&end2);
	vector <treeNode*> middle;
	middle.push_back(middle1);
	middle.push_back(middle2);

	treeNode* root = new treeNode(14, &middle);
	
	dfs(root);
}