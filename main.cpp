#include <iostream>
#include "algorithm"
#include <map>

using namespace std;

// struct definitions


typedef struct node node_t;

struct node {
    unsigned char key;        // character corresponding to node
    int weight;            // number of character in the text for the current time
    int code;        // code used in algorithm to define height of the node
    node_t *left;           // left subtree
    node_t *right;        // right subtree
    node_t *father;     //his father
};

// globals declarations

node_t root;
map <unsigned char, int> characterCode;


// function declarations

string getText();
void processText(string);
void init();
bool isSpecialSymbol(node_t *);
node_t * findNodeForSymbol(node_t * , unsigned char, int);
void addingNewChar(node_t *, unsigned char);
void initAsSpecial(node_t *, node_t *);
void initAsNewLeaf (node_t *, node_t *, unsigned char);


// function definitions

void init() {
    root.key = '#';
    root.weight = 0;
    root.left = nullptr;
    root.right = nullptr;
    root.father = nullptr;
    root.code = 255;
    
    characterCode['#'] = 0;
}

//function initialize the node as a special node
void initAsSpecial(node_t * node, node_t * theFather){
    node->key = '#';
    node->weight = 0;
    node->left = nullptr;
    node->right = nullptr;
    node->father = theFather;
    //we have the father of the special node, so we can have the code by sub 2 from the code of his father,
    //because we add another node of a character
    if(theFather != nullptr){
        node->code = theFather->code - 2 ;
        int wayToFather = (characterCode.find(theFather->key))->second;
        /*the special node is allways on the left, so we allways add zero on the right of
         the int representing the way to his father, then we multiply by 10 */
        characterCode['#'] = wayToFather*10;
    }else {
        // if we don't have a father, then it is the first element of the tree
        node->code = 255;
        characterCode['#'] = 0;
    }
}

//this function initialize the node like a new Leaf with a key character
void initAsNewLeaf (node_t * node , node_t * theFather, unsigned char k){
    node->key = k;
    node->weight = 1;
    node->left = nullptr;
    node->right = nullptr;
    node->father = theFather;
    //here the father shouldn't be a nullptr !!!
    //we sub 1 from the father's code to have thi one's code
    node->code = theFather->code - 1;
    //for the way, this node is allways putted at the right side of his father, so we add 1 to the right of his father's way
    //to do that we just multiply by 10 and add 1 to the int representing the way of his father
    int wayToFather = (characterCode.find(theFather->key))->second;
    characterCode[k] = (wayToFather * 10) + 1;
}


node_t * findNodeForSymbol(node_t *node, unsigned char k, int wayToCharacter) {
    if (isSpecialSymbol(node))            // if we have reached special character, we return it
        return node;                      // this means, we didn't have this symbol in tree before
    
    if (node->key == k)                    // we have found symbol we are searching for
        return node;
    
    if ((wayToCharacter & 1) == 0)        // our symbol is on the left side of the current node
        return findNodeForSymbol(node->left, k, wayToCharacter >> 1);
    
    // our symbol is on the right side of the current node
    return findNodeForSymbol(node->right, k, wayToCharacter >> 1);
}


//Paramter node well be the root
// parametre C well be the character we want to add
void addingNewChar (node_t * node, unsigned char k){
    
    
    //we creat two other nodes
    node_t * newNode1 = new node_t;
    node_t * newNode2 = new node_t;
    
    // we need to get the special node first so we can add the two new nodes as sons and one of them will be the special node
    node_t *special = findNodeForSymbol(node, '#', characterCode['#']);
    
    //initializing son node
    
    initAsSpecial(newNode1, special);
    initAsNewLeaf(newNode2, special, k);
    
    
}



void processText(string text) {
    void init();
    for (int i = 0; i < text.size(); i++) {
        
    }
    
}


bool isSpecialSymbol(node_t *node) {
    if (node->weight == 0)
        return true;
    return false;
}







int main(int argc, const char * argv[])
{
    string text;
    
    text = getText();
    processText(text);
    
    return 0;
}