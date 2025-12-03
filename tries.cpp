#include<bits/stdc++.h>
using namespace std;

class Node{
    public:
    Node *links[26] = {NULL};
    bool flag = false;
    int cntEndWith = 0;
    int cntPrefix = 0;

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

    void increaseEnd(){
        cntEndWith++;
    }

    void increasePrefix(){
        cntPrefix++;
    }

    void deleteEnd(){
        cntEndWith--;
    }

    void reducePrefix(){
        cntPrefix--;
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
            node->increasePrefix(); 
        }

        node->increaseEnd();
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

    int countWordsEqualto(string word){
        Node* node = root;
        
        for( int i=0; i<word.size(); i++ ){
            if( !node->containskey(word[i]) ){
                return 0;
            }
            node = node->get(word[i]);
        }

        return node->cntEndWith;
    }

    int countWordsStartingWith(string word){
        Node* node = root;
        
        for( int i=0; i<word.size(); i++ ){
            if( !node->containskey(word[i]) ){
                return 0;
            }
            node = node->get(word[i]);
        }

        return node->cntPrefix;
    }

    void erase(string word){
        Node* node = root;

        for( int i=0; i<word.size(); i++ ){
            if( !node->containskey(word[i]) ){
                return;
            }
            node = node->get(word[i]);
            node->reducePrefix();
        }
        node->deleteEnd();
    }
};


int main(){
    Trie t;

    t.insert("apple");
    t.insert("apple");
    t.insert("apps");
    t.insert("apps");
    t.insert("aplx");
    cout<<t.search("apple")<<endl;
    cout<<t.search("apps")<<endl;
    cout<<t.search("ap")<<endl;
    cout<<t.search("apll")<<endl;
    cout<<t.startswith("app")<<endl;
    cout<<t.startswith("apl")<<endl;
    cout<<t.startswith("bac")<<endl;

    cout<<t.countWordsEqualto("apple")<<endl;
    cout<<t.countWordsStartingWith("app")<<endl;
    t.erase("apps");
    cout<<t.countWordsEqualto("apps")<<endl;
    cout<<t.countWordsStartingWith("app")<<endl;

    return 0;
}