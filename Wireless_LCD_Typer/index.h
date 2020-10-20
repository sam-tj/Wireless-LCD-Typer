//const char MAIN_page[] PROGMEM = R"=====(
//<!DOCTYPE html>
//<HTML>
//  <HEAD>
//      <TITLE>My first web page</TITLE>
//  </HEAD>
//<BODY>
//  <CENTER>
//      <B>Hello World.... </B>
//  </CENTER> 
//</BODY>
//</HTML>
//)=====";


const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML>
<html>
  <head>
    <title> Wireless LCD Input Form </title>    
    <meta name="viewport" content="width=device-width, initial-scale=1">  
  </head>
  <body>
  Text auto updates in 2 seconds.<br><br>
  Message deletes after 10 seonds<br><br>  
  <form id="myForm" action="/get">
    Your Text: <input type="text" name="val" autofocus autocomplete="off" maxlength="31" onkeyup="myFunction()">
    <!-- <input id="fname" type="button" onclick="myFunction()" value="Submit"> -->
  <input type="button" onclick="myFunction()" value="Submit">
  </form>
  <br>  
  <script> 
  function myFunction() {          
  try{
  console.log('clear timeout');  
  clearTimeout(myVar);
  }
  catch(e){}
  myVar = setTimeout(
  function(){
  console.log('in timeout');
  document.getElementById("myForm").submit();  
  done=true;  
  }
  ,2000); 
  console.log('got here');  
  }
  </script> 
  </body>
</html>
)rawliteral";
