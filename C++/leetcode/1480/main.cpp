#include <iostream>
#include <vector>
#include <initializer_list>
using namespace std; // para não precisar escrever std::vector, std::cout, etc

class Solution {
public:
    int runningSum(int &nums) {
        for (int i = 1; i < length(nums); i++) {
            nums[i] += nums[i - 1];
        }
        return nums;
    }

    

    int runningSumInt(int& nums) {
        for (size_t i = 1; i < nums.size(); i++) {
            nums[i] += nums[i - 1];
        }
        return nums;
    }
};

int main() {
    Solution solution;

    // Caso 1
    vector<int> nums1{3, 1, 2, 10, 1};
    cout << "Output for Case 1: ", solution.runningSum(nums1);

    // vector<int> result1 = solution.runningSum(nums1);
    // cout << "Output for Case 1: ";
    // for (int num : result1) {
    //     cout << num << " ";
    // }
    // cout << endl;

    // Caso 2
    int vetorEntrada02[4]={1,2,3,4};
    cout << "Output for Case 2: ", solution.runningSum(vetorEntrada02);

    vector<int> nums2 = {1, 1, 1, 1, 1};
    
    // vector<int> result2 = solution.runningSum(nums2);
    // cout << "Output for Case 2: ";
    // for (int num : result2) {
    //     cout << num << " ";
    // }
    // cout << endl;

    return 0;
}

