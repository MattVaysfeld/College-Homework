
public class SingleLL<E> {
	private ListNode<E> head;
	private int size;

	  public SingleLL() {
	    this.head = null;
	    this.size = 0;
	  }

	  public int size() {
	    return this.size;
	  }

	  public ListNode<E> getHead() {
	    return this.head;
	  }

	  /**
	   * Adds data to the head of the list
	   * 
	   * @param data
	   */
	  public void push(E data) {
	    this.head = new ListNode<E>(data, this.head);
	    this.size++;
	  }

	  /**
	   * Adds data to the end of the list
	   * 
	   * @param data
	   */
	  public void append(E data) {
	    this.insert(this.size, data);
	  }

	  /**
	   * Inserts data at the specified index
	   * 
	   * @param index
	   * @param data
	   */
	  public void insert(int index, E data) {
	    if (index < 0 || index > this.size) {
	      throw new IllegalArgumentException("Index is out of bounds.");
	    }
	    if (index == 0) {
	      this.push(data);
	      return;
	    }
	    ListNode<E> curr = this.head;
	    for (int i = 0; i < index - 1; i++) {
	      curr = curr.getNext();
	    }
	    curr.setNext(new ListNode<E>(data, curr.getNext()));
	    this.size++;
	  }

	  /**
	   * Sets the element to the specified index in the list
	   * 
	   * @param index
	   * @param elem
	   */
	  public void set(int index, E elem) {
	    if (index < 0 || index >= this.size) {
	      throw new IllegalArgumentException("Out of bounds");
	    }
	    ListNode<E> curr = this.head;
	    for (int i = 0; i != index; i++) {
	      curr = curr.getNext();
	    }
	    curr.setData(elem);
	  }

	  /**
	   * returns the element at the specified index
	   * 
	   * @param index
	   * @return
	   */
	  public E get(int index) {
	    if (index < 0 || index >= this.size) {
	      throw new IllegalArgumentException("Out of bounds");
	    }
	    ListNode<E> curr = this.head;
	    for (int i = 0; i != index; i++) {
	      curr = curr.getNext();
	    }
	    return curr.getData();
	  }

	  /**
	   * Returns the List in string form
	   */
	  public String toString() {
	    StringBuilder sb = new StringBuilder();
	    sb.append("[");
	    for (ListNode<E> curr = this.head; curr != null; curr = curr.getNext()) {
	      sb.append(curr.toString() + (curr.getNext() != null ? ", " : ""));
	    }
	    sb.append("]");
	    return sb.toString();
	  }

}
