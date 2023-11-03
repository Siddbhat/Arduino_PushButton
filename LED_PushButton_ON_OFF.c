int led = 13;
int push_button = 2;
int buttonstate;

void setup()
{
  Serial.begin(115200);
  pinMode(led, OUTPUT);
  pinMode(push_button,INPUT);
}

void loop() 
{
int state=digitalRead(push_button);
if(state==HIGH)
{
  digitalWrite(led, HIGH);
  Serial.println("LOGIC 1");
  delay(50);
}
else
{
  digitalWrite(led, LOW);
  Serial.println("Logic 0");
  delay(200);
}
}
