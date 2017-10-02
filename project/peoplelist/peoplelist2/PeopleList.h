//
//  peoplelist.h
//  peoplelist
//
//  Created by Weijia Shi on 7/24/17.
//  Copyright © 2017 Weijia Shi. All rights reserved.
//

#ifndef PeopleList_h
#define PeopleList_h

#include <iostream>
#include <string>

typedef std::string InfoType;

struct Node {
    Node *next;
    Node *prev;
    std::string fn;
    std::string ln;
    InfoType val;
    
    Node(std::string firstName, std::string lastName, InfoType value): fn(firstName), ln(lastName), val(value)
    {
        next = nullptr;
        prev = nullptr;
    };
    Node(){
        next = nullptr;
        prev = nullptr;
    }
    
};

class PeopleList
{
public:
    const PeopleList& operator=(const PeopleList& rhs);
    PeopleList(const PeopleList& rhs);
    ~PeopleList();
    void dump();
    
    PeopleList();          // Create an empty In (i.e., one with no InfoType values)
    
    bool empty() const;    // Return true if the list is empty, otherwise false.
    
    int size() const;      // Return the number of elements in the linked list.
    
    bool add(const std::string& firstName, const std::string& lastName, const InfoType& value);
    // If the full name (both the first and last name) is not equal to any full name currently
    // in the list then add it and return true. Elements should be added according to
    // their last name. Elements with the same last name should be added according to
    // their first names. Otherwise, make no change to the list and return false
    // (indicating that the name is already in the list).
    
    bool change(const std::string& firstName, const std::string& lastName, const InfoType& value);
    // If the full name is equal to a full name currently in the list, then make that full
    // name no longer map to the value it currently maps to, but instead map to
    // the value of the third parameter; return true in this case.
    // Otherwise, make no change to the list and return false.
    
    bool addOrChange(const std::string& firstName, const std::string& lastName, const InfoType& value);
    // If full name is equal to a name currently in the list, then make that full name no
    // longer map to the value it currently maps to, but instead map to
    // the value of the third parameter; return true in this case.
    // If the full name is not equal to any full name currently in the list then add it
    // and return true. In fact this function always returns true.
    
    bool remove(const std::string& firstName, const std::string& lastName);
    // If the full name is equal to a full name currently in the list, remove the
    // full name and value from the list and return true.  Otherwise, make
    // no change to the list and return false.
    
    bool contains(const std::string& firstName, const std::string& lastName) const;
    // Return true if the full name is equal to a full name currently in the list, otherwise
    // false.
    
    bool lookup(const std::string& firstName, const std::string& lastName, InfoType& value) const;
    // If the full name is equal to a full name currently in the list, set value to the
    // value in the list that that full name maps to, and return true.  Otherwise,
    // make no change to the value parameter of this function and return
    // false.
    
    bool get(int i, std::string& firstName, std::string& lastName, InfoType& value) const;
    // If 0 <= i < size(), copy into firstName, lastName and value parameters the
    // corresponding information of the element at position i in the list and return
    // true.  Otherwise, leave the parameters unchanged and return false.
    // (See below for details about this function.)
    
    void swap(PeopleList& other);
    // Exchange the contents of this list with the other one.
    
    
private:
    //private members
    int m_size;
    Node *head;
    //private functions
    int compare(const std::string& firstName, const std::string& lastName, Node*checkNode);
};

//no main routin
//add whatever private data members and private member functions
//////////////////////////////////////////////public function//////////////////////////////////////////////////
inline bool combine(const PeopleList& m1, const PeopleList& m2, PeopleList& result)
{
    //You must not assume result is empty when it is passed in to this function; it might not be
    //set m1 as result
    //destruct the nodes in result
    result = m1;
    //store the value getting
    std::string firstName;
    std::string lastName;
    InfoType m2_value;
    InfoType m1_value;
    bool record = 1;
    //extract node from m2
    for(int i=0; m2.get(i, firstName, lastName, m2_value)!=0;i++)
    {
        //put nodes in m2 into result
        //if the name in m2 is in result
        if(result.add(firstName, lastName, m2_value) == 0)
        {
            //if value is different, return false
            //delete that node
            result.lookup(firstName, lastName, m1_value);
            if(m1_value != m2_value)
            {
                result.remove(firstName, lastName);
                record = 0;
            }
        }
    }
    return record;
}


//Be sure these functions behave correctly in the face of aliasing: What if m1 and result refer to the same PeopleList, for example??
inline void psearch (const std::string& fsearch, const std::string& lsearch,
             const PeopleList& p1, PeopleList& result)
{
    //You must not assume result is empty when it is passed in to this function; it may not be
    //set result as p1
    //destruct the nodes in result
    result = p1;
    //check the condition: if all *, return result
    if (fsearch == "*" && lsearch == "*")
        return;
    //store the value getting
    std::string firstName;
    std::string lastName;
    InfoType value;
    
    //loop every node in p1;
    for(int i=0; p1.get(i, firstName, lastName, value)!=0;i++)
    {
        //check for the first name or last name with condition
        //first name and last name both exists: if not same, remove node
        if(fsearch != "*" && lsearch != "*")
        {
            if(fsearch != firstName || lsearch != lastName)
                result.remove(firstName, lastName);
        }
        //first name exists: if not same, remove
        if(fsearch != "*")
        {
            if(fsearch != firstName)
                result.remove(firstName, lastName);
        }
        //last name exists: if not same, remove
        if(lsearch != "*")
        {
            if(lsearch != lastName)
                result.remove(firstName, lastName);
        }
    }
}

#endif /* peoplelist_h */
