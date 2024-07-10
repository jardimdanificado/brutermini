#include <cstdlib>
#include "wrench.h"
#include <string.h>
#include <stdio.h>
#include "SSD1306Wire.h" // legacy include: `#include "oled.h"`

#define BUZZER D3


#define BTN_1 D8
#define BTN_2 D7
#define BTN_3 D4
#define BTN_4 D2
#define BTN_5 D1


#include "font.h"
SSD1306Wire display(0x3c, D5, D6); 



//------------------------------------------------------------------------------
void ino_delay( WRValue* stackTop, const int argn, WRContext* c )
{
	WRValue* argv = stackTop - argn;
	if( argn == 1)
	{
		delay( argv[0].asInt() );
	}
}

//------------------------------------------------------------------------------
void ino_pinMode( WRValue* stackTop, const int argn, WRContext* c )
{
	WRValue* argv = stackTop - argn;
	if( argn == 2)
	{
		pinMode(argv[0].asInt(), argv[1].asInt());
	}
}

//------------------------------------------------------------------------------
void ino_digitalWrite( WRValue* stackTop, const int argn, WRContext* c )
{
	WRValue* argv = stackTop - argn;
	if( argn == 2)
	{
		digitalWrite(argv[0].asInt(), argv[1].asInt());
	}
}

void ino_digitalRead( WRValue* stackTop, const int argn, WRContext* c )
{
	WRValue* argv = stackTop - argn;
	if( argn == 1)
	{
		wr_makeInt( stackTop, digitalRead( argv[0].asInt() ));
	}
}

//------------------------------------------------------------------------------
void ino_analogRead( WRValue* stackTop, const int argn, WRContext* c )
{
	WRValue* argv = stackTop - argn;
	if ( argn == 1)
	{
		// return the value
		wr_makeInt( stackTop, analogRead( argv[0].asInt() ));
	}
}

void ino_tone( WRValue* stackTop, const int argn, WRContext* c )
{
	WRValue* argv = stackTop - argn;
	if( argn == 2)
	{
		tone(argv[0].asInt(), argv[1].asInt());
	}
}

//------------------------------------------------------------------------------
/*void wr_allocateBuffer(WRContext* c, const WRValue* argv, const int argn, WRValue& retVal, void* usr)
{
    if (argn == 0)
{
        wr_makeInt(&retVal, display.allocateBuffer());
    }
}*/

//------------------------------------------------------------------------------
void wr_init( WRValue* stackTop, const int argn, WRContext* c )
{
	WRValue* argv = stackTop - argn;
    if (argn == 0) 
	{
        wr_makeInt(stackTop, display.init());
		display.setFont(Font6x8);
		display.setContrast(255);
		display.flipScreenVertically();
    }
}

//------------------------------------------------------------------------------
void wr_end( WRValue* stackTop, const int argn, WRContext* c )
{
	WRValue* argv = stackTop - argn;
    
	if (argn == 0) 
	{
        display.end();
    }
}

//------------------------------------------------------------------------------
void wr_resetDisplay( WRValue* stackTop, const int argn, WRContext* c )
{
	WRValue* argv = stackTop - argn;	if (argn == 0) 
	{
        display.resetDisplay();
    }
}

//------------------------------------------------------------------------------
void wr_setPixel( WRValue* stackTop, const int argn, WRContext* c )
{
	WRValue* argv = stackTop - argn;
    if (argn == 2) 
	{
        display.setPixel(argv[0].asInt(), argv[1].asInt());
    }
}

//------------------------------------------------------------------------------
void wr_clearPixel( WRValue* stackTop, const int argn, WRContext* c )
{
	WRValue* argv = stackTop - argn;
    if (argn == 2) 
	{
        display.clearPixel(argv[0].asInt(), argv[1].asInt());
    }
}

void wr_setColor( WRValue* stackTop, const int argn, WRContext* c )
{
	WRValue* argv = stackTop - argn;
	if (argn == 1) 
	{
		display.setColor(argv[0].asInt() ? WHITE : BLACK);
	}
}

void wr_getColor( WRValue* stackTop, const int argn, WRContext* c )
{
	WRValue* argv = stackTop - argn;
	if (argn == 0)
	{
		wr_makeInt(stackTop, display.getColor() == WHITE);
	}
}

//------------------------------------------------------------------------------
void wr_drawLine( WRValue* stackTop, const int argn, WRContext* c )
{
	WRValue* argv = stackTop - argn;
    if (argn == 4)
	{
        display.drawLine(argv[0].asInt(), argv[1].asInt(), argv[2].asInt(), argv[3].asInt());
    }
}

//------------------------------------------------------------------------------
void wr_drawRect( WRValue* stackTop, const int argn, WRContext* c )
{
	WRValue* argv = stackTop - argn;
    if (argn == 4)
	{
        display.drawRect(argv[0].asInt(), argv[1].asInt(), argv[2].asInt(), argv[3].asInt());
    }
}

//------------------------------------------------------------------------------
void wr_fillRect( WRValue* stackTop, const int argn, WRContext* c )
{
	WRValue* argv = stackTop - argn;
    if (argn == 4)
	{
        display.fillRect(argv[0].asInt(), argv[1].asInt(), argv[2].asInt(), argv[3].asInt());
    }
}

//------------------------------------------------------------------------------
void wr_drawCircle( WRValue* stackTop, const int argn, WRContext* c )
{
	WRValue* argv = stackTop - argn;
    if (argn == 3)
	{
        display.drawCircle(argv[0].asInt(), argv[1].asInt(), argv[2].asInt());
    }
}

