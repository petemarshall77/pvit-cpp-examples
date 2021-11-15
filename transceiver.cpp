//Combined Transmitter and Receiver Code

#include <RadioLib.h>         //#?
#include <list>
#include <map>
#include <iterator>
#include <queue>

using namespace std;

#define PONG    //COMMENT THIS LINE OUT IF THIS IS PONG

//pin numbers for LORA to Arduino from SEMTECH to BUSY
#define SEMTECH
#define NRST        A0 //reset
#define ANT_SW      8 //antenna software, radio = half duplex (ex. switches to listening to sending)
#define NSS         7 //software selector, how we select radio to start talking
#define DIO1        5 // internal for radio
#define BUSY        3 //radio = busy, can’t do it

#define PONG_INTERVAL             7       // seconds, how much time to wait between PINGs sent from this node

//initial conditions
#define FREQUENCY_900M30S         433.0//915.0   // MHz carrier, for E22-900M30S
#define FREQUENCY_400M30S         433.0   // MHz carrier, for E22-400M30S
#define FREQUENCY_GATEWAY         433.0   // MHz carrier, for ESP32 single-channel gateway
#define BANDWIDTH                 125.0   // kHz dual-sideband
#define SPREADING_FACTOR          9       // 2^9 chips
#define CODING_RATE               7       // 4/7 coding
#define SYNC_WORD                 0x12    // private network
#define OUTPUT_POWER              14      // +14 dBm
#define CURRENT_LIMIT             60.0    // mA
#define PREAMBLE_LENGTH           8       // symbols
#define TCXO_VOLTAGE              2.4     // V



unsigned long loopCount=0;         //unsigned?
bool bReady=false;
volatile bool operationDone = false;    // flag to indicate that a packet was sent or received
volatile bool enableInterrupt = true;    // disable interrupt when it's not needed

 bool Ready(){return bReady;}
 void Ready(bool tmp){bReady=tmp;}

void setFlag(void) {   // this function is called when a complete packet is transmitted
  // check if the interrupt is enabled
  if(!enableInterrupt) { //enableInterrupt = no interrupt at beginning = 0; if = 1, then it will send or receive
    return;
  }

  // we sent or received a packet, set the flag
  operationDone = true;

}


    SX1262 lora = new Module(NSS, DIO1, NRST, BUSY);

    int transmissionState = ERR_NONE;   // save transmission state between loops
    bool transmitting = false;   // flag to indicate if we're currently sending ping packet or just listening
    unsigned long lastPong = 0;   // timestamp of the last PING packet
    unsigned long lastTransmit=0;


  std::queue<std::string> receivedQueue;
  std::queue<std::string> transmitQueue;
  std::queue<std::string> transmitAckQueue;


//receive and transmit at essentially the same time
// no more than 25% in transmit
  bool isReadyToTransmit(){
    if(transmitQueue.size()>0) return true;
    return false;
  }

  bool NewMessage(){
    if(receivedQueue.size()>0) {  //Need to check the packet format
      return true;
    }
    return false;
    }


  void setRfMode(bool transmit) {   // function to set RF mode to transmit or receive
    #if !defined(USE_ESP32_GATEWAY)
    if(transmit) {
      #if !defined(SEMTECH)
      digitalWrite(RXEN, LOW);
      digitalWrite(TXEN, HIGH);
      #endif
    } else {
      #if !defined(SEMTECH)
      digitalWrite(RXEN, HIGH);
      digitalWrite(TXEN, LOW);
      #endif                //endif?
    }
    delay(100);                //delay(100)?
    #endif
  }



void setup() {
    Serial.begin(115200); //set up data rate, set up for debugging communication when on home computer, don’t need this for space

  #ifdef SEMTECH //connects antenna
    pinMode(ANT_SW, OUTPUT);
    digitalWrite(ANT_SW, HIGH);

  #endif

  // initialize the radio
  Serial.print(F("Initializing ... "));

  #if defined(SEMTECH)
    int state = lora.begin(915.0, 125.0,9, 7, 0x12, 22, 120, 8, 0);  //when radio is turning on

  #else
    int state = lora.begin(FREQUENCY_400M30S, BANDWIDTH, SPREADING_FACTOR, CODING_RATE, SYNC_WORD, OUTPUT_POWER, CURRENT_LIMIT, PREAMBLE_LENGTH, TCXO_VOLTAGE);
  #endif
  if(state == ERR_NONE) {
    Ready(true);
    Serial.println(F("success!"));
  } else {
    Ready(false);
    Serial.print(F("failed, code ")); //need code for what to do when radio fails, take in to account we have two radios
    Serial.println(state);
    return;
  }

  // set the function that will be called when packet transmission or reception is finished
  #if defined(USE_ESP32_GATEWAY)
    lora.setDio0Action(setFlag);
  #else
    lora.setDio1Action(setFlag);
  #endif

  // set receive mode
  //setRfMode(false);
  //lora.startReceive();
  SetRadioReceive();
}



// check if it's time to transmit a ping packet

bool isTransmitTime(){
     if(millis()>lastTransmit)  {
      return true;
     }
     return false;         //wouldn't this always return false?
}

