# Russell Todd
# Lab 4 for UWYO COSC 2030
# Stacks and Queues
#
# You'll be checking parentheses and reversing strings just like you did in C++
# However, in Python the class you'll be using is a List

paren1 = "(()((((()()()((()(((()()()()(((()(()()()(())()())()()))))()()()))()))()())())())))";
paren2 = "()((((((()(((((()((()()()()()(()))))))))()))()(())(())(((((()()(())))(()()())(()))";
paren3 = "(()((()(()()(()(((((()()(()()()((((()()(()()))()))))()()())))))()()())()()))())())";
paren4 = "(()()(((()()(()(()()(()()()()()()(()(((((((((())())))))()))))()()))()())()()))()))";
paren5 = "((())";
paren6 = ")))(((";

rev1 = "sekopog";
rev2 = "racecar";
rev3 = "regnolsignirtssiht";
rev4 = "wonybnwodsihtevahyllufepohdluohssyuguoy";

parens = [paren1, paren2, paren3, paren4, paren5, paren6]
rever = [rev1, rev2, rev3, rev4]

# Finish this function
# You must complete it using a List in a similar manner as a Queue
def parenCheck(toCheck):
    pseudoQueue = []
    counter = 0

    for char in toCheck:
        pseudoQueue.insert(0, char)

    while (pseudoQueue):
        if (pseudoQueue[-1] == "("):
            counter += 1
        elif (pseudoQueue[-1] == ")"):
            counter -= 1
            if counter < 0:
                return False
            
        pseudoQueue.pop()

    return True if counter == 0 else False


# Finish this function
# You must complete it using a List in a similar manner as a Stack
def stringReverse(toReverse):
    pseudoStack = []
    returnString = ""

    for char in toReverse:
        pseudoStack.append(char)
    
    while (pseudoStack):
        returnString += pseudoStack.pop()

    return returnString


# Time to check some parentheses
for i in range(6):
    print("Checking string"+str(i+1))
    if parenCheck(parens[i]):
        print("String"+str(i+1)+" is good.")
    else:
        print("String"+str(i+1)+" is bad.")

# Time to reverse some strings
for j in range(4):
    print("Reversing string"+str(j+1))
    print(stringReverse(rever[j]))

