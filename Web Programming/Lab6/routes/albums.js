const express = require('express');
const router = express.Router();
const data = require('../data');
const albumsData = data.albums;
const bandsData = data.bands;
const { ObjectId } = require('mongodb');


router.get('/:id', async (req, res) => {
    let id = req.params.id;
    try {
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
      } catch (e) {
        return res.status(400).json({error: e});
      }
    try {
        await bandsData.get(req.params.id);
      } catch (e) {
        res.status(404).json({error: e});
      }
    try {
      const albumList = await albumsData.getAll(req.params.id);
      if(albumList.length == 0){
          throw "no albums in this band found"
      }
      res.json(albumList);
    } catch (e) {
      res.status(404).json({error: e});
    }
});

router.post('/:id', async (req, res) => {
    let AlbumInfo = req.body;
    let bandId = req.params.id;
    try {
        if(!bandId || !AlbumInfo.title || !AlbumInfo.releaseDate || !AlbumInfo.tracks || !AlbumInfo.rating){
            throw "field not provided";
        }
        if(typeof bandId !== "string" || typeof AlbumInfo.title !== "string" || typeof AlbumInfo.releaseDate !== "string"){
            throw "not string";
        }
        bandId = bandId.trim();
        AlbumInfo.title = AlbumInfo.title.trim();
        AlbumInfo.releaseDate = AlbumInfo.releaseDate.trim();
        if(bandId.length == 0 || AlbumInfo.title.length == 0  || AlbumInfo.releaseDate.length == 0 ){
            throw "not string";
        }
        if (!ObjectId.isValid(bandId)){
            throw 'invalid object ID';
        }
        if(!Array.isArray(AlbumInfo.tracks)) {
            throw 'not an array';
        }
        if(AlbumInfo.tracks.length < 3) {
            throw 'need at least 3 tracks';
        }
        for(let i = 0; i<AlbumInfo.tracks.length;i++){
            if(typeof AlbumInfo.tracks[i] !== "string"){
                throw 'element in genre not string';
            }
            if(AlbumInfo.tracks[i].trim().length == 0){
                throw "string cannot be empty"
            }
        }
        if(typeof AlbumInfo.releaseDate !== "string"){
            throw "year formed not a string";
        }
        release1 = parseInt(AlbumInfo.releaseDate.substring(0,2)); 
        if(release1 > 12 || release1 < 1 || isNaN(release1)){
            throw "not valid date (month)"
        }
        release2 = AlbumInfo.releaseDate.charAt(2);
        if(release2 != "/"){
            throw "not valid date"
        }
        release3 = parseInt(AlbumInfo.releaseDate.substring(3,5));
        if(release3 > 31 || release3 < 1 || isNaN(release3)){
            throw "not valid date (day)"
        }
        release4 = AlbumInfo.releaseDate.charAt(5);
        if(release4 != "/"){
            throw "not valid date"
        }
        release5 = parseInt(AlbumInfo.releaseDate.substring(6,10));
        if(release5 < 1900 || release5 > 2022 || isNaN(release5)){
            throw "not valid date(year)"
        }
        if(typeof AlbumInfo.rating !== "number"){
            throw "rating not a number";
        }
        rating = Math.round(AlbumInfo.rating * 10) / 10;
        if(rating < 1 || rating > 5){
            throw "rating not valid"
        }
      } catch (e) {
        return res.status(400).json({error: e});
      }
      try {
        await bandsData.get(req.params.id);
      } catch (e) {
        res.status(404).json({error: e});
      }
    try {
        const newAlbum = await albumsData.create(
        bandId,
        AlbumInfo.title,
        AlbumInfo.releaseDate,
        AlbumInfo.tracks,
        AlbumInfo.rating
        );
        res.json(newAlbum);
      } catch (e) {
        res.sendStatus(500).json({error: e});
      }
});

router.get('/album/:id', async (req, res) => {
    id = req.params.id;
    try {
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
      } catch (e) {
        return res.status(400).json({error: e});
      }
      try {
        let album = await albumsData.get(req.params.id);
        res.json(album);
      } catch (e) {
        res.status(404).json({error: e});
      }
  });

  router.delete('/album/:id', async (req, res) => {
    id = req.params.id;
    try {
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
    } catch (e) {
      return res.status(400).json({error: e});
    }
    try {
      await albumsData.get(req.params.id);
    } catch (e) {
      return res.status(404).json({error: e});
    }
  
    try {
      await albumsData.remove(req.params.id);
      res.json({"albumId":req.params.id, deleted: true});
    } catch (e) {
      res.status(500).send('Internal Server Error');
    }
  })


module.exports = router;