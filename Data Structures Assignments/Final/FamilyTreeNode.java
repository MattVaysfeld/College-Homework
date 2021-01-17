import java.util.ArrayList;
import java.util.List;

//Matthew Vaysfeld
//I pledge my honor that I have abided by the Steven's Honor System
public class FamilyTreeNode {
	// Data fields
	private String lastName;
	private List<Person> members;
	public FamilyTreeNode left;
	public FamilyTreeNode right;

	/**
     	* Constructor: instantializes a new FamilyTreeNode
     	* given a lastName
     	*/
	public FamilyTreeNode(String lastName) {
        	this.lastName = lastName;
        	this.members = new ArrayList<Person>();
        	this.left = null;
        	this.right = null;
	}

	/**
     	* Returns the last name of the FamilyTreeNode
     	*/
	public String getLastName() {
		return this.lastName;
	}

	/**
     	* Returns the arraylist of members in the FamilyTreeNode
     	*/
	public List<Person> getMembers() {
		return this.members;
	}

	/*
	 * Returns true if there is an instance of Person in the FamilyTreeNode that has
	 * the same first and last name provided Return false otherwise
	 */
	public boolean doesFamilyMemberExist(String lastName, String firstName) {
        	for(int i=0; i<members.size(); i++) {
        		if(members.get(i).getLastName().equals(lastName) &&  members.get(i).getFirstName().equals(firstName)) {
        			return true;
        		}
        	}
        	return false;
	}

	/**
	 * Returns true if there is an instance of Person in the FamilyTreeNode whose
	 * phone number matches the one provided Returns false otherwise
	 */
	public boolean doesNumberExist(String phoneNumber) {
		for(int i=0; i<members.size(); i++) {
    		if(members.get(i).getPhoneNumber().equals(phoneNumber)) {
    			return true;
    		}
    	}
    	return false;
	}

	/*
	 * Adds a Person to this FamilyTreeNode
	 * Throw an exception if the last name provided does not match the last name of the FamilyTreeNode
	 */
	public void addFamilyMember(String lastName, String firstName, String phoneNumber) {
		Person p = new Person(lastName, firstName, phoneNumber);
		this.addFamilyMember(p);
	}

	/**
	 * Adds a Person to this FamilyTreeNode
	 * Throw an exception if the last name provided does not match the last name of the FamilyTreeNode
	 */
	public void addFamilyMember(Person person) {
		if(! this.lastName.equals(person.getLastName())) {
			throw new IllegalArgumentException("last name invalid");
		}
		if(this.doesFamilyMemberExist(lastName, person.getFirstName())){
			throw new IllegalArgumentException();
		}
		if(this.doesNumberExist(person.getPhoneNumber())) {
			throw new IllegalArgumentException();
		}
		
		this.members.add(person);
	}

	/*
	 * Returns the phone number of the person in the family with the given phone
	 * number Returns "Does not exist." if not found
	 */
	public String getPhoneNumberOfFamilyMember(String lastName, String firstName) {
		for(int i=0; i<members.size(); i++) {
    		if(members.get(i).getLastName().equals(lastName) &&  members.get(i).getFirstName().equals(firstName)) {
    			return members.get(i).getPhoneNumber();
    		}
    	}
    	return "Does not exist.";
	}

	/*
	 * toString method Ex: [] [John Smith (5551234567), May Smith (5551234568),
	 * April Smith (5551234569), August Smith (5551234570)]
	 */
	public String toString() {
		StringBuilder sb = new StringBuilder();
		sb.append("[");
		for(int i=0; i<members.size(); i++) {
			sb.append(members.get(i).getFirstName());
			sb.append(" ");
			sb.append(members.get(i).getLastName());
			sb.append(" ");
			sb.append("(");
			sb.append(members.get(i).getPhoneNumber());
			sb.append(")");
			if(i != members.size() - 1) {
				sb.append(", ");
			}
		}
		sb.append("]");
		return sb.toString();
	}
}
