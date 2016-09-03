#include <string>

using namespace std;

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        // IMPORTANT: Please reset any member data you declared, as
        // the same Solution instance will be reused for each test case.
        if (s.empty())
        {
            return 0;
        }
        int maxlen = 1, len = 1;
        int start = 0;
        int spos = 1;
        while(spos < s.length())
        {
            string tmp(s, start, len);
            std::size_t ret = tmp.find(s[spos]);
            if (ret == std::string::npos)
            {
                len++;
                maxlen = len > maxlen ? len : maxlen;
                spos++;
            }
            else
            {
                start++;
                len--;
            }
        }

        return maxlen;
    }
};

int main()
{
    Solution s;
    printf("%d\n", s.lengthOfLongestSubstring("wlrbbmqbhcdarzowkkyhiddqscdxrjmowfrxsjybldbefsarcbynecdyggxxpklorellnmpapqfwkhopkmco"));
}
