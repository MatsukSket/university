#include <iostream>
#include <vector>
#include <iomanip>
#include <utility>

using namespace std;

bool findEl(vector<int> vec, int el) {
    for (int it : vec)
        if (el == it)
            return true;
    return false;
}

bool findPair(vector<pair<int, int>> vec, pair<int, int> el)
{
    for (pair<int, int> it : vec)
        if (el == it)
            return true;
    return false;
}

void enterSet(vector<int>& set, int len)
{
    int val;
    for (int i = 0; i < len; i++) {
        cin >> val;
        set.push_back(val);
    }
}

void enterRelation(vector<pair<int, int>>& rel, int len)
{
    int first, second;
    for (int i = 0; i < len; i++) {
        rel.push_back(pair<int, int>());
        cin >> rel[i].first >> rel[i].second;
    }
}

void unificationSet(vector<int>& uniSet, vector<int> set1, vector<int> set2)
{
    uniSet = set1;
    for (int it : set2)
        if (!findEl(uniSet, it))
            uniSet.push_back(it);
}

void unificationRel(vector<pair<int, int>>& uniRel, vector<pair<int, int>> rel1, vector<pair<int, int>> rel2)
{
    uniRel = rel1;
    for (pair<int, int> it : rel2)
        if (!findPair(uniRel, it))
            uniRel.push_back(it);
}

void intersectionSet(vector<int>& interSet, vector<int> set1, vector<int> set2)
{
    for (int it : set1)
        if (findEl(set2, it))
            interSet.push_back(it);
}

void intersectionRel(vector<pair<int, int>>& interRel, vector<pair<int, int>> rel1, vector<pair<int, int>> rel2)
{
    for (pair<int, int> it : rel1)
        if (findPair(rel2, it))
            interRel.push_back(it);
}

void differenceSet(vector<int>& diffSet, vector<int> set1, vector<int> set2)
{
    for (int it : set1)
        if (!findEl(set2, it))
            diffSet.push_back(it);
}

void differenceRel(vector<pair<int, int>>& diffRel, vector<pair<int, int>> rel1, vector<pair<int, int>> rel2)
{
    for (pair<int, int> it : rel1)
        if (!findPair(rel2, it))
            diffRel.push_back(it);
}

void outputSet(vector<int> vec)
{
    int len = vec.size();
    cout << "{ ";
    for (int i = 0; i < len; i++)
        cout << vec[i] << ((i == len - 1) ? " " : ", ");
    cout << "}\n";
}

void outputRel(vector<pair<int, int>> rel)
{
    int len = rel.size();
    cout << "{ ";
    for (int i = 0; i < len; i++)
        cout << '<' << rel[i].first << ", " << rel[i].second << ((i == len - 1) ? "> " : ">, ");
    cout << "}\n";
}


int main()
{
    setlocale(LC_ALL, "ru");

    // ввод
    int powerX, powerY, powerG, powerM, powerN, powerP;
    vector<int> x, y, m, n;
    
    cout << "Введите мощность множества X: ";   cin >> powerX;  // множество X
    if (powerX)
        cout << "Введите множество X: ";
    enterSet(x, powerX);
    
    cout << "Введите мощность множества Y: ";   cin >> powerY;  // множество Y
    if (powerY)
        cout << "Введите множество Y: ";
    enterSet(y, powerY);
    
    vector<pair<int, int>> g;
    cout << "Введите мощность отношения G: ";   cin >> powerG;  // отношение G
    if(powerG) 
        enterRelation(g, powerG);

    cout << "Введите мощность множества M: ";   cin >> powerM;  // множество M
    if (powerM)
        cout << "Введите множество M: ";
    enterSet(m, powerM);
    
    cout << "Введите мощность множества N: ";   cin >> powerN;  // множество N
    if (powerN)
        cout << "Введите множество N: ";
    enterSet(n, powerN);
    
    vector<pair<int, int>> p;
    cout << "Введите мощность отношения P: ";   cin >> powerP;  // отношение P
    if (powerP)
        enterRelation(p, powerP);

    // объединение
    vector<int> uniSet1, uniSet2;
    vector<pair<int, int>> uniRel;
    unificationSet(uniSet1, x, m);
    unificationSet(uniSet2, y, n);
    unificationRel(uniRel, g, p);

    // пересечение
    vector<int> interSet1, interSet2;
    vector<pair<int, int>> interRel;
    intersectionSet(interSet1, x, m);
    intersectionSet(interSet2, y, n);
    intersectionRel(interRel, g, p);

    // разность
    vector<int> diffSet1, diffSet2;
    vector<pair<int, int>> diffRel;
    differenceSet(diffSet1, x, m);
    differenceSet(diffSet2, y, n);
    differenceRel(diffRel, g, p);

    // инверсия
    vector<int> invX = y, invY = x;
    vector<pair<int, int>> invG;
    for (pair<int, int> it : g)
        invG.push_back(pair<int, int>(it.second, it.first));

    // композиция 
    vector<pair<int, int>> compRel;
    for (pair<int, int> i : g) 
        for (pair<int, int> j : p) 
            if (i.second == j.first)
                compRel.push_back(pair<int, int>(i.first, j.second));

    cout << endl;
    cout << "X: ";  outputSet(x);
    cout << "Y: ";  outputSet(y);
    cout << "G: ";  outputRel(g);
    cout << "M: ";  outputSet(m);
    cout << "N: ";  outputSet(n);
    cout << "P: ";  outputRel(p);
    cout << "\nОперации над соответствиями:\n";
    cout << "1. Объединение\n";
    outputSet(uniSet1);
    outputSet(uniSet2);
    outputRel(uniRel);

    cout << "\n2. Пересечение\n";
    outputSet(interSet1);
    outputSet(interSet2);
    outputRel(interRel);

    cout << "\n3. Разность\n";
    outputSet(diffSet1);
    outputSet(diffSet2);
    outputRel(diffRel);

    cout << "\n4. Инверсия\n";
    outputSet(invX);
    outputSet(invY);
    outputRel(invG);

    cout << "\n5. Композиция\n";
    outputSet(x);
    outputSet(n);
    outputRel(compRel);

    return 0;
}