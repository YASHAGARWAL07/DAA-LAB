#include<iostream>
using namespace std;

/*
    Rabin Karp Algorithm
    - uses hashing to find pattern in text
    - base = 256 (no. of characters), mod = large prime to avoid overflow
    - if hash matches, verify character by character (to handle spurious hits)
*/

#define d 256
#define q 101   // prime number

void rabinKarp(string txt, string pat){
    int n = txt.length();
    int m = pat.length();
    bool found = false;

    int h = 1;
    int p_hash = 0;   // hash of pattern
    int t_hash = 0;   // hash of current window in text

    // h = d^(m-1) % q
    for(int i = 0; i < m-1; i++)
        h = (h * d) % q;

    // initial hash values
    for(int i = 0; i < m; i++){
        p_hash = (d * p_hash + pat[i]) % q;
        t_hash = (d * t_hash + txt[i]) % q;
    }

    for(int i = 0; i <= n - m; i++){

        // check hash first
        if(p_hash == t_hash){
            // verify char by char (spurious hit check)
            bool match = true;
            for(int j = 0; j < m; j++){
                if(txt[i+j] != pat[j]){
                    match = false;
                    break;
                }
            }
            if(match){
                cout << "Pattern found at index " << i << endl;
                found = true;
            }
        }

        // rolling hash for next window
        if(i < n - m){
            t_hash = (d * (t_hash - txt[i] * h) + txt[i+m]) % q;

            // can be negative, fix it
            if(t_hash < 0)
                t_hash += q;
        }
    }

    if(!found)
        cout <<"Not Found -1 " << endl;
}

int main(){
    string text, pattern;

    cout << "Enter text: ";
    cin >> text;
    cout << "Enter pattern: ";
    cin >> pattern;

    rabinKarp(text, pattern);

    return 0;
}