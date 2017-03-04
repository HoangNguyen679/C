#include <iostream>
#include <algorithm>
#include <vector>

void bucketSort(float list[], int n){
	std::vector<float> b[n];
	for(int i = 0; i < n; i++){
		int bi = n*list[i];           // index of bucket
		b[bi].push_back(list[i]);
	}

	for(int i = 0; i < n; i++)
		sort(b[i].begin(), b[i].end());
	int index = 0;
	for(int i = 0; i < n; i++)
		for(int j = 0; j < b[i].size(); j++)
			list[index++] = b[i][j];
}

int main(){
    float arr[] = {0.897, 0.565, 0.656, 0.1234, 0.665, 0.3434};
    int n = sizeof(arr)/sizeof(arr[0]);
    bucketSort(arr, n);
 
    std::cout << "Sorted array is \n";
    for (int i=0; i<n; i++)
       std::cout << arr[i] << " ";
   std::cout <<"\n";

   return 0;
}