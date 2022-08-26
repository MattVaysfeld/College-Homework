const showRoutes = require('./searchshows');
const path = require('path');

const constructorMethod = (app) => {
  app.use('/', showRoutes);

  app.use('*', (req, res) => {
    res.status(404).json({ error: 'Not found' });
  });
};

module.exports = constructorMethod;