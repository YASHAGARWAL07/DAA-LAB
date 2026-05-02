#include<iostream>
using namespace std;

// KMP - Knuth Morris Pratt
// avoids re-checking characters using lps array
// lps = longest proper prefix which is also suffix

void computeLPS(string pat, int m, vector<int> &lps){
    int len = 0;   // length of previous longest prefix suffix
    lps[0] = 0;    // first element always 0
    int i = 1;

    while(i < m){
        if(pat[i] == pat[len]){
            len++;
            lps[i] = len;
            i++;
        }
        else{
            if(len != 0){
                // don't increment i here
                len = lps[len - 1];
            }
            else{
                lps[i] = 0;
                i++;
            }
        }
    }
}

void KMPsearch(string txt, string pat){
    int n = txt.size();
    int m = pat.size();
    bool found = false;

    vector<int> lps(m);
    computeLPS(pat, m, lps);

    int i = 0;  // index for txt
    int j = 0;  // index for pat

    while(i < n){
        if(txt[i] == pat[j]){
            i++;
            j++;
        }

        if(j == m){
            cout << "Pattern found at index " << (i - j) << endl;
            found = true;
            j = lps[j-1];   // get next position from lps
        }
        else if(i < n && txt[i] != pat[j]){
            if(j != 0)
                j = lps[j-1];
            else
                i++;
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

    KMPsearch(text, pattern);

    return 0;
}