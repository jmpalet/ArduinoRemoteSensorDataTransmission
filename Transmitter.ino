#include <VirtualWire.h>                        // |  RF transmitter library
void setup(){                                   // |  
  Serial.begin(9600);                           // |  
  pinMode(13,OUTPUT);                           // |  Port 13, LED to check data transmission
  pinMode(1,INPUT);                             // |  Analog input 1, TMP36 analog data pin
  vw_set_ptt_inverted(true);                    // |  
  vw_set_tx_pin(12);                            // |  Emitter digital data pin
  vw_setup(4000);                               // |  Data transfer velocity (bps)
}                                               // |  
void loop(){                                    // |  
  int Temp=(analogRead(1)-105)*27/(156-105);    // |  Zero adjustment (105 --> 0ºC; 156 --> 27ºC)
  char Signal[24];                              // |  Variable which content will be sent through the antenna
  sprintf(Signal,"%i",Temp);                    // |  Variable filling
  vw_send((uint8_t *)Signal,strlen(Signal));    // |  Variable content sending
  Serial.print("Temperature: ");                // |  Comprovation of data sent visualizing_
  Serial.print(Signal);                         // |  _it by the Serial console
  Serial.print(" C");                           // |  
  Serial.println();                             // |  
  vw_wait_tx();                                 // |  Pause for letting the emitter complete the transmission
  digitalWrite(13,1);                           // |  Turn on LED on port 13 for checking data transmission
  delay(10);                                    // |  
}                                               // |  
