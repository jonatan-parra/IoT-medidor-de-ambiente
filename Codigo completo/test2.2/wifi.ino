//#include <ESP8266HTTPClient.h>
//#include <ESP8266WiFi.h>
//
//const char CR = 13;
//boolean stringComplete;
//String inputString;
//
//const byte numChars = 100;
//char receivedChars[numChars];   // an array to store the received data
//
//boolean newData = false;
//
//#define LED 0 //Define blinking LED pin
// 
//void setup() {
//
//  serialEvent();
//  stringComplete = false;
//  inputString = "";
//  Serial.begin(115200); //Serial connection
//  WiFi.begin("Familia Viveros", "nmjy481012"); //WiFi connection
// q
//  pinMode(LED_BUILTIN, OUTPUT);
//  digitalWrite(LED_BUILTIN, HIGH);
//
//  while (WiFi.status() != WL_CONNECTED) {  //Wait for the WiFI connection completion
// 
//    delay(2000);
//    Serial.println("Waiting for connection");
//  }
//}
// 
//void loop() {
//
//  recvWithStartEndMarkers();
//
//  if(WiFi.status()== WL_CONNECTED){   //Check WiFi connection status
// 
//   HTTPClient http;    //Declare object of class HTTPClient
// 
//   http.begin("http://iot.bytersoft.webfactional.com/api/measures");      //Specify request destination
//   http.addHeader("Content-Type", "application/json");  //Specify content-type header
//   http.addHeader("Accept", "application/json");
//   http.addHeader("Authorization", "Bearer eyJ0eXAiOiJKV1QiLCJhbGciOiJSUzI1NiIsImp0aSI6IjgwMGVlMzFmYTMyNjUyMDRhNTAwZTlhZGE0ZDI0NTRiN2E3ZWU1YjY5YjY5NzJiODI2Yzc3Y2UyMDFmYWU5Zjc5OGI1NTg2YThmM2ZhZjVmIn0.eyJhdWQiOiI0IiwianRpIjoiODAwZWUzMWZhMzI2NTIwNGE1MDBlOWFkYTRkMjQ1NGI3YTdlZTViNjliNjk3MmI4MjZjNzdjZTIwMWZhZTlmNzk4YjU1ODZhOGYzZmFmNWYiLCJpYXQiOjE1NTE2NjI2NTUsIm5iZiI6MTU1MTY2MjY1NSwiZXhwIjoxNTgzMjg1MDU1LCJzdWIiOiIyIiwic2NvcGVzIjpbXX0.cD99Oou3cYdrnCMG3e7lOtPhlcMpjJ9GPyit-rZ08iu1AEDOa_Bge8i9PpeO7lX_qxyorawg3wmhJEci3v-BDhG5ddaTnV9iadk122GIltTUyaNehuVMweljYm73eEnrMwVsRBWI5Tc0ipEps5rlh59CEmUnlMBfwmkW4qdsR-7oZFmQzvBkqrtD5j24NYKikzmAybl5y1ZIkIK3uTYyL4sYHF7q_Jgh6Paks58bzrCmb5TgV358zqCH1uPT0nt6mj4dsyHInqdmI8YMQjahaZdlq3axZmnpb3119FTvCc3PKxrEI6rV-Ux_fq3KG_DJxNHewyht11dpDvfUtoh9kEiB25kjSAmSQg3jNLle_H5k9B0VqWVw4cIqJC0VS6_Df4AOcIkVZ81mwaF7w-Pb4y46qakCv4D2xaaY7E_FQUuHdOWaH82gMSR8bxnQHW0y0OH2iA8oo_A02ml-_7sDwh6jqD5hI8a0snTfRJmd7xIOxi9RYgVrFMwkBg5TM9SeIb8N74t2V53A_9J9kNQnpsS9RTj7d3ftiO880RJJSUfqv2xWWnYrbyMiD2cn6RbNXDnoHLCTQINu97rx46QGU7O_096k1anLlsqzaev9lIot54VvjUAo5iZjIPPgf8sUOpYmB9B4GKV4ruSeRzDH1rDYfQ4LUHQtYnzkWxFtI44");  //Specify content-type header
//
////   Serial.print("INPUT: " + inputString);
//   // Mediocre verification for JSON
//   if(newData){
//      int httpCode = http.POST(inputString);   //Send the request
//      String payload = http.getString();                  //Get the response payload
//      Serial.println(httpCode);   //Print HTTP return code
//      Serial.println(payload); 
//      newData = false;
//   }
// 
//   http.end();  //Close connection
// 
// }else{
// 
//    Serial.println("Error in WiFi connection");   
// 
// }
//
//  digitalWrite(LED_BUILTIN, HIGH);
//}
//
//void recvWithEndMarker() {
//    static byte ndx = 0;
//    char endMarker = '\n';
//    char rc;
//    
//    while (Serial.available() > 0 && newData == false) {
//        rc = Serial.read();
//
//        if (rc != endMarker) {
//            receivedChars[ndx] = rc;
//            ndx++;
//            if (ndx >= numChars) {
//                ndx = numChars - 1;
//            }
//        }
//        else {
//            receivedChars[ndx] = '\0'; // terminate the string
//            inputString = String(receivedChars);
//            ndx = 0;
//            newData = true;
//        }
//    }
//}
//
//void recvWithStartEndMarkers() {
//    static boolean recvInProgress = false;
//    static byte ndx = 0;
//    char startMarker = '<';
//    char endMarker = '>';
//    char rc;
// 
//    while (Serial.available() > 0 && newData == false) {
//      digitalWrite(LED_BUILTIN, LOW);
//        rc = Serial.read();
//
//        if (recvInProgress == true) {
//            if (rc != endMarker) {
//                receivedChars[ndx] = rc;
//                ndx++;
//                if (ndx >= numChars) {
//                    ndx = numChars - 1;
//                }
//            }
//            else {
//                receivedChars[ndx] = '\0'; // terminate the string
//                inputString = String(receivedChars);
//                Serial.print(inputString);
//                recvInProgress = false;
//                ndx = 0;
//                newData = true;
//            }
//        }
//
//        else if (rc == startMarker) {
//            recvInProgress = true;
//        }
//    }
//}
//
//void serialEvent() {
////  Serial.println("CALLED");
//  while (Serial.available()) {
//    Serial.println(Serial.available());
//    Serial.print("YASSSS");
//    char inChar = (char)Serial.read();
//    Serial.print(" ");
//    Serial.println(inChar);
//    if(inChar == '\n') {
//      inputString = "";
//    }
//    else if(inChar != CR) inputString += inChar;
//    if (inChar == CR) stringComplete = true;
//  }
////  Serial.println(inputString);
//}
