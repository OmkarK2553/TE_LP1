#include <bits/stdc++.h>
using namespace std;

int number(int a[], int n, int p, int k)
{
    sort(a, a + n);

    int ord[n] = {0};
    ord[0] = a[0];

    int val, i,j, ans = 0;

    if (ord[0] <= p)
        ans = 1;

    // Iterating through the first
    // K items and finding the
    // ordfix sum
    for (i = 1; i < k - 1; i++)
    {
        ord[i] = ord[i - 1] + a[i];

        // Check the number of items
        // that can be bought
        if (ord[i] <= p)
            ans = i + 1;
    }

    ord[k - 1] = a[k - 1];

    // Finding the ordfix sum for
    // the remaining elements
    for (i = k - 1; i < n; i++)
    {
        if (i >= k)
        {
            ord[i] += ord[i - k] + a[i];
        }

        // Check the number of items
        // that can be bought
        if (ord[i] <= p)
            ans = i + 1;
    }

    return ans;
}

// Driver code
int main()
{
    int n = 5;
    int arr[] = {2, 4, 3, 5, 7};
    int p = 11;
    int k = 2;

    cout << number(arr, n, p, k) << endl;

    return 0;
}