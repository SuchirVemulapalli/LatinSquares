#include <iostream>
#include <algorithm>
#include <vector>
#include <stdlib.h>
#include <ctime>
#include <cmath>

using namespace std;

#define ull unsigned long long int


ull factorial(int n);
ull latinLowerBound(int dimension);
ull latinUpperBound(int dimension);
void printLatin(vector<vector<int>> finalLatin);
vector<vector<int>> generateStandardLatin(int dimension);
vector<vector<int>> generatePermutation(int dimension, vector<vector<int>> permutedLatin);
void keepPermuting(int dimension, vector<vector<int>> permutedLatin); 

vector<vector<vector<int>>> allLatins;
ull vector3dlength = 0;


int main(){
	srand(time(0));
	int n;
	cout<<"Enter the dimension of the standard Latin Square"<<endl;
	cin>>n;
	vector<vector<int>> result;
	result = generateStandardLatin(n);
	allLatins.push_back(result);
	vector3dlength++;

	printLatin(result);

	cout<<endl;

	keepPermuting(n, result);

	return 0;
}

ull factorial(int n)
{
    ull f = 1;
    for (int i=1; i<=n; ++i){
        f *= i;
    }
    return f;
}

ull latinLowerBound(int dimension){
	ull n = factorial(dimension);
	ull numerator = pow(n, 2*dimension);
	ull denominatorPartial = pow(dimension, 2);
	ull denominator = pow(dimension,denominatorPartial);
	ull lowerBound = numerator/denominator;
	return lowerBound;
}

ull latinUpperBound(int dimension){
	ull product = 1;
	for(int i = 1; i <= dimension; i++){
		ull k = factorial(i);
		k = pow(k, (dimension/i));
		product = product * k;
	}
	return product;
}


void printLatin(vector<vector<int>> finalLatin){
	for(int i = 0; i<finalLatin.size(); ++i){
		for(int j = 0; j<finalLatin[i].size(); ++j){
			cout << " " << finalLatin[i][j] << " ";;
		}
		cout<<endl;
	}

	return;
}


vector<vector<int>> generateStandardLatin(int dimension){
	vector<vector<int>> standardLatin;
	for(int i = 0; i<dimension; i++){
		standardLatin.push_back(vector<int> ());
		for(int j = 0; j<dimension; j++){
			int x = j+1+i;
			if(x!=dimension){
				x %= dimension;
			}
			standardLatin[i].push_back(x);
		}
	}

	return standardLatin;

}

vector<vector<int>> generatePermutation(int dimension, vector<vector<int>> permutedLatin){

	int row1= rand() % dimension;
	int row2=row1;
	row2 = rand() % dimension;
	permutedLatin[row1].swap(permutedLatin[row2]);

	if(dimension==2){
		return permutedLatin;
	}

	int col1= rand() % dimension;
	int col2=col1;
	col2 = rand() % dimension;
	

	for(int i = 0; i<dimension; i++){
		int temp = permutedLatin[i][col1];
		permutedLatin[i][col1] = permutedLatin[i][col2];
		permutedLatin[i][col2] = temp;
	} 

	return permutedLatin;

}

void keepPermuting(int dimension, vector<vector<int>> permutedLatin){
	ull totalPermutations = factorial(dimension); //Change the function call from factorial to latinUpperBound or latinLowerBound to print up to the upper and lower bound respectively of possible nxn Latin Squares possible
	int realcount = 1;
	 for(ull count=1; count<totalPermutations; count++){
	 	bool canPrint = true;
		permutedLatin = generatePermutation(dimension, permutedLatin);


		for(int i = 0; i<vector3dlength; i++){
			if(permutedLatin==allLatins[i]){
				canPrint=false;
				totalPermutations++;

			}

		}



		if(canPrint){
			allLatins.push_back(permutedLatin);
			vector3dlength++;
			realcount++;
			cout<<"Permutation "<<realcount<<":"<<endl;
			printLatin(permutedLatin);
		}
	}


}

