struct vec2(x,y)
{
    var x = x;
    var y = y;
};
var redraw = true;
var cursor = vec2(0, 0);
var canvas[][] = 
{
    {32,32,32,32,32,32},
    {32,32,32,32,32,32},
    {32,32,32,32,32,32},
    {32,32,32,32,32,32},
    {32,32,32,32,32,32},
    {32,32,32,32,32,32},
    {32,32,32,32,32,32},
    {32,32,32,32,32,32},
    {32,32,32,32,32,32},
    {32,32,32,32,32,32},
    {32,32,32,32,32,32},
    {32,32,32,32,32,32},
    {32,32,32,32,32,32},
    {32,32,32,32,32,32},
    {32,32,32,32,32,32},
    {32,32,32,32,32,32},
};

function drawBoard()
{
    var tempstr = "a";
    for (var i = 0; i < 16; i++)
    {
        for (var j = 0; j < 6; j++)
        {
            if (cursor.x == i && cursor.y == j)
            {
                oled::setColor(oled::WHITE);
                oled::fillRect(i * 8, j * 8, 8, 8);
                oled::setColor(oled::BLACK);
            }
            tempstr[0] = canvas[i][j];
            oled::drawString(i * 8, j * 8, tempstr);
            oled::setColor(oled::WHITE);
        }
    }
}

function setup() 
{
    oled::init();
    ino::pinMode(ino::BTN_1, ino::INPUT);
    ino::pinMode(ino::BTN_2, ino::INPUT);
    ino::pinMode(ino::BTN_3, ino::INPUT);
    ino::pinMode(ino::BTN_4, ino::INPUT);
    ino::pinMode(ino::BTN_5, ino::INPUT);
    ino::pinMode(ino::BUZZER, ino::OUTPUT);
}

function move()
{
    if (ino::digitalRead(ino::BTN_1) == ino::HIGH)
    {
        if (ino::digitalRead(ino::BTN_2) == ino::HIGH)
        {
            if(ino::digitalRead(ino::BTN_4) == ino::HIGH)
            {
                if (cursor.y > 0)
                    cursor.y = cursor.y - 1;
                else 
                    cursor.y = 5;
                redraw = true;
            }
            else if(ino::digitalRead(ino::BTN_5) == ino::HIGH)
            {
                if (cursor.y < 5)
                    cursor.y = cursor.y + 1;
                else 
                    cursor.y = 0;
                redraw = true;
            }
        }
        else if(ino::digitalRead(ino::BTN_4) == ino::HIGH)
        {
            if (cursor.x > 0)
                cursor.x = cursor.x - 1;
            else
            {
                if (cursor.y > 0)
                {
                    cursor.y = cursor.y - 1;
                    cursor.x = 15;
                }
                else 
                {
                    cursor.y = 5;
                    cursor.x = 15;
                }
            }
            redraw = true;
        }
        else if(ino::digitalRead(ino::BTN_5) == ino::HIGH)
        {
            if (cursor.x < 15)
                cursor.x = cursor.x + 1;
            else
            {
                if (cursor.y < 5)
                {
                    cursor.y = cursor.y + 1;
                    cursor.x = 0;
                }
                else 
                {
                    cursor.y = 0;
                    cursor.x = 0;
                }
            }
            redraw = true;
        }
    }
    else if (ino::digitalRead(ino::BTN_5) == ino::HIGH)
    {
        if (canvas[cursor.x][cursor.y] < 255)
            canvas[cursor.x][cursor.y]++;
        else
            canvas[cursor.x][cursor.y] = 0;
        redraw = true;
    }
    else if (ino::digitalRead(ino::BTN_4) == ino::HIGH)
    {
        if (canvas[cursor.x][cursor.y] > 0)
            canvas[cursor.x][cursor.y]--;
        else
            canvas[cursor.x][cursor.y] = 255;
        redraw = true;
    }
}

function loop() 
{
    move();
    if (redraw == true)
    {
        oled::clear();
        oled::setColor(oled::WHITE);

        //footer
        oled::drawString(0, 56, atoi(canvas[cursor.x][cursor.y]));
        oled::drawLine(0, 54, 127, 54);
        drawBoard();
        oled::display();


        redraw = false;
    }
};