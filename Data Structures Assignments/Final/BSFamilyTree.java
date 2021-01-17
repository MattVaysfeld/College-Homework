import java.util.ArrayList;

//Matthew Vaysfeld
//I pledge my honor that I have abided by the Steven's Honor System

/**
 * BSFamilyTree creates a tree for specific families. 
 */
public class BSFamilyTree {
    //Data Fields
    private FamilyTreeNode root;

    /**
     * Constructor: constructs an empty BSFamilyTree
     */
    public BSFamilyTree() {
        this.root = null;
    }

    /**
     * takes in the last name and returns true if there
     * is a FamilyTreeNode with the given last name.
     */
    public boolean doesFamilyExist(String lastName) {
    	return doesFamilyExistHelper(lastName,root);
    }
    
    /**
     * Helper for doesFamilyExist 
     *
     */
    private boolean doesFamilyExistHelper(String lastName, FamilyTreeNode parent) {
    	if (root == null) {
    		return false;
    	}
    	if (lastName.compareTo(parent.getLastName()) < 0) {
    		if(parent.left == null) {
    			return false;
    		}
    		else if(parent.left.getLastName().equals(lastName)) {
    			return true;
    		}
    		else {
    			return this.doesFamilyExistHelper(lastName, parent.left);
    		}
    	}
    	else if(lastName.compareTo(parent.getLastName()) > 0) {
    		if(parent.right == null) {
    			return false;
    		}
    		else if (parent.right.getLastName().equals(lastName)) {
    			return true;
    		}
    		else {
    			return this.doesFamilyExistHelper(lastName, parent.right);
    		}
    	}
    	return true;
    }


    /**
     * Takes in a last name and creates a new instance of
     * FamilyTreeNode and adds it to the BSFamilyTree.
     */
    public void addFamilyTreeNode(String lastName) {
        if (this.root == null) {
        	FamilyTreeNode node = new FamilyTreeNode(lastName);
        	this.root = node;
        }
        else if(this.doesFamilyExist(lastName)) {
        	throw new IllegalArgumentException();
        }
        else {
        	addFamilyTreeNodeHelper(lastName, this.root);
        	
        }
    }
    /**
     * Helper for addFamilyTreeNode
     * 
     */
    private void addFamilyTreeNodeHelper(String lastName, FamilyTreeNode parent) {
    	if (lastName.compareTo(parent.getLastName()) < 0) {
    		if(parent.left == null) {
    			parent.left = new FamilyTreeNode(lastName);
    		}
    		else {
    			this.addFamilyTreeNodeHelper(lastName, parent.left);
    		}
    	}
    	else if(lastName.compareTo(parent.getLastName()) > 0) {
    		if(parent.right == null) {
    			parent.right = new FamilyTreeNode(lastName);
    		}
    		else {
    			this.addFamilyTreeNodeHelper(lastName, parent.right);
    		}
    	}
    }
    

    /**
     * Takes a last name and then finds that specific
     * family tree and then returns that FamilyTreeNode
     * If last name is not in tree, throws an exception.
     */
    public FamilyTreeNode getFamilyTreeNode(String lastName) throws IllegalArgumentException {
        FamilyTreeNode current = root;
    	while(current != null) {
        	if(current.getLastName().compareTo(lastName) == 0) {
        		return current;
        	}
        	else if(lastName.compareTo(current.getLastName()) < 0) {
        		current= current.left;
        	}
        	else if(lastName.compareTo(current.getLastName()) > 0) {
        		current= current.right;
        	}
    	}
    	throw new IllegalArgumentException();
    }

    /**
     * Returns true if the input phone number exists in the BSFamilyTree
     * false otherwise.
     */
    public boolean doesNumberExist(String phoneNumber) {
    	return doesNumberExistHelper(phoneNumber,root);
    }
    
    private boolean doesNumberExistHelper(String phoneNumber, FamilyTreeNode parent) {
    	if(this.root == null) {
    		return false;
    	}
    	if (parent.doesNumberExist(phoneNumber)) {
    		return true;
    	}
    	else {
    		if (parent.left == null && parent.right == null) {
    			return false;
    		}
    		else if (parent.left == null) {
    			return doesNumberExistHelper(phoneNumber,parent.right);
    		}
    		else if(parent.right == null) {
    			return doesNumberExistHelper(phoneNumber,parent.left);
    		}
    		return doesNumberExistHelper(phoneNumber,parent.left)
    		|| doesNumberExistHelper(phoneNumber,parent.right);
    		}
    	}
    

    /**
     * Helper for toString
     */
    public String toString(FamilyTreeNode current, int i) {
    	StringBuilder r = new StringBuilder();
		for (int j=0; j<i; j++) {
			r.append("  ");
		}
		
		if (current==null) {
			r.append("null\n");
		} else {
			r.append(current +"\n");
			r.append(toString(current.left,i+1));
			r.append(toString(current.right,i+1));
			
		}
		return r.toString();
		
    }
    
    /**
     * Returns the string representation of the BSFamilyTree
     */
    public String toString() {
		return toString(root,0).toString();
	}
    public static void main(String args[]) {
    	
    }
}
