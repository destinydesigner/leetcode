class Solution {
private:
    // Why the last argument is count, not position?
    // Because, count is convenient to cut down, position can't cut down.
    double findkth(int A[], int m, int B[], int n, int count)
    {
        if ( m > n )
        {
            return findkth(B, n, A, m, count);
        }
        // First Boundary Condition
        if ( m == 0 )
        {
            return B[count - 1];
        }

        // Second Boundary Condition
        if ( count == 1 )
        {
            return A[0] > B[0] ? B[0] : A[0];
        }

        int pa = (count / 2) > m ? m : (count / 2) , pb = count - pa;
        if ( A[pa-1] > B[pb-1] )
        {
            return findkth(A, m, B + pb, n - pb, count - pb);
        }
        else if ( A[pa-1] < B[pb-1] )
        {
            return findkth(A + pa, m - pa, B, n, count -pa);
        }
        else
        {
            // Third Boundary Condition
            return A[pa-1];
        }
    }

public:
    double findMedianSortedArrays(int A[], int m, int B[], int n) {
        // IMPORTANT: Please reset any member data you declared, as
        // the same Solution instance will be reused for each test case.
        int total = ( m + n );

        if ( total & 1)
        {
            return findkth(A, m, B, n, total / 2 + 1);
        }
        else
        {
            return (findkth(A, m, B, n, total / 2) + findkth(A, m, B, n, total / 2 + 1)) / 2;
        }
    }
};
