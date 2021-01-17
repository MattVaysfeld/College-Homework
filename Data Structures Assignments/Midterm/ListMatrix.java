//Matthew Vaysfeld
//I pledge my honor that I have abided by the Steven's Honor System.

public class ListMatrix extends ListCollection<Integer> {
	  private int rows;
	  private int columns;

	  /**
	   * Initializes a `ListMatrix` with the specified number of rows and columns. By
	   * default, ALL elements are set to 0.
	   * 
	   * @param rows
	   * @param columns
	   */
	  public ListMatrix(int rows, int columns) {
		  super();
		  this.rows = rows;
		  this.columns= columns;
		  for (int i=0; i<rows; i++) {
			  SingleLL<Integer> row = new SingleLL<Integer>();
			  this.addList(row);
			  for(int j=0; j<columns; j++) {
				  row.push(0);
			  }
		  }  
	  }

	  /**
	   * @return the number of rows
	   */
	  public int numRows() {
	    return this.rows;
	  }

	  /**
	   * 
	   * @return the number of columns
	   */
	  public int numColumns() {
	    return this.columns;
	  }

	  /**
	   * Adds the `ListMatrix` to `ListMatrix other`, storing the result in the caller
	   * (this)
	   * 
	   * @throws IllegalArgumentException if dimensions do not properly coincide
	   * @param other
	   * @complexity The Big O is O(n*m^2) because there is a for loop inside of a for
	   * loop which causes the inside for loop to be run n times. The inner for loop runs
	   * m times (since columns and rows are different variables) and inside that for loop
	   * the get and set methods are called (which combined has a Big O of O(m)). This means 
	   * the inner for loop has a total Big O of O(m^2) and multiplying it by n gives 
	   * you the O(n*m^2) which is the Big O of the method.
	   */
	  public void add(ListMatrix other) {
		  if(this.rows != other.numRows() || this.columns !=other.numColumns()) {
			  throw new IllegalArgumentException("Dimensions don't match");
		  }
		  for(int i=0; i<rows; i++) {
			  for(int j=0; j<columns; j++) {
				  int result = this.collection.get(i).get(j)+ other.collection.get(i).get(j);
				  this.getList(i).set(j, result);
			  }
		  }

	  }

	  /**
	   * Returns the transpose of the matrix
	   * 
	   * @param matrix
	   * @return matrix transpose
	   */
	  public static ListMatrix transpose(ListMatrix matrix) {
		  
		  ListMatrix newm = new ListMatrix(matrix.columns, matrix.rows);
		  for(int i=0; i<matrix.columns;i++) {
			  for(int j=0; j<matrix.rows; j++) {
				  int el= matrix.getList(j).get(i);
				  newm.getList(i).set(j,el);
			  }
		  }
		  return newm;
	  }

	  /**
	   * Multiplies the `ListMatrix` with `ListMatrix other`, returning the result as
	   * a new `ListMatrix.
	   * 
	   * @throws IllegalArgumentException if dimensions do not properly coincide
	   * @param other
	   * @return
	   */
	  public ListMatrix multiply(ListMatrix other) {
		  if(this.columns != other.numRows()) {
			  throw new IllegalArgumentException("Dimensions do not properly coincide");
		  }
		  ListMatrix product = new ListMatrix(this.rows,other.numColumns());
		  for(int i=0; i<rows; i++) {
			  for(int j=0; j<other.numColumns(); j++) {
				  int result = 0;
				  for(int k=0; k<columns;k++) {
					  result += this.getList(i).get(k) * other.getList(k).get(j);
					}
				  product.getList(i).set(j, result);
			  }
		  }
		  return product;

	  }
}
