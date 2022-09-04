#include <iostream>
#include <algorithm>
#include <vector>
#include <stdlib.h>
#include <ctime>
#include <cmath>
#include <numeric>

#define UNASSIGNED 0

using namespace std;
vector<vector<int>> partialLatin;
bool valid = true;
bool init = false;
void performChecks(int dimension, vector<vector<int>> partialLatin);
bool validPlacement(vector<vector<int>> partialLatin, int dimension, int row, int col, int k);
bool solveLatinBrute(int dimension, vector<vector<int>> &partialLatin, int row, int col);
bool validPlacement2(int i,int j,int number, vector<int> &row, vector<int> &col);
void setInitialValues(vector<vector<int>> &partialLatin, int dimension, vector<int> &row, vector<int> &col);
bool solveLatinBitmask(vector<vector<int>> &partialLatin ,int i, int j, int dimension, vector<int> &row, vector<int> &col);
bool GetUnassigned(vector<vector<int>> &partialLatin, int &row, int &col, int dimension);
bool UsedInRow(vector<vector<int>> &partialLatin, int row, int num, int dimension);
bool UsedInCol(vector<vector<int>> &partialLatin, int col, int num, int dimension);
bool isSafe(vector<vector<int>> &partialLatin, int row, int col, int num, int dimension);
bool solveLatinBacktracking(vector<vector<int>> &partialLatin, int dimension);




int main(){
	int dimension;
	cout<<"Enter the dimension of the partially row filled latin square"<<endl;
	cin>>dimension;
	vector<int> row(dimension);
	vector<int> col(dimension);


	for(int i = 0; i<dimension; i++){
		partialLatin.push_back(vector<int> ());
	}
	cout<<endl;
	cout<<"Enter the partially row filled latin square and denote empty entries with 0. Data must be entered row by row, left to right, and have spaces between each entry. "<<endl;
	for(int i = 0; i<dimension; i++){
		for(int j = 0; j<dimension; j++){
			int entry;
			cin>>entry;
			partialLatin[i].push_back(entry);
		}
	}
	cout<<endl;

	cout<<"The partially row filled latin square appears as below."<<endl;

	for(int i = 0; i<partialLatin.size(); ++i){
		for(int j = 0; j<partialLatin[i].size(); ++j){
			cout << " " << partialLatin[i][j] << " ";;
		}
		cout<<endl;
	}

	cout<<endl;

	performChecks(dimension, partialLatin);

	if(valid){
		if(solveLatinBacktracking(partialLatin, dimension)){  //Change the function call from solveLatinBacktracking to solveLatinBitmask with appropriate parameters to change the approach used to solve the Latin Square
			cout<<"The solved latin square appears as below.";
			cout<<endl;
			for(int i = 0; i<partialLatin.size(); ++i){
				for(int j = 0; j<partialLatin[i].size(); ++j){
					cout << " " << partialLatin[i][j] << " ";;
				}
			cout<<endl;
			}

		}

	}



	


}

void performChecks(int dimension, vector<vector<int>> partialLatin){

	for(int i = 0; i < dimension; i++){
		for(int j = 0; j<dimension; j++){
			if(partialLatin[i][j]==0 && accumulate(partialLatin[i].begin(), partialLatin[i].end(), 0) !=0 ){
				cout<<"The latin square is not partially row filled. The square contains a zero entry in the nonzero row "<<i+1<<". Try again!"<<endl;
				valid = false;;
				return;

			}
		}
	}

	vector<vector<int>> temp = partialLatin;

	for(int i = 0; i < dimension; i++){
		sort(temp[i].begin(), temp[i].end());
		for(int j = 0; j<dimension-1; j++){
			if(temp[i][j]==temp[i][j+1] && accumulate(temp[i].begin(), temp[i].end(),0)!=0){
				cout<<"The latin square is not partially row filled. The square contains a duplicate in row "<<i+1<<". Try again!"<<endl;
				valid = false;;
				return;

			}
		}

	}

	for(int j = 0; j<dimension; j++){
		for(int i = 0; i<dimension; i++){
				int num = partialLatin[i][j];
				for(int row = i+1; row<dimension; row++){
					if((num==partialLatin[row][j])&&(num!=0)){
						cout<<"The latin square is not partially row filled. There is a duplicate in column "<<j+1<<". Try again!"<<endl;
						valid = false;
						return;
					}
				}

		}
	}


	for(int i = 0; i<dimension; i++){
		int rowsum = accumulate(partialLatin[i].begin(), partialLatin[i].end(), 0);
		float correctsum = dimension;
		correctsum = (correctsum/2)*(correctsum+1);
		if(rowsum != correctsum && rowsum != 0){
			cout<<"The latin square is not partially row filled. The square contains an incorrect sequence of numbers in row "<<i+1<<". Try again!"<<endl;
			valid = false;;
			return;
		}
		
	} 

	return;

} 



