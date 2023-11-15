#include <Arduino.h>

#include <Adafruit_NeoPixel.h>

#ifndef NEOPIXEL
#define NEOPIXEL	39
#endif

#ifndef NEOPIXEL_POWER
#define NEOPIXL_POWER	38
#endif

static Adafruit_NeoPixel _flasher(  1, NEOPIXEL, NEO_RGB + NEO_KHZ800 );

void setup(
        )
    {
		pinMode( NEOPIXEL_POWER, OUTPUT );
		digitalWrite( NEOPIXEL_POWER, HIGH );

		_flasher.begin();
		_flasher.show();

        Serial.begin( 11500 );
        delay( 1000 );
    }

static bool _state = false;
static unsigned long _nxt = 0;

void loop(
        )
    {
        if ( millis() > _nxt )

        {
            _nxt = millis() + 1000;
            Serial.printf( "%lu\r\n", millis() );

			if ( _state )
				{
				_flasher.setPixelColor( 0, 255,255,255 );
				}
			else
				{
				_flasher.setPixelColor( 0, 0,0,0 );
				}
			_flasher.show();

			_state = !(_state);
        }
    }

