#include <VirtualWire.h>                // |  RF receiver library
int num[2];                             // |  
int num_int;                            // |  
int num_int_ant;                        // |  
int rang=3;                             // |  
void setup(){                           // |  
  Serial.begin(9600);                   // |  
  vw_set_ptt_inverted(true);            // |  Required for DR3100
  vw_set_rx_pin(12);                    // |  Receiver digital data pin
  vw_setup(4000);                       // |  Data transfer velocity (bps)
  pinMode(13, OUTPUT);                  // |  Port 13, LED to check data reception
  vw_rx_start();                        // |  Start the receiver PLL running
}                                       // |  
void loop(){                            // |  
  num_int_ant=num_int;                  // |  Storage of previous reception
  uint8_t buf[VW_MAX_MESSAGE_LEN];      // |  Declaration of buffer variable
  uint8_t buflen=VW_MAX_MESSAGE_LEN;    // |  Maximum length of buffer variable
  if(vw_get_message(buf,&buflen)){      // |  Comprovation of data reception
    for(int i=0;i<buflen;i++){          // |  
      num[i]=int(buf[i]);               // |  Storage of data received on the buffer_
      }                                 // |  _variable
  num_int=10*num[0]+num[1];             // |  Union of data received in a single variable
  if(abs(num_int-num_int_ant)<rang){    // |  
    for(int i=0;i<buflen;i++){          // |  
      Serial.print(char(buf[i]));       // |  Transmission of data variable to Serial_
      }                                 // |  _Console
    Serial.println();                   // |  
    }                                   // |  
  }                                     // |  
  delay(100);                           // |  
}                                       // |  
