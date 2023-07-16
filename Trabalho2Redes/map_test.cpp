#include <iostream>
#include <map>
#include <vector>
using namespace std;
int main() {

    map<vector<int> *, int> m;

    m[NULL] = 5; 
    cout << m[NULL] << endl;

    return 0;
}