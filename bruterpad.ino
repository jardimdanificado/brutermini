#include <cstdlib>
#include "wrench.h"
#include <string.h>
#include <stdio.h>
#include "SSD1306Wire.h" // legacy include: `#include "SSD1306.h"`

#define BUZZER D3


#define BTN_1 D8
#define BTN_2 D7
#define BTN_3 D4
#define BTN_4 D2
#define BTN_5 D1


#include "font.h"
SSD1306Wire display(0x3c, D5, D6); 



//------------------------------------------------------------------------------
void ino_delay( WRContext* c, const WRValue* argv, const int argn, WRValue& retVal, void* usr )
{
	if( argn == 1)
	{
		delay( argv[0].asInt() );
	}
}

//------------------------------------------------------------------------------
void ino_pinMode( WRContext* c, const WRValue* argv, const int argn, WRValue& retVal, void* usr )
{
	if( argn == 2)
	{
		pinMode(argv[0].asInt(), argv[1].asInt());
	}
}

//------------------------------------------------------------------------------
void ino_digitalWrite( WRContext* c, const WRValue* argv, const int argn, WRValue& retVal, void* usr )
{
	if( argn == 2)
	{
		digitalWrite(argv[0].asInt(), argv[1].asInt());
	}
}

void ino_digitalRead( WRContext* c, const WRValue* argv, const int argn, WRValue& retVal, void* usr )
{
	if( argn == 1)
	{
		wr_makeInt( &retVal, digitalRead( argv[0].asInt() ));
	}
}

//------------------------------------------------------------------------------
void ino_analogRead( WRContext* c, const WRValue* argv, const int argn, WRValue& retVal, void* usr )
{
	if ( argn == 1)
	{
		// return the value
		wr_makeInt( &retVal, analogRead( argv[0].asInt() ));
	}
}

void ino_tone( WRContext* c, const WRValue* argv, const int argn, WRValue& retVal, void* usr )
{
	if( argn == 2)
	{
		tone(argv[0].asInt(), argv[1].asInt());
	}
}

//------------------------------------------------------------------------------
/*void wr_allocateBuffer(WRContext* c, const WRValue* argv, const int argn, WRValue& retVal, void* usr) {
    if (argn == 0) {
        wr_makeInt(&retVal, display.allocateBuffer());
    }
}*/

//------------------------------------------------------------------------------
void wr_init(WRContext* c, const WRValue* argv, const int argn, WRValue& retVal, void* usr) {
    if (argn == 0) 
	{
        wr_makeInt(&retVal, display.init());
		display.setFont(Font6x8);
		display.setContrast(255);
		display.flipScreenVertically();
    }
}

//------------------------------------------------------------------------------
void wr_end(WRContext* c, const WRValue* argv, const int argn, WRValue& retVal, void* usr) {
    if (argn == 0) {
        display.end();
    }
}

//------------------------------------------------------------------------------
void wr_resetDisplay(WRContext* c, const WRValue* argv, const int argn, WRValue& retVal, void* usr) {
    if (argn == 0) {
        display.resetDisplay();
    }
}

//------------------------------------------------------------------------------
void wr_setPixel(WRContext* c, const WRValue* argv, const int argn, WRValue& retVal, void* usr) {
    if (argn == 2) {
        display.setPixel(argv[0].asInt(), argv[1].asInt());
    }
}

//------------------------------------------------------------------------------
void wr_clearPixel(WRContext* c, const WRValue* argv, const int argn, WRValue& retVal, void* usr) {
    if (argn == 2) {
        display.clearPixel(argv[0].asInt(), argv[1].asInt());
    }
}

void wr_setColor(WRContext* c, const WRValue* argv, const int argn, WRValue& retVal, void* usr) {
	if (argn == 1) {
		display.setColor(argv[0].asInt() ? WHITE : BLACK);
	}
}

void wr_getColor(WRContext* c, const WRValue* argv, const int argn, WRValue& retVal, void* usr) {
	if (argn == 0) {
		wr_makeInt(&retVal, display.getColor() == WHITE);
	}
}

//------------------------------------------------------------------------------
void wr_drawLine(WRContext* c, const WRValue* argv, const int argn, WRValue& retVal, void* usr) {
    if (argn == 4) {
        display.drawLine(argv[0].asInt(), argv[1].asInt(), argv[2].asInt(), argv[3].asInt());
    }
}

//------------------------------------------------------------------------------
void wr_drawRect(WRContext* c, const WRValue* argv, const int argn, WRValue& retVal, void* usr) {
    if (argn == 4) {
        display.drawRect(argv[0].asInt(), argv[1].asInt(), argv[2].asInt(), argv[3].asInt());
    }
}

//------------------------------------------------------------------------------
void wr_fillRect(WRContext* c, const WRValue* argv, const int argn, WRValue& retVal, void* usr) {
    if (argn == 4) {
        display.fillRect(argv[0].asInt(), argv[1].asInt(), argv[2].asInt(), argv[3].asInt());
    }
}

//------------------------------------------------------------------------------
void wr_drawCircle(WRContext* c, const WRValue* argv, const int argn, WRValue& retVal, void* usr) {
    if (argn == 3) {
        display.drawCircle(argv[0].asInt(), argv[1].asInt(), argv[2].asInt());
    }
}

//------------------------------------------------------------------------------
void wr_fillCircle(WRContext* c, const WRValue* argv, const int argn, WRValue& retVal, void* usr) {
    if (argn == 3) {
        display.fillCircle(argv[0].asInt(), argv[1].asInt(), argv[2].asInt());
    }
}

