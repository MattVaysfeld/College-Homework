package Binary;

import java.util.Arrays;

//Matthew Vaysfeld Section A
//I pledge my honor that I have abided by the Steven's Honor Systen.

public class BinaryNumber {
	//data fields
	private int[] data;
	private int length;
	//constructors
	public BinaryNumber(int length) {
		if(length<0) {
			throw new IllegalArgumentException();
		}
		this.length = length;
		this.data=new int[length];
	}
	
	public BinaryNumber(String str) {
		this.length = str.length();
		this.data = new int[this.length];
		for (int i=0; i<str.length(); i++) {
			if(!(str.charAt(i)=='0' || str.charAt(i)=='1')) {
				throw new IllegalArgumentException();
			}
			this.data[i]= Character.getNumericValue(str.charAt(i));
		}
	}
	//Methods
	public int getLength(){
		return this.length;
	}
	public int[] getInnerArray() {
		return this.data;
	}
	
	public int getDigit(int index) {
		if(index<0 || index>=this.length) {
			throw new IndexOutOfBoundsException();
		}
		return this.data[index];
	}

	public static int[] bwor(BinaryNumber bn1, BinaryNumber bn2) {
		if (bn1.length != bn2.length){
			throw new IllegalArgumentException();
		}
		else {
			int[] bword = new int[bn1.length];
			for(int i=0; i<bn1.length; i++) {
				if (bn1.data[i] == 0 && bn2.data[i]== 0) {
					bword[i]= 0;
				}
				else {
					bword[i]=1;
				}
			}
			return bword;
		}
	}
	public static int[] bwand(BinaryNumber bn1, BinaryNumber bn2) {
		if (bn1.length != bn2.length){
			throw new IllegalArgumentException();
		}
		else {
			int[] bward = new int[bn1.length];
			for(int i=0; i<bn1.length; i++) {
				if (bn1.data[i] == 1 && bn2.data[i]== 1) {
					bward[i]= 1;
				}
				else {
					bward[i]=0;
				}
			}
			return bward;
		}
	}
	public void bitShift(int direction, int amount) {
		//Shift to the Right
		if (direction==1 && amount>=0) {
			if(amount>length) {
				throw new IllegalStateException();
			}
			int[] array = new int[(this.length) - amount];
			length= length - amount;
			for (int i=0; i<length;i++) {
				array[i]= data[i];
			}
			this.data=array;
		}
		//Shift to the Left
		else if (direction==-1 && amount>=0) {
			int[] array = new int[(this.length) + amount];
			length= length + amount;
			for (int i=0; i<length-amount;i++) {
				array[i]= this.data[i];
				}
			this.data=array;
			}
		else {
			throw new IllegalArgumentException();
		}
		}
	public void prepend(int amount) {
		int[] pArray= new int[this.length+amount];
		for(int i=0;i<length;i++) {
			pArray[i+amount]=data[i];
		
		}
		length+=amount;
		data=pArray;
	}
	
	
	public void add(BinaryNumber aBinaryNumber) {
		if (aBinaryNumber.getLength() > this.length) {
			this.prepend(aBinaryNumber.getLength()-this.length);
			}
		else if (aBinaryNumber.getLength() < this.length) { 
			aBinaryNumber.prepend(this.length-aBinaryNumber.getLength());
		}
		int carry= 0;
		int[] allsum= new int[aBinaryNumber.getLength()];
		for(int i=aBinaryNumber.getLength()-1; i>=0;i--) {
			int sum = aBinaryNumber.getInnerArray()[i] + this.data[i] + carry;
			if (sum==3) {
				carry=1;
				allsum[i]=1;
			}
			else if (sum==2) {
				carry=1;
				allsum[i]=0;
			}
			else if (sum==1) {
				carry=0;
				allsum[i]=1;
			}
			else if (sum==0) {
				carry=0;
				allsum[i]=0;
			}
		}
		if(carry==1) {
			int [] carryarray= new int[allsum.length+1];
			for (int i=1; i<=allsum.length;i++) {
				carryarray[i]= allsum[i-1];
			}
			carryarray[0]=1;
			allsum=carryarray;
				
		}
		this.data = allsum;
		this.length = this.data.length;
	}




	public String toString(){
		String binstr = new String("");
		for(int i=0;i<this.length;i++) {
			binstr+=data[i];
		}
		return binstr;
		
	}

	public int toDecimal() {
		double sum = 0;
		for (int i=this.length-1; i>=0; i--) {
			if (data[i]==1) {
				sum = sum+Math.pow(2,(this.length-1-i));
			}
		}
		return (int)sum;
	}

}
