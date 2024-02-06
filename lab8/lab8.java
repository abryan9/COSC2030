import java.io.*;
import java.util.*;

class Lab8
{
	// Refer to lab instructions for program requirements.
	
	static String processWord (String word)
	{
		//*********************
		// YOUR CODE GOES HERE

        char[] charWord = word.toCharArray();
        String outputString = "";
		
        for (int i=0; i<charWord.length; i++) {
            if (Character.isLetter(charWord[i])) {
                if (Character.isUpperCase(charWord[i])) {
                    charWord[i] = Character.toLowerCase(charWord[i]);
                }
                outputString += charWord[i];
            }
        }

        return outputString;
		//*********************
	}
	
	public static void main (String[]args) throws IOException
	{
		//*********************
		// YOUR CODE GOES HERE

        String line = new String();
        BufferedReader in = new BufferedReader(new FileReader("input.txt"));
        Vector<String> outVector = new Vector<String>();

        line = in.readLine();
        while (line != null) {

            line = processWord(line);
            outVector.add(processWord(line));
            line = in.readLine();
        }

        Collections.sort(outVector);
        for (int i=0; i<outVector.size(); i++) {
            System.out.println(outVector.get(i));
        }

        in.close();
		//*********************
	}
	
}