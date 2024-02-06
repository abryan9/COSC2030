// Danny Radosevich
// Lab 5
// Written for UWYO COSC 2030
// must be compiled with c++ 11

#include "card.h"
#include <vector>
#include <string>
#include <deque>
#include <iostream>
#include <algorithm>
#include <random>
#include <ctime>
#include <cstdlib>

using namespace std;

bool parenCheck(string toCheck);
string stringReverse(string toReverse);
void buildAndDeal();

int myRand(int i)
{
  return rand()%i;
}

/*DO NOT CHANGE MAIN OR THE FUNCTION DECLARATIONS*/
int main()
{
  //paren strings
  string paren1 = "(()((((()()()((()(((()()()()(((()(()()()(())()())()()))))()()()))()))()())())())))";
  string paren2 = "(()))";
  string paren3 = "(()((()(()()(()(((((()()(()()()((((()()(()()))()))))()()())))))()()())()()))())())";
  string paren4 = "(()()(((()()(()(()()(()()()()()()(()(((((((((())())))))()))))()()))()())()()))()))";
  string paren5 = "((())";
  string paren6 = ")))(((";

  //strings to reverse
  string rev1 = "sekopog";
  string rev2 = "racecar";
  string rev3 = "regnolsignirtssiht";
  string rev4 = "wonybnwodsihtevahyllufepohdluohssyuguoy";

  //Putting the strings in the vector
  vector<string> parens;
  parens.push_back(paren1);
  parens.push_back(paren2);
  parens.push_back(paren3);
  parens.push_back(paren4);
  parens.push_back(paren5);
  parens.push_back(paren6);

  vector<string> rever;
  rever.push_back(rev1);
  rever.push_back(rev2);
  rever.push_back(rev3);
  rever.push_back(rev4);


  //this is the function call for the card deck
  //you will need to complete the function.
  cout<<"-"<<endl;
  buildAndDeal();
  cout<<"-"<<endl;

  // Now the string checks with deques
  //call the parenCheck
  for(int i=0; i<6; i++)
  {
    cout<<"Checking string"<<i+1<<endl;
    if(parenCheck(parens.at(i)))
    {
      cout<<"String"<<i+1<<" is good"<<endl<<endl;
    }
    else
    {
      cout<<"String"<<i+1<<" is bad"<<endl<<endl;
    }
  }

  //now to reverse some strings
  for(int i =0; i<4; i++)
  {
    cout<<"Reversing string"<<i+1<<endl;
    cout<<stringReverse(rever.at(i))<<endl<<endl;
  }
}

void buildAndDeal()
{
  /*
    For this function you will be using a vector to build a standard 52 card deck,
    and then dealing a hand of 5 cards.
    Remeber a deck of cards has 4 suits, hearts, diamonds, spades, clovers
    and each suit has 13 cards 2,3,4,5,6,7,8,9,10,Jack,Queen,King,Ace

  */
  //vector declaraion
  //need card* as we will be storing pointers
  //we do this to add the cards dynamically
  vector<card*> myDeck;
  //here is an example of declaring cards
  /*
    //putting a new card in the deck
    myDeck.push_back(new card);

    Want an example of setting the face and suit? Look at card.h for the functions
    and read through the code below to see how to access functions
  */
  //build a deck of card
  int position = 0;
  string suit[4] = {"Spades", "Clubs", "Hearts", "Diamonds"};
  string face[13] = {"Ace", "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King"};
  for(int i = 0; i <4; i++)
  {
    //your code goes Here
    //hint think about suits

    for(int j = 0; j <13; j++)
    {
      //your code goes Here
      //hint think about face

      card * tmp = new card;
      tmp -> setSuit(suit[i]);
      tmp -> setFace(face[j]);
      myDeck.push_back(tmp);

      position++;
    }
  }
  //print deck, make sure you have it all!

  // DO NOT CHANGE THESE FOLLOWING TWO LINES OF CODE
  // OR THE FUNCTION UP TOP
  // it will break and you will be sad
  srand(unsigned(time(NULL)));
  random_shuffle(myDeck.begin(), myDeck.end(),myRand);

  cout<<"here is your hand"<<endl;
  for(int i =0; i<5&&i<myDeck.size(); i++)
  {
    cout<<myDeck.at(i)->getSuit()<<" "<<myDeck.at(i)->getFace()<<endl;
  }
}

bool parenCheck(string toCheck)
{
  deque<char> checker; //declare my queue
  
  for (char paren : toCheck) {
    if (paren == '(') {
      checker.push_front(paren);
    } else {
      if (checker.empty()) {
        return false;
      }

      checker.pop_back();
    }
  }

  if (checker.empty()) {
    return true;
  }

  return false;
}

string stringReverse(string toReverse)
{
  deque<char> reverse;
  string newString = "";
  
  for (char i : toReverse) {
    reverse.push_front(i);
  }

  while (!reverse.empty()) {
    newString += (reverse.at(0));
    reverse.pop_front();
  }

  return newString;
}