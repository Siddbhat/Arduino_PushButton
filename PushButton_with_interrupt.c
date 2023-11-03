int led = 13;
int push_button = 12;
int buttonstate = false;
void handleInterrupt() 
{
  buttonstate = true;
}
void setup() 
{
  Serial.begin(115200);
  pinMode(led, OUTPUT);
  pinMode(push_button, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(push_button), handleInterrupt, RISING);
}
void loop() 
{
  if (buttonstate) 
  {
    digitalWrite(led, HIGH);
    Serial.println("External event has occurred");
    Serial.println("Logic 1");
    delay(1000);
    buttonstate = false;  // Reset button state to false
  } 
  else     
   {
    digitalWrite(led, LOW);
    Serial.println("Logic 0");
    delay(100);
   } 
}
