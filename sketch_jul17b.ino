#include <DHT.h>     // including the library of DHT11 temperature and humidity sensor
#define DHTTYPE DHT11   // DHT 11
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
DHT dht(D5, DHT11);
#define HOST "192.168.10.9"          // Enter HOST URL without "http:// "  and "/" at the end of URL

#define WIFI_SSID "Anonymous"            // WIFI SSID here                                   
#define WIFI_PASSWORD "F@h@d@likh@n2000"
#include <WiFiClient.h>

WiFiClient wifiClient;

int val;
int val2;

String sendval, sendval2, postData;

void setup(void)
{ Serial.begin(115200); 
Serial.println("Communication Started \n\n");  
delay(1000);
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

delay(30);

  dht.begin();
  

}
void loop() {
  


    float h = dht.readHumidity();
    float t = dht.readTemperature();         
    
  delay(800);
  HTTPClient http;    // http object of clas HTTPClient


// Convert integer variables to string
sendval = String(h);  
sendval2 = String(t);   

 
postData = "sendval=" + sendval + "&sendval2=" + sendval2;

http.begin(wifiClient,"http://192.168.10.9/sensordata/dbwrite.php");              // Connect to host where MySQL databse is hosted
http.addHeader("Content-Type", "application/x-www-form-urlencoded");            //Specify content-type header

  
 
int httpCode = http.POST(postData);   // Send POST request to php file and store server response code in variable named httpCode
Serial.println("Values are, sendval = " + sendval + " and sendval2 = "+sendval2 );


// if connection eatablished then do this
if (httpCode == 200) { 
  Serial.println("Values uploaded successfully."); 
  Serial.println(httpCode); 
  String webpage = http.getString();    // Get html webpage output and store it in a string
  Serial.println(webpage + "\n"); 
}

// if failed to connect then return and restart

else { 
  Serial.println(httpCode); 
  Serial.println("Failed to upload values. \n"); 
  http.end(); 
  return; }



}
