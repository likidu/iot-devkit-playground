#include <Arduino.h>
#include <OLEDDisplay.h>
#include <AZ3166WiFi.h>

// Indicate whether WiFi is ready
static bool hasWifi = false;

int lastButtonAState;

static void startWiFi() {
  Screen.print(0, "Connecting...");
  
  if (WiFi.begin() == WL_CONNECTED) {
    IPAddress ip = WiFi.localIP();
    Screen.print(0, ip.get_address());
    hasWifi = true;
  } else {
    hasWifi = false;
    Screen.print(0, "No Wi-Fi\r\n ");
  }
}

static void record() {
  if (digitalRead(USER_BUTTON_A) == LOW && lastButtonAState == HIGH) {
    Screen.clean();
    Screen.print(0, "Recording...");
  }
}

void setup() {
  // Set serial baudrate
  Serial.begin(115200);

  // Init the button pin as a input
  pinMode(USER_BUTTON_A, INPUT);
  lastButtonAState = digitalRead(USER_BUTTON_A);

  // Init screen
  Screen.init();

  // Init WiFi
  startWiFi();
  if (!hasWifi) {
    return;
  }

  // Init audio
}

void loop() {
  if (hasWifi) {
    record();
  }
}