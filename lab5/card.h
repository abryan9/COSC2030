// Danny Radosevich
// Written for UWYO COSC 2030
// Card Struct
#ifndef CARD_H
#define CARD_H
#include<string>

using namespace std;

struct card
{
private:
  string suit;
  string face;

public:
  void setSuit(string newSuit)
  {
    suit = newSuit;
  }
  void setFace(string newFace)
  {
    face = newFace;
  }
  string getSuit()
  {
    return suit;
  }
  string getFace()
  {
    return face;
  }
};
#endif