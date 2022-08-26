//Matthew Vaysfeld
//I pledge my honor that I have abided by the Stevens Honor System
const express = require('express');
const app = express();
const session = require('express-session');
const configRoutes = require('./routes');
const exphbs = require('express-handlebars');

app.use(express.json());

app.engine('handlebars', exphbs.engine({defaultLayout: 'main'}));
app.set('view engine', 'handlebars');
app.use(express.urlencoded({extended:true}));

app.use(
  session({
    name: 'AuthCookie',
    secret: 'some secret string!',
    resave: false,
    saveUninitialized: true
  })
);

app.use((req, res, next) => {
  let timestamp = new Date();
  let method = req.method;
  let route = req.originalUrl;
  let auth =  "Non Authenticated User"
  if(req.session.user){
    auth =  "Authenticated User"
  }
  console.log(timestamp + ": " + method + " " + route + " " + auth);
  next()
});


app.use('/private', (req, res, next) => {
  if (!req.session.user) {
    return res.status(403).render('layouts/notlog');
  } else {
    next();
  }
});




configRoutes(app);

app.listen(3000, () => {
  console.log("We've now got a server!");
  console.log('Your routes will be running on http://localhost:3000');
});