//Matthew Vaysfeld
//I pledge my honor that I have abided by the Stevens Honor System.

const arrayUtils = require('./arrayUtils');
const stringUtils = require('./stringUtils');
const objUtils = require('./objUtils');

// Mean Tests

console.log("Mean TESTS:")
try {
    // Should Pass
    console.log(arrayUtils.mean([1, 2, 3]));// Returns: 2
 } catch (e) {
    console.error(e);
 }
 try {
    // Should Fail
    console.error(arrayUtils.mean([]));
 } catch (e) {
    console.log(e);
 }
 try {
   // Should Fail
   console.error(arrayUtils.mean("banana"));
} catch (e) {
   console.log(e);
}
try {
   // Should Fail
   console.error(arrayUtils.mean(["guitar", 1, 3, "apple"]));
} catch (e) {
   console.log(e);
}
try {
   // Should Fail
   console.error(arrayUtils.mean());
} catch (e) {
   console.log(e);
}
 try {
   // Should Fail
   console.error(arrayUtils.mean(1234));
} catch (e) {
   console.log(e);
}
//Own Tests
try {
   // Should Fail
   console.error(arrayUtils.mean([undefined,null]));
} catch (e) {
   console.log(e);
}
try {
   // Should Pass
   console.log(arrayUtils.mean([1.5])); //returns 1
} catch (e) {
   console.log(e);
}
try {
   // Should Fail
   console.error(arrayUtils.mean([1,2,3],[1,2,3]));
} catch (e) {
   console.log(e);
}

 //Median Tests

 console.log("medianSquared TESTS:")
 try {
    // Should Pass
    console.log(arrayUtils.medianSquared([10,20,5]));
 } catch (e) {
    console.error(e);
 }
 try {
   // Should Pass
   console.log(arrayUtils.medianSquared([4, 1, 2]));
} catch (e) {
   console.error(e);
}
try {
   // Should Fail
   console.error(arrayUtils.medianSquared([]));
} catch (e) {
   console.log(e);
}
 try {
    // Should Fail
    console.error(arrayUtils.medianSquared(1234));
 } catch (e) {
    console.log(e);
 }
 try {
   // Should Fail
   console.error(arrayUtils.medianSquared("banana"));
} catch (e) {
   console.log(e);
}
try {
   // Should Fail
   console.error(arrayUtils.medianSquared(1,2,3));
} catch (e) {
   console.log(e);
}
try {
   // Should Fail
   console.error(arrayUtils.medianSquared(["guitar", 1, 3, "apple"]));
} catch (e) {
   console.log(e);
}
try {
   // Should Fail
   console.error(arrayUtils.medianSquared());
} catch (e) {
   console.log(e);
}
try {
   // Should Pass
   console.log(arrayUtils.medianSquared([1.5])); //returns 1.5
} catch (e) {
   console.log(e);
}
try {
   // Should Fail
   console.error(arrayUtils.medianSquared([1,2,3],[1,2,3]));
} catch (e) {
   console.log(e);
}


 //maxElement Tests
 console.log("maxElement TESTS:")
 try {
    // Should Pass
   console.log(arrayUtils.maxElement([5, 6, 7]));
} catch (e) {
   console.log(e);
}
try {
   // Should Pass
   console.log(arrayUtils.maxElement([1]));
} catch (e) {
   console.log(e);
}
try {
   // Should Fail
   console.error(arrayUtils.maxElement([]));
} catch (e) {
   console.log(e);
}
try {
   // Should Fail
   console.error(arrayUtils.maxElement());
} catch (e) {
   console.log(e);
}
try {
   // Should Fail
   console.error(arrayUtils.maxElement("test"));
} catch (e) {
   console.log(e);
}
try {
   // Should Fail
   console.error(arrayUtils.maxElement([1, 2, "nope"]));
} catch (e) {
   console.log(e);
}
//Own Tests
try {
   // Should Pass
   console.log(arrayUtils.maxElement([1,2,3,3,1]));
} catch (e) {
   console.log(e);
}
try {
   // Should Fail
   console.error(arrayUtils.maxElement([1,2,3],[1,2,3]));
} catch (e) {
   console.log(e);
}
 try {
    // Should Fail
    console.error(arrayUtils.maxElement(5, 6, 7));
 } catch (e) {
    console.log(e);
 }
 
 //fill Tests
 console.log("fill TESTS:")
 try {
    // Should Pass
    console.log(arrayUtils.fill(6));
 } catch (e) {
    console.error(e);
 }
 try {
    // Should Pass
    console.log(arrayUtils.fill(3,"Welcome"));
 } catch (e) {
    console.error(e);
 }
 try {
   // Should Fail
   console.error(arrayUtils.fill());
} catch (e) {
   console.log(e);
}
try {
   // Should Fail
   console.error(arrayUtils.fill("test"));
} catch (e) {
   console.log(e);
}
 try {
    // Should Fail
    console.error(arrayUtils.fill(0));
 } catch (e) {
    console.log(e);
 }
 try {
    // Should Fail
    console.error(arrayUtils.fill(-4));
 } catch (e) {
    console.log(e);
 }

 //Own Tests

