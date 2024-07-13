#include <LuaWrapper.h>

#include <cstdlib>
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

LuaWrapper lua;

static int lua_delay(lua_State *L)
{
    delay(luaL_checkinteger(L, 1));
    return 0;
}

static int lua_pin_mode(lua_State *L)
{
    int pin = luaL_checkinteger(L, 1);
    int mode = luaL_checkinteger(L, 2);
    pinMode(pin, mode);
    return 0;
}

static int lua_digital_write(lua_State *L)
{
    int pin = luaL_checkinteger(L, 1);
    int value = luaL_checkinteger(L, 2);
    digitalWrite(pin, value);
    return 0;
}

static int lua_digital_read(lua_State *L)
{
    int pin = luaL_checkinteger(L, 1);
    lua_pushinteger(L, digitalRead(pin));
    return 1;
}

static int lua_analog_write(lua_State *L)
{
    int pin = luaL_checkinteger(L, 1);
    int value = luaL_checkinteger(L, 2);
    analogWrite(pin, value);
    return 0;
}

static int lua_analog_read(lua_State *L)
{
    int pin = luaL_checkinteger(L, 1);
    lua_pushinteger(L, analogRead(pin));
    return 1;
}

static int lua_print(lua_State *L)
{
    Serial.println(luaL_checkstring(L, 1));
    return 0;
}

// oled

static int lua_oled_init(lua_State *L)
{
    lua_pushnumber(L, display.init());
    display.setFont(Font6x8);
    display.setContrast(255);
    //display.flipScreenVertically();
    return 0;
}

static int lua_oled_setColor(lua_State *L)
{
    display.setColor((OLEDDISPLAY_COLOR)luaL_checkinteger(L, 1));
    return 0;
}

static int lua_oled_drawLine(lua_State *L)
{
    display.drawLine((int)luaL_checkinteger(L, 1), (int)luaL_checkinteger(L, 2), (int)luaL_checkinteger(L, 3), (int)luaL_checkinteger(L, 4));
    return 0;
}

static int lua_oled_drawRect(lua_State *L)
{
    display.drawRect((int)luaL_checkinteger(L, 1), (int)luaL_checkinteger(L, 2), (int)luaL_checkinteger(L, 3), (int)luaL_checkinteger(L, 4));
    return 0;
}

static int lua_oled_fillRect(lua_State *L)
{
    display.fillRect((int)luaL_checkinteger(L, 1), (int)luaL_checkinteger(L, 2), (int)luaL_checkinteger(L, 3), (int)luaL_checkinteger(L, 4));
    return 0;
}

static int lua_oled_drawCircle(lua_State *L)
{
    display.drawCircle((int)luaL_checkinteger(L, 1), (int)luaL_checkinteger(L, 2), (int)luaL_checkinteger(L, 3));
    return 0;
}

static int lua_oled_fillCircle(lua_State *L)
{
    display.fillCircle((int)luaL_checkinteger(L, 1), (int)luaL_checkinteger(L, 2), (int)luaL_checkinteger(L, 3));
    return 0;
}

static int lua_oled_drawTriangle(lua_State *L)
{
    display.drawTriangle((int)luaL_checkinteger(L, 1), (int)luaL_checkinteger(L, 2), (int)luaL_checkinteger(L, 3), (int)luaL_checkinteger(L, 4), (int)luaL_checkinteger(L, 5), (int)luaL_checkinteger(L, 6));
    return 0;
}

static int lua_oled_fillTriangle(lua_State *L)
{
    display.fillTriangle((int)luaL_checkinteger(L, 1), (int)luaL_checkinteger(L, 2), (int)luaL_checkinteger(L, 3), (int)luaL_checkinteger(L, 4), (int)luaL_checkinteger(L, 5), (int)luaL_checkinteger(L, 6));
    return 0;
}

static int lua_oled_drawString(lua_State *L)
{
    display.drawString((int)luaL_checkinteger(L, 1), (int)luaL_checkinteger(L, 2), luaL_checkstring(L, 3));
    return 0;
}

static int lua_oled_display(lua_State *L)
{
    display.display();
    return 0;
}

static int lua_oled_clear(lua_State *L)
{
    display.clear();
    return 0;
}

#include "test_.h"

void setup()
{
    Serial.begin(115200);

    lua.Lua_register("delay", (const lua_CFunction)&lua_delay);
    lua.Lua_register("pinMode", (const lua_CFunction)&lua_pin_mode);
    lua.Lua_register("digitalWrite", (const lua_CFunction)&lua_digital_write);
    lua.Lua_register("digitalRead", (const lua_CFunction)&lua_digital_read);
    lua.Lua_register("analogWrite", (const lua_CFunction)&lua_analog_write);
    lua.Lua_register("analogRead", (const lua_CFunction)&lua_analog_read);
    //lua.Lua_register("print", (const lua_CFunction)&lua_print);

    lua.Lua_register("oled_init", (const lua_CFunction)&lua_oled_init);
    lua.Lua_register("oled_setColor", (const lua_CFunction)&lua_oled_setColor);
    lua.Lua_register("oled_drawLine", (const lua_CFunction)&lua_oled_drawLine);
    lua.Lua_register("oled_drawRect", (const lua_CFunction)&lua_oled_drawRect);
    lua.Lua_register("oled_fillRect", (const lua_CFunction)&lua_oled_fillRect);
    lua.Lua_register("oled_drawCircle", (const lua_CFunction)&lua_oled_drawCircle);
    lua.Lua_register("oled_fillCircle", (const lua_CFunction)&lua_oled_fillCircle);
    lua.Lua_register("oled_drawTriangle", (const lua_CFunction)&lua_oled_drawTriangle);
    lua.Lua_register("oled_fillTriangle", (const lua_CFunction)&lua_oled_fillTriangle);
    lua.Lua_register("oled_drawString", (const lua_CFunction)&lua_oled_drawString);
    lua.Lua_register("oled_display", (const lua_CFunction)&lua_oled_display);
    lua.Lua_register("oled_clear", (const lua_CFunction)&lua_oled_clear);

    

    String script = String(//"BUILTIN_LED = " + String(BUILTIN_LED) + 
                            "\nBTN_1 = " + String(BTN_1)
                           + "\nBTN_2 = " + String(BTN_2)
                           + "\nBTN_3 = " + String(BTN_3)
                           + "\nBTN_4 = " + String(BTN_4)
                           + "\nBTN_5 = " + String(BTN_5)
                           + "\nBUZZER = " + String(BUZZER)
                           + "\nWHITE = " + String(WHITE)
                           + "\nBLACK = " + String(BLACK)
                           + "\n" + String(test)
                           + "\npinMode(BTN_1, INPUT)"
                           + "\npinMode(BTN_2, INPUT)"
                           + "\npinMode(BTN_3, INPUT)"
                           + "\npinMode(BTN_4, INPUT)"
                           + "\npinMode(BTN_5, INPUT)"
                           + "\npinMode(BUILTIN_LED, OUTPUT)");
    //Serial.println(script);
    Serial.println(lua.Lua_dostring(&script));
}

String loopscript = "loop()";

void loop()
{
    Serial.println(lua.Lua_dostring(&loopscript));
    //delay(200);
}
