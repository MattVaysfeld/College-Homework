const Data = require('./userApi');
const peopleData = Data.peopleMethods;
const workData = Data.workMethods;

module.exports = {
  people: peopleData,
  work : workData
};