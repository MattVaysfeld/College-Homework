//Matthew Vaysfeld
//I pledge my honor that I have abided by the Stevens Honor System.

function isNonEmptyArray(arr){
    //if array does not exist
    if(arr == undefined){
        throw 'array does not exist';
    }
    //The array is of the proper type (meaning, it's an array)
    if(!Array.isArray(arr)) {
        throw 'not an array';
    }
    if(arr.length == 0) {
        throw 'array is empty';
    }
    
}
function isObject(obj){
    //if object does not exist
    if(obj == undefined){
        throw 'array does not exist';
    }
    //The object is of the proper type
    if(typeof obj !== "object") {
        throw 'not an object'
    }
    if(Array.isArray(obj)){
        throw 'is an array, not object'
    }
    
}
function isFunction(func){
    //if object does not exist
    if(func == undefined){
        throw 'function does not exist';
    }
    //The object is of the proper type
    if(typeof func !== "function") {
        throw 'not an function'
    }
    
}

function compareArrays(arr1,arr2){
    if(arr1.length != arr2.length){
        return false;
    }
    for(let i = 0; i<arr1.length; i++){
        if(typeof arr1[i] === "object"){
            if(typeof arr2[i] !== "object"){
                return false;
            }
            if(Array.isArray(arr1[i])){
                if(!Array.isArray(arr2[i])){
                    return false;
                }
                if (compareArrays(arr1[i],arr2[i]) == false){
                    return false;
                }
            }
            else if(isDeepEqual(arr1[i],arr2[i]) == false){
                return false;
            }
        }
        else if(arr1[i] !== arr2[i]){
            return false;
        }
    }
    return true;
}


   
    
    const makeArrays = function makeArrays(objects){
        if(arguments.length == 0){
            throw "not enough arguments"
        }
        else if(arguments.length == 1){
        isNonEmptyArray(objects);
        //check if its an array of objects
        for(let i = 0; i<objects.length;i++){
            if(typeof objects[i] !== "object"){
                throw 'element in array not an Object'
            }
            if(Array.isArray(objects[i])){
                throw 'element in array not an Object'
            }
            if(Object.keys(objects[i]).length == 0){
                throw 'Object cannot be empty'
            }
        }
        if(objects.length < 2){
            throw 'needs at least 2 objects'
        }
        let ansArray = [];
        for (let i of objects){
            ansArray = ansArray.concat(Object.entries(i));
        }
        return ansArray;
    }
        else{
            throw "too many arguments"
        }
    }


    const isDeepEqual = function isDeepEqual(obj1,obj2){
        if(arguments.length <= 1){
            throw "not enough arguments"
        }
        else if(arguments.length == 2){
            isObject(obj1);
            isObject(obj2);
            if(Object.keys(obj1).length !== Object.keys(obj2).length){
                return false;
            }
            for (let i of Object.keys(obj1)){
                if(typeof obj1[i] === "object"){
                    if(typeof obj2[i] !== "object"){
                        return false;
                    }
                    if(obj1[i] === null){
                        if(obj2[i] !== null){
                            return false;
                        }
                    }
                    else if(Array.isArray(obj1[i])){
                        if(!Array.isArray(obj2[i])){
                            return false;
                        }
                        if(compareArrays(obj1[i],obj2[i]) == false){
                            return false;
                        }
                    }
                    else if(isDeepEqual(obj1[i],obj2[i]) == false){
                        return false;
                    }
                
                }
                else if(obj1[i] !== obj2[i]){
                    return false;
                }
            }
            return true;
        }
        else{
            throw "too many arguments"
        }
    }

    const computeObject = function computeObject(object,func) {
        if(arguments.length <= 1){
            throw "not enough arguments"
        }
        else if(arguments.length == 2){
            isObject(object);
            isFunction(func);
            if(Object.keys(object).length == 0){
                throw 'Object cannot be empty'
            }
            for (let i of Object.keys(object)){
                if(typeof object[i] !== "number"){
                    throw "object value is not a number";
                }
            }
            for(let i of Object.keys(object)){
                object[i] = func(object[i]);
            }
            return object;
        }
        else{
            throw "too many arguments"
        }
    }
    


    module.exports = {
        makeArrays,
        isDeepEqual,
        computeObject
    };