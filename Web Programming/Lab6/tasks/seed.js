const dbConnection = require('../config/mongoConnection');
const data = require('../data/');
const bands = data.bands;
const albums = data.albums;

async function main() {
  const db = await dbConnection.connectToDb();
  await db.dropDatabase();
  //Create Bands
  const pink = await bands.create("Pink Floyd", ["Progressive Rock", "Psychedelic rock", "Classic Rock"], "http://www.pinkfloyd.com", "EMI", ["Roger Waters", "David Gilmour", "Nick Mason", "Richard Wright", "Sid Barrett" ], 1965);
  const pink2 = await bands.create("Pink Floyd2", ["Progressive Rock", "Psychedelic rock", "Classic Rock"], "http://www.pinkfloyd.com", "EMI", ["Roger Waters", "David Gilmour", "Nick Mason", "Richard Wright", "Sid Barrett" ], 1965);
  const pink3 = await bands.create("Pink Floyd3", ["Progressive Rock", "Psychedelic rock", "Classic Rock"], "http://www.pinkfloyd.com", "EMI", ["Roger Waters", "David Gilmour", "Nick Mason", "Richard Wright", "Sid Barrett" ], 1965);
  const pink4 = await bands.create("Pink Floyd4", ["Progressive Rock", "Psychedelic rock", "Classic Rock"], "http://www.pinkfloyd.com", "EMI", ["Roger Waters", "David Gilmour", "Nick Mason", "Richard Wright", "Sid Barrett" ], 1965);
  const pink5 = await bands.create("Pink Floyd5", ["Progressive Rock", "Psychedelic rock", "Classic Rock"], "http://www.pinkfloyd.com", "EMI", ["Roger Waters", "David Gilmour", "Nick Mason", "Richard Wright", "Sid Barrett" ], 1965);
  const blue = await bands.create("Blue Boys", ["AAAA"], "http://www.Blueyfloyd.com", "BLy", ["Blue Waters", "ABABAB", "yooo", "Sid Barrett" ], 2000);
  const blue2 = await bands.create("Blue Boys2", ["BBBB"], "http://www.Blueyfloyd.com", "BLy", ["Blue Waters", "ABABAB", "yooo", "Sid Barrett" ], 2001);
  const blue3 = await bands.create("Blue Boys3", ["BBBB"], "http://www.Blueyfloyd.com", "BLy", ["Blue Waters", "ABABAB", "yooo", "Sid Barrett" ], 2001);
  const blue4 = await bands.create("Blue Boys4", ["BBBB"], "http://www.Blueyfloyd.com", "BLy", ["Blue Waters", "ABABAB", "yooo", "Sid Barrett" ], 2001);
  const blue5 = await bands.create("Blue Boys5", ["BBBB"], "http://www.Blueyfloyd.com", "BLy", ["Blue Waters", "ABABAB", "yooo", "Sid Barrett" ], 2001);
  const id = pink._id.toString();
  const id2 = pink2._id.toString();
  const id3 = pink3._id.toString();
  const id4 = pink4._id.toString();
  const id5 = pink5._id.toString();
  const id6 = blue._id.toString();
  const id7 = blue2._id.toString();
  const id8 = blue3._id.toString();
  const id9 = blue4._id.toString();
  const id10 = blue5._id.toString();

  //Create Albums
  await albums.create(id, "HelloWorld", "01/01/2020", ["Yes","No","Maybe"], 4);
  await albums.create(id, "HelloWorld2", "01/01/2020", ["Yes","No","Maybe"], 4);
  await albums.create(id2, "Bye", "01/01/2020", ["Yes","No","Maybe"], 3);
  await albums.create(id2, "Bye2", "01/01/2020", ["Yes","No","Maybe"], 3);
  await albums.create(id3, "HOwdy", "01/01/2020", ["Yes","No","Maybe"], 2);
  await albums.create(id3, "HOwdy", "01/01/2020", ["Yes","No","Maybe"], 2);
  await albums.create(id4, "AAAA", "01/01/2020", ["Yes","No","Maybe"], 1.2);
  await albums.create(id4, "AAAAA2", "01/01/2020", ["Yes","No","Maybe"], 2);
  await albums.create(id5, "LLLLL", "01/01/2020", ["Yes","No","Maybe"], 3);
  await albums.create(id6, "SSSSS", "01/01/2020", ["Yes","No","Maybe"], 4);
  await albums.create(id7, "Big", "01/01/2020", ["Yes","No","Maybe"], 4.8);
  await albums.create(id8, "Small", "01/01/2020", ["Yes","No","Maybe"], 2);
  await albums.create(id10, "One", "01/01/2020", ["Yes","No","Maybe"], 2.5);
  await albums.create(id10, "Two", "01/01/2020", ["Yes","No","Maybe"], 3.5);
  await albums.create(id10, "Tnree", "01/01/2020", ["Yes","No","Maybe"], 3);

  console.log('Done seeding database');

  await dbConnection.closeConnection();
}

main();