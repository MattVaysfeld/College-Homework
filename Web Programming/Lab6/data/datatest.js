//Matthew Vaysfeld
//I pledge my honor that I have abided by the Stevens Honor System


const bands = require("./bands");
const albums = require("./albums");
const connection = require('../config/mongoConnection');

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
            All = await bands.getAll();
            console.log(All);
        }catch(e){
            console.log(e);
        }
    
    
    //Testing update
    // try{
    //     pinkFloyd = await bands.create("Pink Floyd", ["Progressive Rock", "Psychedelic rock", "Classic Rock"], "http://www.pinkfloyd.com", "EMI", ["Roger Waters", "David Gilmour", "Nick Mason", "Richard Wright", "Sid Barrett" ], 1965);
    //     console.log(pinkFloyd);
    // }catch(e){
    //     console.log(e);
    // }
    // try{
    //     pinkFloyd2 = await bands.create("Pink Floyd2", ["Progressive Rock", "Psychedelic rock", "Classic Rock"], "http://www.pinkfloyd.com", "EMI", ["Roger Waters", "David Gilmour", "Nick Mason", "Richard Wright", "Sid Barrett" ], 1965);
    //     console.log(pinkFloyd);
    // }catch(e){
    //     console.log(e);
    // }
    // try{
    //     updatedFloyd = await bands.update(pinkFloyd._id.toString(),"Blue Floyd", ["Hello", "Psychedelic rock", "Classic Rock"], "http://www.bluefloyd.com", "EBlueI", ["Roger Fires", "Hello Gilmour", "Nick Mason", "Richard Wright", "Sid Barrett" ], 2019);
    //     console.log(updatedFloyd);
    // }catch(e){
    //     console.log(e);
    // }
    //Testing albums
    try{
        testAlbum = await albums.create(pinkFloyd._id.toString(), "HelloWorld", "01/01/2020", ["Yes","No","Maybe"], 4);
        console.log(testAlbum);
    }catch(e){
        console.log(e);
    }
    try{
        testAlbum2 = await albums.create(pinkFloyd._id.toString(), "HelloWorld2", "01/01/2020", ["Yes","No","Maybe"], 2);
        console.log(testAlbum2);
    }catch(e){
        console.log(e);
    }
    // try{
    //     testAlbum3 = await albums.create(pinkFloyd2._id.toString(), "Yes1", "01/01/2020", ["Yes","No","Maybe"], 1);
    //     console.log(testAlbum);
    // }catch(e){
    //     console.log(e);
    // }
    // //Testing getAll
    // try{
    //     allAlbums = await albums.getAll(pinkFloyd._id.toString());
    //     console.log(allAlbums);
    // }catch(e){
    //     console.log(e);
    // }
    //Testing get
    console.log("get:")
    try{
        getAlbum = await albums.get(testAlbum2._id.toString());
        console.log(getAlbum);
    }catch(e){
        console.log(e);
    }
    // //Testing remove
    // console.log("remove:")
    // try{
    //     removedAlbum = await albums.remove(testAlbum._id.toString());
    //     console.log(removedAlbum);
    // }catch(e){
    //     console.log(e);
    // }
    // try{
    //     removedAlbum2 = await albums.remove(testAlbum2._id.toString());
    //     console.log(removedAlbum2);
    // }catch(e){
    //     console.log(e);
    // }


    await connection.closeConnection();
    console.log('Done!');
}

main();