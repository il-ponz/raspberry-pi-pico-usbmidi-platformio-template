#include <Arduino.h>
#include <Adafruit_TinyUSB.h>
#include <MIDI.h>

// Smooth buttons and potentiometers, see the libraries for examples on how to use them.
#include <Bounce2.h>
#include <ResponsiveAnalogRead.h>

// USB MIDI object
Adafruit_USBD_MIDI usbMidi;
MIDI_CREATE_INSTANCE(Adafruit_USBD_MIDI, usbMidi, MIDI);

// -----------------------------------------------------------------------------

// This example shows the old way of checking for input messages.
// It's simpler to use the callbacks now, check out the dedicated example.

#define LED 13 // LED pin on Arduino Uno

// -----------------------------------------------------------------------------



// Example of handling midi input to the device
// void handle_midi_note_on(byte channel, byte note, byte velocity) {
//   Serial.printf("Got note on! {0} {1} {2}", channel, note, velocity );
// }


void BlinkLed(byte num) // Basic blink function
{
  // for (byte i = 0; i < num; i++)
  // {
    digitalWrite(LED, HIGH);
    delay(50);
    digitalWrite(LED, LOW);
    delay(50);
  // }
  Serial.println(num);
}


// -----------------------------------------------------------------------------

void setup()
{
  Serial.begin(115200);
  Serial.println("start midi sample");

  // Set the MIDI note on handling function
  // MIDI.setHandleNoteOn(handle_midi_note_on);

  pinMode(LED, OUTPUT);

  TinyUSBDevice.setManufacturerDescriptor("il ponz");
  TinyUSBDevice.setProductDescriptor("mongos_midi_destroyer");

  usbMidi.begin();
  // Launch MIDI, by default listening to channel 1.
  MIDI.begin(MIDI_CHANNEL_OMNI);

  // Turn midi thru off
  MIDI.turnThruOff();
}

void loop()
{
  if (MIDI.read()) // Is there a MIDI message incoming ?
  {
    switch (MIDI.getType()) // Get the type of the message we caught
    {
    case midi::ProgramChange:    // If it is a Program Change,
      BlinkLed(MIDI.getData1()); // blink the LED a number of times
                                 // correponding to the program number
                                 // (0 to 127, it can last a while..)
      break;
    // See the online reference for other message types
    case midi::NoteOn:
      BlinkLed(MIDI.getData1());
      break;
    default:
      break;
    }
  }
}
