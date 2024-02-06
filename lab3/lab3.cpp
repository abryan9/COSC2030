//UWYO COSC 2030
//Lab 3
//Written by Danny Radosevich
//9-11-19
//recursion


#include<iostream>
#include<algorithm>
#include<string>

using namespace std;

//functions
/*
 For lab you will write the functions:
 findBinaryNotation
 isPalindrome
 recurSummation
 arrRev
*/
/*DO NOT CHANGE MAIN OR THE FUNCTION DEFINITIONS*/
string findBinaryNotation(int num);
bool isPalindrome(string palin);
int recurSummation(int bound);
void arrRev(char (&arr)[26], int low, int high);
string pad(string toPad);

int main()
{

  /*DO NOT CHANGE MAIN OR THE FUNCTION DEFINITIONS*/
  //variable declarations for the isPalindrome
  string palOne = "ppwtrrdooffffsmppnnvveeleewaszzpttmmrnhhnnmxbbvttauummkkbbvvjccjvvbbkkmmuuattvbbxmnnhhnrmmttpzzsaweeleevvnnppmsffffoodrrtwpp";
  string palTwo = "ffpmzaboodppvvvvwprryxzlluueffgghhdhehhdhgfjffeuullzxxyyymrpwwvwvpddoogbazznemsppf";
  string palThr = "tkkbbsbbgzaafwwhenttddccnnccbbelyyjjffkkjwewwjjkfjyleebcnnccdtnnehewwfgazgbsbkkktt";
  string palFou = "vjjuuqsvxxmfhwlluujjcjjffssggyxxaazppllysslxxoyttlllkaajxqqhhphhqqxjaaklllttyoxxlssyllppzaaxxyggssffjjcjjuullwhfmxxvsquujjv";
  string palFiv = "nkkgggnnghhdppccebbrrccceevvjjxxjdffyykkfejjgggkvyycssuubrqiistsiiqrbuusscyyvkgggjjefkkyyffdjxxjjvveecccrrbbeccppdhhgnngggkkn";
  string palSix = "ffkkrmrzzqggdkkddzkeemmttvtthsscmqqfcggggqqccccqiggggccfqjmcsshttvvtmmekzdkkddggqzzbvtrrmmrkff";
  //array for the reverse
  char alph[] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};

  //checking your findBinaryNotation
  (pad(findBinaryNotation(1))=="00000001")?(cout<<"You matched 00000001 correctly for 1"<<endl):(cout<<"You didn't match 00000001 correctly for 1"<<endl);
  (pad(findBinaryNotation(15))=="00001111")?(cout<<"You matched 00001111 correctly for 15"<<endl):(cout<<"You didn't match 00001111 correctly for 15"<<endl);
  (pad(findBinaryNotation(72))=="01001000")?(cout<<"You matched 01001000 correctly for 72"<<endl):(cout<<"You didn't match 01001000 correctly for 72"<<endl);
  (pad(findBinaryNotation(91))=="01011011")?(cout<<"You matched 01011011 correctly for 91"<<endl):(cout<<"You didn't match 01011011 correctly for 91"<<endl);

  cout<<"--------------------------------------------------------------------"<<endl;
  //Checking your isPalindrome
  cout<<"Checking palOne: ";
  (isPalindrome(palOne))?(cout<<"is a palindrome"<<endl):(cout<<"isn't a palindrome"<<endl);
  cout<<"Checking palTwo: ";
  (isPalindrome(palTwo))?(cout<<"is a palindrome"<<endl):(cout<<"isn't a palindrome"<<endl);
  cout<<"Checking palThr: ";
  (isPalindrome(palThr))?(cout<<"is a palindrome"<<endl):(cout<<"isn't a palindrome"<<endl);
  cout<<"Checking palFou: ";
  (isPalindrome(palFou))?(cout<<"is a palindrome"<<endl):(cout<<"isn't a palindrome"<<endl);
  cout<<"Checking palFiv: ";
  (isPalindrome(palFiv))?(cout<<"is a palindrome"<<endl):(cout<<"isn't a palindrome"<<endl);
  cout<<"Checking palSix: ";
  (isPalindrome(palSix))?(cout<<"is a palindrome"<<endl):(cout<<"isn't a palindrome"<<endl);
  cout<<"--------------------------------------------------------------------"<<endl;
  //checking recurSummation
  cout<<"Your summation for 0-6 is ";
  (recurSummation(6)==21)?(cout<<recurSummation(6)<<", Correct"<<endl):(cout<<recurSummation(21)<<", incorrect"<<endl);

  cout<<"Your summation for 0-47 is ";
  (recurSummation(47)==1128)?(cout<<recurSummation(47)<<", Correct"<<endl):(cout<<recurSummation(47)<<", incorrect"<<endl);

  cout<<"Your summation for 0-100 is ";
  (recurSummation(100)==5050)?(cout<<recurSummation(100)<<", Correct"<<endl):(cout<<recurSummation(100)<<", incorrect"<<endl);

  cout<<"Your summation for 0-500 is ";
  (recurSummation(500)==125250)?(cout<<recurSummation(500)<<", Correct"<<endl):(cout<<recurSummation(500)<<", incorrect"<<endl);
  cout<<"--------------------------------------------------------------------"<<endl;
  //checking your arrRev
  arrRev(alph,0,25);
  cout<<"Here is the reversed array";
  for(int i = 0; i< 26; i++)
  {
    if(i%5==0) cout<<endl;
    cout<<alph[i]<<", ";
  }
  cout<<endl;

}

