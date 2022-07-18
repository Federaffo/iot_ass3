$(document).ready(function(){
  
  $("input[type=submit]").click(function(){
    $.ajax({
      //url: http://localhost:porta/ pythone route
      url: "data.php",
      method: "GET" ,
      contentType:"application/json",
    })
      .done(function( data ) {
        console.log(data);
        $("#lux").html(data.lux+" lux");
        $("#temp").html(data.temp+" °C");
        $("#l1").html(data.l1=="true"?"ON":"OFF");
        $("#l2").html(data.l2=="true"?"ON":"OFF");
        $("#l3").html("(Intensity="+data.l3+")");
        $("#l4").html("(Intensity="+data.l4+")");
        $("#ir").html(data.ir=="true"?"ON":"OFF");
        $("#state").html(data.state);
        if(data.state=="MANUAL"){
          $("#state").addClass("border-success");
        }

      });
  });

    
});