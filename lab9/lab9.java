// Lab 9 
// Written by Russell Todd for COSC 2030

import java.io.*;
import java.util.*;
import java.util.regex.*;

class Lab9
{
    // Alter this value as needed
	final static int MAXSIZE = 100;
	
	static String stringReverse(String word)
	{
		Stack<Character> reverse = new Stack<Character>();
		String newString = "";
		char[] charWord = word.toCharArray();

		for (int i=0; i<charWord.length; i++) {
            reverse.push(charWord[i]);
        }

        while (!reverse.isEmpty()) {
            newString += reverse.pop();
        }
		
		return newString;
	}
	
	static Boolean parenCheck(String word)
	{
		Queue<Character> checker = new LinkedList<Character>();
        char[] charWord = word.toCharArray();
		
		for (int i=0; i<charWord.length; i++) {
            if (charWord[i] == ')') {
                if (checker.isEmpty()) {
                    return false;
                } else {
                    checker.remove();
                }
            } else {
                checker.add(charWord[i]);
            }
        }

        if (!checker.isEmpty()) {
            return false;
        }
		
		return true;
	}
	
	static String stringReverseVector(String word)
	{
		Vector<Character> reverse = new Vector<Character>();
		String newString = "";
        char[] charWord = word.toCharArray();
		
		for (int i=0; i<charWord.length; i++) {
            reverse.add(charWord[i]);
        }

        for (int i=reverse.size()-1; i>0; i--) {
            newString += reverse.get(i);
        }
		
		return newString;
	}
	
	static Boolean parenCheckDeque(String word)
	{
		Deque<Character> checker = new ArrayDeque<Character>();

        char[] charWord = word.toCharArray();
		
		for (int i=0; i<charWord.length; i++) {
            if (charWord[i] == ')') {
                if (checker.isEmpty()) {
                    return false;
                } else {
                    checker.remove();
                }
            } else {
                checker.add(charWord[i]);
            }
        }

        if (!checker.isEmpty()) {
            return false;
        }
		
		return true;
	}
	
	static Integer partition(Integer[] arr, Integer low, Integer high)
	{
	    Integer pivot = arr[high];
	    Integer lowIndex = (low - 1);
	    
	    for(int i = low; i < high; i++)
	    {
	        if(arr[i]<=pivot)
	        {
	            lowIndex++;
	            // Collections.swap(arr, lowIndex, i);
	            Integer temp = arr[lowIndex];
	            arr[lowIndex] = arr[i];
	            arr[i] = temp;
	        }
	    }
	    // Collections.swap(arr, lowIndex+1, high);
	    Integer temp = arr[lowIndex+1];
	    arr[lowIndex+1] = arr[high];
	    arr[high] = temp;
	    
	    return (lowIndex+1);
	}
	
	static void quickSort(Integer[] quick, Integer low, Integer high)
	{
	    if(low<high)
	    {
	        Integer partIndex = partition(quick, low, high);
	        
	        quickSort(quick, low, partIndex-1);
	        quickSort(quick, partIndex+1, high);
	    }
	}
	
	static void merge(Integer[] arr, Integer left, Integer mid, Integer right, Integer size)
	{
	    Integer i, j, k = 0;
	    Integer sizeOne = mid - left + 1;
	    Integer sizeTwo = right - mid;
	    
	    Integer[] leftArray = new Integer[sizeOne];
	    Integer[] rightArray = new Integer[sizeTwo];
	    
	    for(i = 0; i < sizeOne; i++)
	    {
	        leftArray[i] = arr[i+left];
	    }
	    
	    for(j = 0; j < sizeTwo; j++)
	    {
	        rightArray[j] = arr[mid + 1 + j];
	    }
	    
	    i = 0;
	    j = 0;
	    k = left;
	    
	    while(i<sizeOne && j<sizeTwo && k<size)
	    {
	        if(leftArray[i]<=rightArray[j])
	        {
	            arr[k] = leftArray[i];
	            i++;
	        }
	        else
	        {
	            arr[k] = rightArray[j];
	            j++;
	        }
	        k++;
	    }
	    
	    while(i<sizeOne && k<size)
	    {
	        arr[k] = leftArray[i];
	        i++;
	        k++;
	    }
	    
	    while(j<sizeTwo && k<size)
	    {
	        arr[k] = rightArray[j];
	        j++;
	        k++;
	    }
	    
	    leftArray = null;
	    rightArray = null;
	}
	
