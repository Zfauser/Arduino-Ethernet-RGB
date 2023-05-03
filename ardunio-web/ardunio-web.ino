#include <SPI.h>
#include <Ethernet.h>

const int PIN_RED = 3;
const int PIN_GREEN = 5;
const int PIN_BLUE = 6;
int red = 0;
int green = 0;
int blue = 0;
byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED}; // physical mac address
byte ip[] = {10, 190, 160, 200};                   // change with desired ip address
byte gateway[] = {10, 190, 160, 1};                // internet access via router
byte subnet[] = {255, 255, 240, 0};                // subnet mask
EthernetServer server(80);                         // server port
String readString;

void setup()
{
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial)
  {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  pinMode(PIN_RED, OUTPUT);
  pinMode(PIN_GREEN, OUTPUT);
  pinMode(PIN_BLUE, OUTPUT);
  setColor(0, 0, 0);
  // start the Ethernet connection and the server:
  Ethernet.begin(mac, ip, gateway, subnet);
  server.begin();
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());
}

void loop()
{
  // Create a client connection
  EthernetClient client = server.available();
  if (client)
  {
    while (client.connected())
    {
      if (client.available())
      {
        char c = client.read();

        // read char by char HTTP request
        if (readString.length() < 100)
        {
          // store characters to string
          readString += c;
          // Serial.print(c);
        }

        // if HTTP request has ended
        if (c == '\n')
        {
          Serial.println(readString); // print to serial monitor for debuging

          client.println("HTTP/1.1 200 OK"); // send new page
          client.println("Content-Type: text/html");
          client.println();
          client.println("<HTML>");
          client.println("<HEAD>");
          client.println("<meta name='apple-mobile-web-app-capable' content='yes' />");
          client.println("<meta name='apple-mobile-web-app-status-bar-style' content='black-translucent' />");
          client.println("<link rel='stylesheet' type='text/css' href='https://zfauser.github.io/Arduino-Ethernet-RGB/website/index.css' />");
          client.println("<title>ArduinoRGB</title>");
          client.println("</HEAD>");
          client.println("<BODY>");
          client.println("<div class='container'>");
          client.println("<H1>ArduinoRGB</H1>");
          client.println("<hr>");
          client.println("<h3 id='powerValue'>LED: off</h3>");
          client.println("<label class='switch'>");
          client.println("<input type='checkbox' id='powerSlider'/>");
          client.println("<span class='slider round'></span>");
          client.println("</label>");
          client.println("<h3 id='redValue'>Red: 0</h3>");
          client.println("<input type='range' onchange='redChange()' min='0' max='255' value='0' class='sliderRed' id='redSlider' />");
          client.println("<h3 id='greenValue'>Green: 0</h3>");
          client.println("<input type='range' onchange='greenChange()' min='0' max='255' value='0' class='sliderGreen' id='greenSlider' />");
          client.println("<h3 id='blueValue'>Blue: 0</h3>");
          // The colors recieve their requested values in the following format /?color=value so for example /?red=255
          client.println("<input type='range' onchange='blueChange()' min='0' max='255' value='0' class='sliderBlue' id='blueSlider' />");
          client.println("<br>");
          client.println("<button onclick='RESET()'>RESET</button>");
          client.println("</div>");
          client.println("<script src='https://zfauser.github.io/Arduino-Ethernet-RGB/website/index.js'></script>");
          client.println("</BODY>");
          client.println("</HTML>");
          delay(1);
          // stopping client
          client.stop();
          // controls the Arduino if you press the buttons
          if (readString.indexOf("?button1on") > 0)
          {
            setColor(255, 255, 255);
          }
          if (readString.indexOf("?button1off") > 0)
          {
            setColor(0, 0, 0);
          }
          if (readString.indexOf("?red=") > 0)
          {
            int red = readString.substring(readString.indexOf("?red=") + 5, readString.indexOf("HTTP")).toInt();
            setColor(red, green, blue);
          }
          if (readString.indexOf("?green=") > 0)
          {
            int green = readString.substring(readString.indexOf("?green=") + 7, readString.indexOf("HTTP")).toInt();
            setColor(red, green, blue);
          }
          if (readString.indexOf("?blue=") > 0)
          {
            int blue = readString.substring(readString.indexOf("?blue=") + 6, readString.indexOf("HTTP")).toInt();
            setColor(red, green, blue);
          }
          if (readString.indexOf("?reset") > 0)
          {
            setColor(0, 0, 0);
          }
          // TODO: Add support for different colors
          // clearing string for next read
          readString = "";
        }
      }
    }
  }
}

void setColor(int R, int G, int B)
{
  analogWrite(PIN_RED, R);
  analogWrite(PIN_GREEN, G);
  analogWrite(PIN_BLUE, B);
}
