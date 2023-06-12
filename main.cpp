/*
This program will give the derivative of the contents of a file (if it's an expression) using
linked lists and a lot of string parsing. 
*/

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include "Node.h"
#include "LList.h"

using namespace std;

string getFileName(fstream& f)                                                  //gets the file name which has contents of file
{
    string fn = "";
    bool fileOpened = 0;
    
    while(!fileOpened)                                                          //loops while fileOpened is still false
    {
        cout << "Enter the name of the file that contains the functions: ";     //prompts user to enter file name and takes contents
        cin >> fn;
    
        f.open(fn, ios::in);                                                    //tries to open the file provided by the user
    
        if(f)
        {
            fileOpened = 1;                                                     //if it works, set fileOpened to true and close the file
            f.close();
        }
        else                                                                    //if it does not open, displays an error message
        {
            cout << "ERROR: File not found.\n";
        }
    }
    
    return fn;                                                                  //returns file name
}

void parseBonus(string &p, bool &neg, Node*& n)                                 //parses the string if it contains a ()
{
    if(p[0] == '-')                                                             //if the first character in the string is -, set neg to true
    {
        neg = 1;
    }
    p = p.substr(static_cast<int>(p.find('('))+1);                              //adjust the string so that index 0 will be the numerator
    if(neg)
    {
        n->setNum(-1*stoi(p.substr(0, static_cast<int>(p.find('/')))));         //set numerator to -1* what is before the / character if neg
    }
    else
    {
        n->setNum(stoi(p.substr(0, static_cast<int>(p.find('/')))));            //set numerator to what is before the / character
    }
    p = p.substr(static_cast<int>(p.find('/'))+1);                              //adjust the string so it goes to the denominator and set the node's denominator
    n->setDenom(stoi(p.substr(0, static_cast<int>(p.find(')')))));              //to what was after / but before )
    p = p.substr(static_cast<int>(p.find(')'))+1);
    if(static_cast<int>(p.find("sin")) != -1 || static_cast<int>(p.find("tan")) != -1 || static_cast<int>(p.find("cos")) != -1) //if trig is there
    {
        n->setTrig(p.substr(0, 3));                         //set trig to whatever value it is 
        p = p.substr(static_cast<int>(p.find(" "))+1);      //then adjust the string so it is the value after the space
        if(p[0] != 'x')
        {
            n->setInner(stoi(p.substr(0, static_cast<int>(p.find('x')))));  //if x is not the first character, get the value before x and store it inner
        }
    }
    else            //if no trig values are present
    {
        if(static_cast<int>(p.find('x')) == -1)         //if x is not there
        {
            n->setExp(0);                               //set exponent value to 0
        }
        else if(static_cast<int>(p.find('^')) == -1)    //if there is no ^, set exponent value to 1
        {
            n->setExp(1);
        }
        else if(static_cast<int>(p.find("x^")) != -1)   //if there is x^ in the string, get the numerical value before it and store it as exponent
        {
            p = p.substr(static_cast<int>(p.find('^'))+1);
            n->setExp(stoi(p));
        }
    }
    p = "";         //set p to an empty string
    neg = 0;        //set neg to false to prevent any sign errors
    
    if(n->getNum()%n->getDenom() == 0)          //if numerator is divisible by the denominator
    {
        n->setOuter(n->getNum()/n->getDenom()); //set outer to the quotient and set the num and denom values to 0
        n->setNum(0);
        n->setDenom(0);
    }
    
    
}

