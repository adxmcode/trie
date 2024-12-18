#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

class TrieNode {
    public:
        std::vector<TrieNode*> children;
        bool isLastLetter;

        TrieNode() : children(26, nullptr), isLastLetter(false) {}
};

class Trie {
    private:
        TrieNode* root;

        void collect(TrieNode* node, string currentWord, vector<string>& words) {
        if(node->isLastLetter) {
            words.push_back(currentWord);
        }

        for (int i = 0; i < 26; ++i) {
            if (node->children[i]) {
                char nextChar = 'a' + i;
                collect(node->children[i], currentWord + nextChar, words);
            }
        }
      }
    
    public:
        Trie() {
            root = new TrieNode();
        }

        void insert(const std::string& word) {
            TrieNode* current = root;

            for(char letter : word) {
              int index = letter - 'a';

              if(!current->children[index]) {
                current->children[index] = new TrieNode();
              }
              current = current->children[index];
            }
            current->isLastLetter = true;
        }

        bool search(std::string word) {
            TrieNode* current = root;

            for (char letter : word) {
                int index = letter - 'a';

                if (current->children[index] == nullptr) {
                    return false;
                }

                current = current->children[index];
            }
            return current->isLastLetter;
        }

        void printTrieAsList() {
            vector<string> wordList;
            collect(root, "", wordList);

            sort(wordList.begin(), wordList.end());

            for(const string& word : wordList) {
                cout << word << endl;
            }
        }

        void printTrieinDepth(TrieNode* node, string current, int level) {
           if(node->isLastLetter) {
            cout << "Level " << level << ": " << current << endl;
           }

           for(int i = 0; i < 26; ++i) {
            if(node->children[i] != nullptr) {
                char nextChar = 'a' + i;
                printTrieinDepth(node->children[i], current + nextChar, level + 1);
            }
           }
        }

        TrieNode* getRoot() {
            return root;
        }
    
};

void searchMethod(Trie trie) {
    string input;
    cout << "Type a word you want to search: " << endl;
    cin >> input;

    if(trie.search(input)) {
        cout << "Word found!" << endl;
    } else {
        cout << "Word not found." << endl;
    }
}

int main() {
    Trie trie;
    string input;

    cout << "Input some words! Type 'stop' to stop adding words." << endl;

    while(true) {
        getline(cin, input);

        if (input == "stop") {
            break;
        }

        if(!input.empty()) {
            trie.insert(input);
        }
    }

    cout << "Want to search for words?" << endl;
    cin >> input;

    while (input == "yes") {
        searchMethod(trie);
        cout << "Keep searching?" << endl;
        cin >> input;
    }

    cout << "Would you like to see the trie? Answer yes or no." << endl;
    cin >> input;

    if(input == "yes") {
        cout << "which order?" << endl;
        cout << "A. AS LIST" << endl;
        cout << "B. USING DEPTH INFO" << endl;
        string glad;
        cin >> glad;

        if(glad == "A") {
            trie.printTrieAsList();
        } else if (glad == "B") {
            cout << "From which level? Enter a number" << endl;
            int num;
            cin >> num;
            trie.printTrieinDepth(trie.getRoot(), "", num);
        }
    }

    return 0;
}

