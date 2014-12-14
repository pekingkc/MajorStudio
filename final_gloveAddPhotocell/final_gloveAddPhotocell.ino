int note = 0;   
int hitavg = 0;
int dtcolor = 0;
int led = 12;
char pinAssignments[] ={'A0', 'A1', 'A2', 'A3', 'A4', 'A5'};
byte PadNote[] = {58, 57, 55, 53, 50}; 

void setup() 
{
  Serial.begin(57600);                                       // Default speed of the Serial to MIDI Converter serial port
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(A4, INPUT);
  pinMode(A5, INPUT);
  pinMode(led, OUTPUT);
}

void loop(){
  digitalWrite(led, HIGH);
  for(int pin=0; pin < 5; pin++){ 
    
    hitavg = analogRead(pin);
//    Serial.println(hitavg);
    
    dtcolor = analogRead(A5);
    Serial.println(dtcolor);
    
    //sense the color
    if(dtcolor < 50){
      if(hitavg > 25){
        MIDI_TX(144,PadNote[pin] -5,127);                                  // NOTE ON
        delay(100);
        MIDI_TX(128,PadNote[pin]-5 ,127);                                  // NOTE OFF
        delay(100);
      } 
    }
    
    if(dtcolor > 50){
      if(hitavg > 25){
        MIDI_TX(144,PadNote[pin], 127);                                  // NOTE ON
        delay(100);
        MIDI_TX(128,PadNote[pin], 127);                                  // NOTE OFF
        delay(100);
      } 
    }
    
  } 
}
  
void MIDI_TX(unsigned char MESSAGE, unsigned char PITCH, unsigned char VELOCITY) 
{
  Serial.write(MESSAGE);
  Serial.write(PITCH);
  Serial.write(VELOCITY);
}