void MakeAck(String sstr){
std::string str=sstr.c_str();    //c_?

 if (str.size()>0){
  if (str[0]=='A') return;  //Don't need to Ack and Ack, but do need to process ack
 }

 std::string strAck="A";
 strAck=strAck+str.substr(1,10);

 Serial.print("                             Making Ack String ");
  Serial.println(strAck.c_str());

 transmitAckQueue.push(strAck);

}

void Transmit(std::string str){
    Serial.print(F(" Transmitting ........"));

    // set mode to transmission
    setRfMode(true);
    transmitting = true;

    // start transmitting

    //Serial.println(str);
    transmissionState = lora.startTransmit(str.c_str());
    unsigned long timeonairmilli=lora.getTimeOnAir(str.size())/1000;
    Serial.print(str.c_str());
    Serial.print(" TOA:");
    Serial.println(timeonairmilli);
    // save timestamp
    lastPong = millis();
    lastTransmit=lastPong+timeonairmilli;
}

void TransmitPacket(){  //*************Not done yet  ack stuff, ack that we’re done transmitting
    std::string str;
    if(!transmitAckQueue.empty()){
      str=transmitAckQueue.front();
      transmitAckQueue.pop();
      if(str.size()!=0)  Transmit(str);
    }

    else if(!transmitQueue.empty()) {
      str=transmitQueue.front();
      transmitQueue.pop();
      if(str.size()!=0)  Transmit(str);
    }
}

void SetRadioReceive(){
      setRfMode(false);
      transmitting = false;
      Serial.print(F("Starting to listen ... "));
      int state = lora.startReceive();
      if (state == ERR_NONE) {
        // packet was successfully sent
        Serial.println(F(" Success!"));

      } else {
        Serial.print(F(" Failed to start reception, code "));
        Serial.println(state);
        delay(2000);
        Serial.println(F(" Delaying 2 secs  Restarting Radio "));
        setup();
        return;

      }
}

std::string Received(){
   String str;
   int state = lora.readData(str);

   if(state == ERR_NONE) {
        // print data
        MakeAck(str);
        Serial.print(F("Data:\t\t"));
        Serial.println(str);
        Serial.print(F("RSSI:\t\t"));
        Serial.print(lora.getRSSI());
        Serial.print(F("  dBm"));
        Serial.print(F(" SNR:\t\t"));
        Serial.print(lora.getSNR());
        Serial.println(F(" dB"));
        return str.c_str();

      } else if (state == ERR_CRC_MISMATCH) {
        Serial.println(F("CRC error!"));

      } else {
        Serial.print(F("failed, code "));
        Serial.println(state);

      }
      str="";
      return str.c_str();

}

//Packet .  Place in Rcvd queue.
bool ReceivedPacket(){
      Serial.println(F("Received packet!"));
      std::string str=Received();
      if(str.size()){                                                //str.size()?
        receivedQueue.push(str);
        return true;
      }

      return false;
}



  // you can also transmit byte array up to 256 bytes long
  /*
  std::string str1=lora.getSNR());
  std::string str2=lora.getRSSI());
  std::string str3=lora.getTEMP());
   size_t len = 6;

    str stringArr[len] = {“RSSI:”, str1, “TEMP”, str3,
                         “SNR:”, str2,};
    int state = lora.transmit(byteArr, len);
  */

  if (state == ERR_NONE) {
    // the packet was successfully transmitted
    Serial.println(F(" success!"));

void loop(){
  //Serial.println(F(" Radio loop"));
  if (!Ready()) {
     Serial.println(F(" Radio NOT Ready"));
    return;
  }

  loopCount++;


#ifdef PONG
  if (loopCount % 1500000==0) {
    std::string str="PONG";
    transmitQueue.push(str);

   std::string str=lora.getRSSI();
    transmitQueue.push(str);

std::string str=lora.getSNR();
    transmitQueue.push(str);
  }
#else
if (loopCount % 1000000==0) {
    std::string str="PONG";
    transmitQueue.push(str);
  }
#endif

   // check if it's time to transmit a ping packet or what is in queue
    if(!transmitAckQueue.empty() || !transmitQueue.empty()){
      if (isTransmitTime()) {
        TransmitPacket();
      }
    }

  if((lastTransmit>0) && (millis()>(lastTransmit+5000))){  //Prevent lock waiting for it to finish and just go back to receive mode
     Serial.println(F("Look   Timeout  returning to Receive Mode"));
     lastTransmit=0;
     SetRadioReceive();
  }


  // check if the previous operation finished     this is set by interrupt


  if(operationDone) {
     //   Serial.println(F("Transmit or Receive Finished"));
    // disable the interrupt service routine while processing the data
    enableInterrupt = false;

    // check which operation finished
    if(transmitting) {
      // packet transmission finished, check the result
      if (transmissionState == ERR_NONE) {
        // packet was successfully sent
        //Serial.println(F(" ... Transmission finished!"));       //accidentally commented out?

      } else {
        Serial.print(F("failed, code "));
        Serial.println(transmissionState);
      }

      // set mode to reception
      lastTransmit=0;


    } else {
      // received packet, read the data
      ReceivedPacket();
      //delay(4000);
    }
    SetRadioReceive();  //Always set radio back to receive mode
    // reset flag
    operationDone = false;

    // we're ready to send more packets, enable interrupt service routine
    enableInterrupt = true;
  }
}
