/*******************************************************************************
 * Name        : fastmult.cpp
 * Author      : Matthew Vaysfeld
 * Date        : November 28, 2020
 * Description : Implementation of fast multiplication algorithm.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>

using namespace std;

string add(const string& a, const string& b) {
	string ans = "";
	string tempa = a;
	string tempb = b;
	//Makes sure length of a is longer than b
	if(a.length() < b.length()){
		tempa = b;
		tempb = a;
	}
	// adds 0s to the front, so like 100 + 1 would be 100 + 001
	while(tempa.length() > tempb.length()){
		tempb = "0" + tempb;
	}
	//reverses both strings, could also be avoided if you start from the end of
	//the string and decrement
	reverse(tempa.begin(), tempa.end());
	reverse(tempb.begin(), tempb.end());

	int carry = 0;
	for(long unsigned int i=0; i < tempb.length(); i++){
		int aint = tempa[i]-'0'; //gets the char at index i in string a as an int
		int bint = tempb[i]-'0'; //gets the char at index i in string b as an int
		int sum = aint + bint + carry; //finds the sum of one line (if you think about addition as the sum of both number's digits in each digit place)
		ans+=(sum%10 + '0');  //adds the mod of the sum, since you cant have a digit longer than 10, to the answer
		carry = sum/10; //finds new carry
	}

	if(carry){
		ans+=(carry + '0');
	}
	reverse(ans.begin(),ans.end());
	return ans;

}



string subtract(const string& a, const string& b) {
	string ans = "";
	string tempa = a;
	string tempb = b;
	//reverses both strings, could also be avoided if you start from the end of
	//the string and decrement
	reverse(tempa.begin(), tempa.end());
	reverse(tempb.begin(), tempb.end());

	int carry = 0;
	for(long unsigned int i=0; i < tempb.length(); i++){
		int aint = tempa[i]-'0'; //gets the char at index i in string a as an int
		int bint = tempb[i]-'0'; //gets the char at index i in string b as an int
		int diff = aint - bint - carry; //finds the difference of one line

		//if the difference is negative we add 10 to it
		//in order to make it positive and then the carry becomes one
		//since the top number was less than the bottom
		if(diff < 0){
			diff += 10;
			carry = 1;
		}
		//otherwise we're fine, and the carry is just 0
		else{
			carry = 0;
		}
		ans+=(diff + '0'); //put the difference into the answer
	}

	//do the same thing but for the difference of the a and b
	for(long unsigned int i=tempb.length(); i < tempa.length(); i++){
		int aint = tempa[i]-'0';
		int diff = aint - carry;
		if(diff < 0){
			diff += 10;
			carry = 1;
		}
		else{
			carry = 0;
		}
		ans+=(diff + '0');
	}
	reverse(ans.begin(),ans.end());
	return ans;

}

string onedigmultiply(const string& a, const string& b) {
	string ans = "";
	int prod = (a[0] -'0') * (b[0] - '0');
	string product = to_string(prod);
	ans = ans + product;
	return ans;
}


bool isnotEven(int n){
	if(n%2 == 0){
		return false;
	}
	else{
		return true;
	}
}
string multiply(const string& a, const string& b) {
	string tempa = a;
	string tempb = b;
	if(a.length() != b.length()){
		if(a.length() > b.length()){
			while(tempa.length() > tempb.length()){
				tempb = "0" + tempb;
			}
		}

		else if(a.length() < b.length()){
			while(tempa.length() < tempb.length()){
				tempa = "0" + tempa;
			}
		}

	}
	if(isnotEven(tempa.length())){
				tempa = "0" + tempa;
	}
	if(isnotEven(tempb.length())){
				tempb= "0" + tempb;
	}
	if(tempa.length() == 2){
		string a1 = tempa.substr(0,(int) (tempa.length() / 2));
		string a0 = tempa.substr((int) (tempa.length() / 2),a.length());
		string b1 = tempb.substr(0,(int) (tempb.length() / 2));
		string b0 = tempb.substr((int) (tempb.length() / 2),tempb.length());

		string c2 = onedigmultiply(a1,b1);
		string c0 = onedigmultiply(a0,b0);
		string sum1 = add(a1,a0);
		string sum2 = add(b1,b0);
		string c1 = "0";
		if(sum1.length() != 1 || sum2.length() !=1){
			c1 = subtract(multiply(sum1,sum2), add(c2,c0));
		}
		else{
			c1 = subtract(onedigmultiply(sum1,sum2), add(c2,c0));
		}
		c2 = c2 + "00";
		c1 = c1 + "0";
		string ans = add(add(c2,c1),c0);
		if(stoi(ans) != 0){
			ans = ans.erase(0, ans.find_first_not_of('0'));
		}
		else{
			ans = "0";
		}
		return ans;
	}
	string a1 = tempa.substr(0,(int) (tempa.length() / 2));
	string a0 = tempa.substr((int) (tempa.length() / 2),tempa.length());
	string b1 = tempb.substr(0,(int) (tempb.length() / 2));
	string b0 = tempb.substr((int) (tempb.length() / 2),tempb.length());

	string c2 = multiply(a1,b1);
	string c0 = multiply(a0,b0);
	string sum1 = add(a1,a0);
	string sum2 = add(b1,b0);
	string c1 = subtract(multiply(sum1,sum2), add(c2,c0));
	c2 = c2 + string(tempa.length(), '0') ;
	c1 = c1 + string(tempa.length()/2, '0');
	string ans= add(add(c2,c1),c0);
	ans = ans.erase(0, ans.find_first_not_of('0'));
	if(ans.length() == 0){
		ans= "0";
	}
	return ans;
}




int main(int argc, char* const argv[])
{
	string s1 = argv[1];
	string s2 = argv[2];
	string ans = multiply(s1, s2);
	cout << ans << endl;

}
