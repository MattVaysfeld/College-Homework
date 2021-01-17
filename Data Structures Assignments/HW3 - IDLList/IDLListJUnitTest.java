import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.Test;

import junit.framework.TestCase;

public class IDLListJUnitTest extends TestCase {
	
	@Test
	public void testadd() {							//Test Add at Index 0
		IDLList<Integer> l = new IDLList<Integer>();
		int size= 10;
		for (int i=0; i<size ; i++) {
			l.add(i);
		}
		
		assertEquals(size,l.size());
		
		l.add(1);
		assertTrue(1 == l.get(0));
		assertTrue(l.add(1));
		
		l.add(2);
		assertTrue(2 == l.get(0));
		assertTrue(l.add(2));
		
		l.add(3);
		assertTrue(3 == l.get(0));
		assertTrue(l.add(3));
		
	}
	@Test
	public void test2addat() {							//Test add at any index
		IDLList<Integer> l = new IDLList<Integer>();
		int size= 10;
		for (int i=0; i<size ; i++) {
			l.add(i);
		}
		
		assertEquals(size,l.size());
		
		l.add(1,1);
		assertTrue(1 == l.get(1));
		assertTrue(l.add(1,1));
		
		l.add(1,2);
		assertTrue(2 == l.get(1));
		assertTrue(l.add(1,2));
		
		l.add(1,3);
		assertTrue(3 == l.get(1));
		assertTrue(l.add(1,3));
		
		l.add(2,4);
		assertTrue(4 == l.get(2));
		assertTrue(l.add(2,4));
		
		l.add(3,5);
		assertTrue(5 == l.get(3));
		assertTrue(l.add(3,5));
		
		l.add(4,6);
		assertTrue(6 == l.get(4));
		assertTrue(l.add(4,6));
		
		l.add(5,7);
		assertTrue(7 == l.get(5));
		assertTrue(l.add(5,7));
		
		l.add(10,10);
		assertTrue(10 == l.get(10));
		assertTrue(l.add(5,7));
		
		assertThrows(IllegalArgumentException.class, () -> l.add(100, 100));
		assertThrows(IllegalArgumentException.class, () -> l.add(-1, 1));
		

		}
	
	@Test
	public void testappend() {							//Test Append
		IDLList<Integer> l = new IDLList<Integer>();
		l.append(1);
		assertTrue(1 == l.get(0));
		
		l.append(2);

		assertTrue(2 == l.get(1));
		
		l.append(3);
		assertTrue(3 == l.get(2));
		
		l.append(4);
		assertTrue(4 == l.get(3));
		
		assertEquals(l.toString(), "[1,2,3,4,]");
		
		
		
	}
	@Test
	public void testremoveAt() {							
		IDLList<Integer> l = new IDLList<Integer>();
		IDLList<Integer> n = new IDLList<Integer>();
		int size= 10;
		for (int i=0; i<size ; i++) {
			l.add(i);
		}
		
		assertEquals(size,l.size());
		
		l.removeAt(5);
		assertTrue(3 == l.get(5));   
		
		l.removeAt(0);
		assertTrue(8 == l.get(0));
		assertTrue(l.removeAt(7) == 0);
		
		
		IDLList<Integer> l1 = new IDLList<Integer>();
		assertThrows(IllegalArgumentException.class, () -> l1.remove());
		assertThrows(IllegalStateException.class, () -> l1.removeLast());
		assertThrows(IllegalArgumentException.class, () -> l1.removeAt(0));
		assertThrows(IllegalArgumentException.class, () -> l1.removeAt(1));
		assertThrows(IllegalArgumentException.class, () -> l1.removeAt(-2));
		assertEquals(l1.remove(1), false);
		}
	@Test
	public void testremove() {							
		IDLList<Integer> l = new IDLList<Integer>();
		int size= 10;
		for (int i=0; i<size ; i++) {
			l.add(i);
		}
		l.remove(7);
		assertTrue( l.get(2) == 6);
		
		assertEquals(l.remove(1), true);
		assertEquals(l.remove(4), true);
		assertEquals(l.remove(8), true);
		assertEquals(l.remove(4), false);
		assertEquals(l.remove(100), false);
	}
	@Test
	public void testGet() {
		IDLList<Integer> l1 = new IDLList<Integer>();
		
		assertThrows(IllegalStateException.class, () -> l1.getHead());
		assertThrows(IllegalStateException.class, () -> l1.getLast());
		assertThrows(IllegalStateException.class, () -> l1.get(0));
		assertThrows(IllegalArgumentException.class, () -> l1.get(-1));
		assertEquals(l1.size(), 0);
	}
	@Test
	public void testtoString() {
		IDLList<Integer> l = new IDLList<Integer>();
		assertEquals(l.toString(), "[]");
		for (int i=0; i<5 ; i++) {
			l.add(i);
		}
		assertEquals(l.toString(), "[4,3,2,1,0,]");
	}
	
}
