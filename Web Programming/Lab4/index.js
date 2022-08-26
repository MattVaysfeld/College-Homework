//Matthew Vaysfeld
//I pledge my honor that I have abided by the Stevens Honor System
const bands = require("./data/bands");
const connection = require('./config/mongoConnection');

let pinkFloyd = undefined;
let best = undefined;
let IDK = undefined;

async function main() {
    const db = await connection.connectToDb();
    await db.dropDatabase();
    try{
        pinkFloyd = await bands.create("Pink Floyd", ["Progressive Rock", "Psychedelic rock", "Classic Rock"], "http://www.pinkfloyd.com", "EMI", ["Roger Waters", "David Gilmour", "Nick Mason", "Richard Wright", "Sid Barrett" ], 1965);
        console.log(pinkFloyd);
    }catch(e){
        console.log(e);
    }
    try{
        best = await bands.create("Best Band", ["Best","Heavy Metal","Rock"], "http://www.bestband.com", "Best", ["Peterson Daniels","Tommy Johnson", "Dr.Who", "Dwayne Johnson"], 2021);
    }catch(e){
        console.log(e);
    }
    try{
        const allBands = await bands.getAll();
        console.log(allBands);
    }catch(e){
        console.log(e);
    }
    try{
        IDK = await bands.create("IDK", ["Big","IDK"], "http://www.noclue.com", "NOCLUE", ["Man","Woman","Person"], 2000);
        console.log(IDK);
    }catch(e){
        console.log(e);
    }
    try{
        const renamedpinkFloyd = await bands.rename(pinkFloyd._id, "Renamed Pinky"); 
        console.log(renamedpinkFloyd); 
    }catch(e){
        console.log(e);
    }
    try{
        const remove = await bands.remove(best._id.toString()); 
        console.log(remove); 
    }catch(e){
        console.log(e);
    }
    try{
        const allBands2 = await bands.getAll();
        console.log(allBands2);
    }catch(e){
        console.log(e);
    }
    try{
        const fakestuff = await bands.create(1,2,3);
    }catch(e){
        console.log(e);
    }
    try{
        const removefake = await bands.remove(best._id.toString());
        console.log(removefake); 
    }catch(e){
        console.log(e);
    }
    try{
        const renamedFake = await bands.rename(best._id.toString(),"hello"); 
        console.log(renamedFake); 
    }catch(e){
        console.log(e);
    }
    try{
        const renamedFake2 = await bands.rename(pinkFloyd._id,1); 
        console.log(renamedFake2); 
    }catch(e){
        console.log(e);
    }
    try{
        const getFake = await bands.get(best._id.toString());
        console.log(getFake);
    }catch(e){
        console.log(e);
    }

    await connection.closeConnection();
    console.log('Done!');
}

main();