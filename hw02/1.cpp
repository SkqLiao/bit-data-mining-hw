#include <bits/stdc++.h>

using namespace std;

void trim(string &s) {
    s.erase(s.begin(), find_if(s.begin(), s.end(), [](int ch) {
        return !isspace(ch);
    }));
    s.erase(find_if(s.rbegin(), s.rend(), [](int ch) {
        return !isspace(ch);
    }).base(), s.end());
}

vector<pair<string, string>> read(const string &filename) {
    ifstream file(filename);
    vector<pair<string, string>> res;
    string line;

    while (getline(file, line)) {
        stringstream ss(line);
        string a, b;
        getline(ss, a, '\t');
        getline(ss, b, '\n');
        trim(a);
        trim(b);
        res.push_back({a, b});
    }

    return res;
}

map<string, vector<string>> mp1, mp2;
map<pair<string, string>, int> mp;

int main() {
    cin.tie(NULL)->ios_base::sync_with_stdio(false);
    auto booktitle = read("booktitle.txt");
    auto journal = read("journal.txt");

    for (auto &[a, b] : booktitle) {
        mp1[a].push_back(b);
    }

    for (auto &[a, b] : journal) {
        mp2[a].push_back(b);
    }

    for (auto &[x, v] : mp1) {
        if (!mp2.count(x))
            continue;

        for (auto &y : v) {
            for (auto &z : mp2[x]) {
                mp[ {y, z}]++;
            }
        }
    }

    vector<pair<pair<string, string>, int>> res;

    for (auto &[x, y] : mp) {
        res.push_back({x, y});
    }

    sort(res.begin(), res.end(), [&](auto & a, auto & b) {
        return a.second > b.second;
    });

    for (auto &[x, y] : res) {
        cout << x.first << '\t' << x.second << '\t' << y << '\n';
    }   

    return 0;
}