//Matthew Vaysfeld
//I pledge my honor that I have abided by the Stevens Honor System


const users = require("./users");
const connection = require('../config/mongoConnection');

async function main() {
    const db = await connection.connectToDb();
    await db.dropDatabase();
    try{
        let newUser = await users.createUser("MatthewV","password");
        console.log(newUser);
    }catch(e){
        console.log(e);
    }
    try{
        let test = await users.checkUser("MatthewV","password");
        console.log(test);
    }catch(e){
        console.log(e);
    }
    
    


    await connection.closeConnection();
    console.log('Done!');
}

main();