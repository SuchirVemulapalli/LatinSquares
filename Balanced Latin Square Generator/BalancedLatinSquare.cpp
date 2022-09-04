#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;


/*Time Complexity of main(): O(n) from for-loop #1, O(n) from for-loop #2, O(n^2) from nested for loop, 
equates to O(n+n+n^2)=O(2n+n^2)=O(n^2) */

/*Time Complexity of balancedLatinSquare(): Recurs n times with for loop being called recursively results in O(n*n)=O(n^2)
*/

int conditions;
vector<vector<int>> balancedLatin;

vector<vector<int>> balancedLatinSquare(vector<int> vect);


int main(){
	ios_base::sync_with_stdio(false);
	vector<vector<int>> result;
	vector<int> nums;

	cout<<"Enter the dimension/# of conditions for the balanced latin square:"<<endl;
	cin>>conditions;

	cin.ignore(std::cin.rdbuf()->in_avail());

	for(int i = 0; i<conditions; ++i){
		nums.push_back(i+1);
	}

	if(conditions % 2 != 0){
		conditions *= 2;
	} 

	for(int i = 0; i<conditions; i++){
		balancedLatin.push_back(vector<int> ());
	}

	result = balancedLatinSquare(nums);

	for(int i = 0; i<result.size(); ++i){
		for(int j = 0; j<result[i].size(); ++j){
			cout << " " << result[i][j] << " ";
		}
		cout<<endl;
	}

	cout << "Press enter to exit the program" << endl;

	cin.ignore();

	return 0;
}


vector<vector<int>> balancedLatinSquare(vector<int> vect) {

	for(int permutations = 0; permutations<conditions; permutations++){
		for (int i = 0, j = 0, h = 0; i < vect.size(); ++i) {
			int val = 0;
			if (i < 2 || i % 2 != 0) {
				val = j++;
			} else {
				val = vect.size() - h - 1;
				++h;
			}

			int idx = (val + permutations) % vect.size();
			balancedLatin[permutations].push_back(vect[idx]);

		}

		if (vect.size() % 2 != 0 && permutations % 2 != 0) {
			 reverse(balancedLatin[permutations].begin(),balancedLatin[permutations].end());	
			}
		}

		return balancedLatin;

}
