/*

*/
#include <iostream>
#include <vector>

struct course
{
    int num;
    int credit;
    int fee;
};
typedef struct course course;
int main()
{
    int n;
    std::cout << "n = ";
    std::cin >> n;
    std::vector<course> courses;
    for (int i = 0; i < n; i++)
    {
        course current;
        current.num = i + 1;
        std::cout << "credit of course " << i + 1 << ": ";
        std::cin >> current.credit;
        std::cout << "fee of course " << i + 1 << ": ";
        std::cin >> current.fee;
        courses.push_back(current);
    }
    int T;
    std::cout << "T = ";
    std::cin >> T;
    for (auto it = courses.begin(); it != courses.end(); /* No increment here */)
    {
        if (it->credit * it->fee > T)
        {
            it = courses.erase(it);
        }
        else
        {
            ++it;
        }
    }
    // for (int i = 0; i < n - 1; i++)
    // {
    //     int current = i;
    //     for (int j = i + 1; j < n; j++)
    //     {
    //         if (courses[j].credit >= courses[current].credit)
    //         {
    //             current = j;
    //         }
    //     }
    //     course temp = courses[i];
    //     courses[i] = courses[current];
    //     courses[current] = temp;
    // }
    for (int i = 0; i < courses.size(); i++)
    {
        std::cout << courses[i].credit << std::endl;
    }

    return 0;
}