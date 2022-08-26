(function ($) {
  
    var showList =  $('#showList');
    var form = $('#searchForm');
    var searchTermInput = $('#search_term');
    var showDiv = $('#show');
    var searcherror = $('#searcherror');
    var homeLink = $('#homeLink');
      var requestConfig = {
        method: 'GET',
        url: 'http://api.tvmaze.com/shows'
      };

      $.ajax(requestConfig).then(function (response) {
        var List = $(response);
        for(i of List){
            const li = `<li> <a class = "showlink" href = "${i._links.self.href}"> ${i.name} </a>  </li>`;
            showList.append(li);
        }
        
        showList.show();
        showDiv.hide();
        homeLink.hide();
      });

      form.submit(function (event){
        event.preventDefault();
        searchTerm = searchTermInput.val();
        searchTerm = searchTerm.trim();
        if(!searchTerm){
          searcherror.show();
        } else{
          searcherror.hide();
        }
        showList.html("");
        
        var requestConfig = {
          method: 'GET',
          url: 'http://api.tvmaze.com/search/shows?q=' + searchTerm
        };
  
        $.ajax(requestConfig).then(function (response) {
          var List = $(response);
          for(i of List){
              const li = `<li> <a class = "showlink" href = "${i.show._links.self.href}"> ${i.show.name} </a>  </li>`;
              showList.append(li);
          }
          showList.show();
          showDiv.hide();
          homeLink.show();
        });
      });

      
       $("#showList").on('click', 'a.showlink', function (event) {
          event.preventDefault();
          showDiv.empty();
          var currlink = event.target.getAttribute("href");
    
          var requestConfig = {
            headers: {
              "Content-Type": "application/x-www-form-urlencoded"
            },
            method: 'GET',
            url: currlink
          };
    
          $.ajax(requestConfig).then(function (responseMessage) {
            var newElement = responseMessage;
            let h1 = '';
            let img = ''; 
            if(!newElement.name){
              h1 = `<h1> N/A </h1>`;
            }
            else{
              h1 = `<h1> ${newElement.name} </h1>`; 
            }
            if(!newElement.image){
              img = `<img alt = "Image of Show" src = "public/images/no_image.jpeg" >  </img>`;
            }
            else{
              img = `<img alt = "Image of Show" src = "${newElement.image.medium}" >  </img>`; 
            }
            showDiv.append(h1);
            showDiv.append(img);

            let dl = '<dl id="deflist" > </dl>';
            showDiv.append(dl);

            let lang = "";
            let langt = `<dt> Language </dt>`;
            if(!newElement.language){
              lang = `<dd> N/A </dd>`;
            }
            else{
              lang = `<dd> ${newElement.language} </dd>`;
            }
            $("#deflist").append(langt);
            $("#deflist").append(lang);

            let genres = "";
            let genrest = `<dt> Genres </dt>`
            if(!newElement.genres){
              genres = `<dd> N/A </dd>`;
            }
            else{
              genres = `<dd> <ul id="genres"> </ul> </dd>`
            }
            $("#deflist").append(genrest);
            $("#deflist").append(genres);
            if(newElement.genres){
              for(i of newElement.genres){
                const li = `<li> ${i} </li>`;
                $("#genres").append(li);
              }
            }
            
            let rating = "";
            let ratingt = `<dt> Rating </dt>`;
            $("#deflist").append(ratingt);
            if(!newElement.rating?.average){
              rating = `<dd> N/A </dd>`;
            }
            else{
              rating = `<dd> ${newElement.rating.average} </dd>`;
            }
            $("#deflist").append(rating);

            let network = "";
            let networkt = `<dt> Network </dt>`;
            $("#deflist").append(networkt);
            if(!newElement.network?.name){
              network = `<dd> N/A </dd>`;
            }
            else{
              network = `<dd> ${newElement.network.name} </dd>`;
            }
            $("#deflist").append(network);


            let summary = "";
            let summaryt = `<dt> Summary </dt>`;
            $("#deflist").append(summaryt);
            if(!newElement.summary){
              summary = `<dd> N/A </dd>`;
            }
            else{
              summary = `<dd> ${newElement.summary} </dd>`;
            }
            $("#deflist").append(summary);


            showList.hide();
            showDiv.show();
            homeLink.show();
          });
        });
     



})(window.jQuery);