

#include "LList.h"
#include "Node.h"

LList::LList(Node *cr)      //makes new LList object with a Node pointer passed in
{
    Node *trav1 = nullptr;  //creates node pointers trav1 and trav2
    Node *trav2 = nullptr;
    
    trav1 = cr;             //sets trav1 to the node pointer passed in
    trav2 = new Node;       //trav2 creates a new Node
    Node *prev = trav2;     //set prev to trav2
    head = trav2;           //set the head to trav2
    
    while(trav1->getNext()) //while trav1 can go forward one node
    {
        trav2->setOuter(trav1->getOuter()); //sets the member variables to each others values
        trav2->setInner(trav1->getInner());
        trav2->setNum(trav1->getNum());
        trav2->setDenom(trav1->getDenom());
        trav2->setExp(trav1->getExp());
        trav2->setTrig(trav1->getTrig());
        if(trav1->getNext())                
        {
            trav1 = trav1->getNext();       //sets trav1 to the next node
            trav2 = new Node;               //trav2 makes another node
            prev->setNext(trav2);           //prev connects the nodes
            prev = prev->getNext();         //moves prev to trav2
        }
    }
    trav2->setOuter(trav1->getOuter());     //sets member variables to one another
    trav2->setInner(trav1->getInner());
    trav2->setNum(trav1->getNum());
    trav2->setDenom(trav1->getDenom());
    trav2->setExp(trav1->getExp());
    trav2->setTrig(trav1->getTrig());
    
}

void LList::setHead(Node* cr)               //sets head of the LList
{
    Node *trav1 = nullptr;                  //makes new node pointers trav1 and trav2
    Node *trav2 = nullptr;
    
    if(head)                                //if there is a head, delete the contents of the LList
    {
        trav1 = head;
        trav2 = nullptr;
        while(trav1)
        {
            trav2 = trav1->getNext();
            delete trav1;
            trav1 = trav2;
        }
    }
    
    trav1 = cr;
    trav2 = new Node;                       //creates a new node, courtesey of trav2    
    Node *prev = trav2;
    head = trav2;
    while(trav1->getNext())                 //after that set the values of the members (excluding the next pointer) to trav2
    {
        trav2->setOuter(trav1->getOuter()); 
        trav2->setInner(trav1->getInner());
        trav2->setNum(trav1->getNum());
        trav2->setDenom(trav1->getDenom());
        trav2->setExp(trav1->getExp());
        trav2->setTrig(trav1->getTrig());
        if(trav1->getNext())
        {
            trav1 = trav1->getNext();
            trav2 = new Node;               //creates a new node and adjusts pointers for the next iteration by moving them one node ahead
            prev->setNext(trav2);
            prev = prev->getNext();
        }
    }
    trav2->setOuter(trav1->getOuter()); //does the same thing as the loop does not get to the next value
    trav2->setInner(trav1->getInner());
    trav2->setNum(trav1->getNum());
    trav2->setDenom(trav1->getDenom());
    trav2->setExp(trav1->getExp());
    trav2->setTrig(trav1->getTrig());
    
    trav1 = cr;                         //deletes the contents of previous LList that we copied so no memory leaks occur
    trav2 = nullptr;
    
    while(trav1)
    {
        trav2 = trav1->getNext();
        delete trav1;
        trav1 = trav2;
    }
}

LList::~LList()                     //destructor
{
    Node *nDelete = head;           //sets nDelete to the head of the LList
    Node *next = nullptr;           //sets the next node pointer to nullptr
    while(nDelete)                  //while there are still nodes
    {
        next = nDelete->getNext();  //set next to one after nDelete
        delete nDelete;             //delete nDelete
        nDelete = next;             //set nDelete to next
    }
}

void LList::sort()                  //sorts the expressions based on exponent and trig
{
    bool flag = 0;                  //intializes the flag var as false
    int temp1, temp2, temp3, temp4, temp5;  //makes a bunch of temp variables
    std::string temp6;              
    Node *tracker = head;           //sets the tracker node pointer to head
    Node *traverse;                 
    
    do
    {
        temp1 = 0;                  //sets every temp variable to basically mean it is empty
        temp2 = 0;
        temp3 = 0;
        temp4 = 0;
        temp5 = 0;
        temp6 = "";
        flag = 0;
        tracker = head;             //set tracker to head
        traverse = tracker->getNext();      //transverse is set to node after tracker
  
        while(traverse)                 //while transverse still can go
        {
            if (tracker->getExp() < traverse->getExp()) //if the exponent value of tracker is less than that of transverse
            { 
                temp1 = tracker->getExp();      //set tracker's member variables to temp variables
                temp2 = tracker->getOuter();
                temp3 = tracker->getInner();
                temp4 = tracker->getNum();
                temp5 = tracker->getDenom();
                temp6 = tracker->getTrig();
                tracker->setExp(traverse->getExp());        //set tracker's member variables to transverse's
                tracker->setOuter(traverse->getOuter());
                tracker->setInner(traverse->getInner());
                tracker->setNum(traverse->getNum());
                tracker->setDenom(traverse->getDenom());
                tracker->setTrig(traverse->getTrig());
                traverse->setExp(temp1);                    //set transverse's to temp variables
                traverse->setOuter(temp2);
                traverse->setInner(temp3);
                traverse->setNum(temp4);
                traverse->setDenom(temp5);
                traverse->setTrig(temp6);
                flag = 1;
            }
            tracker = tracker->getNext();           //move both of the pointers
            traverse = tracker->getNext();
        }
    }
    while(flag);                                    

do
    {
        temp1 = 0;                              //initalizes all int vars to 0 and string to ""
        temp2 = 0;
        temp3 = 0;
        temp4 = 0;
        temp5 = 0;
        temp6 = "";
        flag = 0;
        tracker = head;                         //set tracker to head
        traverse = tracker->getNext();          //set transverse to 1 after head
  
        while(traverse)                     //while transverse is not null
        {
            if (tracker->getTrig() != "" && traverse->getTrig() == "")
            { 
                temp1 = tracker->getExp();      //set temp vars to tracker's members
                temp2 = tracker->getOuter();
                temp3 = tracker->getInner();
                temp4 = tracker->getNum();
                temp5 = tracker->getDenom();
                temp6 = tracker->getTrig();
                tracker->setExp(traverse->getExp());        //set tracker's member vars to tranverse's
                tracker->setOuter(traverse->getOuter());
                tracker->setInner(traverse->getInner());
                tracker->setNum(traverse->getNum());
                tracker->setDenom(traverse->getDenom());
                tracker->setTrig(traverse->getTrig());
                traverse->setExp(temp1);        //set tranverse's to temp vars
                traverse->setOuter(temp2);
                traverse->setInner(temp3);
                traverse->setNum(temp4);
                traverse->setDenom(temp5);
                traverse->setTrig(temp6);
                flag = 1;
            }
            tracker = tracker->getNext();       //move the two node pointers 1
            traverse = tracker->getNext();
        }
    }
    while(flag);
}

