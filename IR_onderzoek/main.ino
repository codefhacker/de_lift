void setup() {
  pinMode(12, INPUT);
  Serial.begin(9600);

}
bool old_IR_state;
bool current_IR_state;
void loop() {
  current_IR_state = digitalRead(12);
  
  if (current_IR_state != old_IR_state){
    Serial.println(current_IR_state);
    current_IR_state== old_IR_state;
  }
  else{
    Serial.println("0");
  }