//This function will find the binary notation of a supplied integer
/*
Supply the decimal number.
Divide the number by 2.
Make the remainder the right most number of the string.
Divide the result of the division by 2 and again concatenate it on to the string, building from the right to left.
Continue dividing and concatenating remainders until the result of the division is 0.
The most significant bit (MSB) is left side of the string and the least significant bit (LSB) is the right.
Return the series of 1s and 0s on the right from the bottom up. This is the binary equivalent of the decimal number.
*/
string  findBinaryNotation(int num)
{
 string binaryOutput;
 if (num > 0) {
  binaryOutput.append(findBinaryNotation(num / 2) + to_string(static_cast<char>(num % 2)));
 }

 return binaryOutput;
}
//This function will check to see if a string is a palindrome
/*
Starting with the base string check if the first and last characters match.
Recursively call the function on a substring without the first and last character if they match
If the characters do not match, return false.
Make sure you account for odd number strings, and when you are finished Checking
Return true when you get to the last 1 || 2 matching characters
*/
bool isPalindrome(string palin)
{
  bool check;
  
  if ((palin.length() > 1) && (palin[0] == palin[(palin.length() - 1)])) {
    palin.pop_back();
    palin.erase(0,1);

    // cout << palin << endl;
    isPalindrome(palin);
  } else if (palin.length() <= 1) {
    check = true;

  } else {
    check = false;
  }
  
  return check;
}
//This will form the summation of 0 to the supplied bound
/*
Starting with the bound work backwards towards zero
Recursivley call the function on bound-1 and sum each result
Make sure you have an exit coniditon for the function
*/
int recurSummation(int bound)
{
 int sum = bound;
 if (bound > 0) {
  sum += recurSummation(bound - 1);
 }

 return sum;
}
//This function will recursivley swap an array
/*
Starting with the outedges recursively call the function to swap elements moving from the out in
Move the low, high variables on each call
Check for when the varaibles cross paths to no longer call recursively
*/
void arrRev(char (&arr)[26], int low, int high)
{
 if (high > low) {
  char tmp = arr[low];
  arr[low] = arr[high];
  arr[high] = tmp;
  
  arrRev(arr, low + 1, high - 1);
 }
}
//this function simply pads the results of the findBinaryNotation to 8 characters
string pad(string toPad)
{
  if(toPad.length()>=8)
  {
    return toPad;
  }
  else
  {
    toPad.insert(toPad.begin(),8-toPad.length(),'0');
    return toPad;
  }

}
