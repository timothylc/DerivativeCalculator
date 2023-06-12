

#include "Node.h"

Node::Node()
{
    outer = 1;          //sets all the numerical values to 1
    inner = 1;
    num = 0;
    denom = 0;  
    exp = 1;
    trig = "";          //sets trig to empty string
    next = nullptr;     //sets next to nullptr
}

std::ostream& operator<<(std::ostream &o, const Node* dis)      //allows nodes to be printed (like cout << node)
{   
    if(dis->getOuter() == 0)        //if the outer coefficient is 0, exit the function
    {
        exit(0);    
    }
    if(dis->getTrig() == "")        //if no trig values
    {
        if(dis->getNum() == 0 && dis->getDenom() == 0)
        {
            if(dis->getExp() != 1 && dis->getExp() != 0)        //if exponent is not equal to one or zero
            {
                if(abs(dis->getOuter()) != 1)                   //if outer is not -1 or 1
                {
                    o << abs(dis->getOuter()) << "x^" << (dis->getExp());   //print out with format outerx^exp
                }
                else
                {
                    o << "x^" << (dis->getExp());           //if outer is 1 or -1, print out x^exp
                }
            }
            else if(dis->getExp() == 1)                     //if exp is equal to 1
            {
                if(abs(dis->getOuter()) != 1)               //if outer is not 1
                {
                    o << abs(dis->getOuter()) << "x";       //print out in format outerx
                }
                else                                        //if outer is 1, print out x
                {
                    o << "x";
                }
            }
            else if(dis->getExp() == 0)                     //if exp is 0
            {
                o << abs(dis->getOuter());                  //just print out outer
            }
        }
        else
        {
            if(dis->getExp() != 1 && dis->getExp() != 0)        //if exponent is not equal to one or zero
            {
                o << "(" << abs(dis->getNum()) << "/" << abs(dis->getDenom()) << ")x^" << dis->getExp();
            }
            else if(dis->getExp() == 1)                     //if exp is equal to 1
            {
                o << "(" << abs(dis->getNum()) << "/" << abs(dis->getDenom()) << ")x";
            }
            else if(dis->getExp() == 0)                     //if exp is 0
            {
                o << "(" << abs(dis->getNum()) << "/" << abs(dis->getDenom()) << ")";
            }
            
        }
    }
    else                                                //if trig values are present
    {
        if(dis->getNum() == 0 && dis->getDenom() == 0)
        {
            if(abs(dis->getOuter()) != 1 && (dis->getTrig() == "sin" || dis->getTrig() == "cos" || dis->getTrig() == "tan" || dis->getTrig() == "sec^2") && dis->getInner() != 1)
            {
                o << abs(dis->getOuter()) << dis->getTrig() << " " << dis->getInner() << "x";   //if inner is not 1, print out in format outertrig innerx
            }
            else if(abs(dis->getOuter()) == 1 && (dis->getTrig() == "sin" || dis->getTrig() == "cos" || dis->getTrig() == "tan" || dis->getTrig() == "sec^2") && dis->getInner() != 1)
            {
                o << dis->getTrig() << " " << dis->getInner() << "x";   //if outer is 1, print out trig innerx
            }
            else if(abs(dis->getOuter()) != 1 && (dis->getTrig() == "sin" || dis->getTrig() == "cos" || dis->getTrig() == "tan" || dis->getTrig() == "sec^2") && dis->getInner() == 1)
            {
                o << abs(dis->getOuter()) << dis->getTrig() << " x";    //if inner equal 1, print out outertrig x
            }
            else if(abs(dis->getOuter()) == 1 && (dis->getTrig() == "sin" || dis->getTrig() == "cos" || dis->getTrig() == "tan" || dis->getTrig() == "sec^2") && dis->getInner() == 1)
            {
                o << dis->getTrig() << " x";    //if inner is 1 and outer is 1, print out trig x
            }
        }
        else
        {
            if((dis->getTrig() == "sin" || dis->getTrig() == "cos" || dis->getTrig() == "tan" || dis->getTrig() == "sec^2") && dis->getInner() != 1)
            {
                o << "(" << abs(dis->getNum()) << "/" << abs(dis->getDenom()) << ")" << dis->getTrig() << " " << dis->getInner() << "x"; //print (num/denom)trig innerx
            }
            else if((dis->getTrig() == "sin" || dis->getTrig() == "cos" || dis->getTrig() == "tan" || dis->getTrig() == "sec^2") && dis->getInner() == 1)
            {
                o << "(" << abs(dis->getNum()) << "/" << abs(dis->getDenom()) << ")" << dis->getTrig() << " x"; //print (num/denom)trig x
            }
        }
    }
   return o;
}