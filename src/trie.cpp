#include<bits/stdc++.h>
using namespace std;

struct TrieNode
{

    map<char, TrieNode *> children;
    bool isEndOfWord[1];
    int cnt ;

    TrieNode()
    {
        isEndOfWord[0] = false;
        cnt =0;
    }
};

struct Trie
{

    int total_nodes;
    int total_words;
    int total_cnt;
    TrieNode *root;

    Trie()
    {
        root = new TrieNode();
        total_cnt = 0;
    }

    TrieNode *search_exact(string str);
    vector<string> search_pre(string str);
    void draw(TrieNode *current, int depth);
    void insert(string str);
    bool remove(string str);
    bool _remove(TrieNode *current, string str, int index);

};

void Trie::insert(string str)
{
    TrieNode *current = root;
    int len = str.size();

    for (char ch:str)
    {
       
        if (current->children.find(ch) == current->children.end())
        {
            current->children.insert({ch, new TrieNode()});
            current = current->children[ch];
        }
        else
        {   
            current = current->children[ch];
            
        }
    }

    current->isEndOfWord[0] = true;
    return;
}

TrieNode *Trie::search_exact(string str)
{
    TrieNode *current = root;

    auto start = chrono::high_resolution_clock::now();
    for (char ch: str)
    {
        
        if (current->children.find(ch) != current->children.end())
        {
            current = current->children[ch];
        }
        else
        {
            return NULL;
        }
    }
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::nanoseconds>(stop - start);
    cerr << "\033[32m\n"
         << current->isEndOfWord[0] << " results in " << double(duration.count() / double(1000000)) << " ms.\033[0m\n\n";

    return current->isEndOfWord[0] ? current : NULL;
}

void get_words_dfs(TrieNode *current, string pre, vector<string> &results)
{
    if (current == NULL) return;
    
    else if (current->isEndOfWord[0])
    {
        results.push_back(pre);
    }

    for (auto i : current->children)
    {
        get_words_dfs(i.second, (pre + i.first), results);
    }
}

vector<string> Trie::search_pre(string str)
{
    auto start = chrono::high_resolution_clock::now();

    TrieNode *current = root;
    vector<string> results;

    for ( char ch : str)
    {
       
        if (current->children.find(ch) != current->children.end())
        {
            current = current->children[ch];
        }
        else
        {
            return results;
        }
    }

    get_words_dfs(current, str, results);

    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::nanoseconds>(stop - start);

    cerr << "\033[32m\n"
         << results.size() << " results in " << double(duration.count() / double(1000000)) << " ms.\033[0m\n\n";

    return results;
}

// Delete a string
bool Trie::remove(string str)
{
    _remove(root, str, 0);
    return true;
}

bool Trie::_remove(TrieNode *current, string str, int index)
{

    if (index == str.length())
    {
        // End of the word ?
        if (!current->isEndOfWord[0])
        {
            return false; // word don't exist.
        }
        current->isEndOfWord[0] = false;

        // if no more children
        return current->children.size() == 0; // true?
    }else if(index < 0 ){

        cout<<"Someting is wrong \n";
        return false;
    }

    char ch = str[index];

    if (!current->children[ch])
    {
        return false; // word don't exist.
    }

    bool shouldDeleteCurrentNode = _remove(current->children[ch], str, index + 1);

    // after recursion
    if (shouldDeleteCurrentNode)
    {
        current->children.erase(ch);
        return current->children.size() == 0; // true ?
    }

    return false;
}

void Trie::draw(TrieNode *current, int depth = 0)
{
   
    if(depth < 0){

        cout<<"Input invalid\n";
        return;
    } 
    else if (current == NULL)
    {
        current = root;
    } 

    for (auto ch : current->children)
    {  
        for (int i = 0; i < depth; i++)
        {
            cout << "_ ";
        }

        cout << ch.first << "\n";

        draw(ch.second, depth + 1);
    }
}