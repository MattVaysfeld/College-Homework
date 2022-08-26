//Matthew Vaysfeld
//I pledge my honor that I have abided by the Stevens Honor System.


const axios = require("axios");

async function getPeople(){
    const { data } = await axios.get('https://gist.githubusercontent.com/graffixnyc/a1196cbf008e85a8e808dc60d4db7261/raw/9fd0d1a4d7846b19e52ab3551339c5b0b37cac71/people.json')
    return data // this will be the array of people objects
}

const getPersonById = async function getPersonById(id){
    if(arguments.length <= 0){
        throw "not enough arguments";
    }
    else if(arguments.length == 1){
        if(id == undefined || id == null){
            throw "id parameter does not exist";
        }
        if(typeof id !== "string"){
            throw `${arguments[0]} is not a string`;
        }
        id = id.trim();
        if(id.length == 0){
            throw "empty string"
        }
        const data = await getPeople();
        for (let i of data){
            if(i["id"] == id){
                return i;
            }
        }
        throw "person not found";
    }
    else{
        throw "too many arguments";
    }
    
}
//https://stackoverflow.com/questions/9862761/how-to-check-if-character-is-a-letter-in-javascript
async function isLetter(c){
    return c.toLowerCase() != c.toUpperCase();
}
async function checkEmail(emailDomain){
    if(emailDomain == undefined || emailDomain == null){
        throw "emailDomain parameter does not exist";
    }
    if(typeof emailDomain !== "string"){
        throw `${arguments[0]} is not a string`;
    }
    emailDomain = emailDomain.trim();
    if(emailDomain.length == 0){
        throw "empty string"
    }
    let dot = false;
    let countafter = 0;
    if(emailDomain[0] == "."){
        throw "no domain name"
    }
    for(let i of emailDomain){
        if(i == "."){
            dot = true;
            countafter = 0;
        }
        else if(dot == true && await isLetter(i)){
            countafter+=1;
        }
    }
    if(dot == false){
        throw "email does not contain a dot"
    }
    
    if(countafter < 2){
        throw "does not have at LEAST 2 LETTERS after the dot"
    }
}

const sameEmail = async function sameEmail(emailDomain){
    if(arguments.length <= 0){
        throw "not enough arguments";
    }
    else if(arguments.length == 1){
        await checkEmail(emailDomain);
        const data = await getPeople();
        let answer = [];
        for (let i of data){
            if(i["email"].toLowerCase().substring(i["email"].indexOf('@') + 1).includes(emailDomain.toLowerCase())){
                answer.push(i);
            }
        }
        if(answer.length < 2){
            throw "need at least two people with same domain";
        }
        return answer;
    }
    else{
        throw "too many arguments";
    }
    
}

const manipulateIp = async function manipulateIp(){
    if(arguments.length != 0){
        throw "should have no arguments";
    }
    const data = await getPeople();
    let answer = {};
    let lowest = {};
    let min = Number.MAX_SAFE_INTEGER;
    let highest = {}
    let max = 0;
    let total = 0;
    for (let i of data){
        let ip =i["ip_address"].replaceAll('.','');
        ip = ip.split('')
        ip = ip.sort();
        ip = ip.join('');
        ip = parseInt(ip);
        if(ip > max){
            max = ip;
            highest["firstName"] = i["first_name"];
            highest["lastName"] = i["last_name"];
        }
        if(ip < min){
            min = ip;
            lowest["firstName"] = i["first_name"];
            lowest["lastName"] = i["last_name"];
        }
        total += ip;
    }
    answer["highest"] = highest;
    answer["lowest"] = lowest;
    answer["average"] = Math.floor(total / data.length);
    return answer;
    
}


async function checkDate(month,day){
    if(month == undefined || month == null){
        throw "month parameter does not exist";
    }
    if(typeof month !== "string" && typeof month !== "number"){
        throw `${arguments[0]} is not a valid input`;
    }
    if(day == undefined || day == null){
        throw "month parameter does not exist";
    }
    if(typeof day !== "string" && typeof day !== "number"){
        throw `${arguments[1]} is not a valid input`;
    }
    if(typeof month === "string"){
        month=parseInt(month)
        if(isNaN(month)){
            throw "month string cannot be parsed"
        }
    }
    if(typeof day === "string"){
        day=parseInt(day)
        if(isNaN(day)){
            throw "month string cannot be parsed"
        }
    }
    if(month < 1){
        throw "Month < 1";
    }
    if(month > 12){
        throw "Month > 12";
    }
    if(month == 1 || month ==3 || month ==5 || month ==7 || month ==8 || month ==10 || month ==12){
        if(day < 1 || day > 31){
            if(month == 1){
                throw `There are not ${day} days in Jan`
            }
            if(month == 3){
                throw `There are not ${day} days in March`
            }
            if(month == 5){
                throw `There are not ${day} days in May`
            }
            if(month == 7){
                throw `There are not ${day} days in July`
            }
            if(month == 8){
                throw `There are not ${day} days in Aug`
            }
            if(month == 10){
                throw `There are not ${day} days in Oct`
            }
            if(month == 12){
                throw `There are not ${day} days in Dec`
            }
        }
    }
    if(month == 4 || month == 6 || month == 9 || month == 11 ){
        if(day < 1 || day > 30){
            if(month == 4){
                throw `There are not ${day} days in April`
            }
            if(month == 6){
                throw `There are not ${day} days in June`
            }
            if(month == 9){
                throw `There are not ${day} days in Sept`
            }
            if(month == 11){
                throw `There are not ${day} days in Nov`
            }
        }
    }
    if(month == 2){
        if(day < 1 || day > 28){
            throw `There are not ${day} days in Feb`
        }
    }
}

const sameBirthday = async function sameBirthday(month,day){
    if(arguments.length <= 1){
        throw "not enough arguments";
    }
    else if(arguments.length == 2){
        await checkDate(month,day);
        month=parseInt(month);
        day=parseInt(day);
        const data = await getPeople();
        let answer = [];
        for (let i of data){
            if(parseInt(i["date_of_birth"].substring(0,2)) == month && parseInt(i["date_of_birth"].substring(3,5)) == day){
                answer.push(i["first_name"] + " " + i["last_name"]);
            }
        }
        if(answer.length == 0){
            throw "no people with birthday";
        }
        return answer;
    }
    else{
        throw "too many arguments";
    }
    
}



module.exports = {
    getPeople,
    getPersonById,
    sameEmail,
    manipulateIp,
    sameBirthday
}