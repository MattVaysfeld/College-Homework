import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.Test;

class TreapsTester {

	@Test
	void testAdd() {
		//Testing if add puts nodes in right places
		Treap<Integer> Treap1 = new Treap <Integer>();
		
		assertEquals(Treap1.add (4 ,19), true ); // When the Treap is empty
		assertEquals(Treap1.toString().substring(0,20), "(key=4, priority=19)");
		
		assertEquals(Treap1.add (2 ,31), true);
		assertEquals(Treap1.toString().substring(0,20), "(key=2, priority=31)");
		
		assertEquals(Treap1.add (6 ,70), true);
		assertEquals(Treap1.add (1 ,84), true);
		assertEquals(Treap1.add (3 ,12), true);
		assertEquals(Treap1.add (5 ,83), true);
		assertEquals(Treap1.add (7 ,26), true);
		assertEquals(Treap1.toString().substring(0,20), "(key=1, priority=84)");
		assertEquals(Treap1.toString().substring(28,48), "(key=5, priority=83)");
		assertEquals(Treap1.toString().substring(104,128), "    (key=3, priority=12)");
		
		assertEquals(Treap1.add (5, 66), false);
		assertEquals(Treap1.add (7 ,76), false);
		
		//Testing if add with random priority works
		Treap<Integer> TreapR = new Treap <Integer>();
		assertEquals(TreapR.add(4), true);
		assertEquals(TreapR.add(2), true);
		assertEquals(TreapR.add(3), true);
		assertEquals(TreapR.add(2), false);
	}
	
	@Test
	void testDelete() {
		//Building Treap
		Treap<String> Treap2 = new Treap <String>();
		assertEquals(Treap2. add ("p" ,99), true );
		assertEquals(Treap2. add ("g" ,80), true );
		assertEquals(Treap2. add ("a" ,60), true );
		assertEquals(Treap2. add ("j" ,65), true );
		assertEquals(Treap2. add ("u" ,75), true );
		assertEquals(Treap2. add ("r" ,40), true );
		assertEquals(Treap2. add ("z" ,47), true );
		assertEquals(Treap2. add ("w" ,32), true );
		assertEquals(Treap2. add ("x" ,25), true );
		assertEquals(Treap2. add ("v" ,21), true );
		assertEquals(Treap2.toString().substring(0,20), "(key=p, priority=99)");
		
		//Testing Delete
		assertEquals(Treap2. delete ("p"), true ); //deleting root
		assertEquals(Treap2. delete ("m"), false ); //deleting when the key doesn't exist
		assertEquals(Treap2. toString().substring(0,20), "(key=g, priority=80)");
		
		//Making a new Treap and testing delete
		Treap<String> Treap3 = new Treap <String>();
		assertEquals(Treap3. add ("p" ,99), true );
		assertEquals(Treap3. add ("g" ,80), true );
		assertEquals(Treap3. add ("a" ,60), true );
		assertEquals(Treap3. add ("j" ,65), true );
		assertEquals(Treap3. add ("u" ,75), true );
		assertEquals(Treap3. add ("r" ,40), true );
		assertEquals(Treap3. add ("z" ,47), true );
		assertEquals(Treap3. add ("w" ,32), true );
		assertEquals(Treap3. add ("x" ,25), true );
		assertEquals(Treap3. add ("v" ,21), true );
		assertEquals(Treap3. delete ("z"), true );
		assertEquals(Treap3. delete ("hello"), false );
		assertEquals(Treap3.toString().substring(0,20), "(key=p, priority=99)");
		assertEquals(Treap3. toString().substring(255,256), "x");
		
	}
	
	@Test
	void testFind() {
		Treap<String> Treap4 = new Treap <String>();
		Treap4. add ("hi");
		Treap4. add ("howdy");
		Treap4. add ("yo");
		Treap4. add ("whatsup");
		Treap4. add ("sup");
		Treap4. add ("chao");
		Treap4. add ("hola");
		Treap4. add ("hey");
		Treap4. add ("hello");
		Treap4. add ("howsitgoin");
		assertTrue(Treap4.find("hello"));
		assertTrue(Treap4.find("howdy"));
		assertFalse(Treap4.find("bye"));
		assertFalse(Treap4.find("seeya"));
		assertFalse(Treap4.find("r"));
		
	}

}
