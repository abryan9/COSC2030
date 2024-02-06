# Danny Radosevich
# Lab 5
# Written for UWYO COSC 2030
import collections

def rever(toRever):
    revDeq = collections.deque([])
    returnVal = ''
    
    for char in toRever:
        revDeq.insert(0, char)
    
    while not (len(revDeq) == 0):
        returnVal += (revDeq.popleft())

    return returnVal

def parenCheck(toCheck):
    checkDeq = collections.deque([])
    
    for paren in toCheck:
        if paren == '(':
            checkDeq.insert(0, paren)
        else:
            if (len(checkDeq) == 0):
                return 0
                break
            
            checkDeq.pop()

    return not len(checkDeq) #return for the size evaluation

#think of this area as main
print("Starting reversal\n")
print(rever("sekopog"))
print(rever("peehsehttaeb"))
print(rever("sgnirtsgnisreverfoderitsyuguoyera"))
print(rever("maiesuaceb"))

if(parenCheck("(()((((()()()((()(((()()()()(((()(()()()(())()())()()))))()()()))()))()())())())))")):
    print("Paren string 1 is good") #should be
else:
    print("Paren string 1 is bad")

if(parenCheck("(()))")):
    print("Paren string 2 is good")
else:
    print("Paren string 2 is bad") #should be

if(parenCheck("(()((()(()()(()(((((()()(()()()((((()()(()()))()))))()()())))))()()())()()))())())")):
    print("Paren string 3 is good") #should be
else:
    print("Paren string 3 is bad")

if(parenCheck("(()()(((()()(()(()()(()()()()()()(()(((((((((())())))))()))))()()))()())()()))()))")):
    print("Paren string 4 is good") #should be
else:
    print("Paren string 4 is bad")

if(parenCheck("((())")):
    print("Paren string 5 is good")
else:
    print("Paren string 5 is bad") #should be

if(parenCheck(")))(((")):
    print("Paren string 6 is good")
else:
    print("Paren string 6 is bad") #should be