$(document).ready(function(){
  
  $("input[type=submit]").click(function(){
    $.ajax({
      url: "data.php",
      method: "POST" ,
      data: {action: 'test'},
      dataType:'JSON', 
    })
      .done(function( data ) {
        alert(data);
        $("#lux").html(data.lux);
        $("#temp").html(data.temp);
        $("#l1").html(data.l1=="true"?"accesa":"spenta");
        $("#l3").html(data.l3);
      });
  });

    
});