void parseString(string &p, bool &neg, Node*& n)                                //sets the proper values to a node's members
{
    if(p[0] == '-')                                                             //if the first character in a string is -, then get rid of it and set neg to true
    {
        neg = 1;        
        p = p.substr(1);
    }
    if(static_cast<int>(p.find("sin")) != -1 || static_cast<int>(p.find("tan")) != -1 || static_cast<int>(p.find("cos")) != -1)     //if there is trig
    {
        if(static_cast<int>(p.find("sin")) == 0 || static_cast<int>(p.find("tan")) == 0 || static_cast<int>(p.find("cos")) == 0)    //and if it is the first thing in the string
        {
            if(neg)                         //if neg is true, set outer to -1
            {
                n->setOuter(-1);
            }
            n->setTrig(p.substr(0, 3));     //then set trig to the first three characters 
        }
        else if(static_cast<int>(p.find("sin")) > 0 && static_cast<int>(p.find("tan")) == -1 && static_cast<int>(p.find("cos")) == -1)  //if sin is found (not at beginning)
        {
            if(neg)                                                                     //sets outer to its outer coefficient times -1
            {
                n->setOuter(stoi(p.substr(0,static_cast<int>(p.find("sin")))) * -1);
            }
            else                                                                        //sets outer to its outer coefficient
            {
                n->setOuter(stoi(p.substr(0,static_cast<int>(p.find("sin")))));         
            }
            n->setTrig("sin");                                                          //sets the trig value to sin
        }
        else if(static_cast<int>(p.find("tan")) > 0 && static_cast<int>(p.find("sin")) == -1 && static_cast<int>(p.find("cos")) == -1)  //if tan is found (not at beginning)
        {
            if(neg)                                                                     //sets outer to its outer coefficient times -1
            {
                n->setOuter(stoi(p.substr(0,static_cast<int>(p.find("tan")))) * -1);
            }
            else                                                                        //sets outer to its outer coefficient 
            {
                n->setOuter(stoi(p.substr(0,static_cast<int>(p.find("tan")))));    
            }
            n->setTrig("tan");                                                          //sets trig value to tan
        }
        else if(static_cast<int>(p.find("cos")) > 0 && static_cast<int>(p.find("tan")) == -1 && static_cast<int>(p.find("sin")) == -1)  //if cos is found (not at beginning)
        {
            if(neg)                                                                     //sets outer to its outer coefficient times -1
            {
                n->setOuter(stoi(p.substr(0,static_cast<int>(p.find("cos")))) * -1);
            }
            else                                                                        //sets outer to its outer coefficient
            {
                n->setOuter(stoi(p.substr(0,static_cast<int>(p.find("cos")))));    
            }
            n->setTrig("cos");                                                          //sets trig value to cos
        }
        p = p.substr(static_cast<int>(p.find(" "))+1);                                  //cuts the string to start where there aren't no spaces
        
        if(p[0] != 'x')                                                                 //if the first character of the string is NOT x
        {
            n->setInner(stoi(p.substr(0, static_cast<int>(p.find('x')))));              //set inner to the numerical value before the x
        }
    }
    else                                                                                //if there is no trig
    {
        if(static_cast<int>(p.find('x')) == -1)                                         //if x is not found in the string, set outer to the string & exponent to 0
        {
            n->setOuter(stoi(p));                                                       
            n->setExp(0);
        }
        else
        {
            if(p[0] == 'x')                                                             //if x is the first element of the string     
            {
                if(neg)                                                                 //if neg is true, set outer to -1
                {
                    n->setOuter(-1);
                    n->setExp(1);
                }
                else
                {
                    n->setOuter(1);
                    n->setExp(1);
                }
            }
            else                                                                        //if x is not the first element of the string
            {
                if(neg)
                {
                    n->setOuter(stoi(p.substr(0,static_cast<int>(p.find('x')))) * -1);  //set outer coefficient to whatever was in front of x times -1
                }
                else
                {
                    n->setOuter(stoi(p.substr(0,static_cast<int>(p.find('x')))));       //sets outer coefficient to whatever was in front of x
                }
            }
            if(static_cast<int>(p.find('^')) != -1)                                     //if there is the ^ symbol
            {
                p = p.substr(static_cast<int>(p.find('^'))+1);                          //cut the string and get the numerical value after ^ and set it to exp
                n->setExp(stoi(p));
            }
        }
    }
    p = "";                                                                             //make the string empty
    neg = 0;                                                                            //set neg to false
}

