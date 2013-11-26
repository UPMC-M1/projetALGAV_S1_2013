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
	node_t *father;		//his father
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
void initAsInterNode(node_t *, node_t *, node_t *, node_t *, int theCode);
void initAsNewLeaf (node_t *, node_t *, unsigned char);

node_t * modify(node_t *, unsigned char);
// function definitions

void init() {
    root.key = '#';
    root.weight = 0;
    root.left = nullptr;
    root.right = nullptr;
	root.father = nullptr;
    root.father = nullptr;
    root.code = 255;
    
    characterCode['#'] = 0;
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