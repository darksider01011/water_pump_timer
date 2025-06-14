unsigned long previousMillis = 0;
const long interval = 0.5 * 60 * 1000;
bool allow_timer = true;


const int yellow_led = D1;
const int on_button = D6;
const int red_led = D5;
const int off_button = D7;
const int relay = D3;
const int green_led = D4;


void setup() {
  Serial.begin(9600);
  pinMode(on_button, INPUT_PULLUP);
  pinMode(off_button, INPUT_PULLUP);
  pinMode(relay, OUTPUT);
  pinMode(red_led, OUTPUT);
  pinMode(yellow_led, OUTPUT);
  pinMode(green_led, OUTPUT);
}

// timer function
void timer() {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    
    delay(100);
    analogWrite(yellow_led, 0);
    analogWrite(red_led, 0);
    digitalWrite(relay, HIGH);
    analogWrite(green_led, 10);
    analogWrite(red_led, 0);
    delay(5000);
    digitalWrite(relay, LOW);
    analogWrite(green_led, 0);
    analogWrite(yellow_led, 10);
  }

}

void loop() {
  int off_state = digitalRead(on_button);
  int on_state = digitalRead(off_button);
  
  if (allow_timer == true) {
  timer();
  }
  
  if (on_state == LOW) {
    delay(100);
    digitalWrite(relay, HIGH);
    analogWrite(red_led, 10);
    analogWrite(yellow_led, 0);
    allow_timer = false;
  }
  
  if (off_state == LOW) {
    analogWrite(red_led, 0);
    digitalWrite(relay, LOW);
    analogWrite(yellow_led, 10);
    delay(100);
    allow_timer = true; 
  }
 
}
