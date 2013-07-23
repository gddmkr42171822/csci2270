// 
// btree.cpp
//
// Your Name: Robert Werthman
// 
// Collaboration is not only encouraged, it is basically
// demanded. Work together! Share code!
//
// Just write down your main collaborators here:
// ...



#include "btree.h"

using namespace std;


void putvalueinrightplace(btree* &root, int key);
void splitfull_childnode(btree* &root, btree* &parent, int j);
void splitfull_rootnode(btree* &root);
void splitfull_childnoderootnode(btree* &root, btree* &parent, int h);
void swapkeys(btree* &root, btree* &parent, int i);

// -------------------------------------------- I N S E R T ---------
//
// Insert the given key into a b-tree rooted at 'root'.  If the key is
// already contained in the btree this should do nothing.  
// 
// On exit: 
// -- the 'root' pointer should refer to the root of the
//    tree. (the root may change when we insert or delete)
// -- the btree pointed to by 'root' is valid.
void insert(btree* &root, int key) {
	int i;
	bool is_there = contains(root, key);
	//if the tree is empty
	if ( root == NULL)
	{
		return;
	}
	//if the value is already there do nothing
	else if (is_there == true)
	{
		return;
	}
	else
	{
		

		//if the array in the node is not full and has no children...
		if (root->num_keys < BTREE_ORDER-1 && root->is_leaf == true)
		{
			//iterate through array
			int keysinarray = root->num_keys;
			for ( i = 0; i < keysinarray; i++)
			{
				int temp = root->keys[i];
				//check if the value we are looking for is less than any
				//of the values in the array.  Those values are swapped.
				if ( key < root->keys[i])
				{
					if( root->num_keys == 1)
					{
						
						root->keys[0] = key;
						root->keys[1] = temp;
						root->num_keys++;
						
						return;
					}
					else
					{
						int j;
						root->keys[i] = key;
						for (j = i; j < keysinarray; j++)
						{
						
							//the rest of the values are pushed right
							int temp1 = root->keys[j+1];
							root->keys[j+1] = temp;
							temp = temp1; 
						}
						root->num_keys++;
						return;
					}
				}
			}
			//the key is the larger value in the array, insert it into empty slot
			root->keys[keysinarray] = key;
			root->num_keys++;
		}
		
		//if inserting into a root node with an array that is full with no children
		else if (root->num_keys == BTREE_ORDER-1 && root->is_leaf == true)
		{
			
			putvalueinrightplace(root, key);
			splitfull_rootnode(root);
			
		}
			//insert into child of non full root node
		else if (root->num_keys < (BTREE_ORDER-1) && root->is_leaf == false)
		{
			//check if the child is full
			for(i = 0; i< root->num_keys;i++)
			{
				if(key<root->keys[i])
				{
					
					//if not full
					if(root->children[i]->num_keys < BTREE_ORDER-1)
					{	
						insert(root->children[i], key);
						return;
					}
					//otherwise the child is full and has no children
					else if(root->children[i]->num_keys == BTREE_ORDER-1 && root->children[i]->is_leaf == true)
					{
						
						putvalueinrightplace(root->children[i], key);
						splitfull_childnode(root->children[i],root, i);
						return;
					}
					//otherwise the child is full but has children
					//else if (root->children[i]->num_keys == BTREE_ORDER-1 && root->children[i]->is_leaf == false)
					//{
						//insert(root->children[i], key);
						//return;
					//}
				}
			}
			//otherwise the key needs to go to the end
			//if the end child is not full
			if (root->children[i]->num_keys < BTREE_ORDER-1)
			{
				insert(root->children[i], key);
				return;
			}
			//if the end child is full
			else
			{
				
				putvalueinrightplace(root->children[i], key);
				splitfull_childnode(root->children[i],root, i);
				return;
			}
		}
		//if the root node is full and has children
		else if( root->num_keys == BTREE_ORDER-1 && root->is_leaf == false)
		{
			
				for (i=0; i < root->num_keys; i++)
				{
					//if child is full
					if( key < root->keys[i] && root->children[i]->num_keys == BTREE_ORDER-1)
					{
						putvalueinrightplace(root->children[i], key);
						splitfull_childnoderootnode(root->children[i], root, i);
						return;
					}
					// other wise we can just insert into the child node
					else if( key < root->keys[i] && root->children[i]->num_keys < BTREE_ORDER-1)
					{
						insert(root->children[i],key);
						return;
					}
				}
				if(key > root->keys[i] && root->children[i]->num_keys == BTREE_ORDER-1)
				{
				 
					putvalueinrightplace(root->children[i], key);
					splitfull_childnoderootnode(root->children[i], root, i);
					return;
				}
				else if ( key > root->keys[i] && root->children[i]->num_keys < BTREE_ORDER-1)
				{
					insert(root->children[i], key);
					return;
				}
		
		}
	}
}

