#include <user_config.h>
#include "IRremote.h"
#include "IRremoteInt.h"
#include <SmingCore/SmingCore.h>


Timer irTimer;
decode_results dresults;
IRrecv irrecv(12);
IRsend irsend(13);

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

void receiveIR()
{
		irTimer.stop();
		irsend.sendNEC(0xE0E048B7, 32);
		delay(500);
		irsend.sendSAMSUNG(0xE0E048B7, 32);
		Serial.println("Sent ...");
		irTimer.start();
}

void init()
{
	System.setCpuFrequency(eCF_80MHz);
	Serial.begin(SERIAL_BAUD_RATE); // 115200 by default
	Serial.systemDebugOutput(true);
	Serial.println("Setting up...");
	irTimer.initializeMs(2000, receiveIR).start();
	Serial.println("Ready...");
	Serial.print(system_get_cpu_freq());
	Serial.println();
}
