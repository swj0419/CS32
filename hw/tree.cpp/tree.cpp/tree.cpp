//
//  main.cpp
//  tree.cpp
//
//  Created by Weijia Shi on 8/12/17.
//  Copyright © 2017 Weijia Shi. All rights reserved.
//

#include <iostream>
#include <string>
#include <cassert>
using namespace std;

typedef string ItemType;

struct WordNode {
    ItemType m_data;
    WordNode *m_left;
    WordNode *m_right;
    int count = 0;
    // You may add additional data members and member functions in WordNode
};

class WordTree {
    
private:
    WordNode *root;
    int countDW(WordNode *base) const;
    int countTW(WordNode *base)const;
    void copy_aux(WordNode* &base, WordNode *copy);
    void add_aux(ItemType v, WordNode* &base);
    void swap(const WordTree& rhs);
    void swap(WordTree& rhs);
    void Destroy(WordNode* &nodeptr);
    void print(WordNode *base, ostream &out) const;
    
public:
    
    // default constructor
    WordTree() : root(nullptr) { };
    
    // copy constructor
    WordTree(const WordTree& rhs);
    
    // assignment operator
    const WordTree& operator=(const WordTree& rhs);
    
    // Inserts val at the front of the list
    void add(ItemType v);

    // Returns the number of distince words / nodes
    int distinctWords() const;
    
    // Returns the total number of words inserted, including duplicate
    // values
    int totalWords() const;
    
    // Prints the LinkedList
    friend ostream& operator<<(ostream &out, const WordTree& rhs);
    
    // Destroys all the dynamically allocated memory
    // in the tree.
    ~WordTree();
};


WordTree :: WordTree(const WordTree& rhs){
    //special case
    if(rhs.root == nullptr)
    {
        root=nullptr;
        return;
    }
    
    //recursive call
    copy_aux(root, rhs.root);
}


void WordTree ::copy_aux(WordNode* &base, WordNode *copy)
{

    //base case: reach to the end
    if(copy == nullptr)
        return;
    
     //recursive call: set equal
    WordNode* temp = new WordNode;
    temp->m_data = copy->m_data;
    temp->m_left = temp->m_right = nullptr;
    base = temp;
    base->count = copy->count;
    
    //recursive
    copy_aux(base->m_left, copy->m_left);
    copy_aux(base->m_right, copy->m_right);
    
}

const WordTree& WordTree::operator=(const WordTree& rhs)
{
    WordTree temp(rhs);
    temp.swap(*this);
    return *this;
}

WordTree :: ~WordTree()
{
    Destroy(root);
}

void WordTree::Destroy(WordNode* &nodeptr)
{
    if(nodeptr != nullptr)
    {
        Destroy(nodeptr->m_right);
        Destroy(nodeptr->m_left);
        delete nodeptr;
        nodeptr = nullptr;
    }
}


void WordTree::swap(WordTree& rhs)
{
    WordNode* temp = root;
    root = rhs.root;
    rhs.root = temp;

}

void WordTree::add(ItemType v)
{
    add_aux(v, root);
}

void WordTree::add_aux(ItemType v, WordNode* &base)
{

    if(base == nullptr)
    {
        base = new WordNode;
        base->m_data = v;
        base->m_left = base->m_right = nullptr;
        base->count++;
        return;
    }
    
    //base case
    if(base->m_data == v)
    {
        base->count++;
        return;
    }
    
    //recursive call
    if(base->m_data < v)
        add_aux(v, base->m_right);
    if(base->m_data > v)
        add_aux(v, base->m_left);
}

int WordTree :: distinctWords() const{
    return countDW(root);
}

int WordTree :: totalWords() const{
    return countTW(root);
}

int WordTree :: countDW(WordNode *base) const
{
    if(base == nullptr)
        return 0;
    return 1+countDW(base->m_right)+countDW(base->m_left);
}

int WordTree :: countTW(WordNode *base) const
{
    if(base == nullptr)
        return 0;
    return base->count+countTW(base->m_right)+countTW(base->m_left);
}

ostream& operator<<(ostream &out, const WordTree& rhs)
{
    string store = "";
    rhs.print(rhs.root, out);
    return out;
}

void WordTree :: print(WordNode *base, ostream &out) const
{
    if(base == nullptr)
        return;
    print(base->m_left, out);
    out << base->m_data << " "  << base->count<< endl;
    print(base->m_right, out);

}


int main(){
    WordTree a;
    
    a.add("1");
    a.add("2");
    a.add("3");
    a.add("4");
    a.add("5");
    a.add("1");
    a.add("2");
    a.add("3");
    a.add("4");
    a.add("1");
    a.add("2");
    a.add("3");
    a.add("1");
    a.add("2");
    a.add("1");
    
    cout<< a <<endl;
    
    cout<<a.totalWords()<<endl;
    cout<<a.distinctWords()<<endl;
    
    WordTree b = a;
    cout<< b <<endl;
    
    WordTree c;
    c.add("");
    a = b = c;
    cout<< b <<endl;
    cout<< a <<endl;
    cout<< c <<endl;
    cout<<a.totalWords()<<endl;
    cout<<a.distinctWords()<<endl;
    
    WordTree t;
    
    t.add("Skyler");
    t.add("Walter");
    t.add("Walter");
    t.add("Walter");
    
    assert(t.distinctWords() == 2);
    assert(t.totalWords() == 4);
    t.add("Skyler");
    t.add("Walter");
    t.add("Walter");
    t.add("Hank");
    t.add("Gus");
    t.add("Walter");
    t.add("Gus");
    
    cout << t;
    
}