// -------------------------------------------- R E M O V E ---------
//
// Remove the given key from a b-tree rooted at 'root'. If the key is
// not in the btree this should do nothing.
//
// On exit:
// -- the 'root' pointer should refer to the root of the
//    tree. (the root may change when we insert or delete)
// -- the btree pointed to by 'root' is valid.
void remove(btree* &root, int key) {
	bool is_there = contains(root, key);
	if (root == NULL)
	{
		return;
	}
	else if (is_there == false)
	{
		return;
	}
	//otherwise the value is there
	else
	{
		//node is in root
		if ( root->is_leaf == true && root->num_keys > 0)
		{
			
			int i = 0;
			for(i = 0; i < root->num_keys; i++)
			{	
				if( root-> keys[i] == key)
				{
					//move all the values to the right of it left
					root->keys[i] = root->keys[i+1];
					root->keys[i+1] = root->keys[i+2];
				}
			}
			root->num_keys--;
			return;
		}
		//remove from a node that has children
		else if(root->is_leaf == false)
		{
			
			int i;
			for ( i = 0; i < root->num_keys; i++)
			{
				// if the key to be removed is in the root and the successor child can spare a key
				if ( root->keys[i] == key && root->children[i+1]->num_keys > 2)
				{
					//then take successor key and put it in place of key to be deleted
					root->keys[i] = root->children[i]->keys[0];
					return remove(root->children[i], key);
				}
				//if the key is possibly in the child and the child is a leaf
				else if( key < root->keys[i] && root->children[i]->is_leaf == true)
				{
					
					//if removing the key doesn't break and invariant
					if( root->children[i]->num_keys > 2)
					{
						return remove(root->children[i], key);
					}
					//if removing the key does break an invariant look for keys to swap
					else if ( root->children[i]->num_keys <= 2)
					{
						swapkeys(root->children[i], root, i);
						return remove(root->children[i], key);	
					}
				}
				else if ( key == root->keys[i] && root->is_leaf == false)
				{
					//shift the keys in the node to the left
					int l; 
					for(l = i; l < root->num_keys; l++)
					{
						root->keys[l] = root->keys[l+1];
					}
					root->num_keys--;
					//shift the child pointers over one
					for (l = i + 1; l < root->num_keys; l++)
					{
						root->children[l] = root->children[l+1];
					}
					
					return;
				}
				else if( key < root->keys[i] && root->children[i]->is_leaf == false)
				{
					int d;
					for (d = 0; d < root->children[i]->num_keys; d++)
					{
						
						if( key < root->children[i]->keys[d])
						{
							int j;
							//remove the key
							remove(root->children[i]->children[d], key);
							//insert a key from the root into the child next to it
							insert(root->children[i]->children[d-1], root->children[i]->keys[d-1]);
							//put remaining keys from child into left sibling
							for(j = 0; j <root->children[i]->children[d]->num_keys; j++)
							{
								insert(root->children[i]->children[d-1], root->children[i]->children[d]->keys[j]);
							}
							//replace pointer that the key was removed from with the the one next to it 
							root->children[i]->children[d] = root->children[i]->children[d+1];
							//remove the key that was inserted into the child from the root
							remove(root->children[i], root->children[i]->keys[d-1]);
							//copy values from root children into a temp node
							btree* temp = new btree;
							temp->is_leaf = true;
							temp->num_keys = 0;
							int o = 0;
							for( j = 0; j <= root->num_keys;j++)
							{
								int y;
								for( y = 0; y < root->children[j]->num_keys; y++)
								{
									temp->keys[o] = root->children[j]->keys[y];
									temp->num_keys++;
									o++;
								}
							}
							//copy children of the root children to temp node
							int v = 0;
							for( j = 0; j <= root->num_keys; j++)
							{
								int y;
								for( y = 0; y <= root->children[j]->num_keys; y++)
								{
									temp->is_leaf = false;
									temp->children[v] = root->children[j]->children[y];
									v++;
								}
							}
							//set root children to null
							for( j=0; j <= root->num_keys; j++)
							{
								root->is_leaf = true;
								root->children[j] = NULL;
							}
							//insert keys from temp into root
							for(j = 0; j < temp->num_keys; j++)
							{
								 insert(root, temp->keys[j]);
							}
							//assign pointers from temp to root
							for(j = 0; j < temp->num_keys+2; j++)
							{
								root->is_leaf = false;
								root->children[j] = temp->children[j];
							}
							return;
						}	
					}
				}
			}
					
		}
	}

	
}

