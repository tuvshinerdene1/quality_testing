#include <iostream>
using namespace std;
int main()
{
    int n, arr[n];
    cout << "N = ";
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cout << i << " = ";
        cin >> arr[i];
    }
    int index = 0;
    for (int i = 0; i < n; i++)
    {
        if (arr[i] < 0)
        {
            int temp = arr[i];
            for (int j = i; j > index; j--)
            {
                arr[j] = arr[j - 1];
            }
            arr[index] = temp;
            index++;
            continue;
        }
    }
    for (int i = 0; i < n; i++)
    {
        if (arr[i] == 0)
        {
            int temp = arr[i];
            for (int j = i; j > index; j--)
            {
                arr[j] = arr[j - 1];
            }
            arr[index] = temp;
            index++;
            continue;
        }
    }
    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
    return 0;
}