void addNode(LList& l, Node* n)                                                         //adds nodes in chronological order    
{
    if(!l.getHead())                                                                    //if there is no head in the LList
    {
        l.setHead(n);                                                                   //set the n as the head
    }
    else                                                                                //if there is a head
    {
        if(l.getHead()->getNext() == nullptr)                                           //if there is nothing after head, set n as the next node
        {
            l.getHead()->setNext(n);    
        }
        else                                                                            //if there are things after head
        {
            Node *trav = l.getHead();
            while(trav->getNext())                                                      //travel to the end and set the node as the next of the last node
            {
                trav = trav->getNext();
            }
            trav->setNext(n);
        }
    }
}
void createNodes(string &c, LList& l)                                                   //creates the nodes for the linked list
{
    Node *newNode;                                                                      //creates node pointer, counter variable, string, and a boolean variable
    int count = 0;                                                                      //that will tell if outer should be negative to make the function possible
    string p = "";
    bool isNeg = 0;
    
    while(c != "")                                                                      //while c is not an empty string
    {
        newNode = new Node;                                                             //create a new node
        if(static_cast<int>(c.find(" - ")) == -1 && static_cast<int>(c.find(" + ")) == -1)  //if there are no operators in the string
        {
            p = c;                                                                      //make the string we created equal to the string as an argument
            if(static_cast<int>(p.find('(')) == -1)
                parseString(p, isNeg, newNode);
            else
                parseBonus(p, isNeg, newNode);
            c = "";                                                                     //set c as empty
        }
        else if(static_cast<int>(c.find(" - ")) != -1 && static_cast<int>(c.find(" + ")) != -1) //if both a + and - operators are in the string
        {
            if(static_cast<int>(c.find(" - ")) < static_cast<int>(c.find(" + ")))               //if the - operator comes first
            {
                p = c.substr(0, static_cast<int>(c.find(" - ")));                               //find it and parse that string and make p equal what c is until that index    
                if(static_cast<int>(p.find('(')) == -1)
                    parseString(p, isNeg, newNode);
                else
                    parseBonus(p, isNeg, newNode);
                c = c.substr(static_cast<int>(c.find(" - "))+3);                                //remove what we already processed from the string
                isNeg = 1;                                                                      //set isNeg to true because of the - operator
            }
            else if(static_cast<int>(c.find(" - ")) > static_cast<int>(c.find(" + ")))          //if + operator comes first
            {
                p = c.substr(0, static_cast<int>(c.find(" + ")));                               //find it and parse that string and make p equal what c is until that index
                if(static_cast<int>(p.find('(')) == -1)
                    parseString(p, isNeg, newNode);
                else
                    parseBonus(p, isNeg, newNode);
                c = c.substr(static_cast<int>(c.find(" + "))+3);                                //remove what we processed from c
            }
        }
        else if(static_cast<int>(c.find(" - ")) != -1 && static_cast<int>(c.find(" + ")) == -1) //if there is only a - operator
        {
            p = c.substr(0, static_cast<int>(c.find(" - ")));                                   //find it and parse that string and make p equal what c is until that index
            if(static_cast<int>(p.find('(')) == -1)
                parseString(p, isNeg, newNode);
            else
                parseBonus(p, isNeg, newNode);
            c = c.substr(static_cast<int>(c.find(" - "))+3);                                    //remove what we processed from c
            isNeg = 1;                                                                          //set isNeg is true because of the - operator
        }
        else if(static_cast<int>(c.find(" - ")) == -1 && static_cast<int>(c.find(" + ")) != -1) //if there is only a + operator
        {
            p = c.substr(0, static_cast<int>(c.find(" + ")));                                   //find it and parse that string and make p equal what c is until that index
            if(static_cast<int>(p.find('(')) == -1)
                parseString(p, isNeg, newNode);
            else
                parseBonus(p, isNeg, newNode);
            c = c.substr(static_cast<int>(c.find(" + "))+3);                                    //remove what we processed from c
           
        }
        if(count == 0)          //if counter variable is still 0
        {
            l.setHead(newNode); //calls setHead function and increment the counter
            count++;
        }
        else
        {
            addNode(l, newNode);    //if counter is not 0, calls the addNode function and increments the counter
            count++;
        }
    }
}

