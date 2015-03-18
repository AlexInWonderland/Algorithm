//============================================================================
// Name        : avltree.cpp
// Author      : alex
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

#include <iostream>
using namespace std;
#define IS_FULL(ptr) (!ptr)

typedef struct
{
	int key;
}element;

typedef struct tree_node * tree_pointer;
struct tree_node
{
	tree_pointer left_child;
	element data;
	short int bf;
	tree_pointer right_child;
};

int unbalanced = false;
tree_pointer root = NULL;

void left_rotation(tree_pointer *parent, int *unbalanced)
{
	tree_pointer grand_child, child;
	child = (*parent)->left_child;
	if(child->bf==1)
	{
		/*LL*/
		(*parent)->left_child=child->right_child;
		child->right_child=*parent;
		(*parent)->bf=0;
		(*parent)=child;
	}
	else
	{
		/*LR*/
		grand_child=child->right_child;
		child->right_child=grand_child->left_child;
		grand_child->left_child=child;
		(*parent)->left_child=grand_child->right_child;
		grand_child->right_child=*parent;

		switch(grand_child->bf)
		{
		case 1:
			(*parent)->bf=-1;
			child->bf=0;
			break;
		case 0:
			(*parent)->bf=child->bf=0;
			break;
		case -1:
			(*parent)->bf=0;
			child->bf=1;

		}
		*parent=grand_child;
	}
	(*parent)->bf=0;
	*unbalanced=false;
}

void right_rotation(tree_pointer *parent, int *unbalanced)
{
	tree_pointer child, grand_child;
	child=(*parent)->right_child;
    if(child->bf==-1)
    {
    	/*RR*/
    	(*parent)->right_child=child->left_child;
    	child->left_child=*parent;
    	(*parent)->bf=0;
    	*parent=child;
    }
    else
    {
    	/*RL*/
       grand_child=child->left_child;
       (*parent)->right_child=grand_child->left_child;
       child->left_child=grand_child->right_child;
       grand_child->left_child=*parent;
       grand_child->right_child=child;
       switch(grand_child->bf)
       {
       case 1:
    	    (*parent)->bf=0;
    	    child->bf=-1;
    	  break;
       case 0:
    	   (*parent)->bf=child->bf=0;
          break;
       case -1:
    	   (*parent)->bf=1;
    	   child->bf=0;

       }
       *parent=grand_child;
    }
    (*parent)->bf=0;
    *unbalanced=false;
}

void avl_insert(tree_pointer *parent, element x, int *unbalanced)
{
   if(!(*parent))
   {
	   *unbalanced = true;    //why?
	   (*parent) = (tree_pointer) malloc(sizeof(tree_node));
	   (*parent)->data=x;
	   (*parent)->right_child=(*parent)->left_child=NULL;
	   (*parent)->bf=0;

   }
   else if((*parent)->data.key > x.key)
   {
	   avl_insert(&((*parent)->left_child),x,unbalanced);
	   if(*unbalanced)
	   {
		   switch((*parent)->bf)
		   {
		   case -1:
			   *unbalanced = false;
			   (*parent)->bf=0;
		     break;
		   case 0:
			   (*parent)->bf=1;
			 break;
		   case 1:
			   left_rotation(parent, unbalanced);

		   }

	   }

   }
   else if((*parent)->data.key < x.key)
   {
	   avl_insert(&((*parent)->right_child),x,unbalanced);
	   if(*unbalanced)
	   {
	   		   switch((*parent)->bf)
	   		   {
	   		   case 1:
	   			   *unbalanced = false;
	   			   (*parent)->bf=0;
	   		     break;
	   		   case 0:
	   			   (*parent)->bf=-1;
	   			 break;
	   		   case -1:
	   			   right_rotation(parent, unbalanced);

	   		   }

	   }
   }
   else
   {
	   *unbalanced = false;    //why
	   cout<<"data already exist"<<endl;
   }

}

void print(tree_pointer root)
{
	//cout<<"BBB"<<endl;
     if(root)
     {
    	 //cout<<"AAA"<<endl;
    	 print(root->left_child);
    	 cout<<root->data.key;
    	 print(root->right_child);
     }

}
element test[3] = {{1},{2},{3}};

int main() {
	//cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
    //element test[3];
    //test[0].key=2;
    //test[1].key=1;
    //test[2].key=3;
	for(int i=0;i<3;i++)
    	avl_insert(&root,test[i], &unbalanced);
    print(root);
	return 0;
}
