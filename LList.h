

#ifndef LLIST_H
#define LLIST_H
#include "Node.h"
#include <iostream>
#include <cmath>

class LList
{
    private:
        Node *head; //points to the head of the LList
    
    public:
        //constructors
        LList() { head = nullptr; }
        LList(Node*);
        
        //destructor
        ~LList();
        
        //mutator
        void setHead(Node*);
        
        //accessor
        Node* getHead() const { return head; }
        
        //sorting function
        void sort();
        
        //overloaded opeators
        const Node* operator[](int) const;
        friend std::ostream& operator<<(std::ostream&, const LList&);
        void operator>>(Node*);
        
};

#endif