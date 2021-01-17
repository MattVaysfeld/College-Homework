import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.Test;


//Matthew Vaysfeld Section B
//I pledge my honor that I have abided by the Steven's Honor System.
class AnagramsTest {

	
	@Test
	void testLetterTable() {
		Anagrams a = new Anagrams();
		assertEquals(a.letterTable.toString() , "{a=2, b=3, c=5, d=7, e=11, f=13, g=17, h=19, i=23, j=29, k=31, l=37, m=41, n=43, o=47, p=53, q=59, r=61, s=67, t=71, u=73, v=79, w=83, x=89, y=97, z=101}" );
		assertEquals(a.anagramTable.toString() , "{}" );
	}

	@Test
	void testAddWord() {
		Anagrams a = new Anagrams();
		a.addWord("abcd");
		a.addWord("bcda");
		assertEquals(a.anagramTable.toString() , "{210=[abcd, bcda]}" );
		Anagrams b = new Anagrams();
		b.addWord("yes");
		b.addWord("no");
		b.addWord("maybe");
		assertEquals(b.anagramTable.toString() , "{71489=[yes], 2021=[no], 262482=[maybe]}" );
		b.addWord("on");
		b.addWord("sey");
		assertEquals(b.anagramTable.toString() , "{71489=[yes, sey], 2021=[no, on], 262482=[maybe]}" );
	}
	@Test
	void testGetMax() {
		Anagrams a = new Anagrams();
		a.addWord("car");
		a.addWord("arc");
		a.addWord("yes");
		a.addWord("abets");
		a.addWord("baste");
		a.addWord("betas");
		a.addWord("sey");
		a.addWord("beast");
		a.addWord("beats");
		assertEquals(a.anagramTable.toString() , "{71489=[yes, sey], 610=[car, arc], 313962=[abets, baste, betas, beast, beats]}" );
		assertEquals(a.getMaxEntries().toString() ,"[313962=[abets, baste, betas, beast, beats]]");
		assertEquals(a.getMaxEntries().size() , 1 );
		a.addWord("enlist");
		a.addWord("inlets");
		a.addWord("listen");
		a.addWord("silent");
		a.addWord("tinsel");
		assertEquals(a.anagramTable.toString() , "{71489=[yes, sey], 610=[car, arc], 1914801911=[enlist, inlets, listen, silent, tinsel], 313962=[abets, baste, betas, beast, beats]}" );
		assertEquals(a.getMaxEntries().toString() ,"[1914801911=[enlist, inlets, listen, silent, tinsel], 313962=[abets, baste, betas, beast, beats]]");
		assertEquals(a.getMaxEntries().size() , 2 );
	}

}
