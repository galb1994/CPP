//#include <iostream>
//#include <ctime>
//#include "my_set.h"
//#include "catch.hpp"
//#include <set>
//
//using std :: set;
//using std :: cout;
//using std :: endl;
//
//int main()
//{
//    std::srand((unsigned int) std::time(nullptr));
//    set<int> stdIntSet;
//    my_set<int> myIntSet;
//    int a = rand() % 100;
//    for (int i = 0; i < 500; ++i)
//    {
//        stdIntSet.insert(a).second == myIntSet.insert(a).second;
//        a = rand() % 100;
//    }
//    auto stdIt = stdIntSet.crbegin();
//    auto myIt = myIntSet.crbegin();
//    int count = 1;
//    for (; stdIt != stdIntSet.crend() || myIt != myIntSet.crend(); ++stdIt, ++myIt)
//    {
//        cout << (*stdIt == *myIt) << endl;
//        count ++;
//        cout << count << endl;
//    }
//}
//
