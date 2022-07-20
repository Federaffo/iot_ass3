$(document).ready(function(){
  
  $("input[type=submit]").click(function(){
    
    $.ajax({
      //url: http://localhost:porta/ pythone route
      url: "http://192.168.1.106/dashboard",
      method: "GET" ,
      contentType:"application/json",
    })
      .done(function( data ) {
        console.log(data);
        $("#lux").html(data.lux);
        $("#temp").html(data.tmp);
        $("#l1").html(data.l1=="true"?"ON":"OFF");
        $("#l2").html(data.l2=="true"?"ON":"OFF");
        $("#l3").html("(Intensity="+data.l3+")");
        $("#l4").html("(Intensity="+data.l4+")");
        $("#ir").html(data.i=="true"?"ACTIVATED":"PAUSED");
        switch(data.state){
          case 0:
            $("#state").html("AUTO").addClass("border-success");
            break;
            case 1:
            $("#state").html("MANUAL").addClass("border-warning");
            break;
            case 2:
            $("#state").html("ALARM").addClass("border-danger");
            break;
        }

      });
  });

  $.ajax({
    //url: http://localhost:porta/ pythone route
    url: "http://192.168.1.106/dashboard",
    method: "GET" ,
    contentType:"application/json",
  })
    .done(function( data ) {
      console.log(data);
      $("#lux").html(data.lux);
      $("#temp").html(data.tmp);
      $("#l1").html(data.l1==true?"ON":"OFF");
      $("#l2").html(data.l2==true?"ON":"OFF");
      $("#l3").html("(Intensity="+data.l3+")");
      $("#l4").html("(Intensity="+data.l4+")");
      $("#ir").html(data.i==true?"ACTIVATED":"PAUSED");
      switch(data.state){
        case 0:
          $("#state").html("AUTO").addClass("border-success");
          break;
          case 1:
          $("#state").html("MANUAL").addClass("border-warning");
          break;
          case 2:
          $("#state").html("ALARM").addClass("border-danger");
          break;
      }

    });
});