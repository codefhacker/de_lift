void setup() {
  pinMode(12, INPUT);
  Serial.begin(9600);

}
bool old_magnet_state;
bool current_magnet_state;
void loop() {
  current_magnet_state = digitalRead(12);
  
  if (current_magnet_state != old_magnet_state){
    Serial.println(current_magnet_state);
    current_magnet_state == old_magnet_state;
  }
  else{
    Serial.println("0");
  }
  

  

}