	static void mergeSort(Integer[] toMerge, Integer left, Integer right, Integer size)
	{
	    if(left<right)
	    {
	        Integer mid = left+(right-left)/2;
	        
	        mergeSort(toMerge, left, mid, size);
            mergeSort(toMerge, mid+1, right, size);

            merge(toMerge, left, mid, right, size);
	        
	    }
	}
	
	static void heapify(Integer[] arr, Integer size, Integer index)
	{
	    Integer largestPos = index;
	    Integer leftChildPos = 2*index+1;
	    Integer rightChildPos = 2*index+2;
	    
	    if(leftChildPos<size && arr[leftChildPos]>arr[largestPos])
	    {
	        largestPos = leftChildPos;
	    }
	    
	    if(rightChildPos<size && arr[rightChildPos]>arr[largestPos])
	    {
	        largestPos = rightChildPos;
	    }
	    
	    if(largestPos != index)
	    {
	        
	        Integer tmp = arr[largestPos];
            arr[largestPos] = arr[index];
            arr[index] = tmp;
	        
            heapify(arr, size, largestPos);
	    } 
	}
	
	static void heapSort(Integer[] heap, Integer size)
	{
	    for(Integer i = size/2 - 1; i>=0; i--)
	    {
	        heapify(heap, size, i);
	    }
	    
	    for(Integer i = size - 1; i>=0; i--)
	    {
	        //Collections.swap(heap, 0, i);
	        
	        Integer temp = heap[i];
	        heap[i] = heap[0];
	        heap[0] = temp;
	        
	        heapify(heap, i, 0);
	    }
	}
	
	static Boolean regExOne(String inputString)
	{
	    Pattern pattern = Pattern.compile("Cowboys");
        Matcher toMatch = pattern.matcher(inputString);
	    
	    return toMatch.find();
	}
	
	static Boolean regExTwo(String inputString)
	{
	    Pattern pattern = Pattern.compile("^7\\d{4}$");
        Matcher toMatch = pattern.matcher(inputString);
	    
	    return toMatch.find();
	}
	
