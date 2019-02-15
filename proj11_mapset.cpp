#include<iostream>
using std::cout; using std::endl; using std::boolalpha;
#include<string>
using std::string;
#include<sstream>
using std::ostringstream;


#include "proj11_mapset.h"


int main(){

    MapSet<string,long> ms1({ {"bill",1},{"alan",2},{"abby",3} });
    MapSet<string, long> ms2({ {"alan",4},{"abby", 5},{"john",7} });
    MapSet<string, long> ms3({ {"abby",5}, {"alan",17} });
    
    MapSet<string,long> ms_union = ms1.mapset_union(ms2);
    ostringstream oss;
    oss << ms_union;
    string result1 = oss.str();
    cout << "your answer: "<<result1 << endl;
    string ans1 = "abby:3, alan:2, bill:1, john:7";
    cout << "right answer: " <<ans1 << endl;
    //ASSERT_EQ(result1, ans1);

    ms_union = ms2.mapset_union(ms1);
    //oss.str("");
    //oss << ms_union;
    string result2 = oss.str();
    cout << "your answer: "<<result2 << endl;

    string ans2 = "abby:5, alan:4, bill:1, john:7";
    cout << "right answer: " <<ans2 << endl;
    //ASSERT_EQ(ans2,result2);


}