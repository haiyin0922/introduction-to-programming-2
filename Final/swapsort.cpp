#include <iostream>
#include <vector>
#include <set>
#include <list>
#include <algorithm>
using namespace std;
using State = vector<int>;
//#include "function.h"

class SwapSort
{
private:
    set<list<State>> _paths;
    set<list<State>> _solutions;
    set<State> _explored;
public:
    SwapSort(State init)
    {
        list<State> ls;
        ls.push_back(init);
        _paths.insert(ls);
    }

    void show_solutions()
    {
        if (_solutions.size()==0) {
            cout << "No solution.\n";
        } else {
            for (auto p : _solutions) {
                for (auto s : p) {
                    for (auto i : s) {
                        cout << i << " ";
                    }
                    cout << "-> ";
                }
                cout << ".\n";
            }
        }
    }

    set<State> extend(State s);
    void solve(int steps);
};

set<State> SwapSort::extend(State s)
{
    set<State> SS;

    // your code here
    State tmp = s;
    
    swap(tmp[0], tmp[1]);
	swap(s.back(), s.front());
	
	SS.insert(tmp);
	SS.insert(s);

    return SS;
}

int isSorted(State s) {
    int before = s.front();
    for(auto i : s)
        if(before > i)
            return 0;
        else
        	before = i;
    return 1;
}

void SwapSort::solve(int steps)
{
    while (steps>0) {
        set<list<State>> oldPaths;
        set<list<State>> newPaths;

        for (auto p : _paths) {
            // your code here
            _explored.insert(p.back());	//last elem. of p
            auto nextStates = extend(p.back());
            for (auto s : nextStates) {
                if (isSorted(s)) {
                    auto np = p;
                    np.push_back(s);
                    _solutions.insert(np);
                }
				else {
                    auto search = _explored.find(s);
                    if (search == _explored.cend()) {
                        auto np = p;
                        np.push_back(s);
                        newPaths.insert(np);
                    }
                }
            }
            oldPaths.insert(p);

        }

        for (auto p : oldPaths) {
            _paths.erase(p);
        }
        for (auto p : newPaths) {
            _paths.insert(p);
        }
        --steps;
    }
}

int main()
{
    State s;// = {2, 1, 3};
    int e;
    while (cin >> e) { // press Ctrl + Z to end the input
        s.push_back(e);
    }
    SwapSort prob1(s);
    prob1.solve(4);
    prob1.show_solutions();
    cout << "\n";
}
