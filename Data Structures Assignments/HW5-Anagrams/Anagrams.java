import java.io.BufferedReader; 
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.Map;
import java.util.Set;

//Matthew Vaysfeld Section B
//I pledge my honor that I have abided by the Steven's Honor System.

public class Anagrams {
	//data fields
	final Integer[] primes =  
			{2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 
			31, 37, 41, 43, 47, 53, 59, 61, 67, 
			71, 73, 79, 83, 89, 97, 101};
	Map<Character,Integer> letterTable;
	Map<Long,ArrayList<String>> anagramTable;
	
/**
 * Builds the Letter Table that maps each letter to the first 26 primes
 */
	public void buildLetterTable() {
		letterTable = new HashMap<Character,Integer>();
		int charnumber = 97;
		for(int i=0; i< 26 ; i++) {
			letterTable.put( (char) (charnumber + i)  , primes[i]);
		}
	}
/**
 * Base Constructor that builds and empty HashMap which is the anagramTable
 */
	public Anagrams() {
		buildLetterTable();
		anagramTable = new HashMap<Long,ArrayList<String>>();
	}
/**
 * Computes the hashcode of a given word and adds it to the anagramTable
 * @param s
 */
	public void addWord(String s) {
		long hashcode = myhashcode(s);
		ArrayList<String> list = anagramTable.getOrDefault(hashcode,null);
		if (list == null) {
			anagramTable.put(hashcode, new ArrayList<String>());
			list = anagramTable.get(hashcode);
		}
		list.add(s);
	}
/**
 * Given the String s this method computes the hashcode by multiplying together
 * the primes associated with each letter in the string
 * @param s
 * @return the hashcode
 */
	public long myhashcode(String s) {
		long hashcode = 1;
		for (int i=0; i<s.length(); i++) {
			char key= s.charAt(i);
			int currentnumber = letterTable.get(key);
			hashcode = hashcode * currentnumber;
		}
		return hashcode;

	}
/**
 * Receives the name of a text file containing words and builds the anagram table
 * @param s
 * @throws IOException
 */
	public void processFile(String s) throws IOException {
		FileInputStream fstream = new FileInputStream(s);
		BufferedReader br = new BufferedReader(new InputStreamReader(fstream));
		String strLine;
		while ((strLine = br.readLine()) != null)   {
		  this.addWord(strLine);
		}
		br.close();
	}

/**
 * Returns the entries in the anagramTable that have the largest number of Anagrams
 * @return
 */
	public ArrayList<Map.Entry<Long,ArrayList<String>>> getMaxEntries() {
		ArrayList<Map.Entry<Long,ArrayList<String>>> anagram = new ArrayList<Map.Entry<Long,ArrayList<String>>>();
		int max = 0;
		Set<Map.Entry<Long,ArrayList<String>>> set = anagramTable.entrySet();
		for(Map.Entry<Long,ArrayList<String>> entry: set) {
			int current = entry.getValue().size();
			if(current> max) {
				max = current;
				while(anagram.size() > 0) {
					anagram.remove(0);
				}
				anagram.add(entry);
				
			}
			else if(current == max) {
				anagram.add(entry);
			}
		}
		
		
		return anagram;
	}
	/**
	 * Reads all of the strings in the file, places them in a hash table of anagrams
	 * and then iterates over the hash table to report which words have the largest
	 * number of anagrams
	 * @param args
	 */
	public static void main(String[] args) {
		Anagrams a = new Anagrams();

		final long startTime = System.nanoTime();    
		try {
			a.processFile("words_alpha.txt");
		} catch (IOException e1) {
			e1.printStackTrace();
		}
		ArrayList<Map.Entry<Long,ArrayList<String>>> maxEntries = a.getMaxEntries();
		final long estimatedTime = System.nanoTime() - startTime;
		final double seconds = ((double) estimatedTime/1000000000);
		System.out.println("Time: "+ seconds);
		System.out.println("List of max anagrams: "+ maxEntries);
		
	}
}
