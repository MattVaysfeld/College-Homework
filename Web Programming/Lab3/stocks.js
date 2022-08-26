//Matthew Vaysfeld
//I pledge my honor that I have abided by the Stevens Honor System.

const people = require("./people");
const axios = require("axios");

async function getPeople(){
    const { data } = await axios.get('https://gist.githubusercontent.com/graffixnyc/a1196cbf008e85a8e808dc60d4db7261/raw/9fd0d1a4d7846b19e52ab3551339c5b0b37cac71/people.json')
    return data // this will be the array of people objects
}
async function getStocks(){
    const { data } = await axios.get('https://gist.githubusercontent.com/graffixnyc/8c363d85e61863ac044097c0d199dbcc/raw/7d79752a9342ac97e4953bce23db0388a39642bf/stocks.json')
    return data // this will be the array of people objects
}

const listShareholders = async function listShareholders(stockName){
    if(arguments.length <= 0){
        throw "not enough arguments";
    }
    else if(arguments.length == 1){
        if(stockName == undefined || stockName == null){
            throw "stockName parameter does not exist";
        }
        if(typeof stockName !== "string"){
            throw `${arguments[0]} is not a string`;
        }
        stockName = stockName.trim();
        if(stockName.length == 0){
            throw "empty string"
        }
        const data2 = await getStocks();
        let answer = {};
        let flag = false;
        for (let i of data2){
            if(i["stock_name"].toLowerCase() == stockName.toLowerCase()){
                answer = i;
                flag = true;
                break;
            }
        }
        if(flag == false){
            throw "stock not found";
        }
        for (let j of answer["shareholders"]){
            let person = await people.getPersonById(j["userId"]);
            delete j.userId;
            j["first_name"] = person["first_name"];
            j["last_name"] = person["last_name"];
        }
        return answer;
    }
    else{
        throw "too many arguments";
    }
    
}


const totalShares = async function totalShares(stockName){
    if(arguments.length <= 0){
        throw "not enough arguments";
    }
    else if(arguments.length == 1){
        if(stockName == undefined || stockName == null){
            throw "stockName parameter does not exist";
        }
        if(typeof stockName !== "string"){
            throw `${arguments[0]} is not a string`;
        }
        stockName = stockName.trim();
        if(stockName.length == 0){
            throw "empty string"
        }
        const data2 = await getStocks();
        let answer = {};
        let flag = false;
        for (let i of data2){
            if(i["stock_name"].toLowerCase() == stockName.toLowerCase()){
                answer = i;
                flag = true;
                break;
            }
        }
        if(flag == false){
            throw "stock not found";
        }
        let total = 0;
        let amount = 0;
        for (let j of answer["shareholders"]){
            amount+=1;
            total += j["number_of_shares"];
        }
        if(amount == 0){
            return `${answer["stock_name"]} currently has no shareholders.`
        }
        if(amount == 1){
            return `${answer["stock_name"]}, has 1 shareholder that owns a total of ${total} shares.`
        }
        return `${answer["stock_name"]}, has ${amount} shareholders that own a total of ${total} shares.`;
    }
    else{
        throw "too many arguments";
    }
    
}

async function checkName(name){
    if(name == undefined || name == null){
        throw "stockName parameter does not exist";
    }
    if(typeof name !== "string"){
        throw `${arguments[0]} is not a string`;
    }
    name = name.trim();
    if(name.length == 0){
        throw "empty string"
    }
}

async function getPersonByName(firstName, lastName){
    const data = await getPeople();
        for (let i of data){
            if(i["first_name"] == firstName && i["last_name"] == lastName){
                return i["id"];
            }
        }
    throw "person not found";
}

const listStocks = async function listStocks(firstName, lastName){
    if(arguments.length <= 1){
        throw "not enough arguments";
    }
    else if(arguments.length == 2){
        await checkName(firstName);
        await checkName(lastName);
        const data2 = await getStocks();
        let answer = [];
        let personId = await getPersonByName(firstName,lastName);
        for (let i of data2){
            for(let j of i["shareholders"]){
                if(j["userId"] == personId){
                    let newObject = {};
                    newObject["stock_name"] = i["stock_name"];
                    newObject["number_of_shares"] = j["number_of_shares"];
                    answer.push(newObject);
                }
            }
        }
        if(answer.length == 0){
            throw "no shares in any company";
        }
        return answer;
    }
    else{
        throw "too many arguments";
    }
    
}

const getStockById = async function getStockById(id){
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
        const data2 = await getStocks();
        for (let i of data2){
            if(i["id"] == id){
                return i;
            }
        }
        throw "stock not found";
    }
    else{
        throw "too many arguments";
    }
    
}



module.exports={
    listShareholders,
    totalShares,
    listStocks,
    getStockById
}