const Node* LList::operator[](int i) const      //accesses element of linked list like an array would
{
    const Node *trave = head;                   //creates a constant Node pointer trave (short for travel)
    for(int in = 0; in < i; in++)               //for loop so it iterates i times
    {
       trave = trave->getNext();                //moves the pointer to the next node
    }
    return trave;                               //returns the node pointer at the correct node
}

std::ostream& operator<<(std::ostream& o, const LList& l)   //allows user to print out LList using <<
{
    int ctr = 0;            
    const Node *ptr;
    while(l[ctr]->getNext())                //while l can go forward one
    {
        ptr = l[ctr];                       //ptr is set to l at ctr value
        if(ptr->getNum() == 0 && ptr->getDenom() == 0)
        {
            if(ctr == 0 && ptr->getOuter() > 0) //if ctr is 0 and outer is greater than 0, then just print ptr (using node <<)
            {
                o << ptr;
            }
            else if(ctr == 0 && ptr->getOuter() < 0)    //if ctr is 0 but outer is less than 0, print - in front of ptr
            {
                o << "-" << ptr;
            }
            else if(ctr > 0 && ptr->getOuter() > 0) //if ctr greater than 0 and ptr is greater than 0 put a + in front of ptr
            {
                o << " + " << ptr;
            }
            else if(ctr > 0 && ptr->getOuter() < 0) //if ctr greater than 0 and ptr is less than 0 put a - in front of ptr
            {
                o << " - "  << ptr;
            }
        }
        else
        {
            if(ctr == 0 && ptr->getNum() > 0) //if ctr is 0 and outer is greater than 0, then just print ptr (using node <<)
            {
                o << ptr;
            }
            else if(ctr == 0 && ptr->getNum() < 0)    //if ctr is 0 but outer is less than 0, print - in front of ptr
            {
                o << "-" << ptr;
            }
            else if(ctr > 0 && ptr->getNum() > 0) //if ctr greater than 0 and ptr is greater than 0 put a + in front of ptr
            {
                o << " + " << ptr; //s
            }
            else if(ctr > 0 && ptr->getNum() < 0) //if ctr greater than 0 and ptr is less than 0 put a - in front of ptr
            {
                o << " - "  << ptr;
            }
        }
        ctr++;                          //add one to ctr
    }
    ptr = l[ctr];
    if(ctr-1 == 0 && l[ctr-1]->getOuter() == 0)     //if ctr-1 is 0 and outer at l[ctr-1] is 0
    {
        if(ptr->getNum() == 0 && ptr->getDenom() == 0)
        {
            if(ptr->getOuter() > 0)
            {
                o << ptr;                               //just print out ptr
            }
            else if(ptr->getOuter() < 0)
            {
                o << "-" << ptr;                        //if negative, print out - in front of ptr
            }
        }
        else
        {
            if(ptr->getNum() > 0)                       
            {
                o << ptr;                               //just print out ptr if num is positive
            }
            else if(ptr->getNum() < 0)
            {
                o << "-" << ptr;                        //if negative, print out - in front of ptr
            }
        }
    }
    else if(ctr > 0 && (ptr->getNum() == 0 && ptr->getDenom() == 0) && ptr->getOuter() > 0)         //if ctr is greater than 0 and outer of ptr is greater than 0 print + in front of ptr
    {
         o << " + " << ptr;
    }
    else if(ctr > 0 && (ptr->getNum() != 0 && ptr->getDenom() != 0) && ptr->getNum() > 0)         //if ctr is greater than 0 and num of ptr is greater than 0 print + in front of ptr
    {
         o << " + " << ptr;
    }
    else if(ctr > 0 && (ptr->getNum() == 0 && ptr->getDenom() == 0) && ptr->getOuter() < 0)         //if ctr is greater than 0 and outer of ptr is less than 0 print - in front of ptr
    {
        o << " - " << ptr;
    }
    else if(ctr > 0 && (ptr->getNum() != 0 && ptr->getDenom() != 0) && ptr->getNum() < 0)         //if ctr is greater than 0 and num of ptr is less than 0 print - in front of ptr
    {
        o << " - " << ptr;
    }
    o << std::endl;
    return o;
}

void LList::operator>>(Node *n) //adds node and makes it the head of the LList
{
    if(!head)                   //if there is no head
    {
        head = n;               //make n the head of the linked list
    }
    else                        //if there is a head
    {
        n->setNext(head);       //make n the head of the list
        head = n;
    }
}