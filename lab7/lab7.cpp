//  Lab 7
//  Written for UWYO COSC 2030
//  Russell Todd

#include<iostream>
#include<string>
#include<vector>
#include <ctime>
#include <algorithm>

using namespace std;

#define HASHSIZE 73 // YOU CANNOT CHANGE THIS.

int hasher(string toHash)
{
    // Inside of this function is where you write your code. Do not change anything else in the program.
    // You start with a simple hasher function. Improve it! The better your hasher function is, the fewer collisions there will be.
    int i; long int val = 0;

    for (i = 0; i <= toHash.size(); i++)
    {
        val += (int)toHash[i] * (i+9);
    }

    return val % HASHSIZE;
}

// This is a simple example hasher function from Ward. Don't change it!
int example(string toHash)
{
    int i; long int val = 0;

    for (i = 0; i <= toHash.size(); i++)
    {
        val += (int)toHash[i] * (i * i);
    }

    //divide by the size of the array to make sure you always get something within bounds
    return val % HASHSIZE;
}


//################################################################################################
//   YOU DON'T NEED TO WORRY ABOUT ANYTHING BELOW THIS. YOU CAN READ IT, BUT DON'T CHANGE IT
//################################################################################################
struct returnedHash
{
    int hashReturned;
    int collisions;
};

string gen_random(const int len)
{
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
    string tmp_s;
    //tmp_s.reserve(len);

    for (int i = 0; i < len; i++)
    {
        tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];
    }

    return tmp_s;
}

bool collisionCheck(vector<returnedHash>* vec, int hashNum)
{
    if (vec->size() >= 1)
    {
        for (int i = 0; i < vec->size(); i++)
        {
            if (vec->at(i).hashReturned == hashNum)
            {
                vec->at(i).collisions++;
                return true;
            }
        }
        return false;
    }
    else
    {
        return false;
    }
}

bool structCompare(const returnedHash& a, const returnedHash& b)
{
    return a.hashReturned < b.hashReturned;
}

void readCollisions(vector<returnedHash>* vec)
{
    sort(vec->begin(), vec->end(), structCompare);

    if(vec->size() >= 1)
    {
        for (int i = 0; i < vec->size(); i++)
        {
            std::cout << "Hash Value " << to_string(vec->at(i).hashReturned) << " collisions: " << to_string(vec->at(i).collisions) << endl;
        }
    }
    else
    {
        std::cout << "vec is empty" << endl;
    }
}

int main()
{
    string input = "";
    string testInput = "";
    bool control = true;

    vector<returnedHash> wardTestOutput;
    vector<returnedHash> yourTestOutput;
    int numOfStringLengths = 10;
    int numOfStringsPerLengths = 10;
    double wardCollisions;
    double yourCollisions;
    double wardTotalCollisions;
    double yourTotalCollisions;
    double wardMetaCollisions;
    double yourMetaCollisions;
    srand(time(0));

    while (control)
    {
        std::cout << "Enter something to hash, STOP to stop, TEST to compare hasher performance, or TESTMETA to get average of 10,000 TESTs" << endl;
        cin >> input;

        if (input == "STOP")
        {
            control = false;
        }
        else if (input == "TEST")
        {
            wardTestOutput.clear();
            yourTestOutput.clear();

            wardTotalCollisions = 0;
            yourTotalCollisions = 0;

            for (int i = 1; i < numOfStringLengths; i++)
            {
                std::cout << "\n----- SIZE " << to_string(i) << " -----------------------------------------\n" << endl;
                wardCollisions = 0;
                yourCollisions = 0;

                for (int j = 0; j < numOfStringsPerLengths; j++)
                {
                    testInput = gen_random(i);
                    std::cout << "testInput" << to_string(j) << ": " << testInput << endl;

                    int temp1 = example(testInput);
                    int temp2 = hasher(testInput);

                    //cout << "Ward's hash returned " << to_string(temp1) << endl;
                    if (collisionCheck(&wardTestOutput, temp1) == false)
                    {
                        returnedHash tempHash1;
                        tempHash1.hashReturned = temp1;
                        tempHash1.collisions = 0;
                        wardTestOutput.push_back(tempHash1);
                    }
                    else
                    {
                        wardCollisions++;
                    }

                    //cout << "Your hash returned " << to_string(temp2) << endl << endl;
                    if (collisionCheck(&yourTestOutput, temp2) == false)
                    {
                        returnedHash tempHash2;
                        tempHash2.hashReturned = temp2;
                        tempHash2.collisions = 0;
                        yourTestOutput.push_back(tempHash2);
                    }
                    else
                    {
                        yourCollisions++;
                    }
                }

                std::cout << "\nWard example collisions for size " << i << ": " << wardCollisions << endl;
                wardTotalCollisions += wardCollisions;

                std::cout << "Your collisions for size " << i << ": " << yourCollisions << endl << endl;
                yourTotalCollisions += yourCollisions;

                std::cout << "Ward hash history contains " << to_string(wardTestOutput.size()) << " hash numbers:" << endl;
                readCollisions(&wardTestOutput);

                std::cout << "\nYour hash history contains " << to_string(yourTestOutput.size()) << " hash numbers:" << endl;
                readCollisions(&yourTestOutput);
            }

            std::cout << "\nWard example total collisions: " << wardTotalCollisions << endl << endl;
            std::cout << "Your total collisions: " << yourTotalCollisions << endl << endl;
        }
        else if (input == "TESTMETA")
        {
            wardMetaCollisions = 0;
            yourMetaCollisions = 0;

            for (int a = 0; a < 10000; a++)
            {
                //std::cout << "Test # " << to_string(a) << endl;
                wardTestOutput.clear();
                yourTestOutput.clear();

                wardTotalCollisions = 0;
                yourTotalCollisions = 0;

                for (int i = 1; i < numOfStringLengths; i++)
                {
                    wardCollisions = 0;
                    yourCollisions = 0;
                    for (int j = 0; j < numOfStringsPerLengths; j++)
                    {
                        testInput = gen_random(i);

                        int temp1 = example(testInput);
                        int temp2 = hasher(testInput);

                        if (collisionCheck(&wardTestOutput, temp1) == false)
                        {
                            returnedHash tempHash1;
                            tempHash1.hashReturned = temp1;
                            tempHash1.collisions = 0;
                            wardTestOutput.push_back(tempHash1);
                        }
                        else
                        {
                            wardCollisions++;
                        }

                        if (collisionCheck(&yourTestOutput, temp2) == false)
                        {
                            returnedHash tempHash2;
                            tempHash2.hashReturned = temp2;
                            tempHash2.collisions = 0;
                            yourTestOutput.push_back(tempHash2);
                        }
                        else
                        {
                            yourCollisions++;
                        }
                    }

                    wardTotalCollisions += wardCollisions;
                    yourTotalCollisions += yourCollisions;
                }

                wardMetaCollisions += wardTotalCollisions;
                yourMetaCollisions += yourTotalCollisions;
            }

            std::cout << "\nWard example average total collisions: " << to_string(wardMetaCollisions / 10000) << endl << endl;
            std::cout << "Your average total collisions: " << to_string(yourMetaCollisions / 10000) << endl << endl;
        }
        else
        {
            std::cout << "Ward's example hash returned " << to_string(example(input)) << endl;
            std::cout << "Your hash returned " << to_string(hasher(input)) << endl;
        }
    }

    return 0;
}