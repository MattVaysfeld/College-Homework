const express = require('express');
const router = express.Router();
const data = require('../data');
const showData = data.show;

router.get('/', async (req, res) => {
    res.render('shows/form',{title:"Show Finder"});
});

router.post('/searchshows', async (req, res) => {
    let search = req.body.showSearchTerm;
    let noTerm = false;
    let noResults = false;
    if (!search) {
        noTerm=true;
        res.status(400).render('shows/searchshows',{title:"Show Finder",showSearchTerm:search,noTerm:noTerm,noResults:noResults});
        return;
    }
    else{
        search = search.trim();
        if(!search){
            noTerm=true;
            res.status(400).render('shows/searchshows',{title:"Show Finder",showSearchTerm:search,noTerm:noTerm,noResults:noResults});
            return;
        }
    }
    
    shows = await showData.getFiveShows(search);
    if(shows.length == 0 && noTerm == false){
        noResults = true;
    }
    try{
        if(noTerm){
            
        }
        res.render('shows/searchshows',{title:"Show Finder",showSearchTerm:search,shows:shows,noTerm:noTerm,noResults:noResults});
    } catch(e) {
        res.status(500).json({error: e});
    }
});

router.get('/show/:id', async (req, res) => {
    id= req.params.id;
    show = await showData.getShow(id);
    if(!show){
        res.status(404).render('shows/error');
        return;
    }
    let name = "N/A";
    let img = "https://t3.ftcdn.net/jpg/04/34/72/82/360_F_434728286_OWQQvAFoXZLdGHlObozsolNeuSxhpr84.jpg";
    let lang = "N/A";
    let genres = ["N/A"];
    let rating = "N/A";
    let net = "N/A";
    let summary = "N/A";
    
    try{
        name = show["name"];  
        if(!name){
            name = "N/A"
        }
    } catch(e){}
    try{
        img = show["image"]["medium"];
        if(!img){
            img = "https://t3.ftcdn.net/jpg/04/34/72/82/360_F_434728286_OWQQvAFoXZLdGHlObozsolNeuSxhpr84.jpg";
        } 
    } catch(e){}
    try{
        lang = show["language"];
        if(!lang){
            lang = "N/A"
        }  
    } catch(e){}
    try{
        genres = show["genres"];
        if(genres = []){
            genres = ["N/A"]
        }  
    } catch(e){
    }
    try{
        rating= show["rating"]["average"];
        if(!rating){
            rating = "N/A"
        } 
    } catch(e){}
    try{
        net = show["network"]["name"];
        if(!net){
            net = "N/A"
        } 
    } catch(e){}
    try{
        summary = show["summary"];
        if(!summary){
            summary = "N/A"
        } 
    } catch(e){}
    //https://stackoverflow.com/questions/5002111/how-to-strip-html-tags-from-string-in-javascript
    summary = summary.replace(/<\/?[^>]+(>|$)/g, "");
    try{
        res.render('shows/singleshow',{title:name,name:name,img:img,lang:lang,genres:genres,rating:rating,net:net,summary:summary});
    } catch{
        res.status(500).json({error: e});
    }
    
});


module.exports = router;