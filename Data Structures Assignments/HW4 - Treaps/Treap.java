import java.lang.Object;
import java.util.Random;
import java.util.Stack;

//Matthew Vaysfeld
//I pledge my honor that I have abided by the Stevens Honor System.

public class Treap<E extends Comparable<E>> {
	
	private static class Node<E>{
		// data fields
		public E data;       // key for the search
		public int priority; // random heap priority
		private Node<E> left;
		private Node<E> right;
		
		/**
		 * Base Constructor that initializes an empty node
		 */
		Node(E data, int priority) {
			if(data == null) {
				throw new IllegalArgumentException();
			}
			this.data = data;
			this.priority = priority;
			this.left = null;
			this.right = null;
		}
		/**
		 * Takes the current root of the tree and rotates it to the right
		 * @throws IllegalArgumentException when the roots left child is null
		 * @return the root of the new rotated tree
		 */
		public Node<E> rotateRight(){
			if(this.left == null) {
				throw new IllegalStateException();
			}
			Node<E> pivot = this.left;
			this.left= pivot.right;
			pivot.right = this;
			return pivot;
		}
		
		/**
		 * Takes the current root of the tree and rotates it to the left
		 * @throws IllegalArgumentException when the roots right child is null
		 * @return the root of the new rotated tree
		 */
		public Node<E> rotateLeft(){
			if(this.right == null) {
				throw new IllegalStateException();
			}
			Node<E> pivot = this.right;
			this.right = pivot.left;
			pivot.left = this;
			return pivot;
		}
		public String toString(){
			return "("+ "key="+ this.data + ", " + "priority=" + this.priority + ")";
		}

	}
	
	//Data Fields
	private Random priorityGenerator;
	private Node<E> root;
	
	/**
	 * Base Constructor that initializes an empty Treap
	 */
	public Treap() {
		this.root = null;
		this.priorityGenerator = new Random();
	}
	/**
	 * Base Constructor that initializes an empty Treap that 
	 * initializes the random number generator
	 */
	public Treap(long seed) {
		this.root = null;
		this.priorityGenerator = new Random(seed);
	}
	
	//Methods
	/**
	 * Adds a node with a specified key and a random priority to the Treap
	 * @param key
	 * @return true if node was successfully added, false if otherwise
	 */
	public boolean add(E key) {
		int priority = this.priorityGenerator.nextInt();
		return add(key,priority);
	}
	
	/**
	 * Adds a node with a specified key and a specified priority to the Treap
	 * @param key
	 * @param priority
	 * @return true if node was successfully added, false if otherwise
	 */
	public boolean add(E key , int priority ) {
		Node<E> newNode = new Node<E>(key, priority);
		if (root == null) {
			this.root = newNode;
			return true;
		}
		Stack<Node<E>> pancake = new Stack<Node<E>>();
		Node<E> current = this.root;
		Node<E> parent = null;
		while(current!= null) {
			if(current.data.compareTo(key) == 0) {
				return false;
			}
		else if(current.data.compareTo(key) > 0) {
				if (current.left == null) {
					current.left = newNode;
					pancake.push(current);
					pancake.push(newNode);
					break;
				}
				else {
					parent = current;
					pancake.push(current);
					current = current.left;
				}
			}
			else if(current.data.compareTo(key) < 0) {
				if (current.right == null) {
					current.right = newNode;
					pancake.push(current);
					pancake.push(newNode);
					break;
				}
				else {
					parent = current;
					pancake.push(current);
					current = current.right;
				}
			}
		}
		reheap(pancake);
		return true;
	}
	
