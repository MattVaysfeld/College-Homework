const mongoCollections = require('../config/mongoCollections');
const bands = mongoCollections.bands;
const { ObjectId } = require('mongodb');

const arraysEqual= async function arraysEqual(arr1,arr2){
    if(arr1.length !== arr2.length){
        return false;
    }
    for(let i = 0; i<arr1.length; i++){
        if(arr1[i] != arr2[i]){
            return false;
        }
    }
    return true;
}
const create = async function create(name, genre, website, recordLabel, bandMembers, yearFormed){
    if(arguments.length !== 6 ){
        throw "should have 6 arguments";
    }
    if(!name || !genre || !website || !recordLabel || !bandMembers || !yearFormed){
        throw "field not provided";
    }
    if(typeof name !== "string" || typeof website !== "string" || typeof recordLabel !== "string"){
        throw "not string";
    }
    name = name.trim();
    website = website.trim();
    recordLabel = recordLabel.trim();
    if(name.length == 0 || website.length == 0  || recordLabel.length == 0 ){
        throw "not string";
    }
    if(website.length < 20 ){
        throw "string too short"
    }
    if(website.substring(0,11) !== "http://www."){
        console.log(website.substring(0,12))
        throw "does not begin with http://www."
    } 
    if(website.substring(website.length - 4) !== ".com" ){
        throw "does not end with .com"
    }
    if(!Array.isArray(genre) || !Array.isArray(bandMembers)) {
        throw 'not an array';
    }
    if(genre.length == 0 || bandMembers.length == 0) {
        throw 'empty array';
    }
    for(let i = 0; i<genre.length;i++){
        if(typeof genre[i] !== "string"){
            throw 'element in genre not string';
        }
    }
    for(let i = 0; i<bandMembers.length;i++){
        if(typeof bandMembers[i] !== "string"){
            throw 'element in bandMembers not string';
        }
    }
    if(typeof yearFormed !== "number"){
        throw "year formed not a number";
    }
    if(yearFormed < 1900 || yearFormed > 2022 || !Number.isInteger(yearFormed)){
        throw "year formed not a valid number";
    }


    const bandCollection = await bands();

    let newBand = {
        name: name,
        genre: genre,
        website: website,
        recordLabel: recordLabel,
        bandMembers: bandMembers,
        yearFormed: yearFormed,
        albums : [],
        overallRating : 0
    };
    const insertInfo = await bandCollection.insertOne(newBand);
    if (!insertInfo.acknowledged || !insertInfo.insertedId){
      throw 'Could not add band';
    }
    newBand["_id"] = newBand["_id"].toString();
    return newBand;

}

const getAll = async function getAll() {
    if(arguments.length !== 0 ){
        "should take no arguments";
    }
    const bandCollection = await bands();
    const bandList = await bandCollection.find({}).toArray();
    if (!bandList) throw 'Could not get all bands';
    for(let i of bandList){
        i["_id"] = i["_id"].toString();
    }
    return bandList;
}
const getAllProj = async function getAll() {
    if(arguments.length !== 0 ){
        "should take no arguments";
    }
    const bandCollection = await bands();
    const bandList = await bandCollection.find({},{projection: {_id:1,name:1}}).toArray();
    if (!bandList) throw 'Could not get all bands';
    for(let i of bandList){
        i["_id"] = i["_id"].toString();
    }
    return bandList;
}

