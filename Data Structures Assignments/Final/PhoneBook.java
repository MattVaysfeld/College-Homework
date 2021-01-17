import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;

//Matthew Vaysfeld
//I pledge my honor that I have abided by the Steven's Honor System

public class PhoneBook {
	// Data fields
	public Map<Character, BSFamilyTree> directory;

	/**
     	* Creates a new phone book with an empty directory.
     	*/
	public PhoneBook() {
		directory = new HashMap<Character,BSFamilyTree>();
		int charnumber = 65;
		for(int i=0; i< 26 ; i++) {
			BSFamilyTree bs = new BSFamilyTree();
			directory.put( (char) (charnumber + i)  , bs);
		}
	}

	/*
	 * Returns the instance of BSFamilyTree at the indicated letter
	 * Must accept lowercase letters as well as uppercase letters
	 */
	public BSFamilyTree getFamilyTree(char letter) {
		if (! Character.isLetter(letter)) {
			throw new IllegalArgumentException();
		}
		if (letter >= 97 && letter < 123) {
			letter -= 32;
		}
		return this.directory.get(letter);
	}

	/*
	 * Adds a FamilyTreeNode to the PhoneBook
	 */
	public void addFamily(String lastName) {
		char firstLetter = lastName.charAt(0);
		this.getFamilyTree(firstLetter).addFamilyTreeNode(lastName);
	}

	/*
	 * Adds a Person to the PhoneBook
	 * If a FamilyTreeNode with the given last name doesn't currently exist, create the FamilyTreeNode
	 */
	public void addPerson(String lastName, String firstName, String phoneNumber) {
		char firstLetter = lastName.charAt(0);
		if(! this.getFamilyTree(firstLetter).doesFamilyExist(lastName)) {
			this.addFamily(lastName);
		}
		if(this.getFamilyTree(firstLetter).doesNumberExist(phoneNumber)) {
        	throw new IllegalArgumentException();
        }
		boolean exist = false;
		for(int i= 65; i <= 90; i++) {
			if(this.getFamilyTree((char) i).doesNumberExist(phoneNumber)) {
				exist = true;
				break;
			}
		}
		if(exist == true) {
			throw new IllegalArgumentException();
		}
		this.getFamilyTree(firstLetter).getFamilyTreeNode(lastName).addFamilyMember(lastName,firstName, phoneNumber);
	}

	/*
	 * Finds the phone number of a person
	 * Returns 'Does not exist.' if not found.
	 */
	public String getPhoneNumber(String lastName, String firstName) {
		char firstLetter = lastName.charAt(0);
		if(! this.getFamilyTree(firstLetter).doesFamilyExist(lastName)) {
			return "Does not exist.";
		}
		else if(! this.getFamilyTree(firstLetter).getFamilyTreeNode(lastName).doesFamilyMemberExist(lastName,firstName)){
			return "Does not exist.";
		}
		return this.getFamilyTree(firstLetter).getFamilyTreeNode(lastName).getPhoneNumberOfFamilyMember(lastName, firstName);
	}

    	/**
     	* String representation of PhoneBook
     	*/
	public String toString() {
		StringBuilder sb = new StringBuilder();
		for(int i= 65; i<91 ; i++) {
			char current = (char) i;
			sb.append(current);
			sb.append('\n');
			sb.append(this.directory.get(current).toString());
		}
		return sb.toString();
	}
}
