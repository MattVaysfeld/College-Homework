const mongoCollections = require('../config/mongoCollections');
const bands1 = require("./bands");
const bands = mongoCollections.bands;
const albums = mongoCollections.albums;
const { ObjectId } = require('mongodb');

const updateOverall = async function(bandId){
    const bandCollection = await bands();
    let average = await bandCollection.aggregate([{$unwind: "$albums"},{$match: {"_id":ObjectId(bandId)}},{$group :{"_id" : "$_id", "average": {$avg:"$albums.rating"}}}]).toArray();
    if(average.length == 0){
        average = 0;
    }
    else{
        average = average[0]["average"]
        average = Math.round(average * 10) / 10;
    }
    const insertInfo = await bandCollection.updateOne({_id: ObjectId(bandId)}, {$set: {overallRating: average}});
    if (!insertInfo.acknowledged){
      throw 'Could not update overallRating';
    }
}
const create = async function create(bandId, title, releaseDate, tracks, rating){
    if(arguments.length !== 5 ){
        throw "should have 5 arguments";
    }
    if(!bandId || !title || !releaseDate || !tracks || !rating){
        throw "field not provided";
    }
    if(typeof bandId !== "string" || typeof title !== "string" || typeof releaseDate !== "string"){
        throw "not string";
    }
    bandId = bandId.trim();
    title = title.trim();
    releaseDate = releaseDate.trim();
    if(bandId.length == 0 || title.length == 0  || releaseDate.length == 0 ){
        throw "not string";
    }
    if (!ObjectId.isValid(bandId)){
        throw 'invalid object ID';
    } 
    const bandCollection = await bands();
    const band = await bandCollection.findOne({ _id: ObjectId(bandId) });
    if(band == null){
        throw "band does not exist"
    }
    if(!Array.isArray(tracks)) {
        throw 'not an array';
    }
    if(tracks.length < 3) {
        throw 'need at least 3 tracks';
    }
    for(let i = 0; i<tracks.length;i++){
        if(typeof tracks[i] !== "string"){
            throw 'element in genre not string';
        }
        if(tracks[i].trim().length == 0){
            throw "string cannot be empty"
        }
    }
    if(typeof releaseDate !== "string"){
        throw "year formed not a string";
    }
    release1 = parseInt(releaseDate.substring(0,2)); 
    if(release1 > 12 || release1 < 1 || isNaN(release1)){
        throw "not valid date (month)"
    }
    release2 = releaseDate.charAt(2);
    if(release2 != "/"){
        throw "not valid date"
    }
    release3 = parseInt(releaseDate.substring(3,5));
    if(release3 > 31 || release3 < 1 || isNaN(release3)){
        throw "not valid date (day)"
    }
    release4 = releaseDate.charAt(5);
    if(release4 != "/"){
        throw "not valid date"
    }
    release5 = parseInt(releaseDate.substring(6,10));
    if(release5 < 1900 || release5 > 2022 || isNaN(release5)){
        throw "not valid date(year)"
    }
    if(typeof rating !== "number"){
        throw "rating not a number";
    }
    rating = Math.round(rating * 10) / 10;
    if(rating < 1 || rating > 5){
        throw "rating not valid"
    }
    id = new ObjectId();
    let newAlbum = {
        _id : id,
        title: title,
        releaseDate: releaseDate,
        tracks: tracks,
        rating: rating
    };
    const insertInfo = await bandCollection.updateOne({_id: ObjectId(bandId)}, {$push: {albums: newAlbum}}, );
    if (!insertInfo.acknowledged || !insertInfo.modifiedCount){
      throw 'Could not add album';
    }
    newAlbum["_id"] = newAlbum["_id"].toString();
    await updateOverall(bandId);
    return newAlbum;

}

const getAll = async function getAll(bandId) {
    if(arguments.length !== 1 ){
        "should take 1 argument";
    }
    if(!bandId){
        throw "need to provide bandId"
    }
    if(typeof bandId !== "string"){
        throw "bandId needs to be string"
    }
    bandId = bandId.trim()
    if(bandId.length == 0){
        throw "band Id cannot be empty string"
    }    
    if (!ObjectId.isValid(bandId)){
        throw 'invalid object ID';
    }
    const bandCollection = await bands();
    let albumList = await bandCollection.find({_id : ObjectId(bandId)}, {projection: {_id:0,albums:1}}).toArray();
    if(albumList.length == 0) throw 'No band with bandId'
    let albumList2 = albumList[0]["albums"];
    if (!albumList2) throw 'Could not get all albums';
    for(let i of albumList2){
        i["_id"] = i["_id"].toString();
    }
    return albumList2;
}



const get = async function get(albumId) {
    if(arguments.length !== 1 ){
        "should take 1 argument";
    }
    if(!albumId){
        throw "need to provide albumId"
    }
    if(typeof albumId !== "string"){
        throw "bandId needs to be string"
    }
    albumId = albumId.trim()
    if(albumId.length == 0){
        throw "albumId cannot be empty string"
    }    
    if (!ObjectId.isValid(albumId)){
        throw 'invalid object ID';
    }
    const bandCollection = await bands();
    //Find the id of the band which album is in
    const band =  await bandCollection.findOne({'albums._id': ObjectId(albumId)});
    if (band === null){
        throw 'No band with that album';
    }
    let bandId = band["_id"].toString();

    let album = await bandCollection.aggregate([{ "$match":{ _id: ObjectId(bandId)} }, {$unwind: "$albums"}, {"$match":{ "albums._id": ObjectId(albumId)}}, {
        "$replaceRoot": {
          "newRoot": "$albums"
        }
      } ]).toArray();
    
    if (album === null){
        throw 'No album with that id';
    }
    album = album[0];
    album["_id"] = album["_id"].toString();
    return album;
}

const remove = async function remove(albumId){
    if(arguments.length !== 1 ){
        "should take 1 argument";
    }
    if (!albumId){
        throw 'You must provide an id to search for';
    }
    if (typeof albumId !== 'string'){
        throw 'Id must be a string';
    } 
    if (albumId.trim().length === 0){
        throw 'Id cannot be an empty string or just spaces';
    }
    albumId = albumId.trim();
    if (!ObjectId.isValid(albumId)){
        throw 'invalid object ID';
    } 
    const bandCollection = await bands();
    //check if there is an album with that id
    let album = await bandCollection.findOne({ "albums._id": ObjectId(albumId)}, {projection: {albums:1}});
    album = album["albums"][0];
    if (album === null){
        throw 'No album with that id';
    }
    //Find the id of the band which album is in
    const band =  await bandCollection.findOne({'albums._id': ObjectId(albumId)});
    let bandId = band["_id"].toString();
    //delete the album from that band
    const deletionInfo = await bandCollection.updateOne({_id: ObjectId(bandId)}, {$pull: {albums: {_id : ObjectId(albumId)}}});

    if (deletionInfo.deletedCount === 0) {
      throw `Could not delete album with id of ${id}`;
    }
    await updateOverall(bandId);
    const returnband =  await bandCollection.findOne({_id: ObjectId(bandId)});
    return returnband;
}

module.exports = {
    create,
    getAll,
    get,
    remove
}