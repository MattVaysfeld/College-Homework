const express = require('express');
const router = express.Router();
const data = require('../data');
const userData = data.users;
const { ObjectId } = require('mongodb');

router.get('/', async (req, res) => {
    if (req.session.user) {
         res.redirect('/private');
    } else{
      res.render('layouts/form');
    }
    
});

router.get('/signup', async (req, res) => {
  if (req.session.user) {
      return res.redirect('/private');
  } else{
    res.render('layouts/signup');
  }
  
});

router.post('/signup', async (req, res) => {
  let username = req.body.username;
  let password = req.body.password;
  if(!username || !password){
    res.render('layouts/signup',{hasError:true,error:"UserName or Password not provided"});
    return;
  }
  if(typeof username !== "string" || typeof password !== "string"){
    res.status(400).render('layouts/signup',{hasError:true,error:"not string"});
    return;
  }
  //get rid of spaces
  username = username.trim();
  if(!(username == username.split(" ").join(""))){
    res.status(400).render('layouts/signup',{hasError:true,error:"Username cannot have spaces"});
    return;
  }

  if(username.length < 4){
    res.status(400).render('layouts/signup',{hasError:true,error:"Username cannot be less than 4 characters"});
    return;
  }
  username = username.toLowerCase();
  if(!(/^[A-Za-z0-9]*$/.test(username))){
    res.status(400).render('layouts/signup',{hasError:true,error:"Can contain only alphanumeric characters"});
    return;
  }

  if(!(password == password.split(" ").join(""))){
    res.status(400).render('layouts/signup',{hasError:true,error:"Password cannot have spaces"});
    return;
  }
  if(password.length < 6){
    res.status(400).render('layouts/signup',{hasError:true,error:"Password cannot be less than 6 characters"});
    return;
  }

  try{
    const newUser = await userData.createUser(username, password);
    if(typeof newUser === "object" && newUser !== null && newUser.userInserted){
      res.redirect('/');
    } else{
      res.status(500).render('layouts/signup',{hasError:true,error:"Internal Server Error"});
    }
  } catch(e){
    res.status(400).render('layouts/signup',{hasError:true,error:e});
  }
  
});

router.post('/login', async (req, res) => {
  let username = req.body.username;
  let password = req.body.password;
  if(!username || !password){
    res.render('layouts/form',{hasError:true,error:"UserName or Password not provided"});
    return;
  }
  if(typeof username !== "string" || typeof password !== "string"){
    res.status(400).render('layouts/form',{hasError:true,error:"not string"});
    return;
  }
  //get rid of spaces
  username = username.trim();
  if(!(username == username.split(" ").join(""))){
    res.status(400).render('layouts/form',{hasError:true,error:"Username cannot have spaces"});
    return;
  }

  if(username.length < 4){
    res.status(400).render('layouts/form',{hasError:true,error:"Username cannot be less than 4 characters"});
    return;
  }
  username = username.toLowerCase();
  if(!(/^[A-Za-z0-9]*$/.test(username))){
    res.status(400).render('layouts/form',{hasError:true,error:"Can contain only alphanumeric characters"});
    return;
  }

  if(!(password == password.split(" ").join(""))){
    res.status(400).render('layouts/form',{hasError:true,error:"Password cannot have spaces"});
    return;
  }
  if(password.length < 6){
    res.status(400).render('layouts/form',{hasError:true,error:"Password cannot be less than 6 characters"});
    return;
  }

  try{
    const newUser = await userData.checkUser(username, password);
    if(typeof newUser === "object" && newUser !== null && newUser.authenticated){
      req.session.user = {username: username};
      res.redirect('/private');
    } else{
      res.status(400).render('layouts/form',{hasError:true,error:"Did not provide valid username and/or password"});
    }
  } catch(e){
    res.status(400).render('layouts/form',{hasError:true,error:e});
  }
});

router.get('/private', async (req, res) => {
    res.render('layouts/private',{username:req.session.user.username});
});

router.get('/logout', async (req, res) => {
  req.session.destroy();
  res.render('layouts/logout');
});

module.exports = router;