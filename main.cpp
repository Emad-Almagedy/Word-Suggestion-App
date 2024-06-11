#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int editDistance(string word1, string word2) {
    int n = word1.length();
    int m = word2.length();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

    for (int i = 1; i <= n; i++) {
        dp[i][0] = i;
    }

    for (int j = 1; j <= m; j++) {
        dp[0][j] = j;
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (word1[i - 1] == word2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1];
            } else {
                dp[i][j] = 1 + min({dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]});
            }
        }
    }

    return dp[n][m];
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <word>" << endl;
        return 1;
    }

    string word = argv[1];
    vector<string> dictionary;
    ifstream infile("/backend/dictionary.txt");

    if (!infile) {
        cerr << "Error opening dictionary file." << endl;
        return 1;
    }

    string line;
    while (getline(infile, line)) {
        dictionary.push_back(line);
    }

    infile.close();

    vector<pair<int, string>> results;

    for (auto& w : dictionary) {
        int distance = editDistance(word, w);
        results.push_back(make_pair(distance, w));
    }

    sort(results.begin(), results.end());

    int count = 0;
    for (auto& r : results) {
        if (r.first == 0) {
            continue;
        }
        cout << r.second << " (edit distance: " << r.first << ")" << endl;
        count++;
        if (count == 10) {
            break;
        }
    }

    return 0;
}
