#include<bits/stdc++.h>
using namespace std;

class Node{
    public:
    Node *links[26] = {NULL};
    bool flag = false;

    bool containskey(char ch){
        return ( links[ch - 'a'] != NULL );
    }

    void put(char ch, Node* node){
        links[ch - 'a'] = node;
    }

    Node* get(char ch){
        return links[ch-'a'];
    }

    void setEnd(){
        this->flag = true;
    }

    bool isEnd(){
        return this->flag;
    }
};

class Trie{
    public:
    Node *root;

    Trie(){
        root = new Node();
    }

    // TC: O(len)
    void insert(string word){
        Node *node = root;

        for( int i=0; i<word.size(); i++ ){
            if( !node->containskey(word[i]) ){
                node->put( word[i], new Node());
            }
            // moves to the reference
            node = node->get(word[i]);   
        }

        node->setEnd();
    }

    bool search(string word){
        Node* node = root;

        for( int i=0; i<word.size(); i++ ){
            if( !node->containskey(word[i]) ){
                return false;
            }
            node = node->get(word[i]);
        }

        return node->isEnd();
    }

    bool startswith(string word){
        Node* node = root;

        for( int i=0; i<word.size(); i++ ){
            if( !node->containskey(word[i]) ){
                return false;
            }
            node = node->get(word[i]);
        }

        return true;
    }
};



int main(){
    Trie t;

    t.insert("apple");
    t.insert("apps");
    t.insert("aplx");
    cout<<t.search("apple")<<endl;
    cout<<t.search("apps")<<endl;
    cout<<t.search("ap")<<endl;
    cout<<t.search("apll")<<endl;
    cout<<t.startswith("app")<<endl;
    cout<<t.startswith("apl")<<endl;
    cout<<t.startswith("bac")<<endl;

    return 0;
}