const get = async function get(id) {
    if(arguments.length !== 1 ){
        "should have 1 argument";
    }
    if (!id){
        throw 'You must provide an id to search for';
    }
    if (typeof id !== 'string'){
        throw 'Id must be a string';
    } 
    if (id.trim().length === 0){
        throw 'Id cannot be an empty string or just spaces';
    }
    id = id.trim();
    if (!ObjectId.isValid(id)){
        throw 'invalid object ID';
    } 
    const bandCollection = await bands();
    const band = await bandCollection.findOne({ _id: ObjectId(id) });
    if (band === null){
        throw 'No band with that id';
    }
    band["_id"] = band["_id"].toString();
    return band;
}
const remove = async function remove(id){
    if(arguments.length !== 1 ){
        "should take 1 argument";
    }
    if (!id){
        throw 'You must provide an id to search for';
    }
    if (typeof id !== 'string'){
        throw 'Id must be a string';
    } 
    if (id.trim().length === 0){
        throw 'Id cannot be an empty string or just spaces';
    }
    id = id.trim();
    if (!ObjectId.isValid(id)){
        throw 'invalid object ID';
    } 
    const bandCollection = await bands();
    const band = await bandCollection.findOne({ _id: ObjectId(id) });
    if (band === null){
        throw `Could not delete band with id of ${id}`;
    }
    const deletionInfo = await bandCollection.deleteOne({ _id: ObjectId(id) });

    if (deletionInfo.deletedCount === 0) {
      throw `Could not delete band with id of ${id}`;
    }
    return `${band.name} has been  successfully deleted!`;
}


const update = async function update(id, name, genre, website, recordLabel, bandMembers, yearFormed) {
    if(arguments.length !== 7 ){
        "should take 7 arguments";
    }
    if(!id || !name || !genre || !website || !recordLabel || !bandMembers || !yearFormed){
        throw "field not provided";
    }
    if(typeof id !== 'string' || typeof name !== "string" || typeof website !== "string" || typeof recordLabel !== "string"){
        throw "not string";
    }
    if (id.trim().length === 0){
        throw 'Id cannot be an empty string or just spaces';
    }
    id = id.trim();
    if (!ObjectId.isValid(id)){
        throw 'invalid object ID';
    } 
    name.trim();
    website.trim();
    recordLabel.trim();
    if(name.length == 0 || website.length == 0  || recordLabel.length == 0 ){
        throw "not string";
    }
    if(website.length < 20 ){
        throw "string too short"
    }
    if(website.substring(0,11) !== "http://www."){
        throw "does not begin with http://www."
    } 
    if(website.substring(website.length - 4) !== ".com" ){
        throw "does not end with .com"
    }
    if(!Array.isArray(genre) || !Array.isArray(bandMembers)) {
        throw 'not an array';
    }
    if(genre.length == 0 || bandMembers.length == 0) {
        throw 'empty array';
    }
    for(let i = 0; i<genre.length;i++){
        if(typeof genre[i] !== "string"){
            throw 'element in genre not string';
        }
    }
    for(let i = 0; i<bandMembers.length;i++){
        if(typeof bandMembers[i] !== "string"){
            throw 'element in bandMembers not string';
        }
    }
    if(typeof yearFormed !== "number"){
        throw "year formed not a number";
    }
    if(yearFormed < 1900 || yearFormed > 2022 || !Number.isInteger(yearFormed)){
        throw "year formed not a valid number";
    }
    const bandCollection = await bands();
    const band = await bandCollection.findOne({ _id: ObjectId(id) });
    if(band == null){
        throw "band does not exist"
    }
    if(band.name == name && (await arraysEqual(band.genre,genre)) && band.website == website && band.recordLabel == recordLabel && (await arraysEqual(band.bandMembers,bandMembers)) && band.yearFormed == yearFormed){
        throw "No fields will change"
    }
    const updatedBand = {
        name: name,
        genre: genre,
        website: website,
        recordLabel: recordLabel,
        bandMembers: bandMembers,
        yearFormed: yearFormed
    };

    const updatedInfo = await bandCollection.updateOne(
      { _id: ObjectId(id) },
      { $set: updatedBand }
    );
    if (updatedInfo.modifiedCount === 0) {
      throw 'could not update band successfully';
    }

    

    return await this.get(id);
}

module.exports = {
    create,
    getAll,
    get,
    update,
    remove,
    getAllProj
}