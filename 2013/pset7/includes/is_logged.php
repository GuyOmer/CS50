<?php

    function islogged() 
    {
        if(session_status() === PHP_SESSION_ACTIVE)
            return true;
        
        redirect("login.php");
    }

?>
