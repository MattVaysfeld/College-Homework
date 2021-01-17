//Matthew Vaysfeld
//I pledge my honor that I have abided by the Steven's Honor System

public class Person {
	// Data fields
	private String firstName;
	private String lastName;
	private String phoneNumber;

	// Constructor
	public Person(String lastName, String firstName, String phoneNumber) {
		this.lastName = lastName;
		this.firstName = firstName;
		this.phoneNumber = phoneNumber;
	}

	// Getter methods
	public String getFirstName() {
		return this.firstName;
	}

	public String getLastName() {
		return this.lastName;
	}

	public String getPhoneNumber() {
		return this.phoneNumber;
	}

	// Setter methods
	public void setFirstName(String firstName) {
		this.firstName = firstName;
	}

	public void setLastName(String lastName) {
		this.lastName = lastName;
	}

	public void setPhoneNumber(String phoneNumber) {
		this.phoneNumber = phoneNumber;
	}

	public String toString() {
		return this.firstName + " " + this.lastName + " (" + this.phoneNumber + ")";
	}

	@Override
	public boolean equals(Object o) {
		if (o == null) {
			return false;
		}
		Person p = (Person) o;
		return this.firstName.equals(p.getFirstName()) && this.lastName.equals(p.getLastName())
				&& this.phoneNumber.equals(p.getPhoneNumber());
	}
}
