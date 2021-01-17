// Name: Matthew Vaysfeld Section: B
// I pledge my honor that I have abided by the Steven's Honor System 


import java.util.ArrayList;


public class IDLList<E> {
	
	public static class Node<E> {
		// data fields
		private E data;
		private Node<E> next;
		private Node<E> prev;
		
		
		// Constructor

		public Node(E elem) {
			super();
			this.data = elem;
			this.next = null;
			this.prev = null;
		}
		
		public Node(E elem, Node<E> prev, Node<E> next) {
			super();
			this.data = elem;
			this.next = next;
			this.prev = prev;
		}
	}
	//data fields for IDLList
	Node<E> head;
	Node<E> tail;
	int size;
	ArrayList<Node<E>> indices;
	
	//Constructor
	public IDLList() {
		head=null;
		tail=null;
		size=0;
		indices= new ArrayList<Node<E>>();
	}
	
	
	//Methods
	public boolean add(int index, E elem) {
		Node<E> current = head;
		if (index<0 || index>size) { 				//throws exception if index doesn't work
			throw new IllegalArgumentException();
		}
		else if(size==0) {
			indices.add(new Node<E>(elem,null,null));
			tail= indices.get(0);
			head=tail;
			size++;
			return true;
		}
		else if (index == 0) {									//if the index is 0
			Node<E> newNode = new Node<E>(elem, null, current);
			newNode.next.prev=newNode;
			head = newNode;
	        indices.add(0,newNode);
	        size++;
	        return true;
	        }
		else if (index == size) {							//if the index equals size it adds it to the back of the list
			Node<E> newNode = new Node<E>(elem, indices.get(size-1), null);
			indices.add(newNode);
			tail=newNode;
			newNode.prev.next=newNode;
			size++;
			return true;
		}
		else {												//main case
	        Node<E> newNode = new Node<E>(elem, indices.get(index-1), indices.get(index));
	        indices.add(index,newNode);
	        newNode.prev.next = newNode;
	        newNode.next.prev = newNode;
	        size++;
	        return true;
		}
	}
	 public boolean add (E elem) { 				//adds to the front of the list
		 return add(0,elem);
	 }
	
	public boolean append (E elem) {			//adds to the back of the list
		return add(size,elem);
		
	}
	
	public E get (int index) {
		if (index<0) {
			throw new IllegalArgumentException();
		}
		if (index >= indices.size() || size==0) {
			throw new IllegalStateException();
		}
		return indices.get(index).data;
	}
	
	public E getHead () {
		if (size==0) {
			throw new IllegalStateException();
		}
		return head.data;
	}
	
	public E getLast () {
		if (size==0) {
			throw new IllegalStateException();
		}
		Node<E> current = head;
		while (current.next != null) {
			current=current.next;
		}
		return current.data;
	}
	
	 public E remove() {
		 return removeAt(0);
	 }
	 
	 public E removeLast() {
		 if (size==0) {
			 throw new IllegalStateException();
		 }
		 return removeAt(size-1);
	 }
	 
	 
	
	public E removeAt(int index) {
		if (index<0 || index>=size) { 				//throws exception if index doesn't work
			throw new IllegalArgumentException();
		}
		else if (head == null) {							//if list is empty
			throw new IllegalStateException();
		}
		if(size == 1) {
			 Node<E> removed = indices.remove(0);
			 head=null;
			 tail=null;
			 size=0;
			 return removed.data;
		 }
		else if (index == 0) {							//if the index is 0
			Node<E> newNode = indices.remove(0);
			Node<E> current = head;
			head = current.next;
	        if(head != null) {
	        	head.prev = null;
	        }
	        size--;
	        return newNode.data;
	        }
		else if (index == size-1) {
			Node<E> newNode = indices.remove(size-1);
			tail = tail.prev;
			if (head!=null) {
				tail.next = null;
			}
			size--;
			return newNode.data;
		}
		else {
			Node<E> current = indices.remove(index);
			current.prev.next = current.next;
			current.next.prev = current.prev;
	        size--;
	        return current.data;
		}
	}
	
	public boolean remove (E elem) {
		Node<E> current = head, prev=null;
		int index= 0;
		if (current!= null && current.data == elem) {
			head= current.next;
			indices.remove(index);
			return true;
		}
		while(current != null && current.data != elem) {
			prev = current;
			current= current.next;
			index++;
		}
		if (current == null) {
			return false;
		}
		prev.next=current.next;
		indices.remove(index);
		return true;
	}
	
	
	public int size() {
		return size;
	}
	
	public String toString() {
		StringBuilder s = new StringBuilder();
		Node<E> current = head;
		s.append("[");
		while (current!=null) {
			s.append(current.data.toString()+",");
			current = current.next;
		}
		s.append("]");
		return s.toString();
	}
	
}
