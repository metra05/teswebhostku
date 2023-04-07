/* Code Written by Rishi Tiwari
 *  Website:- https://tricksumo.com
*/

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

// Update HOST URL here

#define HOST "wangibumi.000webhost.com"          // Enter HOST URL without "http:// "  and "/" at the end of URL

#define WIFI_SSID "orangepi2"            // WIFI SSID here                                   
#define WIFI_PASSWORD "orangepi"        // WIFI password here

// Declare global variables which will be uploaded to server

int val = 1;
int val2 = 99;
int val3 = 55;

String sendval, sendval2, sendval3, postData;


void setup() {

     
Serial.begin(115200); 
Serial.println("Communication Started \n\n");  
delay(1000);

pinMode(LED_BUILTIN, OUTPUT);     // initialize built in led on the board

WiFi.mode(WIFI_STA);           
WiFi.begin(WIFI_SSID, WIFI_PASSWORD);                                     //try to connect with wifi
Serial.print("Connecting to ");
Serial.print(WIFI_SSID);
while (WiFi.status() != WL_CONNECTED) 
{ Serial.print(".");
    delay(500); }

Serial.println();
Serial.print("Connected to ");
Serial.println(WIFI_SSID);
Serial.print("IP Address is : ");
Serial.println(WiFi.localIP());    //print local IP address

delay(300);
}



void loop() { 

HTTPClient http;    // http object of clas HTTPClient
WiFiClient client;

// Convert integer variables to string
sendval = String(val);  
sendval2 = String(val2);
sendval3 = String(val3);
 
//postData = "sendval=" + sendval + "&sendval2=" + sendval2;
postData = "sendval=" + sendval + "sendval2=" + sendval2 + "sendval3=" +sendval3;


// We can post values to PHP files as  example.com/dbwrite.php?name1=val1&name2=val2&name3=val3
// Hence created variable postDAta and stored our variables in it in desired format
// For more detials, refer:- https://www.tutorialspoint.com/php/php_get_post.htm

// Update Host URL here:-  
  
http.begin(client,"http://wangibumi.000webhost.com/dbwrite.php");              // Connect to host where MySQL databse is hosted
http.addHeader("Content-Type", "application/x-www-form-urlencoded");            //Specify content-type header

 
int httpCode = http.POST(postData);   // Send POST request to php file and store server response code in variable named httpCode
//Serial.println("Values are, sendval = " + sendval + " and sendval2 = "+sendval2 );
Serial.println("Values are, sendval = " + sendval + " and sendval2 = " + sendval2 + " and sendval3 = " + sendval3);


// if connection eatablished then do this
if (httpCode == 200) { Serial.println("Values uploaded successfully."); Serial.println(httpCode); 
String webpage = http.getString();    // Get html webpage output and store it in a string
Serial.println(webpage + "\n"); 
}

// if failed to connect then return and restart

else { 
  Serial.println(httpCode); 
  Serial.println("Failed to upload values. \n"); 
  http.end(); 
  delay(300);
  return; }


delay(3000); 
digitalWrite(LED_BUILTIN, LOW);
delay(3000);
digitalWrite(LED_BUILTIN, HIGH);

val+=1; val2+=2; val3+=3;// Incrementing value of variables


}