	static Boolean regExThree(String inputString)
	{
	    Pattern pattern = Pattern.compile("[^z$J@]");
        Matcher toMatch = pattern.matcher(inputString);
	    
	    return toMatch.find();
	}
	
	
	public static void main (String[]args) throws IOException
	{
	    //paren strings
        String paren1 = "(()((((()()()((()(((()()()()(((()(()()()(())()())()()))))()()()))()))()())())())))";
        String paren2 = "()((((((()(((((()((()()()()()(()))))))))()))()(())(())(((((()()(())))(()()())(()))";
        String paren3 = "(()((()(()()(()(((((()()(()()()((((()()(()()))()))))()()())))))()()())()()))())())";
        String paren4 = "(()()(((()()(()(()()(()()()()()()(()(((((((((())())))))()))))()()))()())()()))()))";
        String paren5 = "((())";
        String paren6 = ")))(((";
        
        //strings to reverse
        String rev1 = "sekopog";
        String rev2 = "racecar";
        String rev3 = "regnolsignirtssiht";
        String rev4 = "wonybnwodsihtevahyllufepohdluohssyuguoy";
        
        Vector<String> parens = new Vector<String>();
        parens.addElement(paren1);
        parens.addElement(paren2);
        parens.addElement(paren3);
        parens.addElement(paren4);
        parens.addElement(paren5);
        parens.addElement(paren6);
        
        Vector<String> rever = new Vector<String>();
        rever.addElement(rev1);
        rever.addElement(rev2);
        rever.addElement(rev3);
        rever.addElement(rev4);
        
        // Calling the parenChecks
        System.out.println("\n" + "Checking parenCheck" + "\n");
        for(int i = 0; i<6; i++)
        {
            System.out.println("Checking string" + (i+1));
            if(parenCheck(parens.elementAt(i)))
            {
                System.out.println("String" + (i+1) + " is good" + "\n");
            }
            else
            {
                System.out.println("String" + (i+1) + " is bad" + "\n");
            }
        }
        
        System.out.println("\n" + "Checking parenCheckDeque" + "\n");
        for(int i = 0; i<6; i++)
        {
            System.out.println("Checking string" + (i+1));
            if(parenCheckDeque(parens.elementAt(i)))
            {
                System.out.println("String" + (i+1) + " is good" + "\n");
            }
            else
            {
                System.out.println("String" + (i+1) + " is bad" + "\n");
            }
        }
        
        System.out.println("\n" + "Checking stringReverse" + "\n");
        for(int i = 0; i<4; i++)
        {
            System.out.println("Reversing string" + (i+1) + "\n");
            System.out.println(stringReverse(rever.elementAt(i)));
        }
        
        System.out.println("\n" + "Checking stringReverseVector" + "\n");
        for(int i = 0; i<4; i++)
        {
            System.out.println("Reversing string" + (i+1) + "\n");
            System.out.println(stringReverseVector(rever.elementAt(i)));
        }
        
        
        System.out.println("\n" + "Beginning Sorting Check" + "\n");
        
        Integer[] heap = new Integer[MAXSIZE];
        Integer[] merge = new Integer[MAXSIZE];
        Integer[] quick = new Integer[MAXSIZE];
        
        Random rnd = new Random();
        
        for(int i = 0; i<MAXSIZE; i++)
        {
            Integer temp = rnd.nextInt(1000000) % (10*MAXSIZE);
            heap[i] = temp;
            merge[i] = temp;
            quick[i] = temp;
        }
        
        // prints arrays pre-sort to make sure they are the same
        System.out.println("\n" + "Arrays before sorting:");
        System.out.println("heap" + "\t" + "merge" + "\t" + "quick" + "\n");
        for(int i = 0; i<MAXSIZE; i++)
        {
            System.out.println(heap[i] + "\t" + merge[i] + "\t" + quick[i]);
        }
        
        heapSort(heap, MAXSIZE);
        mergeSort(merge, 0, MAXSIZE-1, MAXSIZE);
        quickSort(quick, 0, MAXSIZE-1);
        
        // prints arrays post-sort to make sure they are sorted
        System.out.println("\n" + "Arrays after sorting:");
        System.out.println("heap" + "\t" + "merge" + "\t" + "quick" + "\n");
        for(int i = 0; i<MAXSIZE; i++)
        {
            System.out.println(heap[i] + "\t" + merge[i] + "\t" + quick[i]);
        }
        
        
        System.out.println("Beginning RegEx Checks");
        
        Scanner in = new Scanner(System.in);
        
        System.out.println("The first RegEx will check for occurrences of 'Cowboys' ");
        String test1 = in.nextLine();
        System.out.println("You entered: " + test1);
        if(regExOne(test1))
        {
            System.out.println("Match found");
        }
        else
        {
            System.out.println("Match not found");
        }
        
        System.out.println("The second RegEx will check if your input is a 5-digit string starting with '7'");
        String test2 = in.nextLine();
        System.out.println("You entered: " + test2);
        if(regExTwo(test2))
        {
            System.out.println("Match found");
        }
        else
        {
            System.out.println("Match not found");
        }
        
        System.out.println("The third RegEx will check if your input contains any character other than an 'z', '$', 'J', or '@'");
        String test3 = in.nextLine();
        System.out.println("You entered: " + test3);
        if(regExThree(test3))
        {
            System.out.println("Match found");
        }
        else
        {
            System.out.println("Match not found");
        }
	}
}