// ----------------------------------------- C O N T A I N S --------
//
// Return true if any node accessed from the given root node contains
// the provided key value.
bool contains(btree* &root, int key) {
	
	if (root == NULL) {
    return false;
  }
  for (int i=0; i < root->num_keys; i++) {
    if (root->keys[i] == key) {
      return true;
    } else if (!root->is_leaf && root->keys[i] > key) {
      // if the key is larger than target, answer will be in child i
      return contains(root->children[i], key);
    }
  }
  if (!root->is_leaf && root->keys[root->num_keys-1] < key) {
    return contains(root->children[root->num_keys], key);
  }
	
	
	
  return false;
}


void splitfull_rootnode(btree* &root)
{
	//find median value in array
	int median = ((root->num_keys)/2);
	btree* arr1 = new btree;
	btree* arr2 = new btree;
	int i;
	int k = 0;
	//iterate through left side of array and input keys into new node
	for (i = 0; i < median; i++)
	{
		
		arr1->keys[i] = root->keys[i];
		arr1->is_leaf = true;
		k++;
		arr1->num_keys = k;
		
		
	}
	//iterate through right side of array and input keys into new node
	int j = 0;
	for (i = median+1; i <= root->num_keys;i++)
	{
		arr2->keys[j] = root->keys[i];
		arr2->is_leaf = true;
		arr2->num_keys = j;
		j++;
		
	}
	//move median number to end of array
	root->keys[root->num_keys-1] = root->keys[median];
	//move that number to the front of the array while getting rid of the other numbers
	for(i = root->num_keys-1; i > 0; i--)
	{
		root->keys[i-1] = root->keys[i];
	}
	root->children[0] = arr1;
	root->children[0]->num_keys = arr1->num_keys;
	root->children[1] = arr2;
	root->children[1]->num_keys = arr2->num_keys;
	root->num_keys = 1;
	root->is_leaf = false;
}


//splitting a node that is a child
void splitfull_childnode(btree* &root, btree* &parent, int f)
{
	//find median value in array
	int median = ((root->num_keys)/2);
	btree* arr1 = new btree;
	btree* arr2 = new btree;
	int i;
	int k = 0;
	//iterate through left side of array and input keys into new node
	for (i = 0; i < median; i++)
	{
		arr1->keys[i] = root->keys[i];
		arr1->is_leaf = true;
		k++;
		arr1->num_keys = k;
		
	}
	//iterate through right side of array and input keys into new node
	int j = 0;
	for (i = median+1; i <= root->num_keys;i++)
	{
		arr2->keys[j] = root->keys[i];
		arr2->is_leaf = true;
		arr2->num_keys = j;
		j++;
	}
	putvalueinrightplace(parent,root->keys[median]);
	parent->children[f] = arr1;
	btree* temp = parent->children[f+1];
	btree* temp1 = NULL;
	parent->children[f+1] = arr2;
	int b;
	
	 
	if( parent->num_keys < BTREE_ORDER)
	{
		for(b = f+1; b < parent->num_keys;b++)
		{
			temp1 = parent->children[b+1];
			parent->children[b+1] = temp;
			temp = temp1;
		}
	}
	
	
}



