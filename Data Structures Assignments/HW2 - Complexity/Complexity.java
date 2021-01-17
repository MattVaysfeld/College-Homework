
//Pledge: I pledge my honor that I have abided by the Steven's Honor System.
//Name: Matthew Vaysfeld
//Section B

public class Complexity {

	public static void method1(int n) {
		int counter=0;
		for (int i=0; i<n;i++) {
			for(int j=0; j<n; j++) {
				counter++;
				System.out.println("Operation "+ counter);
			}
		}
	}
	
	public static void method2(int n) {
		int counter=0;
		for (int i=0; i<n;i++) {
			for(int j=0; j<n; j++) {
				for(int k=0; k<n; k++) {
				counter++;
				System.out.println("Operation "+ counter);
				}
			}
		}
	}
	
	public static void method3(int n) {
		int counter=0;
		for(int j=1; j<n; j*=2) {
				counter++;
				System.out.println("Operation "+ counter);
			}
		}
	
	 public static void method4(int n) {
		 int counter=0;
			for (int i=1; i<=n;i++) {
				for(int j=1; j<n; j*=2) {
					counter++;
					System.out.println("Operation "+ counter);
				}
			}
	 }
	 
	 public static void method5(int n) {
		int counter=0;
		for (int i=n; i>1;i= (int) Math.sqrt(i)) {
					counter++;
					System.out.println("Operation "+ counter);
				}
			}
	 public static int method6(int n) {
		 if (n == 0) {
			 return 1;
		 }
		 int counter=0;
		 for (int i=0; i<2 ; i++) {
			 counter += method6(n-1);
		}
		 return counter;
	}
	
	public static void main(String args[]) {
			method1(10);
			method2(3);
			method3(4);
			method4(7);
			method5(5);
			System.out.println(method6(2));
		}
		



}

