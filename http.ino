#include <ArduinoJson.h>

enum {
  NONE = 0, INDEX, XML, JSON
};

void modeHttp(void) {
  WiFiClient client = server.available(); // listen for incoming clients
  int pos, page = 0;

  if (client) { // if you get a client,
    // Serial.println("New Client.");          // print a message out the serial port
    String currentLine = ""; // make a String to hold incoming data from the client
    while (client.connected()) { // loop while the client's connected
      if (client.available()) { // if there's bytes to read from the client,
        char c = client.read(); // read a byte, then
        // Serial.write(c);                    // print it out the serial monitor
        if (c == '\n') { // if the byte is a newline character

          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {

            if (page == INDEX) {
              // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
              // and a content-type so the client knows what's coming, then a blank line:
              client.println("HTTP/1.1 200 OK");
              client.println("Content-type: text/html");
              client.println();
              // the content of the HTTP response follows the header:

              client.println("<!DOCTYPE HTML><html><head><meta name='viewport' content='width=device-width, initial-scale=1.0'><title>ESP32LR88</title></head><body>");
              client.println("<p style='text-align:center'><b>ESP32LR88</b> <br></p>");
              client.println("<style>button{width:44%;height:35px;margin:5px;}</style>");

              char buffer[64];
              for (int i = 1; i <= 8; i++) {
                sprintf(buffer, "<button id='Rly%d' onclick='setRly(%d)'>Relay %d</button>", i, i, i);
                client.println(buffer);
              }

              client.println("<br><br><div> Inputs 1");
              for (int i = 1; i <= 8; i++) {
                sprintf(buffer, "<input type='radio' id='Inp%d'>", i);
                client.println(buffer);
              }
              client.println("8 </div>");

              client.println("<script>");
              client.println("var xhttp = new XMLHttpRequest();");
              client.println("var xmlDoc;");
              client.println("var Rly=0;");
              client.println("var Working=50;");
              client.println("setInterval(toggleRly, 10);");
              client.println("xhttp.onreadystatechange = function() {");
              client.println("    if (this.readyState == 4 && this.status == 200) {");
              client.println("        myFunction(this);");
              client.println("    }");
              client.println("};");

              client.println("function setRly(num) {");
              client.println("    Rly = num");
              client.println("};");

              client.println("function getValue(tag) {");
              client.println("    var x = xmlDoc.getElementsByTagName(tag)[0];");
              client.println("    var y = x.childNodes[0].nodeValue;");
              client.println("    return y;");
              client.println("};");
              client.println("function toggleRly() {");
              client.println("  var file = '';");
              client.println("  if(Working>0) { --Working; return; }");
              client.println("  switch(Rly) {");
              client.println("    case 0: file = \"status.xml\"; break;");
              client.println("    case 1: file = \"?Rly1=2\"; break;");
              client.println("    case 2: file = \"?Rly2=2\"; break;");
              client.println("    case 3: file = \"?Rly3=2\"; break;");
              client.println("    case 4: file = \"?Rly4=2\"; break;");
              client.println("    case 5: file = \"?Rly5=2\"; break;");
              client.println("    case 6: file = \"?Rly6=2\"; break;");
              client.println("    case 7: file = \"?Rly7=2\"; break;");
              client.println("    case 8: file = \"?Rly8=2\"; break;");
              client.println("  };");
              client.println("  Rly = 0; Working = 500;");
              client.println("  xhttp.open(\"GET\", file, true);");
              client.println("  xhttp.send();");
              client.println("}");
              client.println("function myFunction(xml) {");
              client.println("  xmlDoc = xml.responseXML;");
              client.println("  document.getElementById('Rly1').style.backgroundColor = (getValue('RLY1')=='on') ? 'rgba(255,0,0,0.2)' : 'rgba(0,0,255,0.2)';");
              client.println("  document.getElementById('Rly2').style.backgroundColor = (getValue('RLY2')=='on') ? 'rgba(255,0,0,0.2)' : 'rgba(0,0,255,0.2)';");
              client.println("  document.getElementById('Rly3').style.backgroundColor = (getValue('RLY3')=='on') ? 'rgba(255,0,0,0.2)' : 'rgba(0,0,255,0.2)';");
              client.println("  document.getElementById('Rly4').style.backgroundColor = (getValue('RLY4')=='on') ? 'rgba(255,0,0,0.2)' : 'rgba(0,0,255,0.2)';");
              client.println("  document.getElementById('Rly5').style.backgroundColor = (getValue('RLY5')=='on') ? 'rgba(255,0,0,0.2)' : 'rgba(0,0,255,0.2)';");
              client.println("  document.getElementById('Rly6').style.backgroundColor = (getValue('RLY6')=='on') ? 'rgba(255,0,0,0.2)' : 'rgba(0,0,255,0.2)';");
              client.println("  document.getElementById('Rly7').style.backgroundColor = (getValue('RLY7')=='on') ? 'rgba(255,0,0,0.2)' : 'rgba(0,0,255,0.2)';");
              client.println("  document.getElementById('Rly8').style.backgroundColor = (getValue('RLY8')=='on') ? 'rgba(255,0,0,0.2)' : 'rgba(0,0,255,0.2)';");
              client.println("  if(getValue('INP1')=='1') document.getElementById('Inp1').checked = true; else document.getElementById('Inp1').checked = false;");
              client.println("  if(getValue('INP2')=='1') document.getElementById('Inp2').checked = true; else document.getElementById('Inp2').checked = false;");
              client.println("  if(getValue('INP3')=='1') document.getElementById('Inp3').checked = true; else document.getElementById('Inp3').checked = false;");
              client.println("  if(getValue('INP4')=='1') document.getElementById('Inp4').checked = true; else document.getElementById('Inp4').checked = false;");
              client.println("  if(getValue('INP5')=='1') document.getElementById('Inp5').checked = true; else document.getElementById('Inp5').checked = false;");
              client.println("  if(getValue('INP6')=='1') document.getElementById('Inp6').checked = true; else document.getElementById('Inp6').checked = false;");
              client.println("  if(getValue('INP7')=='1') document.getElementById('Inp7').checked = true; else document.getElementById('Inp7').checked = false;");
              client.println("  if(getValue('INP8')=='1') document.getElementById('Inp8').checked = true; else document.getElementById('Inp8').checked = false;");
              client.println("  Working=0;");
              client.println("}");

              client.println("</script>");
              client.println("");

              client.print("</body></html>");

              // The HTTP response ends with another blank line:
              client.println();
            } else if (page == XML) {
              client.println("HTTP/1.1 200 OK");
              client.println("Content-type: application/xml");
              client.println();
              client.println("<?xml version=\"1.0\" encoding=\"UTF-8\"?>");
              client.println("<ESP32LR88DATA>");

              client.println("<RELAYS>");
              char relayLn[32];
              for (int i = 0; i < 8; i++) {
                sprintf(relayLn, "<RLY%d>%s</RLY%d>", i+1, (digitalRead(relayPins[i]) ? "on" : "off"), i+1);
                client.println(relayLn);
              }
              client.println("</RELAYS>");

              client.println("<INPUTS>");
              for (int i = 0; i < 8; i++) {
                sprintf(relayLn, "<INP%d>%d</INP%d>", i+1, digitalRead(inputPins[i]), i+1);
                client.println(relayLn);
              }
              client.println("</INPUTS>");

              client.println("</ESP32LR88DATA>");
              client.println();
            } else if (page == JSON) {
              client.println("HTTP/1.1 200 OK");
              client.println("Content-type: application/json");
              client.println();

              const int capacity = JSON_OBJECT_SIZE(2) + 2 * JSON_ARRAY_SIZE(8);
              StaticJsonDocument<capacity> doc;
              JsonArray relays = doc.createNestedArray("relays");
              JsonArray inputs = doc.createNestedArray("inputs");
              for (int i = 0; i < 8; i++) {
                relays.add(digitalRead(relayPins[i]));
                inputs.add(digitalRead(inputPins[i]));
              }

              String output = "";
              serializeJson(doc, output);
              client.println(output);
              client.println();
            } else {
              client.println("HTTP/1.1 404 Not Found");
              client.println("Content-type: text/html");
              client.println();
              client.println();
            }
            // break out of the while loop:
            break;
          } else { // check for a GET command
            if (currentLine.startsWith("GET / ")) page = INDEX;
            else if (currentLine.startsWith("GET /INDEX.HTM")) page = INDEX;
            else if (currentLine.startsWith("GET /STATUS.XML")) page = XML;
            else if (currentLine.startsWith("GET /STATUS.JSON")) page = JSON;
            else if (currentLine.startsWith("GET /?RLY")) page = XML;
            currentLine = "";
          }

        } else if (c != '\r') { // if you got anything else but a carriage return character,
          c = toupper(c);
          currentLine += c; // add it to the end of the currentLine
        }

        if (currentLine.length() == 12) {
          pos = currentLine.indexOf('?');
          if ((currentLine.substring(pos, pos + 4) == "?RLY") && (pos > 0)) {
            int rly = currentLine.charAt(pos + 4) - 0x30;
            int action = currentLine.charAt(pos + 6) - 0x30;

            switch (action) {
            case 0:
            case 1:
              digitalWrite(relayPins[rly], action);
              break;
            case 2:
              digitalWrite(relayPins[rly], !digitalRead(relayPins[rly]));
            }
          }
        }
      }
    }
    // close the connection:
    client.stop();
    // Serial.println("Client Disconnected.");
  }
}
