
public class ListNode<E> {
	  private E data;
	  private ListNode<E> next;

	  public ListNode(E data) {
	    this.data = data;
	    this.next = null;
	  }

	  public ListNode(E data, ListNode<E> next) {
	    this.data = data;
	    this.next = next;
	  }

	  public void setNext(ListNode<E> newNext) {
	    this.next = newNext;
	  }

	  public ListNode<E> getNext() {
	    return this.next;
	  }

	  public void setData(E data) {
	    this.data = data;
	  }

	  public E getData() {
	    return this.data;
	  }

	  public String toString() {
	    return this.data.toString();
	  }
}
