
#ifndef NODE_H
#define NODE_H

#include <string>
#include <iostream>
#include <cmath>

class Node
{
    private:
    //class members
        int outer;          //will hold outer coefficient
        int inner;          //will hold inner coefficient 4 in (sin 4x)
        int num;            //will hold numerator for extra credit
        int denom;          //will hold denominator of outer coefficient
        int exp;            //will hold exponent value of the node
        std::string trig;   //will hold what trig value the node will have
        Node *next;         //next pointer
        
    public:
        //constructors
        Node();
        Node(int out, int expo) { outer = out; exp = expo; }    
        
        //mutators
        void setOuter(int oute) { outer = oute; }   //assigns arguments to the class member variables since they are private
        void setInner(int inne) { inner = inne; }
        void setNum(int nume) { num = nume; }
        void setDenom(int deno) { denom = deno; }
        void setExp(int expe) { exp = expe; }
        void setTrig(std::string tri) { trig = tri; }
        void setNext(Node* nex) { next = nex; }
        
        //accessors
        int getOuter() const { return outer; }      //gets the class member variables
        int getInner() const { return inner; }
        int getNum() const { return num; }
        int getDenom() const { return denom; }
        int getExp() const { return exp; }
        std::string getTrig() const { return trig; }
        Node* getNext() const { return next; }
        
        //overloaded operator
        friend std::ostream& operator<<(std::ostream&, const Node*);
};
#endif