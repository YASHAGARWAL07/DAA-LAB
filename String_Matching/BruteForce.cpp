#include<iostream>
using namespace std;

// brute force string matching
// basically check every position in text and see if pattern matches

void bruteForce(string txt, string pat){
    int n = txt.size();
    int m = pat.size();
    bool found = false;

    // try every starting position
    for(int i = 0; i <= n - m; i++){
        int j = 0;

        // match characters one by one
        while(j < m && txt[i+j] == pat[j]){
            j++;
        }

        if(j == m){
            cout << "Pattern found at index " << i << endl;
            found = true;
        }
    }

    if(!found)
         cout << -1 << endl;
}
int main(){
    string text, pattern;

    cout << "Enter text: ";
    cin >> text;
    cout << "Enter pattern: ";
    cin >> pattern;

    bruteForce(text, pattern);

    return 0;
}