bool validPlacement(vector<vector<int>> partialLatin, int dimension, int row, int col, int k){
	for(int j = 0; j<dimension; j++){
		if(k==partialLatin[row][j]){
			return false;
		}

	}

	for(int i = 0; i<dimension; i++){
		if(k==partialLatin[i][col]){
			return false;
		}
	}

	return true;
}


bool solveLatinBrute(int dimension, vector<vector<int>> &partialLatin, int row, int col){
	if(row == dimension-1 && col == dimension){
		return true;
	}

	if(col == dimension){
		row++;
		col = 0;
	}

	if(partialLatin[row][col] > 0){
		return solveLatinBrute(dimension, partialLatin, row, col+1);
	}

	for(int k = 1; k<= dimension; k++){

		if(validPlacement(partialLatin, dimension, row, col, k) == true){
			partialLatin[row][col]=k;
			if(solveLatinBrute(dimension,partialLatin,row,col+1) == true){
				return true;
			}

		}

		partialLatin[row][col] = 0;
	}
	return false;
}




bool validPlacement2(int i,int j,int number, vector<int> &row, vector<int> &col)
{
    return !((row[i] >> number) & 1) 
    	&& !((col[j] >> number) & 1);
        
}
 

void setInitialValues(vector<vector<int>> &partialLatin, int dimension, vector<int> &row, vector<int> &col)
{
    for (int i = 0; i < dimension; i++){
        for (int j = 0; j < dimension; j++){
                row[i] |= 1 << partialLatin[i][j], 
                col[j] |= 1 << partialLatin[i][j];

            }
    }

}	
 

bool solveLatinBitmask(vector<vector<int>> &partialLatin ,int i, int j, int dimension,vector<int> &row, vector<int> &col)
{
   
    if(!init)
        init = true,
        setInitialValues(partialLatin, dimension, row, col);
 
    if(i == dimension - 1 && j == dimension)
        return true;
    if(j == dimension)
        j = 0,
    	i++;
 
    if(partialLatin[i][j])
        return solveLatinBitmask(partialLatin, i, j + 1, dimension, row, col);
 
    for (int k = 1; k <= dimension;k++)
    {
        if(validPlacement2(i, j, k, row, col))
        {
            
            partialLatin[i][j] = k;
            row[i] |= 1 << k;
            col[j] |= 1 << k;
 
            if(solveLatinBitmask(partialLatin, i,j + 1, dimension, row, col))
                return true;
 
            
            row[i] &= ~(1 << k);
            col[j] &= ~(1 << k);
        }
 
        partialLatin[i][j] = 0;
    }
 
  return false;
}
 


bool GetUnassigned(vector<vector<int>> &partialLatin, int &row, int &col, int dimension)
{
    for (row = 0; row < dimension; row++)
        for (col = 0; col < dimension; col++)
            if (partialLatin[row][col] == UNASSIGNED)
                return true;
    return false;
}
 

bool UsedInRow(vector<vector<int>> &partialLatin, int row, int num, int dimension)
{
    for (int col = 0; col < dimension; col++)
        if (partialLatin[row][col] == num)
            return true;
    return false;
}
 

bool UsedInCol(vector<vector<int>> &partialLatin, int col, int num, int dimension)
{
    for (int row = 0; row < dimension; row++)
        if (partialLatin[row][col] == num)
            return true;
    return false;
}
 



bool isSafe(vector<vector<int>> &partialLatin, int row,
            int col, int num, int dimension)
{
    
    return !UsedInRow(partialLatin, row, num, dimension) && !UsedInCol(partialLatin, col, num, dimension) && partialLatin[row][col] == UNASSIGNED;
}


bool solveLatinBacktracking(vector<vector<int>> &partialLatin, int dimension)
{
    int row;
    int col;
 

    if (!GetUnassigned(partialLatin, row, col, dimension))
        return true;
 
    for (int num = 1; num <= dimension; num++)
    {
         
        if (isSafe(partialLatin, row, col, num, dimension))
        {
             
            partialLatin[row][col] = num;

            if (solveLatinBacktracking(partialLatin, dimension))
                return true;
 

            partialLatin[row][col] = UNASSIGNED;
        }
    }
    

    return false;
}
 
