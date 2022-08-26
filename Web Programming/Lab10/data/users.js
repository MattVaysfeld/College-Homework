const mongoCollections = require('../config/mongoCollections');
const users = mongoCollections.users;
const { ObjectId } = require('mongodb');
const bcrypt = require('bcrypt');


const createUser = async function createUser(username, password){
    if(arguments.length !== 2 ){
        throw "should have 2 arguments";
    }
    if(!username || !password){
        throw "field not provided";
    }
    if(typeof username !== "string" || typeof password !== "string"){
        throw "not string";
    }
    //get rid of spaces
    if(!(username == username.split(" ").join(""))){
        throw "Username cannot have spaces"
    }
    
    if(username.length < 4){
        throw "Username cannot be less than 4 characters";
    }
    
    username = username.toLowerCase();
    if(!(/^[A-Za-z0-9]*$/.test(username))){
        throw "Can contain only alphanumeric characters";
    }

    if(!(password == password.split(" ").join(""))){
        throw "Password cannot have spaces"
    }
    if(password.length < 6){
        throw "Password cannot be less than 6 characters";
    }

    const hash = await bcrypt.hash(password, 10);


    const userCollection = await users();

    let newUser = {
        username: username,
        password: hash
    };
    const dupuser = await userCollection.findOne({ username: username });
    if (!(dupuser === null)){
        throw 'Name Already Exists';
    }
    const insertInfo = await userCollection.insertOne(newUser);
    if (!insertInfo.acknowledged || !insertInfo.insertedId){
      throw 'Could not add user';
    }
    newUser["_id"] = newUser["_id"].toString();
    return {userInserted: true};
}

const checkUser = async function checkUser(username, password){
    if(arguments.length !== 2 ){
        throw "should have 2 arguments";
    }
    if(!username || !password){
        throw "field not provided";
    }
    if(typeof username !== "string" || typeof password !== "string"){
        throw "not string";
    }
    //get rid of spaces
    if(!(username == username.split(" ").join(""))){
        throw "Username cannot have spaces"
    }
    
    if(username.length < 4){
        throw "Username cannot be less than 4 characters";
    }
    
    username = username.toLowerCase();
    if(await !(/^[A-Za-z0-9]*$/.test(username))){
        throw "Can contain only alphanumeric characters";
    }

    if(!(password == password.split(" ").join(""))){
        throw "Username cannot have spaces"
    }
    if(password.length < 6){
        throw "Password cannot be less than 6 characters";
    }

    const userCollection = await users();

    const user = await userCollection.findOne({ username: username });
    if (user === null){
        throw "Either the username or password is invalid";
    }
    let comp = await bcrypt.compare(password, user.password);
    if(!comp){
        throw "Either the username or password is invalid";
    }
    return {authenticated: true}
}

module.exports = {
    createUser,
    checkUser
}