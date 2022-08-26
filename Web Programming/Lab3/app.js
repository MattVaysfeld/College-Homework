//ToDo: fix error messages, esp for sameBirthday

const people = require("./people");
const stocks = require("./stocks");

async function main(){
    
    //getPersonById
    console.log("")
    console.log("getPersonById")
    console.log("")
    try{
        const person = await people.getPersonById('7989fa5e-8f3f-458d-ad58-23c8d9ef5a10');
        console.log (person);
    }catch(e){
        console.log (e);
    }
    try{
        const person = await people.getPersonById(1001);
        console.log (person);
    }catch(e){
        console.log (e);
    }
    try{
        const person = await people.getPersonById();
        console.log (person);
    }catch(e){
        console.log (e);
    }
    try{
        const person = await people.getPersonById('7989fa5e-5617-43f7-a931-46036f9dbcff');
        console.log (person);
    }catch(e){
        console.log (e);
    }

    //Same Email
    console.log("")
    console.log("SameEmail")
    console.log("")
    try{
        console.log (await people.sameEmail("HArVard.eDu"));
    }catch(e){
        console.log (e);
    }
    try{
        console.log (await people.sameEmail("google.com.hk"));
    }catch(e){
        console.log (e);
    }


    //ManipulateIp
    console.log("")
    console.log("ManipulateIp")
    console.log("")
    try{
        console.log (await people.manipulateIp());
    }catch(e){
        console.log (e);
    }

    //SameBirthday
    console.log("")
    console.log("SameBirthday")
    console.log("")
    try{
        console.log (await people.sameBirthday(9, 25));
    }catch(e){
        console.log (e);
    }
    try{
        console.log (await people.sameBirthday("09", "25"));
    }catch(e){
        console.log (e);
    }
    try{
        console.log (await people.sameBirthday(9, 31));
    }catch(e){
        console.log (e);
    }
    try{
        console.log (await people.sameBirthday("    ", "25"));
    }catch(e){
        console.log (e);
    }

    //listShareholder
    console.log("")
    console.log("listShareHolder")
    console.log("")
    try{
        console.log (await stocks.listShareholders("Just Energy Group, Inc."));
    }catch(e){
        console.log (e);
    }

    //totalShares
    console.log("")
    console.log("totalShares")
    console.log("")
    try{
        console.log (await stocks.totalShares("Aeglea BioTherapeutics, Inc."));
    }catch(e){
        console.log (e);
    }
    try{
        console.log (await stocks.listShareholders('foobar'));
    }catch(e){
        console.log (e);
    }


    //listStocks
    console.log("")
    console.log("ListStocks")
    console.log("")
    try{
        console.log (await stocks.listStocks("Grenville", "Pawelke"));
    }catch(e){
        console.log (e);
    }
    try{
        console.log (await stocks.listStocks("Patrick", "Hill"));
    }catch(e){
        console.log (e);
    }
    try{
        console.log (await stocks.listStocks(1,2));
    }catch(e){
        console.log (e);
    }

    //getStockById
    console.log("")
    console.log("getStockById")
    console.log("")
    try{
        console.log (await stocks.getStockById("f652f797-7ca0-4382-befb-2ab8be914ff0"));
    }catch(e){
        console.log (e);
    }
    try{
        console.log (await stocks.getStockById('7989fa5e-5617-43f7-a931-46036f9dbcff'));
    }catch(e){
        console.log (e);
    }
    
    
}

//call main
main();