#include <algorithm>
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int> &numbers, int target) {
        // IMPORTANT: Please reset any member data you declared, as
        // the same Solution instance will be reused for each test case.
        vector<int> array(numbers.begin(), numbers.end());
        sort(numbers.begin(), numbers.end());

        for (int i = 0; true; i++)
        {
            int tmp = target - array[i];
            int index = search(numbers, tmp);
            if (index > 0)
            {
                vector<int> ret;
                ret.push_back(i+1);

                for (int j = 0; j < array.size(); j++)
                {
                    if (array[j] == tmp && j != i)
                    {
                        ret.push_back(j+1);
                        break;
                    }
                }

                return ret;
            }
        }
    }

private:
    // Classic Binary Search
    int search(vector<int> &numbers, int target) {
        int s = -1, e = numbers.size(), m;
        while (s + 1 < e)
        {
            m = (s + e) >> 1;
            if (numbers[m] > target)
            {
                e = m;
            }
            else if (numbers[m] < target)
            {
                s = m;
            }
            else
            {
                return m;
            }
        }
        return -1;
    }
};
