const bandsRoutes = require('./bands');
const albumsRoutes = require('./albums');

const constructorMethod = (app) => {
  app.use('/bands', bandsRoutes);
  app.use('/albums', albumsRoutes);

  app.use('*', (req, res) => {
    res.status(404).json({ error: 'Not found' });
  });
};

module.exports = constructorMethod;