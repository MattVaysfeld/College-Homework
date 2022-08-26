//Matthew Vaysfeld
//I pledge my honor that I have abided by the Stevens Honor System.

function isProperNumberArray(arr){
    //if array does not exist
    if(arr == undefined){
        throw 'array does not exist';
    }
    //The array is of the proper type (meaning, it's an array)
    if(!Array.isArray(arr)) {
        throw 'not an array';
    }
    //The array is not empty
    if(arr.length == 0){
        throw 'array is empty'
    }
    //Each array element is a number
    for(let i = 0; i<arr.length;i++){
        if(typeof arr[i] !== "number"){
            throw 'element in array not number'
        }
    }
}

function checkEnd(end){
    //if array does not exist
    if(end == undefined){
        throw 'end does not exist';
    }
    //The array is of the proper type (meaning, it's an array)
    if(typeof end !== 'number') {
        throw 'end is not a number';
    }
    //The array is not empty
    if(end <= 0){
        throw 'end is not a positive number greater than 0'
    }
    //Each array element is a number
}

function isNormalArray(arr){
    //if array does not exist
    if(arr == undefined){
        throw 'array does not exist';
    }
    //The array is of the proper type (meaning, it's an array)
    if(!Array.isArray(arr)) {
        throw 'not an array';
    }
}

function comparingFunc(a,b){
    //positive first ones bigger
    //negative second ones bigger
    if(typeof a === "number" && typeof b === "number"){
        return a - b;
    }
    if(typeof a === "string" && typeof b === "string"){
        if(a>b){
            return 1;
        }
        else if(b>a){
            return -1;
        } 
        else if( a === b){
            return 0;
        }
    }
    if(typeof a === "string" && typeof b === "number"){
        return -1;
    }
    if(typeof a === "number" && typeof b === "string"){
        return 1;
    }
    if(typeof a === "boolean" && typeof b === "boolean"){
        if(a === true && b == false){
            return -1;
        }
        if(a === false && b == true){
            return 1;
        }
        if(a === b){
            return 0;
        }
    }
    if(typeof a === "number" && typeof b === "boolean"){
        return 1;
    }
    if(typeof a === "boolean" && typeof b === "number"){
        return -1;
    }  
    if(typeof a === "string" && typeof b === "boolean"){
        return 1;
    }
    if(typeof a === "boolean" && typeof b === "string"){
        return -1;
    }
    if(Array.isArray(a) && Array.isArray(b)){
        cSort(a);
        cSort(b);
        for(let i = 0; i<Math.min(a.length,b.length);i++){
            if(comparingFunc(a[i],b[i]) == -1){
                return -1;
            }
            else if(comparingFunc(a[i],b[i]) == 1){
                return 1;
            }
        }
        return a.length - b.length;
    }
    if(Array.isArray(a)){
       return 1
    }
    if(Array.isArray(b)){
        return -1
    }
}

function cSort(arr){
    for(let i = 0; i<arr.length;i++){
        if (typeof arr[i] === "string"){
            arr[i] = arr[i].trim();
        }
    }
    arr.sort(comparingFunc)
    return arr;
}

function compareArrays(arr1,arr2){
        cSort(arr1);
        cSort(arr2);
        if(arr1.length != arr2.length){
            return false;
        }
        for(let i = 0; i<arr1.length; i++){
            if(Array.isArray(arr1[i])){
                if(!Array.isArray(arr2[i])){
                    return false;
                }
                if (compareArrays(arr1[i],arr2[i]) == false){
                    return false;
                }
            }
            else if(arr1[i] !== arr2[i]){
                return false;
            }
        }
        return true;
}



    const mean = function mean (array) {
        if(arguments.length == 0){
            throw "not enough arguments"
        }
        else if(arguments.length == 1){
            isProperNumberArray(array);
            let sum = 0;
            for(let i = 0; i<array.length;i++){
                sum += array[i];
            }
            return sum/(array.length);
        }
        else{
            throw "too many arguments"
        }
        
    }

    const medianSquared = function medianSquared (array) {
        if(arguments.length == 0){
            throw "not enough arguments"
        }
        else if(arguments.length == 1){
            isProperNumberArray(array);
            //need to specify sorting function
            array.sort((a, b) => a - b);
            let len = array.length;
            if(len % 2 == 1){
                let index = (len + 1) / 2;
                let med = array[index-1];
                return med * med;
            }
            else{
                let index = len/2;
                let med = (array[index-1] + arr[index]) / 2;
                return med * med;
            }
        }
        else{
            throw "too many arguments"
        }
        
        
    }

    const maxElement = function maxElement (array) {
        if(arguments.length == 0){
            throw "not enough arguments"
        }
        else if(arguments.length == 1){
            isProperNumberArray(array);
            let max = Number.NEGATIVE_INFINITY;
            let maxi = 0;
            for(let i = 0; i<array.length;i++){
                if(array[i] > max){
                    max = array[i];
                    maxi = i;
                }
            }
            let obj = {};
            obj[max] = maxi;
            return obj;
        }
        else{
            throw "too many arguments"
        }
         
    }
    
    const fill = function fill(end,value){
        //can also check if value is undefined
        if(arguments.length == 0){
            throw "not enough arguments"
        }
        else if(arguments.length == 1){
            checkEnd(end);
            let newArray = [];
            for(let i = 0; i<end;i++){
                newArray.push(i);
            }
            return newArray;
        }
        else if (arguments.length == 2){
            checkEnd(end);
            let newArray = [];
            if(typeof value === "string"){
                value = value.trim();
            }
            for(let i = 0; i<end;i++){
                newArray.push(value);
            }
            return newArray;
        }
        else{
            throw "too many arguments"
        }
    }

    const countRepeating = function countRepeating(array){
        if(arguments.length == 0){
            throw "not enough arguments"
        }
        else if(arguments.length == 1){
            isNormalArray(array);
            let map = {}
            for (let i of array){
                if(typeof i === "string"){
                    i = i.trim();
                }
                if(!Object.keys(map).includes(String(i))){
                    map[i] = 1;
                }
                else{
                    map[i] += 1;
                }
            }
            //get rid of non repeating
            for(let j in map){
                if(map[j] == 1){
                    delete map[j];
                }
            }
            return map;
        }
        else{
            throw "too many arguments"
        }
        
    }

    const isEqual = function isEqual(arrayOne,arrayTwo){
        
        if(arguments.length <= 1){
            throw "not enough arguments"
        }
        else if(arguments.length == 2){
            isNormalArray(arrayOne);
            isNormalArray(arrayTwo);
            if(arrayOne.length != arrayTwo.length){
                return false;
            }
            return compareArrays(arrayOne,arrayTwo);

        }
        else{
            throw "too many arguments"
        }
        


    }



    module.exports = {
        mean,
        medianSquared,
        maxElement,
        fill,
        countRepeating,
        isEqual
  };
