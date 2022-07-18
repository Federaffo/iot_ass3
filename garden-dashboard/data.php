<?php
    header('Content-Type: application/json');
    $out=array("lux"=>"54","temp"=>"34","l1"=>"true","l2"=>"false","l3"=>"2","l4"=>"5","ir"=>"true","state"=>"MANUAL");
    echo json_encode($out);

?>