//
//  main.cpp
//  peoplelist
//
//  Created by Weijia Shi on 7/24/17.
//  Copyright © 2017 Weijia Shi. All rights reserved.
//

#include <iostream>
#include "PeopleList.h"
#include <cassert>
#include <string>

using namespace std;
/////////////////////////////////////People List Implementation//////////////////////////////////////////

int main(){
    PeopleList m1;
    m1.add("a","b","1");
    m1.add("c","b","2");
    PeopleList m2(m1);
    m2.dump();
}


//default constructor
PeopleList::PeopleList(){
    head = nullptr;
    m_size = 0;
}

//copy constructor
PeopleList::PeopleList(const PeopleList& rhs)
{
    if(rhs.head == nullptr)
    {
        head=nullptr;
        return;
    }
    
    head = nullptr;
    Node* p =nullptr;
    for (Node *q = rhs.head; q != nullptr ; q = q->next)
    {
        //create a new node to store the value
        Node *newNode = new Node(q->fn, q->ln, q->val);
        if(head == nullptr)
        {
            head = newNode;
        }
        if(p!=nullptr)
        {
            p->next = newNode;
            p->next->prev =p;
        }
        p = newNode;
    }
    //assign size
    m_size = rhs.m_size;
}

//assignment operator
const PeopleList& PeopleList:: operator=(const PeopleList& rhs)
{
    PeopleList copy(rhs);
    this->swap(copy);
    return *this;
}


//destructor
//??????????????
PeopleList::~PeopleList()
{
    Node *p;
    while (head != nullptr) {
        p = head;
        head = head->next;
        delete p;
    }
}

void PeopleList::dump()
{
    Node* p = head;
    if (head == nullptr) {
        cerr << "Empty" << std::endl;
        return;
    }
    while (p) {
        std::cout << p->fn << " " << p->ln << " " << p->val << std::endl;
        p = p->next;
    }
}


bool PeopleList::empty() const    // Return true if the list is empty, otherwise false.
{
    if(head==nullptr)
        return true;
    return false;
}

int PeopleList::size() const
{
    return m_size;
}

bool PeopleList::add(const std::string& firstName, const std::string& lastName, const InfoType& value)
// If the full name (both the first and last name) is not equal to any full name currently
// in the list then add it and return true. Elements should be added according to
// their last name. Elements with the same last name should be added according to
// their first names. Otherwise, make no change to the list and return false
// (indicating that the name is already in the list).
{
    //if Peoplelist is empty
    Node *addnode = new Node(firstName, lastName, value);
    if(head == nullptr) {
        head = addnode;
        m_size = 1;
        return true;
    }
    
    //loop every node in the peoplelist
    Node *p = head;
    Node *tail = head;
    for (;p!=nullptr;p=p->next) {
        tail = p;
        // for each p, if p == addNode, then return false
        if (this->compare(firstName, lastName, p) == 0) return false;
        // if p > addNode, insert before p
        if (this->compare(firstName, lastName, p) > 0) {
            // do insert
            if (p == head) {
                addnode->next = p;
                p->prev = addnode;
                head = addnode;
                m_size++;
                return true;
            }
            Node * prev = p->prev;
            prev->next = addnode;
            addnode->prev = prev;
            addnode->next = p;
            p->prev = addnode;
            m_size++;
            return true;
        }
        // if p < addNode, ignore
    }
    
    tail->next = addnode;
    addnode->prev = tail;
    m_size++;
    return true;
    
}

//compare the name
int PeopleList:: compare(const string& firstName, const string& lastName, Node*checkNode)
{
    //if the full last name is same
    if(lastName == checkNode->ln)
    {
        //compare the first name
        if(firstName == checkNode->fn)
            return 0;
        
        //if the node in the peoplelist has larger name
        else if (checkNode->fn > firstName)
        {
            return 1;
        }
    }
    //if the node in the peoplelist has larger last name
    else if (checkNode->ln > lastName)
    {
        return 1;
    }
    return -1;
}

bool PeopleList::change(const std::string& firstName, const std::string& lastName, const InfoType& value)
// If the full name is equal to a full name currently in the list, then make that full
// name no longer map to the value it currently maps to, but instead map to
// the value of the third parameter; return true in this case.
// Otherwise, make no change to the list and return false.
{
    //find the name
    for(Node *p = head; p!=nullptr; p=p->next)
    {
        if(p->ln == lastName && p->fn == firstName)
        {
            //set the value
            p->val = value;
            return true;
        }
    }
    //if we cannot find the name, return false
    return false;
}

bool PeopleList::addOrChange(const std::string& firstName, const std::string& lastName, const InfoType& value)
// If full name is equal to a name currently in the list, then make that full name no
// longer map to the value it currently maps to, but instead map to
// the value of the third parameter; return true in this case.
// If the full name is not equal to any full name currently in the list then add it
// and return true. In fact this function always returns true.
{
    for(Node *p = head; p!=nullptr; p=p->next)
    {
        //if we can find the name in the list
        if(p->ln == lastName && p->fn == firstName)
        {
            //set the value
            p->val = value;
            return true;
        }
    }
    //cannot find then add
    this->add(firstName, lastName, value);
    return true;
    
}

bool PeopleList::remove(const std::string& firstName, const std::string& lastName)
// If the full name is equal to a full name currently in the list, remove the
// full name and value from the list and return true.  Otherwise, make
// no change to the list and return false.
{
    for(Node *p = head; p!=nullptr; p=p->next)
    {
        //if we can find the name in the list
        if(p->ln == lastName && p->fn == firstName)
        {
            //remove that value
            Node *temp = p;
            //if remove node is head
            if(p == head)
                head = p->next;
            //if p->next have value
            if(p->next)
                p->next->prev = p->prev;
            //if p->prev have value
            if(p->prev)
                p->prev->next=p->next;
            delete temp;
            m_size--;
            return true;
        }
    }
    return false;
}


bool PeopleList::contains(const std::string& firstName, const std::string& lastName) const
// Return true if the full name is equal to a full name currently in the list, otherwise
// false.
{
    for(Node *p = head; p!=nullptr; p=p->next)
    {
        //if we can find the name in the list
        if(p->ln == lastName && p->fn == firstName)
            return true;
    }
    return false;
}


bool PeopleList::lookup(const std::string& firstName, const std::string& lastName, InfoType& value) const
// If the full name is equal to a full name currently in the list, set value to the
// value in the list that that full name maps to, and return true.  Otherwise,
// make no change to the value parameter of this function and return
// false.
{
    for(Node *p = head; p!=nullptr; p=p->next)
    {
        //if we can find the name in the list
        if(p->ln == lastName && p->fn == firstName)
        {
            value = p->val;
            return true;
        }
    }
    return false;
}

bool PeopleList::get(int i, std::string& firstName, std::string& lastName, InfoType& value) const
// If 0 <= i < size(), copy into firstName, lastName and value parameters the
// corresponding information of the element at position i in the list and return
// true.  Otherwise, leave the parameters unchanged and return false.
// (See below for details about this function.)
{
    Node *p = head;
    for (int present = 0; p != nullptr && present < i; present++)
    {
        p = p->next;
    }
    if (p==nullptr)
        return false;
    else
    {
        value = p->val;
        firstName = p->fn;
        lastName = p->ln;
        return true;
    }
    
}

void PeopleList::swap(PeopleList& other)
// Exchange the contents of this list with the other one.
{
    Node *p = other.head;
    Node *q = head;
    head = p;
    other.head = q;
    
    //swap size
    int temp = other.m_size;
    other.m_size = this->m_size;
    m_size = temp;
}

 



