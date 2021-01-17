//Matthew Vaysfeld
//I pledge my honor that I have abided by the Steven's Honor System.

import java.util.ArrayList;
import java.util.List;

public class ListCollection<E> {
  private int nodeCount;
  protected List<SingleLL<E>> collection;

  /**
   * Base constructor, initializes an empty ListCollection.
   */
  public ListCollection() {
	  this.nodeCount = 0;
	  this.collection= new ArrayList<SingleLL<E>>();
  }

  /**
   * Initializes a ListCollection with `numLists` lists.
   * 
   * @param numLists
   */
  public ListCollection(int numLists) {
	  this();
	  for (int i=0; i<numLists ; i++) {
		  SingleLL<E> temp = new SingleLL<E>();
		  this.addList(temp);  
	  }
  }

  /**
   * @return The size of the `ListCollection`
   */
  public int size() {
  return collection.size();
  }
  

  /**
   * Sets the nodeCount
   * 
   * @param nodeCount
   */
  public void setNodeCount(int nodeCount) {
	  this.nodeCount = nodeCount;
  }

  /**
   * @return the nodeCount
   */
  public int getNodeCount() {
	  return this.nodeCount;

  }

  /**
   * Adds the specified `SingleLL` to the end of the `ListCollection`
   * 
   * @param list
   */
  public void addList(SingleLL<E> list) {
	  this.collection.add(list);
	  nodeCount+=list.size();
	  
  }

  /**
   * Adds the specified `List` to the `ListCollection`
   * 
   * @param list
   * @complexity The Big O for this method is O(n) because the for loop causes the 
   * values inside the list to be added n times, and since the adding the List to 
   * the collection is constant, the Big O is just O(n).
   */
  public void addList(List<E> list) {
	  SingleLL<E> temp = new SingleLL<E>();
	  for(E val: list) {
		  temp.push(val);
	  }
	  addList(temp);
  }

  /**
   * Returns the list at the specified index
   * 
   * @throws IllegalArgumentException when index out of bounds
   * @param listIndex
   * @return the list
   */
  public SingleLL<E> getList(int listIndex) {
	  if(listIndex >= size()) {
		  throw new IllegalArgumentException("out of bounds");
	  }
	  return collection.get(listIndex);

  }

  /**
   * Adds an element to the `elemIndex` position of the list at `listIndex`
   * 
   * @throws IllegalArgumentException when index out of bounds
   * @param listIndex
   * @param elemIndex
   * @param elem
   * @complexity The Big O for this method is O(n) because the getList method is 
   * constant but the insert method is linear. This means that the Big O is just O(n)
   * since although the T polynomial has both a n and a constant the Big O just becomes
   * O(n).
   */
  public void addElem(int listIndex, int elemIndex, E elem) {
	  if(listIndex >= size()) {
		  throw new IllegalArgumentException("out of bounds");
	  }
	  SingleLL<E> temp = getList(listIndex);
	  temp.insert(elemIndex,elem);
	  nodeCount++;
	 
  }

  /**
   * Sets the element at the `elemIndex` position of the list at `listIndex`
   * 
   * @throws IllegalArgumentException when index out of bounds
   * @param listIndex
   * @param elemIndex
   * @param elem
   */
  public void setElem(int listIndex, int elemIndex, E elem) {
	  if(listIndex >= size()) {
		  throw new IllegalArgumentException("out of bounds");
	  }
	  SingleLL<E> temp = getList(listIndex);
	  temp.set(elemIndex,elem);

  }

  /**
   * Returns the element at the `elemIndex` position of the list at `listIndex`
   * 
   * @throws IllegalArgumentException when index out of bounds
   * @param listIndex
   * @param elemIndex
   * @return
   */
  public E getElem(int listIndex, int elemIndex) {
	  if(listIndex >= size()) {
		  throw new IllegalArgumentException("out of bounds");
	  }
	  SingleLL<E> temp = getList(listIndex);
	  return temp.get(elemIndex);
  }

  /**
   * Returns the `ListCollection` in string form, following STRICTLY the rule of
   * "[LIST1, LIST2, LIST3, ... ]" Ex: [[0, 1, 2], [3, 4, 5] [6, 7, 8]]
   */
  public String toString() {
	    StringBuilder sb = new StringBuilder();
	    sb.append("[");
	    for (int i=0; i<size(); i++) {
	    	SingleLL<E> temp = collection.get(i); 
	    	sb.append(temp.toString());
	    	if(i<size()-1) {
	    		sb.append(", ");
	    	}
	    }
	    sb.append("]");
	    return sb.toString();
  }
}