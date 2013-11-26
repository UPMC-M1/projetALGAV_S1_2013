#include <iostream>
#include "algorithm"
#include <map>

using namespace std;

// struct definitions


typedef struct node node_t;

struct node {
<<<<<<< HEAD
    unsigned char key;        // character corresponding to node 
=======
    unsigned char key;        // character corresponding to node
>>>>>>> f1c07c9a14ac830465cb2bb3467066bb2af83948
    int weight;            // number of character in the text for the current time
    int code;        // code used in algorithm to define height of the node
    node_t *left;           // left subtree
    node_t *right;        // right subtree
<<<<<<< HEAD
	node_t *father;		//his father 
=======
    node_t *father;     //his father
>>>>>>> f1c07c9a14ac830465cb2bb3467066bb2af83948
};

// globals declarations

node_t root;
map <unsigned char, int> characterCode;


// function declarations

string getText();
void processText(string);
void init();
<<<<<<< HEAD
bool isSpecialSymbol(node_t *);
node_t * findNodeForSymbol(node_t * , unsigned char, int);
void addingNewChar(node_t *, unsigned char);
void initAsInterNode(node_t *, node_t *, node_t *, node_t *, int theCode);
void initAsNewLeaf (node_t *, node_t *, unsigned char);

=======
node_t * modify(node_t *, unsigned char);
>>>>>>> f1c07c9a14ac830465cb2bb3467066bb2af83948

// function definitions

void init() {
    root.key = '#';
    root.weight = 0;
    root.left = nullptr;
    root.right = nullptr;
<<<<<<< HEAD
	root.father = nullptr;
=======
    root.father = nullptr;
>>>>>>> f1c07c9a14ac830465cb2bb3467066bb2af83948
    root.code = 255;
    
    characterCode['#'] = 0;
}

<<<<<<< HEAD
//function initialize as internal node
void initAsInterNode(node_t * node, node_t * f, node_t * l, node_t * r, int theCode){
	node->key = '';
	node->weight = l->weight + r->weight;
	node->left = l;
	node->right = r;
	node->father = f;
	//the code should be the special node's code 
	node->code = the;
}

//this function initialize the node like a new Leaf with a key character
void initAsNewLeaf (node_t * node , node_t * theFather, unsigned char k){
	node->key = k;
	node->weight = 1;
	node->left = nullptr;
	node->right = nullptr;
	node->father = theFather;
	//here the father shouldn't be nullptr !!!
	//we sub 1 from the father's code to have thi one's code 
	node->code = theFather->code - 1;
	//for the way, this node is allways putted at the right side of his father, so we add 1 to the right of his father's way 
	//to do that we just multiply by 2 and then add 1 to the int representing the way of his father
	int wayToFather = characterCode[theFather->key];
	characterCode[k] = (wayToFather * 2) +1;
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


// parametre C well be the character we want to add
void addingNewChar (unsigned char k){
	
	//we creat two other nodes 
	node_t * newNode1 = new node_t; //internal node
	node_t * newNode2 = new node_t; //node with new key
	
	//save the root's father and his code 
	node_t * specialsFather = root.father;
	
	//initializing son's node
	initAsInterNode(newNode1, specialsFather, &root, newNode2, root.code);
	initAsNewLeaf(newNode2, newNode1, k);

	//modifying the root (special node)
	root->code = specialCode - 2;
	theWay = characterCode['#'];
	
	//we multiply by 2 the int representing the way to add a zero in the right of the binary representation of this int
	characterCode['#'] = theWay*2;
	
	//now we've got to modify links
	if(specialsFather->left == root){
		specialsFather->left = newNode1;
	}else {
		specialsFather->right = newNode1;
	}
	root.father = newNode1;
	
=======

node_t * modify(node_t *, unsigned char) {
<<<<<<< HEAD
//    asdsad
=======
//    asd
>>>>>>> f1c07c9a14ac830465cb2bb3467066bb2af83948
>>>>>>> a23fda8447d0bd73a9e688ad25342df1d820b017
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