void derivative(LList& l)       //makes another LList and makes it have the derivatives
{
    LList t(l.getHead());       //creates LList t and makes it have the same values as l
    Node *travel = t.getHead(); //set Node pointer to the beginning of t
    
    while(travel)               //while there are still items in LList
    {
        if(travel->getTrig() == "")         //if there are no trig values in the node
        {
            if(travel->getNum() == 0 && travel->getDenom() == 0)    //if numerator and denominator are not set to a value
            {
                travel->setOuter(travel->getOuter()*travel->getExp());  //set outer to outer times exponent
            }
            else
            {
                if(travel->getExp()!= 0 && (travel->getDenom()%travel->getExp() == 0))  //if the denominator can be divided by the exponent without a remainder,
                {                                                                       //set denom to its value divided by the exponent value
                    travel->setDenom(abs(travel->getDenom()/travel->getExp()));
                    if(travel->getExp() < 0)
                    {
                        travel->setNum(travel->getNum()*-1);                            //if the exponent is less than 0, multiply the numerator by -1
                    }
                }
                else
                {
                    travel->setNum(travel->getNum()*travel->getExp());                  //if denominator cannot be divided by exponent without a remainder,
                }                                                                       //set numerator to itself times the exponent value
                    if(travel->getNum()%travel->getDenom() == 0)
                    {
                        travel->setOuter(travel->getNum()/travel->getDenom());          //if numerator is divisible by denominator to make a whole number,
                        travel->setNum(0);                                              //set outer value to the quotient and set num and denom to zero
                        travel->setDenom(0);
                    }
            }
            if(travel->getExp() != 0)                               //if exponent is not 0, make the exponent equal to itself -1
            {
                travel->setExp(travel->getExp()-1);                 
            }
            else                                                    //if exponent is 0
            {
                travel->setOuter(0);                                //outer is set to 0
            }
        }
        else if(travel->getTrig() == "sin")                         //if trig is sin
        {
            if(travel->getNum() == 0 && travel->getDenom() == 0)        //if numerator and denominator values are not set
            {
                travel->setOuter(travel->getOuter()*travel->getInner());    //set outer to outer*inner
            }
            else
            {
                if((travel->getDenom()%travel->getInner() == 0))        //if num and denom are set, and denom is divisble by inner, set deom to itself/inner
                {
                    travel->setDenom(abs(travel->getDenom()/travel->getInner()));
                }
                else
                {
                    travel->setNum(travel->getNum()*travel->getInner());    //if that isn't possible, set numerator to itself times inner
                }
                if(travel->getNum()%travel->getDenom() == 0)                    //if num/denom is a whole number, set outer to their quotient and set num & denom to 0
                {
                    travel->setOuter(travel->getNum()/travel->getDenom());
                    travel->setNum(0);
                    travel->setDenom(0);
                }
            }
            travel->setTrig("cos");                                     //then set the trig value to cos
            
        }   
        else if(travel->getTrig() == "cos")                         //if trig is cos     
        {
            if(travel->getNum() == 0 && travel->getDenom() == 0)    //if numerator and denominator values are not set
            {
                travel->setOuter(-1*travel->getOuter()*travel->getInner());    //set outer to outer*inner
            }
            else
            {
                if((travel->getDenom()%travel->getInner() == 0))                //if num and denom are set, and denom is divisble by inner, set deom to itself/inner
                {
                    travel->setDenom(abs(travel->getDenom()/travel->getInner()));
                    travel->setNum(travel->getNum()*-1);                        //because of cos derivative, times num by -1
                }
                else
                {
                    travel->setNum(-1*travel->getNum()*travel->getInner()); //if not possible for denom and inner to be divisible, set num to -1* num times inner
                }
                if(travel->getNum()%travel->getDenom() == 0)                //if num/denom is a whole numeber, set outer to their quotient and set num & denom to 0
                {
                    travel->setOuter(travel->getNum()/travel->getDenom());
                    travel->setNum(0);
                    travel->setDenom(0);
                }
            }
            travel->setTrig("sin");                                     //set trig value to sin
        }
        else if(travel->getTrig() == "tan")                         //if trig is tan
        {
            if(travel->getNum() == 0 && travel->getDenom() == 0)    //if numerator values are not set
            {
                travel->setOuter(travel->getOuter()*travel->getInner());    //set outer to outer*inner
            }
            else
            {
                if((travel->getDenom()%travel->getInner() == 0))    //if denom can be divisible be inner, set denom to itself divided by inner
                {
                    travel->setDenom(abs(travel->getDenom()/travel->getInner()));
                }
                else
                {
                    travel->setNum(travel->getNum()*travel->getInner());    //if that's not possible, set num times inner value
                }
                if(travel->getNum()%travel->getDenom() == 0)                //if num/denom is a whole number, set outer to their quotient and set num and denom to 0
                {
                    travel->setOuter(travel->getNum()/travel->getDenom());
                    travel->setNum(0);
                    travel->setDenom(0);
                }
            }
            travel->setTrig("sec^2");                                   //set trig value to sec^2
        }
        travel = travel->getNext();                                 //move the pointer to the next node
    }
    
    cout << t;                                                       //prints values of t to the console
    
}
int main()
{
    LList l;                                                        //creates LList l
    fstream file;                                                   //creates file stream file to open the file
    string commands = "";                                           //creates commands to store the commands from the input file
    string fileName = getFileName(file);                            //gives the user input from getFileName function to a string variable
    file.open(fileName);
    while(getline(file, commands))                                  //while there still are commands in the file
    {
        createNodes(commands, l);                                   //call createNodes
        l.sort();                                                   //sorts the linked list
        derivative(l);                                              //calls the derivative function that will print to console
    }
    file.close();                                                   //close file for good programming practice
    return 0;
}