//------------------------------------------------------------------------------
void wr_fillCircle( WRValue* stackTop, const int argn, WRContext* c )
{
	WRValue* argv = stackTop - argn;
    if (argn == 3)
	{
        display.fillCircle(argv[0].asInt(), argv[1].asInt(), argv[2].asInt());
    }
}

//------------------------------------------------------------------------------
void wr_drawTriangle( WRValue* stackTop, const int argn, WRContext* c )
{
	WRValue* argv = stackTop - argn;
    if (argn == 6)
	{
        display.drawTriangle(argv[0].asInt(), argv[1].asInt(), argv[2].asInt(), argv[3].asInt(), argv[4].asInt(), argv[5].asInt());
    }
}

//------------------------------------------------------------------------------
void wr_fillTriangle( WRValue* stackTop, const int argn, WRContext* c )
{
	WRValue* argv = stackTop - argn;
    if (argn == 6)
	{
        display.fillTriangle(argv[0].asInt(), argv[1].asInt(), argv[2].asInt(), argv[3].asInt(), argv[4].asInt(), argv[5].asInt());
    }
}

void wr_drawString( WRValue* stackTop, const int argn, WRContext* c )
{
	WRValue* argv = stackTop - argn;
    if (argn == 3)
	{
		char buffer[64];
        wr_makeInt(stackTop, display.drawString(argv[0].asInt(), argv[1].asInt(), argv[2].asString(buffer, 64)));
    }
}

void wr_display( WRValue* stackTop, const int argn, WRContext* c )
{
	WRValue* argv = stackTop - argn;
	if (argn == 0)
	{
		display.display();
	}
}

void wr_clear( WRValue* stackTop, const int argn, WRContext* c )
{
	WRValue* argv = stackTop - argn;
	if (argn == 0)
	{
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

void wr_atoi( WRContext* c, const WRValue* argv, const int argn, WRValue& retVal, void* usr )
{
	if( argn == 1)
	{
		char buffer[64];
		wr_makeInt( &retVal, atoi( argv[0].asString(buffer, 64) ) );
	}
}

void wr_atof( WRContext* c, const WRValue* argv, const int argn, WRValue& retVal, void* usr )
{
	if( argn == 1)
	{
		char buffer[64];
		wr_makeFloat( &retVal, atof( argv[0].asString(buffer, 64) ) );
	}
}


// wrench ch test.w test.h wrenchCode
#include "test.h"

WRState* w = wr_newState(); // create the state
//unsigned char* outBytes; // compiled code is alloc'ed
//int outLen;
WRContext* _ctx;
bool redraw = true;

void setup()
{
	WRValue bufferobj;
	Serial.begin(115200);
	wr_loadSysLib(w);

	wr_registerFunction( w, "print", print ); // bind a function
	wr_registerFunction( w, "atoi", wr_atoi ); // bind a function
	wr_registerFunction( w, "atof", wr_atof ); // bind a function

	wr_registerLibraryFunction( w, "ino::delay", ino_delay );
	wr_registerLibraryFunction( w, "ino::pinMode", ino_pinMode );
	wr_registerLibraryFunction( w, "ino::digitalWrite", ino_digitalWrite );
	wr_registerLibraryFunction( w, "ino::digitalRead", ino_digitalRead );
	wr_registerLibraryFunction( w, "ino::analogRead", ino_analogRead );
	wr_registerLibraryFunction( w, "ino::tone", ino_tone );
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

	wr_registerLibraryConstant( w, "oled::WHITE", wr_makeInt(&bufferobj,WHITE) );
	wr_registerLibraryConstant( w, "oled::BLACK", wr_makeInt(&bufferobj,BLACK) );
	wr_registerLibraryFunction( w, "oled::init", wr_init );
	wr_registerLibraryFunction( w, "oled::end", wr_end );
	wr_registerLibraryFunction( w, "oled::resetDisplay", wr_resetDisplay );
	wr_registerLibraryFunction( w, "oled::setPixel", wr_setPixel );
	wr_registerLibraryFunction( w, "oled::clearPixel", wr_clearPixel );
	wr_registerLibraryFunction( w, "oled::setColor", wr_setColor );
	wr_registerLibraryFunction( w, "oled::getColor", wr_getColor );
	wr_registerLibraryFunction( w, "oled::drawLine", wr_drawLine );
	wr_registerLibraryFunction( w, "oled::drawRect", wr_drawRect );
	wr_registerLibraryFunction( w, "oled::fillRect", wr_fillRect );
	wr_registerLibraryFunction( w, "oled::drawCircle", wr_drawCircle );
	wr_registerLibraryFunction( w, "oled::fillCircle", wr_fillCircle );
	wr_registerLibraryFunction( w, "oled::drawTriangle", wr_drawTriangle );
	wr_registerLibraryFunction( w, "oled::fillTriangle", wr_fillTriangle );
	wr_registerLibraryFunction( w, "oled::drawString", wr_drawString );
	wr_registerLibraryFunction( w, "oled::display", wr_display );
	wr_registerLibraryFunction( w, "oled::clear", wr_clear );
	

	//int err = wr_compile( wrenchCode_bytecode, strlen(wrenchCode), &outBytes, &outLen ); // compile it
	
	_ctx = wr_run( w, wrenchCode_bytecode, wrenchCode_bytecodeSize, true ); // load and run the code!
	//}
	wr_callFunction( _ctx, "setup",0, 0); // call the setup function
	//wr_destroyState( w );
}

void loop()
{
	wr_callFunction( _ctx, "loop",0, 0); // call the setup function
	delay(50);
}