	/**
	 * Takes in a stack and modifies the Treap to restore its heap properties
	 * @param stack
	 */
	public void reheap(Stack<Node<E>> stack){
			Node<E> current1 = stack.pop();
			Node<E> current2 = stack.pop();
			Node<E> parent = null;
			if(stack.size()>0) {
				parent =stack.pop();
			}
			else {
				parent = null;
			}
			if (current2.priority > current1.priority) {
				return;
			}
			else if(current2.priority < current1.priority) {
				if (current1.data.compareTo(current2.data) < 0) {
					if(parent == null) {
						root = current2.rotateRight();
					}
					else {
						if(current2.data.compareTo(parent.data) > 0) {
							current2 = current2.rotateRight();
							parent.right = current2;
						}
						else{
							current2 = current2.rotateRight();
							parent.left = current2;
						}
					}
				}
				else if(current1.data.compareTo(current2.data) > 0) {
					if(parent == null) {
						root = current2.rotateLeft();
					}
					
					else{
						if(current2.data.compareTo(parent.data) > 0) {
							current2 = current2.rotateLeft();
							parent.right = current2;
						}
						else{
							current2 = current2.rotateLeft();
							parent.left = current2;
						}
					}	
				}
			}
			if (parent != null) {
				stack.push(parent);
				stack.push(current2);
				reheap(stack);
			}
		}
	
	/**
	 * This method deletes the Node with a specified key from the tree
	 * @param key
	 * @return true if the given key is in the tree and was deleted, returns false if the key is not in the tree
	 */
	public boolean delete(E key) {
		if(find(key) == false) {
			return false;
		}else {
			Node<E> current = this.root;
			Node<E> current2 = null;
			while(current.data.compareTo(key) != 0) {
				if(find(current.left, key) == false) {
					current2 = current;
					current = current.right;
				}
				else if(find(current.right, key) == false) {
					current2= current;
					current = current.left;
				}
			}
			if (current==root) {
				root = delete_helper(root);
				return true;
			}
			if(current2.left == current) {
				current2.left = delete_helper(current);
			}
			if(current2.right == current) {
				current2.right = delete_helper(current);
			}
			return true;
		}
	}
	/**
	 * Removes the node by trickling it down until it becomes a leaf, and then removes it
	 * @param current
	 * @return the node that replaces the current node
	 */		
	public Node<E> delete_helper(Node<E> current) {
		if(current.left == null && current.right == null) {
				return null;
			}
		else if (current.left == null){
				current = current.rotateLeft();
				current.left = delete_helper(current.left);
				return current;
			}
		else if (current.right == null) {
				current = current.rotateRight();
				current.right = delete_helper(current.right);
				return current;
			}
		else {
			if(current.left.priority < current.right.priority) {
					current = current.rotateLeft();
					current.left = delete_helper(current.left);
					return current;
					 }
			else if(current.left.priority > current.right.priority) {
					current = current.rotateRight();
					current.right = delete_helper(current.right);
					return current;
					 }
				return current;
				 }
		}
	
	
	
	
	/**
	 * Finds whether the node with a specified key exists in a Treap rooted in a specified root 
	 * @param root
	 * @param key
	 * @return true if the node with the specified key is in the Treap, if not returns false
	 */
	private boolean find(Node<E> root, E key) {
		if (root==null) {
			return false;
		} else {
			int c = key.compareTo(root.data);
			if (c==0) {
				return true;
			} else {
				if (c<0) {
					return find(root.left, key);
				} else {
					return find(root.right, key);
				}
			}
		}
	}
	/**
	 * Finds whether a node with a given key exists in the treap
	 * @param key
	 * @return true if the node with the specified key is in the Treap, if not returns false
	 */
	public boolean find (E key) {
		return find(root,key);
	}
	
	
	
	
	
	/**
	 * Traverses the tree and returns a representation of the nodes as a string
	 * @param current
	 * @param i
	 * @return the StringBuilder that represents the Treap
	 */
	private StringBuilder toString(Node<E> current, int i) {
		StringBuilder r = new StringBuilder() ;
		for (int j=0; j<i; j++) {
			r.append(" ");
		}
		
		if (current==null) {
			r.append("null\n");
		} else {
			r.append(current +"\n");
			r.append(toString(current.left,i+1));
			r.append(toString(current.right,i+1));
			
		}
		return r;
		
	}
	
	/**
	 * @return the String representation of the Treap
	 */
	public String toString() {
		return toString(root,0).toString();
	}
	
}
