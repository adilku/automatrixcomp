#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cstdlib>
#include <cassert>
#include <climits>
#include <random>
#include <typeinfo>
#include <sstream>
#include "requests.h"

using namespace std;


template<typename T>
class matrix {
public:
    int n, m;
    vector<vector<T> > a;

    matrix(vector<vector<T> > &a_) {
        a = a_;
    }

    matrix() {
        n = 0;
        m = 0;
    }

    void matrix_scanf() {
        int n_, m_;
        cin >> n_ >> m_;
        n = n_;
        m = m_;
        vector<vector<T> > a_(n + 1, vector<T>(m + 1));

        for (size_t i = 1; i <= n; i++) {
            for (size_t j = 1; j <= m; j++) {
                int temp;
                cin >> temp;
                a_[i][j] = temp;
            }
        }

        cout << "Matrix scaned\n";
        a = a_;
    }

    void mult(size_t i, T h) {
        for (size_t j = 1; j <= m; j++)
            a[i][j] *= h;
    }

    void divi(size_t i, T h) {
        for (size_t j = 1; j <= m; j++)
            a[i][j] /= h;
    }

    void swapi(size_t i1, size_t i2) {
        for (size_t j = 1; j <= m; j++)
            swap(a[i1][j], a[i2][j]);
    }

    void plusi(size_t i1, size_t i2, T lamda) {
        for (size_t j = 1; j <= m; j++)
            a[i1][j] += a[i2][j] * lamda;
    }

    string print() {
        std::ostringstream stream;
        stream << "\\begin{pmatrix}\n";
        for (size_t i = 1; i <= n; i++) {
            for (size_t j = 1; j <= m; j++) {
                if (j == m) {
                    stream << a[i][j] << "\\" << "\\";
                } else {
                    stream << a[i][j] << " &" << ' ';
                }
            }
            stream << "\n";
        }
        stream << "\\end{pmatrix}\n";
        return stream.str();
    }

    string print_do(vector<node_operations<T> *> &d) {
        std::ostringstream stream;
        stream << "\t\\overset{\\shortstack{";
        for (size_t i = 0; i < d.size(); ++i) {
            if (d[i]->type == 1) {
                stream << "$I_{" << d[i]->get_index_i() << "}" << " \\cdot$" << d[i]->get_val();
            }
            if (d[i]->type == 2) {
                stream << "$I_{" << d[i]->get_index_i() << "}" << " \\cdot" << "\\frac{1}{" << d[i]->get_val() << "}$";
            }
            if (d[i]->type == 3) {
                stream << "swap" << "$I_{" << d[i]->get_index_j() << "} " << "I_{" << d[i]->get_index_j() << "}$";
            }
            if (d[i]->type == 4) {
                stream << "$I_{" << d[i]->get_index_i() << "} + " << d[i]->get_val() << "\\cdot " << "I_{"
                       << d[i]->get_index_j() << "}$";
            }
            if (i != d.size() - 1)
                stream << "\\\\[+0.5ex] \n";

        }
        stream << "}}{\\rightarrow}";
        stream << "\n";
        string operations_string = stream.str();
        return operations_string;
    }
};

template<typename T>
void solve() {
    string all_ops;
    vector<node_operations<T> *> requests;
    matrix<T> cur_matrix;
    cur_matrix.matrix_scanf();
    all_ops += cur_matrix.print();
    cout
            << "functions: \n plus i j lambda\n multi i lamblda \n div i lambda \n swap i j\n show \n save \n print and show(ps) \n enter exit to exit\n";
    while (true) {
        char buffer[100 + 1];
        scanf("%100s", buffer);
        string s(buffer);
        if (s == "exit" || s == "e") {
            break;
        }
        if (s == "print" || s == "p" || s == "show") {
            //show and clear;
            if (!requests.empty()) {
                all_ops += cur_matrix.print_do(requests);
            }
            all_ops += cur_matrix.print();
            cout << all_ops;
            all_ops = "";
            requests.clear();
        }
        if (s == "save" || s == "s") {
            //save and continue
            if (!requests.empty()) {
                all_ops += cur_matrix.print_do(requests);
            }
            all_ops += cur_matrix.print();
        }
        if (s == "p and s" || s == "ps") {
            if (!requests.empty()) {
                all_ops += cur_matrix.print_do(requests);
            }
            all_ops += cur_matrix.print();
            cout << all_ops;
        }
        if (s == "multi" || s == "m") {
            size_t pos;
            T lam;
            cin >> pos;
            cin >> lam;
            cur_matrix.mult(pos, lam);
            requests.push_back(new multiplication<T>(1, pos, lam));
        }
        if (s == "div" || s == "d") {
            cout << "check\n";
            size_t pos;
            T lam;
            cin >> pos >> lam;
            cur_matrix.divi(pos, lam);
            requests.push_back(new div_i_val<T>(2, pos, lam));
        }
        if (s == "swap" || s == "sw") {
            size_t i, j;
            cin >> i >> j;
            cur_matrix.swapi(i, j);
            requests.push_back(new swap_i_j<T>(3, i, j));
        }
        if (s == "plus" || s == "pl") {
            size_t i1, i2;
            T lamda;
            cin >> i1 >> i2;
            cin >> lamda;
            cur_matrix.plusi(i1, i2, lamda);
            requests.push_back(new plus_i_j_val<T>(4, i1, i2, lamda));
        }
    }
}


signed main() {
    //freopen("in.txt", "rt", stdin);
    //freopen("out.txt", "wt", stdout);
    cout << "Choose type for matrix operations\n enter 0 for int or 1 for Rational\n";
    char type_of_ops;
    type_of_ops = getchar();
    if (type_of_ops == '0') {
        solve<int>();
    } else {
        solve<Rational>();
    }
    return 0;
}