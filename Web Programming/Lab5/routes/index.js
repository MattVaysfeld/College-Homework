const routes = require('./userApi');

const constructorMethod = (app) => {
  app.use('/people', routes.peopleRouter);
  app.use('/work', routes.workRouter);

  app.use('*', (req, res) => {
    res.status(404).json({ error: 'Not found' });
  });
};

module.exports = constructorMethod;