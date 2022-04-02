#include <bits/stdc++.h>
using namespace std;

vector<string> get_array_from_file(string src)
{
    fstream file(src);

    string word;
    vector<string> words;

    if (!file)
    {
        cerr << "\nCan't Open File " << src << " Some Error Occurred.!\n";
        return words;
    }

    while (!file.eof())
    {
        getline(file, word);
        if (word.size())
            words.push_back(word);
        word = "\0";
    }
    return words;
}

vector<string> linear_search_pre(vector<string> v, string str)
{

    vector<string> results;

    auto start = chrono::high_resolution_clock::now();

    for (auto s : v)
    {
        bool match = true;
        for (int i = 0; i < str.size(); ++i)
        {
            if (str[i] != s[i])
            {
                match = false;
                break;
            }
        }
        if (match)
            results.push_back(s);
    }

    auto stop = chrono::high_resolution_clock::now();
    auto dur = chrono::duration_cast<chrono::nanoseconds>(stop - start);

    cerr << "\033[32m\n"
         << results.size() << " results in " << double(dur.count() / double(1000000)) << " ms.\033[0m\n\n";

    return results;
}

bool linear_search_exact(vector<string> v, string str)
{
    auto start = chrono::high_resolution_clock::now();

    bool found = false;
    for (auto s : v)
    {
        if (s == str)
        {
            found = true;
            break;
        }
    }

    auto stop = chrono::high_resolution_clock::now();
    auto dur = chrono::duration_cast<chrono::nanoseconds>(stop - start);

    cerr << "\033[32m\n"
         << found << " results in " << double(dur.count() / double(1000000)) << " ms.\033[0m\n\n";

    return false;
}

void computeLPSArray(string pat, int M, int *lps)
{
    int len = 0;

    lps[0] = 0; 

    int i = 1;
    while (i < M)
    {
        if (pat[i] == pat[len])
        {
            len++;
            lps[i] = len;
            i++;
        }
        else 
        {
            if (len != 0)
                len = lps[len - 1];
            else
            {
                lps[i] = 0;
                i++;
            }
        }
    }
}

int KMPSearch(string pat, string txt)
{
    int M = pat.size();
    int N = txt.size();

    int lps[M];

    computeLPSArray(pat, M, lps);

    int i = 0; 
    int j = 0; 
    while (i < N)
    {
        if (pat[j] == txt[i])
        {
            j++;
            i++;
        }

        if (j == M)
        {
            return i - j;
            j = lps[j - 1];
        }

        else if (i < N && pat[j] != txt[i])
        {

            if (j != 0)
                j = lps[j - 1];
            else
                i = i + 1;
        }
    }
    return -1;
}

vector<string> search(vector<string> v, string pat)
{

    vector<string> results;

    auto start = chrono::high_resolution_clock::now();

    for (auto str : v)
    {
        if (KMPSearch(pat, str) != -1)
        {
            results.push_back(str);
        }
    }

    auto stop = chrono::high_resolution_clock::now();
    auto dur = chrono::duration_cast<chrono::nanoseconds>(stop - start);

    cerr << "\033[32m\n"
         << results.size() << " results in " << double(dur.count() / double(1000000)) << " ms.\033[0m\n\n";

    return results;
}