//------------------------------------------------------------------------------
void wr_drawTriangle(WRContext* c, const WRValue* argv, const int argn, WRValue& retVal, void* usr) {
    if (argn == 6) {
        display.drawTriangle(argv[0].asInt(), argv[1].asInt(), argv[2].asInt(), argv[3].asInt(), argv[4].asInt(), argv[5].asInt());
    }
}

//------------------------------------------------------------------------------
void wr_fillTriangle(WRContext* c, const WRValue* argv, const int argn, WRValue& retVal, void* usr) {
    if (argn == 6) {
        display.fillTriangle(argv[0].asInt(), argv[1].asInt(), argv[2].asInt(), argv[3].asInt(), argv[4].asInt(), argv[5].asInt());
    }
}

void wr_drawString(WRContext* c, const WRValue* argv, const int argn, WRValue& retVal, void* usr) {
    if (argn == 3) {
		char buffer[64];
        wr_makeInt(&retVal, display.drawString(argv[0].asInt(), argv[1].asInt(), argv[2].asString(buffer, 64)));
    }
}


void wr_display(WRContext* c, const WRValue* argv, const int argn, WRValue& retVal, void* usr) {
	if (argn == 0) {
		display.display();
	}
}

void wr_clear(WRContext* c, const WRValue* argv, const int argn, WRValue& retVal, void* usr) {
	if (argn == 0) {
		display.clear();
	}
}

void print( WRContext* c, const WRValue* argv, const int argn, WRValue& retVal, void* usr )
{
	if( argn == 1)
	{
		char buffer[64];
		Serial.print( argv[0].asString(buffer, 64) );
	}
}

#include "test.h"

WRState* w = wr_newState(); // create the state
//unsigned char* outBytes; // compiled code is alloc'ed
//int outLen;
WRContext* _ctx;
bool redraw = true;

void setup()
{
	Serial.begin(115200);
	

	wr_registerFunction( w, "print", print ); // bind a function

	wr_registerFunction( w, "delay", ino_delay );
	wr_registerFunction( w, "pinMode", ino_pinMode );
	wr_registerFunction( w, "digitalWrite", ino_digitalWrite );
	wr_registerFunction( w, "digitalRead", ino_digitalRead );

	wr_registerFunction( w, "analogRead", ino_analogRead );
	wr_registerFunction( w, "tone", ino_tone );

	WRValue bufferobj;
	wr_registerLibraryConstant( w, "ino::LOW", wr_makeInt(&bufferobj,LOW) );
	wr_registerLibraryConstant( w, "ino::HIGH", wr_makeInt(&bufferobj,HIGH) );
	wr_registerLibraryConstant( w, "ino::INPUT", wr_makeInt(&bufferobj,INPUT) );
	wr_registerLibraryConstant( w, "ino::OUTPUT", wr_makeInt(&bufferobj,OUTPUT) );
	wr_registerLibraryConstant( w, "ino::BUILTIN_LED", wr_makeInt(&bufferobj,BUILTIN_LED) );


	wr_registerLibraryConstant( w, "ino::BTN_1", wr_makeInt(&bufferobj,BTN_1) );
	wr_registerLibraryConstant( w, "ino::BTN_2", wr_makeInt(&bufferobj,BTN_2) );
	wr_registerLibraryConstant( w, "ino::BTN_3", wr_makeInt(&bufferobj,BTN_3) );
	wr_registerLibraryConstant( w, "ino::BTN_4", wr_makeInt(&bufferobj,BTN_4) );
	wr_registerLibraryConstant( w, "ino::BTN_5", wr_makeInt(&bufferobj,BTN_5) );

	wr_registerLibraryConstant( w, "ino::BUZZER", wr_makeInt(&bufferobj,BUZZER) );

	wr_registerLibraryConstant( w, "ino::WHITE", wr_makeInt(&bufferobj,WHITE) );
	wr_registerLibraryConstant( w, "ino::BLACK", wr_makeInt(&bufferobj,BLACK) );
	
	wr_registerFunction( w, "init", wr_init );
	wr_registerFunction( w, "end", wr_end );
	wr_registerFunction( w, "resetDisplay", wr_resetDisplay );
	wr_registerFunction( w, "setPixel", wr_setPixel );
	
	wr_registerFunction( w, "clearPixel", wr_clearPixel );
	wr_registerFunction( w, "setColor", wr_setColor );
	wr_registerFunction( w, "getColor", wr_getColor );

	wr_registerFunction( w, "drawLine", wr_drawLine );
	wr_registerFunction( w, "drawRect", wr_drawRect );
	wr_registerFunction( w, "fillRect", wr_fillRect );
	wr_registerFunction( w, "drawCircle", wr_drawCircle );
	wr_registerFunction( w, "fillCircle", wr_fillCircle );
	wr_registerFunction( w, "drawTriangle", wr_drawTriangle );
	wr_registerFunction( w, "fillTriangle", wr_fillTriangle );
	wr_registerFunction( w, "drawString", wr_drawString );
	wr_registerFunction( w, "display", wr_display );
	wr_registerFunction( w, "clear", wr_clear );
	

	//int err = wr_compile( wrenchCode_bytecode, strlen(wrenchCode), &outBytes, &outLen ); // compile it
	
	_ctx = wr_run( w, wrenchCode_bytecode, wrenchCode_bytecodeSize, true ); // load and run the code!
	//}
	wr_callFunction( _ctx, "setup",0, 0); // call the setup function
	//wr_destroyState( w );
}

void loop()
{
	wr_callFunction( _ctx, "loop",0, 0); // call the setup function
	delay(100);
}