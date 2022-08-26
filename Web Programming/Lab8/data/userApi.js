const axios = require("axios");

async function getFiveShows(term){
    if(!term){
        throw "term does not exist";
    }
    if(typeof(term) !== "string"){
        throw "term needs to be string"
    }
    if(arguments.length != 1){
        throw "incorrect argument amount"
    }
    try{
        const {data} = await axios.get(`http://api.tvmaze.com/search/shows?q=${term}`)
        let data2 = [];
        counter = 0;
        for(i of data){
        data2.push(i);
        counter++;
        if(counter>=5){
            break;
        }
        }
        return data2;
    }catch(e){
        console.log(e.message);
    }
    
    
}

async function getShow(id){
    if(!id){
        throw "there is no id given";
    }
    if(arguments.length != 1){
        throw "incorrect argument amount"
    }
    try{
        const {data} = await axios.get(`http://api.tvmaze.com/shows/${id}`);
        return data;
    } catch(e){
        return null
    }
   
}

module.exports={
    getFiveShows,
    getShow
}