try {
   // Should Pass
   console.log(arrayUtils.fill(3,null));
} catch (e) {
   console.error(e);
}
try {
   // Should Pass
   console.log(arrayUtils.fill(3,' 7 '));
} catch (e) {
   console.error(e);
}
try {
   // Should Fail
   console.error(arrayUtils.fill(1,2,3));
} catch (e) {
   console.log(e);
}
try {
   // Should Fail
   console.error(arrayUtils.fill(1));
} catch (e) {
   console.log(e);
}

 //countRepeating
 console.log("countRepeating TESTS:")

 try {
    // Should Pass
    console.log(arrayUtils.countRepeating([7, '7', 13, true, true, true, "Hello","Hello", "hello"]));
 } catch (e) {
    console.error('countRepeating failed test case');
 }
 //Own Tests
 try {
    // Should Fail
    cconsole.log(arrayUtils.countRepeating({a: 1, b: 2, c: "Patrick"}));
 } catch (e) {
    console.log('countRepeating failed successfully');
 }

 try {
   // Should Pass
   console.log(arrayUtils.countRepeating([7, '7', ' 7 ', 13, true, true, true, "Hello","Hello", "hello",NaN,NaN,null,null]));
} catch (e) {
   console.error('countRepeating failed test case');
}
try {
   // Should Pass
   console.log(arrayUtils.countRepeating([]));
} catch (e) {
   console.error('countRepeating failed test case');
}

try {
   // Should Fail
   console.error(arrayUtils.countRepeating());
} catch (e) {
   console.log(e);
}
try {
   // Should Fail
   console.error(arrayUtils.countRepeating("test"));
} catch (e) {
   console.log(e);
}
try {
   // Should Fail
   console.error(arrayUtils.countRepeating([1, 2, "nope"],1));
} catch (e) {
   console.log(e);
}
 //isEqual

 console.log("isEqual TESTS:")

try {
   // Should Pass
   console.log(arrayUtils.isEqual([1, 2, 3], [3, 1, 2]));
} catch (e) {
   console.error(e);
}
try {
   // Should Pass
   console.log(arrayUtils.isEqual([ 'Z', 'R', 'B', 'C', 'A' ], ['R', 'B', 'C', 'A', 'Z']));
} catch (e) {
   console.error(e);
}
try {
   // Should Pass
   console.log(arrayUtils.isEqual([1, 2, 3], [4, 5, 6]));
} catch (e) {
   console.error(e);
}
try {
   // Should Pass
   console.log(arrayUtils.isEqual([1, 3, 2], [1, 2, 3, 4]));
} catch (e) {
   console.error(e);
}
try {
   // Should Pass
   console.log(arrayUtils.isEqual([1, 2], [1, 2, 3]));
} catch (e) {
   console.error(e);
}
try {
   // Should Pass
   console.log(arrayUtils.isEqual([[ 1, 2, 3 ], [ 4, 5, 6 ], [ 7, 8, 9 ]], [[ 3, 1, 2 ], [ 5, 4, 6 ], [ 9, 7, 8 ]]));
} catch (e) {
   console.error(e);
}
try {
   // Should Pass
   console.log(arrayUtils.isEqual([[ 1, 2, 3 ], [ 4, 5, 6 ], [ 7, 8, 9 ]], [[ 3, 1, 2 ], [ 5, 4, 11 ], [ 9, 7, 8 ]]));
} catch (e) {
   console.error(e);
}
try {
   // Should Pass
   console.log(arrayUtils.isEqual(["hello", " hello "], ["hello", "hello"]));
} catch (e) {
   console.error(e);
}
try {
   // Should Pass
   console.log(arrayUtils.isEqual([2,3,true,true,false,[1,23,3],[1]], [[23,3,1],false,true,true,3,2,[1]]));
} catch (e) {
   console.error(e);
}
try {
   // Should Pass
   console.log(arrayUtils.isEqual([2,3,true,true,false,[1,23,3],[1]], [[23,3,1],false,true,true,3,2,[1,2]]));
} catch (e) {
   console.error(e);
}
try {
   // Should Fail
   console.log(arrayUtils.isEqual(""));
} catch (e) {
   console.log(e);
}

