/*

  sorting.cpp

  Please refer to sorting.h for documentation on each function.

  Your Name:
  Your TA: 
  List O' Collaborators:
  * Jane, Ian, Steven, Internet (my very best friend)
  * http://mathbits.com/MathBits/CompSci/Arrays/Bubble.htm
  * http://www.algolist.net/Algorithms/Sorting/Bubble_sort
  * http://www.youtube.com/watch?v=IFJi_P68iKk
  * http://www.youtube.com/watch?v=AoVs1s0kfhE
  * http://rosettacode.org/wiki/Sorting_algorithms/Bubble_sort
  * http://www.algolist.net/Algorithms/Sorting/Quicksort
  * http://www.reviewmylife.co.uk/blog/2008/06/25/quicksort-code-in-c/
  * http://mathbits.com/MathBits/CompSci/Arrays/Merge.htm
  * http://en.wikibooks.org/wiki/Algorithm_implementation/Sorting/Merge_sort#C.2B.2B
  * http://forums.codeguru.com/showthread.php?419167-mergesort-with-vectors
  * http://www.youtube.com/watch?v=6pyeMmJTefg
  * http://www.dusanjov.com/blog/insertion-sort-algorithm-source-code/


   + ------ N O T E: -- Big scary warning! ------------------------------
   |
   |    We clearly can't use unit testing to ensure that you're
   |    actually implementing the correct algorithm. I suppose we could
   |    write some complicated static analysis checker. But it is
   |    easier to just look at it with our eyeballs.
   |
   |    After the assignment is due, we will look at the most recent
   |    version of your implementation that got the highest score and
   |    make sure you're not doing something sneaky like using a
   |    standard library call to sort a vector.
   |
   |    Anyone caught doing this (even though it is kinda funny) will
   |    be given 0/15 on the assignment.
   |
   +-------------------------------------------------------------------- 

 */

#include "sorting.h"
#include <iostream>
#include <vector>
using namespace std;


void quicksort(vector<int> &data, int low_idx, int high_idx) {
	//checking if both lists of the vector have not been order yet
	if (low_idx < high_idx)
	{
		//setting pivot to middle of list
		int pivot_index = ((high_idx+low_idx)/2);
		//using quicksort partition to organize left and right side of list
		int newpivot = quicksort_partition(data, low_idx, high_idx, pivot_index);
		//organizing left side of list by calling quicksort recursively
		quicksort(data, low_idx, newpivot-1);
		//organziing right side of list by calling quicksor recursively
		quicksort(data, newpivot+1, high_idx);
	}
}
	

int quicksort_partition(vector<int> &data, int low_idx, int high_idx, int pivot_index) {
	//setting up a temp int to hold data
	int temp = 0;
	//swapping the data at the pivot with the data of high_idx, vice-versa
	temp = data[pivot_index];
	data[pivot_index] = data[high_idx];
	data[high_idx] = temp;
	//setting pivot to beginning of list
	pivot_index = low_idx;
	//iterating through list 
	for ( int i = low_idx; i < high_idx; i++)
		{
			//comparing data at i to data at high_idx, if less then data at i will swap with data at pivot
			if (data[i] < data[high_idx])
			{
				//swapping data at i with data at pivot
				temp = data[i];
				data[i] = data[pivot_index];
				data[pivot_index] = temp;
				//moving pivot along list
				pivot_index++;
			}
		}
		//swapping data at pivot with data at high_idx
		temp = data[pivot_index];
		data[pivot_index] = data[high_idx];
		data[high_idx] = temp;
	//returning pivot position
	return pivot_index;
}
void bubblesort(vector<int> &data) {
	int temp;//setting up a variable for the swap
	unsigned int size = data.size();//putting the size of the vector into a variable
	for (unsigned int j = size - 1;j > 0;j--)//repeats swap loop one less than vector size
		{
			for (unsigned int i = 0; i < size; i++)//runs through the vector and swaps elements
			{
				if (data[i] > data[i+1])//if lower order value is > higher order value those values will be swapped
				{
					temp = data[i];//setting temp to lower order value
					data[i] = data[i+1];//setting lower order value to higher order value position
					data[i+1] = temp;//setting higher order value to lower order position
				
				}
			}
			size--;//subtracting one from the size of the vector so swap goes through vector one less element each time
		}
		
}




void mergesort(vector<int> &data) {
	//int to middle of vector
	int mid;
	//making two vectors to hold elements of data vector
	vector<int> left;
	vector<int> right;
	//checking that data is not sorted already
	if (data.size() <= 1)
	{
		return;
	}
	else
	{
		//getting middle of data vec
		mid = data.size()/2;
		//putting elements into left side before mid
		for (int x = 0; x < mid; x++)
		{
			left.push_back(data[x]);
		}
		//putting elements from mid to end of data into right
		for (int x = mid; x < (int)data.size(); x++)
		{
			right.push_back(data[x]);
		}
	}
		//recursively calling mergesort to breakup both vectors of data
		//further then sorting and merging them into one vector
		mergesort(left);
		mergesort(right);
		data = merge(left, right);
		
}
	


vector<int> merge(vector<int> &left, vector<int> &right) {
	//vec to hold sorted right and left vecs
	vector<int> result;
	//checking to make sure left and right aren't empty
	while (left.size() > 0 && right.size() > 0)
	{
		//if value of left is <= value at right that value is put into
		//result and then deleted from left
		if (left[0] <= right[0])
		{
			//value put into result
			result.push_back(left[0]);
			//value deleted from left, left values then shift right
			left.erase(left.begin());
		}
		//deleting right value and putting it into result
		else if (left[0] > right[0])
		{
			result.push_back(right[0]);
			right.erase(right.begin());
		}
	}
	//if one vec still has elements then it is cleared out and
	//those elements are added to result
	while (left.size() > 0)
	{
		result.push_back(left[0]);
		left.erase(left.begin());
	}
	while (right.size () > 0)
	{
		result.push_back(right[0]);
		right.erase(right.begin());
	}
	//sorted vec is returned
	return result;
}

	
void mystery_sort(vector<int> &data) {
	//insertion sort
	int i, j, key;
	//used to iterate through vector
	for (i = 1; i <(int)data.size(); i++)
	{
		//setting key to value at ith position
		key = data[i];
		//setting j to value before ith position
		j = i - 1;
		//using while loop to check if j position is less than 0 meaning
		//value at j and i position are in right order
		//and checking if value at j is greater than key then more
		//swapping is necessary
		while (j >= 0 && data[j] > key)
		{
			//swapping data at spot before j with data at j
			data[j + 1] = data[j];
			//moving j backwards to check if values
			//are in order or more swapping needs to be done
			j--;
		}
		//swapping the value after j with the value at key
		data[j + 1] = key;
	}

}

