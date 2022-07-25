$(document).ready(function(){
  
  dataRequest();
  
  $("input[type=submit]").click(function(){
    dataRequest();
  });

  function dataRequest(){
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
        $("#l1").html(data.l1?"ON":"OFF");
        $("#l2").html(data.l2?"ON":"OFF");
        $("#l3").html("(Intensity="+data.l3+")");
        $("#l4").html("(Intensity="+data.l4+")");
        $("#ir").html(data.i?"ACTIVATED":"PAUSED");
        $("#is").html(data.is);
        switch(data.state){
          case 0:
            $("#state").html("AUTO").addClass("border-success")
            .removeClass("border-warning").removeClass("border-danger");
            break;
            case 1:
            $("#state").html("MANUAL").addClass("border-warning")
            .removeClass("border-success").removeClass("border-danger");
            break;
            case 2:
            $("#state").html("ALARM").addClass("border-danger")
            .removeClass("border-warning").removeClass("border-success");
            break;
        }

      });
  }

});