//Own Test



 //camelCase

 console.log("camelCase TESTS:")

try {
   // Should Fail
   console.log(stringUtils.camelCase(''));
} catch (e) {
   console.log('camelCase failed successfully');
}
try {
   console.log(stringUtils.camelCase('my function rocks'));
} catch (e) {
   console.log(e);
}
try {
   console.log(stringUtils.camelCase('FOO BAR'));
} catch (e) {
   console.log(e);
}
try {
   console.log(stringUtils.camelCase("How now brown cow"));
} catch (e) {
   console.log(e);
}
try {
   console.log(stringUtils.camelCase());
} catch (e) {
   console.log(e);
}
try {
   console.log(stringUtils.camelCase(''));
} catch (e) {
   console.log(e);
}

try {
   console.log(stringUtils.camelCase(123));
} catch (e) {
   console.log(e);
}
try {
   //Fail
   console.log(stringUtils.camelCase(["Hello", "World"]));
} catch (e) {
   console.log(e);
}
try {
   //Fail
   console.log(stringUtils.camelCase(1, 1));
} catch (e) {
   console.log(e);
}

//Own Tests
try {
   //Should fail
   console.log(stringUtils.camelCase('   '));
} catch (e) {
   console.log(e);
}
try {
   // Should Pass
   console.log(stringUtils.camelCase('hello 3D world'));
} catch (e) {
   console.error(e);
}
try {
   // Should Pass
   console.log(stringUtils.camelCase('Hello mY Name iS MaTt'));
} catch (e) {
   console.error(e);
}




//replaceChar
console.log("replaceChar TESTS:")
try {
   // Should Pass
   console.log(stringUtils.replaceChar("Daddy"));
} catch (e) {
   console.error(e);
}
try {
   // Should Pass
   console.log(stringUtils.replaceChar("Hello, How are you? I hope you are well"));
} catch (e) {
   console.error(e);
}

try {
   // Should Pass
   console.log(stringUtils.replaceChar("babbbbbbble"));
} catch (e) {
   console.error(e);
}
try {
   // Should Fail
   console.log(stringUtils.replaceChar(""));
} catch (e) {
   console.log(e);
}
try {
   // Should Fail
   console.log(stringUtils.replaceChar(123));
} catch (e) {
   console.log(e);
}
//Own Tests
try {
   // Should Pass
   console.log(stringUtils.replaceChar("My name is Matt and I wake up in the morning mmmm"));
} catch (e) {
   console.error(e);
}

try {
   // Should Fail
   console.log(stringUtils.replaceChar("123","hehehe"));
} catch (e) {
   console.log(e);
}


//mashup
console.log("mashup TESTS:")
try {
   // Should Pass
   console.log(stringUtils.mashUp("hello", "world"));
} catch (e) {
   console.error(e);
}
try {
   // Should Pass
   console.log(stringUtils.mashUp("Patrick", "Hill"));
} catch (e) {
   console.error(e);
}
try {
   // Should Fail
   console.log(stringUtils.mashUp("Patrick", ""));
} catch (e) {
   console.log(e);
}
try {
   // Should Fail
   console.log(stringUtils.mashUp());
} catch (e) {
   console.log(e);
}
try {
   // Should Fail
   console.log(stringUtils.mashUp("John"));
} catch (e) {
   console.log(e);
}
try {
   // Should Fail
   console.log(stringUtils.mashUp("h", "Hello"));
} catch (e) {
   console.log(e);
}
try {
   // Should Fail
   console.log(stringUtils.mashUp("h","e"));
} catch (e) {
   console.log(e);
}


