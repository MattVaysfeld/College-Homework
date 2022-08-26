const express = require('express');
const peopleRouter = express.Router();
const workRouter = express.Router();
const data = require('../data');
const peopleData = data.people;
const workData = data.work;

peopleRouter
  .route('/:id')
  .get(async (req, res) => {
    try {
      const person = await peopleData.getPeopleById(req.params.id);
      res.json(person);
    } catch (e) {
      res.status(404).json({ error: e });
    }
  })

peopleRouter
  .route('/')
  .get(async (req, res) => {
    try {
      const peopleList = await peopleData.getAllPeople();
      res.json(peopleList);
    } catch (e) {
      res.status(500).json({ error: e });
    }
  })

  workRouter
  .route('/:id')
  .get(async (req, res) => {
    try {
      const work = await workData.getWorkById(req.params.id);
      res.json(work);
    } catch (e) {
      res.status(404).json({ error: e });
    }
  })

  workRouter
  .route('/')
  .get(async (req, res) => {
    try {
      const workList = await workData.getAllWork();
      res.json(workList);
    } catch (e) {
      res.status(500).json({ error: e });
    }
  })



module.exports = {
    peopleRouter,
    workRouter
};