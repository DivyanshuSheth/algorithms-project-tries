#include <bits/stdc++.h>
#include "trie.cpp"
#include "utils.cpp"
using namespace std;

int main(int argc, char **argv) {
    string file_name;
    Trie T;
    vector <string> strings_data;
    int choice;
    
    if (argc > 1) {
        file_name = argv[1];
        strings_data = get_array_from_file(file_name);
    }
    
    else {
        cout << "What data do you want to search -- dictionary/movies/music? Please select one and type the same:\n";
        cin >> file_name;
        strings_data = get_array_from_file("data/" + file_name + ".txt");
    }

    for (string word : strings_data) {
        T.insert(word);
    }
    
    if (argc > 2) {
        string pattern = argv[2];
        for (string w : search(strings_data, pattern)) {
            cout << w << "\n";
        }
        return 0;
    }

    cout << "###################\n";
    cout << "Please enter the number corresponding to the search you'd like to perform.\n1. Exact Search - searches the data for an exact string\n2. Prefix Search - searches the data for elements having a given prefix\n3. Universal Search - searches the data for elements having the given string as a substring\n0. Exit.\n";
    cin >> choice;
    getchar(); 

    while(choice) {
        string pattern;

        if (choice) {
            cout << "Enter search string (leave empty to list everything - for prefix search and universal search):\n";
            getline(cin, pattern);
        }

        if (choice == 1) {
            if (T.search_exact(pattern)) {
                cout << "The entered string exists.\n";
            }
            else {
                cout << "Not Found.\n";
            }
        }
        else if (choice == 2) {
            for (string w : T.search_pre(pattern)) {
                cout << w << "\n";
            }
        }
        else if (choice == 3) {
            for (string w : search(strings_data, pattern)) {
                cout << w << "\n";
            }
        }
        else {
            break;
        }

        cout << "\n\nPress any key to continue.";
        getchar();
        system("clear");


        cout << "###################\n";
        cout << "Please enter the number corresponding to the search you'd like to perform.\n1. Exact Search - search for an exact string\n2. Prefix Search - search for all strings beginning with a prefix\n3. Universal Search - search for all strings that contain the search query\n0. Exit\n";
        cin >> choice;
        getchar();
    }

    return 0;
}
