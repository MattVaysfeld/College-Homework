const axios = require("axios");

async function getPeople(){
    const { data } = await axios.get('https://gist.githubusercontent.com/graffixnyc/31e9ef8b7d7caa742f56dc5f5649a57f/raw/43356c676c2cdc81f81ca77b2b7f7c5105b53d7f/people.json')
    return data // this will be the array of people objects
}
async function getWork(){
  const { data } = await axios.get('https://gist.githubusercontent.com/graffixnyc/febcdd2ca91ddc685c163158ee126b4f/raw/c9494f59261f655a24019d3b94dab4db9346da6e/work.json')
  return data // this will be the array of work objects
}

let peopleMethods = {
  async getAllPeople() {
    const peopleCollection = await getPeople();
    return peopleCollection;
  },
  async getPeopleById(id) {
    if(arguments.length !== 1 ){
      throw "should have 1 argument";
    }
    if(!id){
      throw "need an id"
    }
    newid = parseInt(id);
    if(isNaN(newid)){
      throw "must be a number"
    }
    if(newid <= 0){
      throw "must be a positive number";
    }
    if(newid.toString() !== id){
      throw "must be a number";
    }
    const peopleCollection = await getPeople();
    for (let i of peopleCollection){
        if(i["id"] == newid){
            return i;
        }
    }
    throw "person not found";
  },
};
let workMethods = {
  async getAllWork() {
    const workCollection = await getWork();
    return workCollection;
  },
  async getWorkById(id) {
    if(arguments.length !== 1 ){
      throw "should have 1 argument";
    }
    if(!id){
      throw "need an id"
    }
    newid = parseInt(id);
    if(isNaN(newid)){
      throw "must be a number"
    }
    if(newid <= 0){
      throw "must be a positive number";
    }
    if(newid.toString() !== id){
      throw "must be a number";
    }
    const workCollection = await getWork();
    for (let i of workCollection){
        if(i["id"] == newid){
            return i;
        }
    }
    throw "work not found";
  },
};

module.exports = {
    peopleMethods,
    workMethods
};