//Own
try {
   // Should Pass
   console.log(stringUtils.mashUp("hi","he"));
} catch (e) {
   console.log(e);
}
try {
   // Should Pass
   console.log(stringUtils.mashUp("hi","he",1));
} catch (e) {
   console.log(e);
}


//makeArrays
console.log("makeArrays TESTS:")
const first = { x: 2, y: 3};
const second = { a: 70, x: 4, z: 5 };
const third = { x: 0, y: 9, q: 10 };
try {
   // Should Pass
   console.log(objUtils.makeArrays([first, second, third]));
} catch (e) {
   console.error(e);
}
try {
   // Should Fail
   console.log(objUtils.makeArrays(""));
} catch (e) {
   console.log(e);
}
//Own
try {
   // Should Pass
   console.log(objUtils.makeArrays([second,first,third]));
} catch (e) {
   console.error(e);
}
try {
   // Should Pass
   console.log(objUtils.makeArrays([second,first]));
} catch (e) {
   console.error(e);
}
try {
   //should fail
   console.log(objUtils.makeArrays([second,first,[]]));
} catch (e) {
   console.error(e);
}
try {
   //should fail
   console.log(objUtils.makeArrays([second,first,[]]));
} catch (e) {
   console.error(e);
}
try {
   //should fail
   console.log(objUtils.makeArrays([second,first,{}]));
} catch (e) {
   console.error(e);
}
try {
   //should fail
   console.log(objUtils.makeArrays());
} catch (e) {
   console.error(e);
}
try {
   //should fail
   console.log(objUtils.makeArrays([{},{},{}]));
} catch (e) {
   console.error(e);
}
//isDeepEqual
console.log("isDeepEqual TESTS:")
const firstob = {a: 2, b: 3};
const secondob = {a: 2, b: 4};
const thirdob = {a: 2, b: 3};
const fourthob = {a: {sA: "Hello", sB: "There", sC: "Class"}, b: {a:"hello", b:[1,2]}, c: true, d: "Test"};
const fifthob  = {c: true, b: {a:"hello", b:[1,2]}, d: "Test", a: {sB: "There", sC: "Class", sA: "Hello"}};
const sixthob= { a: null, c: [1,2,3,[1,2]],b: undefined};
const seventhob = { b: undefined, a: null, c: [1,2,3,[1,2]] };


try {
   // Should Pass
   console.log(objUtils.isDeepEqual(firstob, secondob));
} catch (e) {
   console.error(e);
}
try {
   // Should Pass
   console.log(objUtils.isDeepEqual(fourthob, fifthob));
} catch (e) {
   console.error(e);
}
try {
   // Should Pass
   console.log(objUtils.isDeepEqual(firstob, thirdob));
} catch (e) {
   console.error(e);
}
try {
   // Should Fail
   console.log(objUtils.isDeepEqual("",firstob));
} catch (e) {
   console.log(e);
}
try {
   // Should Pass
   console.log(objUtils.isDeepEqual(sixthob, seventhob));
} catch (e) {
   console.error(e);
}



//computeObject

console.log("computeObject TESTS:")


try {
   // Should Pass
   console.log(objUtils.computeObject({ a: 3, b: 7, c: 5 }, n => n * 2));
} catch (e) {
   console.error(e);
}
try {
   // Should Fail
   console.log(objUtils.computeObject({ a: 3, b: "yes", c: 5 }, n => n * 2));
} catch (e) {
   console.log(e);
}
try {
   // Should Fail
   console.log(objUtils.computeObject({ a: 3, b: "yes", c: 5 }));
} catch (e) {
   console.log(e);
}
try {
   // Should Fail
   console.log(objUtils.computeObject({ a: 3},"hello","hi"));
} catch (e) {
   console.log(e);
}



 
