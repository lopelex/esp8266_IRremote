#include <user_config.h>
#include "IRremote.h"
#include <SmingCore/SmingCore.h>

#define IRR_PIN 12 // GPIO12
#define IRS_PIN 13 // GPIO13
#define LED_PIN 2  // GPIO2

Timer irTimer;
decode_results results;
IRrecv irrecv(IRR_PIN);
IRsend irsend(IRS_PIN);

void dump(decode_results *results)
{
	Serial.print("type: ");
	Serial.print(results->decode_type);
	Serial.print(" hex: 0x");
	Serial.print(results->value, HEX);
	Serial.print(" dec: ");
	Serial.print(results->value, DEC);
	Serial.print(" bits: ");
	Serial.print(results->bits, DEC);
	Serial.println();
}

void loop()
{
	Serial.println("send mute to samsung");
	irsend.sendSAMSUNG(0xE0E0F00F, 32);
}

void init()
{
	System.setCpuFrequency(eCF_160MHz);
	Serial.begin(SERIAL_BAUD_RATE);
	Serial.println("Setting up...");
	irTimer.initializeMs(2000, loop).start();
}
