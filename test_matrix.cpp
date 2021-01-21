#include <iostream>
#include <vector>
#include "requests.h"


using namespace std;

int main() {
    vector<node_operations<int> *> a(0);
    //a[0] = div_i_val<int>(2, 1, 3);
    a.push_back(new div_i_val<int>(2, 1, 3));
    cout << a[0]->get_val() << '\n';

}