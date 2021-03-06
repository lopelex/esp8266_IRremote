/*
 * IRremote for ESP8266
 * Version 0.01 May, 2015
 * Written by Mat Salvaris
 * Based on the IRremote library for Arduino written by Ken Shirriff
 */

#ifndef IRremote_h
#define IRremote_h

#define FRC1_ENABLE_TIMER BIT7
#define FRC1_AUTO_RELOAD BIT6
#define	DIVDED_BY_16 4
#define TM_LEVEL_INT 1


enum decode_type_t {
  NEC = 1,
  SONY = 2,
  RC5 = 3,
  RC6 = 4,
  DISH = 5,
  SHARP = 6,
  PANASONIC = 7,
  JVC = 8,
  SANYO = 9,
  MITSUBISHI = 10,
  SAMSUNG = 11,
  LG = 12,
  WHYNTER = 13,
  AIWA_RC_T501 = 14,

  UNKNOWN = -1
};

// Results returned from the decoder
class decode_results {
public:
  int decode_type; // NEC, SONY, RC5, UNKNOWN
  union { // This is used for decoding Panasonic and Sharp data
    unsigned int panasonicAddress;
    unsigned int sharpAddress;
  };
  unsigned long value; // Decoded value
  int bits; // Number of bits in decoded value
  volatile unsigned int *rawbuf; // Raw intervals in .5 us ticks
  int rawlen; // Number of records in rawbuf.
};

// Values for decode_type
#define NEC 1
#define SONY 2
#define RC5 3
#define RC6 4
#define DISH 5
#define SHARP 6
#define PANASONIC 7
#define JVC 8
#define SANYO 9
#define MITSUBISHI 10
#define SAMSUNG 11
#define LG 12
#define WHYNTER 13
#define UNKNOWN -1

// Decoded value for NEC when a repeat code is received
#define REPEAT 0xffffffff


// main class for receiving IR
class IRrecv
{
public:
  IRrecv(uint8_t recvpin);
  void blink(int blinkflag, int ledpin = 0);
  int decode(decode_results *results);
  void enableIRIn();
  void disableIRIn();
  void resume();
private:
  // These are called by decode
  int getRClevel(decode_results *results, int *offset, int *used, int t1);
  long decodeNEC(decode_results *results);
  long decodeSony(decode_results *results);
  long decodeSanyo(decode_results *results);
  long decodeMitsubishi(decode_results *results);
  long decodeRC5(decode_results *results);
  long decodeRC6(decode_results *results);
  long decodePanasonic(decode_results *results);
  long decodeLG(decode_results *results);
  long decodeJVC(decode_results *results);
  long decodeSAMSUNG(decode_results *results);
  long decodeWhynter(decode_results *results);
  long decodeHash(decode_results *results);
  int compare(unsigned int oldval, unsigned int newval);
} ;


class IRsend
{
public:
  IRsend(uint8_t sendpin);
  void sendWhynter(unsigned long data, int nbits);
  void sendNEC(unsigned long data, int nbits);
  void sendSony(unsigned long data, int nbits);
  // Neither Sanyo nor Mitsubishi send is implemented yet
  //  void sendSanyo(unsigned long data, int nbits);
  //  void sendMitsubishi(unsigned long data, int nbits);
  void sendRaw(unsigned int buf[], int len, int hz);
  void sendRC5(unsigned long data, int nbits);
  void sendRC6(unsigned long data, int nbits);
  void sendDISH(unsigned long data, int nbits);
  void sendSharp(unsigned int address, unsigned int command);
  void sendSharpRaw(unsigned long data, int nbits);
  void sendPanasonic(unsigned int address, unsigned long data);
  void sendJVC(unsigned long data, int nbits, int repeat); // *Note instead of sending the REPEAT constant if you want the JVC repeat signal sent, send the original code value and change the repeat argument from 0 to 1. JVC protocol repeats by skipping the header NOT by sending a separate code value like NEC does.
  void sendSAMSUNG(unsigned long data, int nbits);
private:
  void enableIROut(int khz);
  void mark(int usec);
  void space(int usec);
};

// Some useful constants

#define USECPERTICK 50  // microseconds per clock interrupt tick
#define RAWBUF 100 // Length of raw duration buffer

// Marks tend to be 100us too long, and spaces 100us too short
// when received due to sensor lag.
#define MARK_EXCESS 100

#endif

