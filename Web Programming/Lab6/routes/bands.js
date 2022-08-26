const express = require('express');
const router = express.Router();
const data = require('../data');
const bandsData = data.bands;
const { ObjectId } = require('mongodb');

router.get('/:id', async (req, res) => {
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
      const bandsList = await bandsData.get(req.params.id);
      res.json(bandsList);
    } catch (e) {
      res.status(404).json({error: e});
    }
  });

router.get('/', async (req, res) => {
    try {
      const bandsList = await bandsData.getAllProj();
      res.json(bandsList);
    } catch (e) {
      res.status(500).json({error: e});
    }
});

router.post('/', async (req, res) => {
    let BandInfo = req.body;
    try {
        if(!BandInfo.name || !BandInfo.genre || !BandInfo.website || !BandInfo.recordLabel || !BandInfo.bandMembers || !BandInfo.yearFormed){
            throw "field not provided";
        }
        if(typeof BandInfo.name !== "string" || typeof BandInfo.website !== "string" || typeof BandInfo.recordLabel !== "string"){
            throw "not string";
        }
        BandInfo.name = BandInfo.name.trim();
        BandInfo.website = BandInfo.website.trim();
        BandInfo.recordLabel = BandInfo.recordLabel.trim();
        if(BandInfo.name.length == 0 || BandInfo.website.length == 0  || BandInfo.recordLabel.length == 0 ){
            throw "not string";
        }
        if(BandInfo.website.length < 20 ){
            throw "string too short"
        }
        if(BandInfo.website.substring(0,11) !== "http://www."){
            throw "does not begin with http://www."
        } 
        if(BandInfo.website.substring(BandInfo.website.length - 4) !== ".com" ){
            throw "does not end with .com"
        }
        if(!Array.isArray(BandInfo.genre) || !Array.isArray(BandInfo.bandMembers)) {
            throw 'not an array';
        }
        if(BandInfo.genre.length == 0 || BandInfo.bandMembers.length == 0) {
            throw 'empty array';
        }
        for(let i = 0; i<BandInfo.genre.length;i++){
            if(typeof BandInfo.genre[i] !== "string"){
                throw 'element in genre not string';
            }
        }
        for(let i = 0; i<BandInfo.bandMembers.length;i++){
            if(typeof BandInfo.bandMembers[i] !== "string"){
                throw 'element in bandMembers not string';
            }
        }
        if(typeof BandInfo.yearFormed !== "number"){
            throw "year formed not a number";
        }
        if(BandInfo.yearFormed < 1900 || BandInfo.yearFormed > 2022 || !Number.isInteger(BandInfo.yearFormed)){
            throw "year formed not a valid number";
        }
      } catch (e) {
        return res.status(400).json({error: e});
      }
    try {
        const newBand = await bandsData.create(
          BandInfo.name,
          BandInfo.genre,
          BandInfo.website,
          BandInfo.recordLabel,
          BandInfo.bandMembers,
          BandInfo.yearFormed
        );
        res.json(newBand);
      } catch (e) {
        res.sendStatus(500).json({error: e});
      }
});

router.put('/:id', async (req, res) => {
    let BandInfo = req.body;
    try {
        if(!BandInfo.name || !BandInfo.genre || !BandInfo.website || !BandInfo.recordLabel || !BandInfo.bandMembers || !BandInfo.yearFormed){
            throw "field not provided";
        }
        if(typeof BandInfo.name !== "string" || typeof BandInfo.website !== "string" || typeof BandInfo.recordLabel !== "string"){
            throw "not string";
        }
        BandInfo.name = BandInfo.name.trim();
        BandInfo.website = BandInfo.website.trim();
        BandInfo.recordLabel = BandInfo.recordLabel.trim();
        if(BandInfo.name.length == 0 || BandInfo.website.length == 0  || BandInfo.recordLabel.length == 0 ){
            throw "not string";
        }
        if(BandInfo.website.length < 20 ){
            throw "string too short"
        }
        if(BandInfo.website.substring(0,11) !== "http://www."){
            throw "does not begin with http://www."
        } 
        if(BandInfo.website.substring(BandInfo.website.length - 4) !== ".com" ){
            throw "does not end with .com"
        }
        if(!Array.isArray(BandInfo.genre) || !Array.isArray(BandInfo.bandMembers)) {
            throw 'not an array';
        }
        if(BandInfo.genre.length == 0 || BandInfo.bandMembers.length == 0) {
            throw 'empty array';
        }
        for(let i = 0; i<BandInfo.genre.length;i++){
            if(typeof BandInfo.genre[i] !== "string"){
                throw 'element in genre not string';
            }
        }
        for(let i = 0; i<BandInfo.bandMembers.length;i++){
            if(typeof BandInfo.bandMembers[i] !== "string"){
                throw 'element in bandMembers not string';
            }
        }
        if(typeof BandInfo.yearFormed !== "number"){
            throw "year formed not a number";
        }
        if(BandInfo.yearFormed < 1900 || BandInfo.yearFormed > 2022 || !Number.isInteger(BandInfo.yearFormed)){
            throw "year formed not a valid number";
        }
    } catch (e) {
      return res.status(400).json({error: e});
    }
  
    try {
      await bandsData.get(req.params.id);
    } catch (e) {
      return res.status(404).json({e});
    }
    try {
      const updatedBand = await bandsData.update(req.params.id, BandInfo.name,
        BandInfo.genre,
        BandInfo.website,
        BandInfo.recordLabel,
        BandInfo.bandMembers,
        BandInfo.yearFormed);
      res.json(updatedBand);
    } catch (e) {
      res.status(500).send(e);
    }
  });

  router.delete('/:id', async (req, res) => {
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
      await bandsData.get(req.params.id);
    } catch (e) {
      return res.status(404).json({error: e});
    }
  
    try {
      await bandsData.remove(req.params.id);
      res.json({"bandsId":req.params.id, deleted: true});
    } catch (e) {
      res.status(500).send('Internal Server Error');
    }
  })
module.exports = router;