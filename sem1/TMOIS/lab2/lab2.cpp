#include <iostream>
#include <vector>
#include <utility>

using namespace std;

void enter_gra(vector<pair<int, int>>* gra, int n) {
    int x, y;
    for (int i = 0; i < n; i++) {
        cin >> x >> y;
        gra->emplace_back(x, y);
    }
}

int main()
{
    int what_op;
    cout << "What operation you want to do? \n1. Composition \n2. Inversion\n";

    while (cin) {
        cout << "Enter the number 1 or 2:"; cin >> what_op;
        int na, nb;
        vector <pair <int, int>> a, b, comp;

        switch (what_op)
        {
        case 1:
            cout << "Enter the power of A:"; cin >> na;
            cout << "Enter the A:"; enter_gra(&a, na);

            cout << "Enter the power of B:"; cin >> nb;
            cout << "Enter the B:"; enter_gra(&b, nb);

            for (int i = 0; i < na; i++)
                for (int j = 0; j < nb; j++)
                    if (a[i].second == b[j].first)
                        comp.emplace_back(a[i].first, b[j].second);

            for (auto& i : comp)
                cout << "<" << i.first << ", " << i.second << "> ";
            cout << endl;
            break;

        case 2:
            cout << "Enter the power of A:"; cin >> na;
            cout << "Enter the A:"; enter_gra(&a, na);

            for (auto& i : a)
                swap(i.first, i.second);

            for (auto& i : a)
                cout << "<" << i.first << ", " << i.second << "> ";
            cout << endl;
            break;
        default:
            cout << "Error. Try again.\n";
            break;
        }
    }
}