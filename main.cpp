const float cycle_hour = 6; //hours
const int water_time_minutes = 1; //minutes


const float minutes = cycle_hour * 60;
unsigned long previousMillis = 0;
const long interval = minutes * 60 * 1000;
const long water_time_millis = water_time_minutes * 60 * 1000;


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

void timer() {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    
    Serial.println("Task executed every 5 minutes");
    delay(100);
    analogWrite(yellow_led, 0);
    analogWrite(red_led, 0);
    digitalWrite(relay, HIGH);
    analogWrite(green_led, 10);
    analogWrite(red_led, 0);
    delay(water_time_millis);
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
