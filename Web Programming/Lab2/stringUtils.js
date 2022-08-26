//Matthew Vaysfeld
//I pledge my honor that I have abided by the Stevens Honor System.

function isNormalString(string){
    //if string does not exist
    if(string == undefined){
        throw 'string does not exist';
    }
    //The array is of the proper type (meaning, it's an array)
    if(typeof string !== "string") {
        throw 'not a string';
    }
    if(string.trim().length == 0){
        throw 'empty string'
    }
}



    
    const camelCase = function camelCase (string){
        if(arguments.length == 0){
            throw "not enough arguments"
        }
        else if (arguments.length == 1){
            isNormalString(string);
            let trimmed = string.trim();
            let newString = "";
            let flag = false;
            for (let i of trimmed){
                if(i != " "){
                    // character not a space
                    if(flag == true){
                        newString += i.toUpperCase();
                    }
                    else{
                        newString += i.toLowerCase();
                    }
                    flag = false;
                }
                else{
                    //character is a space
                    flag = true;
                }
            }
            return newString;
        }
        else{
            throw "too many arguments";
        }
        
       
    }

    const replaceChar = function replaceChar(string){
        if(arguments.length == 0){
            throw "not enough arguments"
        }
        else if (arguments.length == 1){
            isNormalString(string);
            let trimmed = string.trim();
            let newString = "";
            let starting = trimmed[0];
            let flag = true;
            for(let i = 0; i<string.length;i++){
                if(i !=0 ){
                    if(string[i].toLowerCase() == starting.toLowerCase()){
                        if(flag == true){
                            newString += "*";
                            flag = false;
                        }
                        else{
                            newString += "$";
                            flag = true;
                        }
                    }
                    else{
                        newString += string[i];
                    }
                }
                else{
                    newString += starting;
                }
            }
            return newString;
        }
        else{
            throw "too many arguments";
        }
    }


    const mashUp = function mashUp(string1,string2){
        if(arguments.length <= 1){
            throw "not enough arguments"
        }
        else if (arguments.length == 2){
            isNormalString(string1);
            isNormalString(string2);
            let trimmed1 = string1.trim();
            let trimmed2 = string2.trim();
            if(trimmed1.length < 2 || trimmed2.length < 2){
                throw 'string length less than 2';
            }
            let starting1 = trimmed1.substring(0,2);
            let starting2 = trimmed2.substring(0,2);
            let ending1 = trimmed1.substring(2);
            let ending2 = trimmed2.substring(2);
            let newString = starting2 + ending1 + " " + starting1 + ending2;
            return newString;
        }
        else{
            throw "too many arguments";
        }
    }

    module.exports = {
        camelCase,
        replaceChar,
        mashUp

    };