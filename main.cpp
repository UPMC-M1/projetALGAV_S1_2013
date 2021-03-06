#include <iostream>
#include "algorithm"
#include <map>
#include <vector>
#include <set>

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
    int floor;
};

// globals declarations

node_t root;
int code = 255;
map<unsigned char, pair<int, int> > characterWay;
set<pair<int, node_t *> > gdbh;                     //GaucheDroitBasHaut parcours
node_t *theSpecialSymbol;

// function declarations

string getText();
void processText(string);


void init();                                            // initialisation
node_t * initAsSpecialNode(node_t *, int, int);              // inits special symbol and returns it
node_t * modify(node_t *, unsigned char);               // modify function defined in the document
node_t * treatment(node_t *, node_t *);                 // treatment function defined in the document
node_t * searchForTheNodeWithCharacter(unsigned char);  // searches for character in the tree

bool isInTheTree(node_t *, unsigned char);
node_t * finBloc(node_t *);
vector<node_t *> getTheWayToRootFromNode(node_t *);
bool isIncrementable(vector<node_t *>);
void increment(vector<node_t * >, int, int);
pair<node_t *, int> extractFirstEqual(vector<node_t * >);
void swapNodes(node_t *, node_t *);
bool isLeft(node_t *);

// function definitions

node_t * initAsSpecialNode(node_t * node, int x, int floor) {
    node->key = '#';
    node->weight = 0;
    node->left = nullptr;
    node->right = nullptr;
	node->father = nullptr;
    node->father = nullptr;
    node->code = x;
    node->floor = floor;
    
    return node;
}


void init() {
    root = *initAsSpecialNode(&root, code--, 0);
    gdbh.insert(make_pair(255, &root));
    theSpecialSymbol = &root;
    characterWay['#'] = make_pair(0, 0);
}


node_t * modify(node_t * H, unsigned char c) {
    node_t * Q;
    if (!isInTheTree(H, c)) {
        Q = theSpecialSymbol->father;
        
        node_t * right = new node_t;
        right->key = c;
        right->weight = 1;
        right->code = code--;
        right->left = nullptr;
        right->right = nullptr;
        right->floor = theSpecialSymbol->floor + 1;
        
        gdbh.insert(make_pair(right->code, right));
        
        node_t *left = new node_t;
        left = initAsSpecialNode(left, code--, theSpecialSymbol->floor + 1);
        
        gdbh.insert(make_pair(left->code, left));
        
        right->father = left->father = theSpecialSymbol;
        
        node_t * f = theSpecialSymbol;
        f->left = left;
        f->right = right;
        
        theSpecialSymbol = left;
    } else {
        Q = searchForTheNodeWithCharacter(c);
        if (Q->father->left == theSpecialSymbol && Q->father == finBloc(Q))
            Q->weight ++; // not written in the documentation
            Q = Q->father;
    }
    
    return treatment(H, Q);
}



node_t * treatment(node_t * H, node_t * Q) {
    vector<node_t *> wayToRoot;
    wayToRoot = getTheWayToRootFromNode(Q);
    if (isIncrementable(wayToRoot)) {
        increment(wayToRoot, 0, (int)wayToRoot.size() - 1);
        return H;
    } else {
        node_t * m;
        pair<node_t *, int> firstEqual = extractFirstEqual(wayToRoot);
        m = firstEqual.first;
        node_t *b = finBloc(m);
        increment(wayToRoot, 0, firstEqual.second);
        swapNodes(m, b);
        
        return treatment(H, m->father);
    }
}


bool isInTheTree(node_t * H, unsigned char c) {
    if (characterWay.find(c) != characterWay.end())
        return true;
    
    return false;
}


// with ->code nodes are sorted in a GaucheDroitBasHaut order

node_t * finBloc(node_t * Q) {
    node_t *fin = Q;
    for (set<pair<int, node_t *> >::iterator it = ++gdbh.find(make_pair(Q->code, Q)); it != gdbh.end(); it++) {
        if (Q->weight != it->second->weight)
            break;
        fin = it->second;
    }
    
    return fin;
}


// returns the vector of the nodes corresponding to a way from Q to root

vector<node_t *> getTheWayToRootFromNode(node_t * Q) {
    vector<node_t *> result;
    node_t * tmp = Q;
    
    while (tmp != nullptr) {
        result.push_back(tmp);
        tmp = tmp->father;
    }
    
    return result;
}


// if all the weights of the nodes in the vector are incrementable returns true

bool isIncrementable(vector<node_t *> vec) {
    node_t *cur;
    for (int i = 0; i < vec.size() - 1; i++) {
        cur = vec[i];
        if (isLeft(cur)) {
            if (cur->weight == cur->father->right->weight)
                return false;
        } else {
            set<pair<int, node_t *> >::iterator it = ++gdbh.find(make_pair(cur->code, cur));
            if (cur->floor == it->second->floor && cur->weight == it->second->weight)
                return false;
        }
    }
    
    return true;
}


// increment the weights of the nodes in in the vector from index start to end

void increment(vector<node_t * > vec, int start, int end) {
    for (; start <= end; start ++)
        vec[start]->weight ++;
}



// extract the first node which cann't be incremented

pair<node_t *, int> extractFirstEqual(vector<node_t * > vec) {
    node_t *cur;
    for (int i = 0; i < vec.size() - 1; i++) {
        cur = vec[i];
        if (isLeft(cur)) {
            if (cur->weight == cur->father->right->weight)
                return make_pair(cur, i);
        } else {
            set<pair<int, node_t *> >::iterator it = ++gdbh.find(make_pair(cur->code, cur));
            if (cur->floor == it->second->floor && cur->weight == it->second->weight)
                return make_pair(cur, i);
        }
    }
    
    return make_pair(nullptr, -1);
}



//

void swapNodes(node_t * x, node_t * y) {
    gdbh.erase(make_pair(x->code, x));
    gdbh.erase(make_pair(y->code, y));
    
    node_t *xFather = x->father;
    node_t *yFather = y->father;
    int tmpCode = x->code;
    
    x->code = y->code;
    if (isLeft(x)) {
        xFather->left = y;
    } else {
        xFather->right = y;
    }
    
    y->code = tmpCode;
    if (isLeft(y)) {
        yFather->left = x;
    } else {
        yFather->right = x;
    }
    
    x->father = yFather;
    y->father = xFather;
    
    gdbh.insert(make_pair(x->code, x));
    gdbh.insert(make_pair(y->code, y));
}


// return true if it's his father's left son

bool isLeft(node_t * Q) {
    if (Q->father->left == Q)
        return true;
    
    return false;
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