void splitfull_childnoderootnode(btree* &root, btree* &parent, int h)
{
	int t;
	btree* temp = new btree;
	btree* temp1 = new btree;
	temp->num_keys = 0;
	temp1->num_keys = 0;
	int median = ((root->num_keys)/2);
	putvalueinrightplace(parent, parent->children[h]->keys[median]);
	//copy all of the parent children except the one to be split
	for ( t = 0; t < h; t++)
	{
		temp->is_leaf = false;
		temp->keys[t] = parent->keys[t];
		temp->children[t] = parent->children[t];
		temp->num_keys++;
	}
	int s = 0;
	for ( t = h+1; t < BTREE_ORDER; t++)
	{
		temp1->is_leaf = false;
		temp1->keys[s] = parent->keys[t];
		temp1->children[s] = parent->children[t];
		temp1->num_keys++;
		s++;
	}
	//split the root which is the full child
	int median1 = ((root->num_keys)/2);
	btree* arr1 = new btree;
	btree* arr2 = new btree;
	int i;
	int k = 0;
	for (i = 0; i < median1; i++)
	{
		arr1->keys[i] = root->keys[i];
		arr1->is_leaf = true;
		k++;
		arr1->num_keys = k;
		
	}
	int j = 0;
	for (i = median1+1; i <= root->num_keys;i++)
	{
		arr2->keys[j] = root->keys[i];
		arr2->is_leaf = true;
		arr2->num_keys = j;
		j++;
	}
	
	splitfull_rootnode(parent);
	//add child pointers to parent
	if (h == 0)
	{
		parent->children[0]->is_leaf = false;
		parent->children[1]->is_leaf = false;
		parent->children[0]->children[0] = arr1;
		parent->children[0]->children[1] = arr2;
		parent->children[0]->children[2] = temp->children[0];
		parent->children[1]->children[0] = temp1->children[0];
		parent->children[1]->children[1] = temp1->children[1];
		parent->children[1]->children[2] = temp1->children[2];
		return;
	}
	else if( h == 1)
	{
		int n;
		for ( n = 0; n < h; n++)
		{
			parent->children[0]->is_leaf = false;
			parent->children[0]->children[n] = temp->children[n];
		}
		parent->children[0]->children[n] = arr1;
		parent->children[0]->children[n+1] = arr2;

		int d = 0;
		int c = 0;
		parent->children[1]->is_leaf = false;
	
		for ( c = h; c <= parent->children[1]->num_keys+1; c++)
		{
			parent->children[1]->children[d]= temp1->children[d];
			d++;
		}
		return;
	}
	else if (h == 3)
	{
		int p;
		for ( p = 0; p <= parent->children[0]->num_keys; p++)
		{
			parent->children[0]->is_leaf = false;
			parent->children[0]->children[p] = temp->children[p];
		}
		parent->children[1]->is_leaf = false;
		parent->children[1]->children[0] = arr1;
		parent->children[1]->children[1] =  arr2;
		parent->children[1]->children[2] = temp1->children[0];
		
		
		return;
		
	}
	else if ( h == 2)
	{
		int p;
		for ( p = 0; p <= parent->children[0]->num_keys; p++)
		{
			parent->children[0]->is_leaf = false;
			parent->children[0]->children[p] = temp->children[p];
		}
		parent->children[1]->is_leaf = false;
		parent->children[1]->children[0] =  arr2;
		parent->children[0]->children[2] = arr1;
		parent->children[1]->children[1] = temp1->children[0];
		parent->children[1]->children[2] = temp1->children[1];
	}
	else
	{
		parent->children[0]->is_leaf = false;
		parent->children[1]->is_leaf = false;
		parent->children[0]->children[0] = temp->children[0];
		parent->children[0]->children[1] = temp->children[1];
		parent->children[0]->children[2] = temp->children[2];
		parent->children[1]->children[0] = temp1->children[3];
		parent->children[1]->children[1] = arr1;
		parent->children[1]->children[2] = arr2;
		
	}
	
}



void swapkeys(btree* &root, btree* &parent, int i)
{
	// if the right sibling node is not null
		if(parent->children[i+1] != NULL )
		{
			//if it can spare a key
			if(parent->children[i+1]->num_keys > 2)
			{
				//take its first key and swap it with root key, move root key to original child
				int temp = parent->children[i+1]->keys[0];
				int temp1 = parent->keys[i];
				insert(root, temp1);
				parent->keys[i] = temp;
				remove(parent->children[i+1], parent->children[i+1]->keys[0]);
				return;
			}
		}
		else
		{
			//look to left child
			if(parent->children[i-1]->num_keys > 2)
			{
				int temp = parent->children[i-1]->keys[parent->children[i-1]->num_keys-1];
				int temp1 = parent->keys[i];
				insert(root, temp1);
				parent->keys[i] = temp;
				remove(parent->children[i-1], parent->children[i-1]->keys[0]);
				return;
			}
		}
				


}

void putvalueinrightplace(btree* &root, int key)
{
	int i;
	int keysinarray = root->num_keys;
	for ( i = 0; i < keysinarray; i++)
	{
		int temp = root->keys[i];
		//insert value into array in the right order
		if (key<root->keys[i])
		{
			int j =i ;
			root->keys[i] = key;
			for (j = i; j < keysinarray; j++)
				{			
					//the rest of the values are pushed right
					int temp1 = root->keys[j+1];
					root->keys[j+1] = temp;
					temp = temp1; 
				}
				root->num_keys++;
				return;
		}
	}
	root->keys[i] = key;
	root->num_keys++;
}


