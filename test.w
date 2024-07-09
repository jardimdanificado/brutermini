struct vec2(x,y)
{
    var x = x;
    var y = y;
};
var redraw = true;
var cursor = vec2(0, 0);
var canvas[][] = 
{
    {46,46,46,46,46,46},
    {46,46,46,46,46,46},
    {46,46,46,46,46,46},
    {46,46,46,46,46,46},
    {46,46,46,46,46,46},
    {46,46,46,46,46,46},
    {46,46,46,46,46,46},
    {46,46,46,46,46,46},
    {46,46,46,46,46,46},
    {46,46,46,46,46,46},
    {46,46,46,46,46,46},
    {46,46,46,46,46,46},
    {46,46,46,46,46,46},
    {46,46,46,46,46,46},
    {46,46,46,46,46,46},
    {46,46,46,46,46,46},
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
                setColor(ino::WHITE);
                fillRect(i * 8, j * 8, 8, 8);
                setColor(ino::BLACK);
            }
            tempstr[0] = canvas[i][j];
            drawString(i * 8, j * 8, tempstr);
            setColor(ino::WHITE);
        }
    }
}

function setup() 
{
    init();
    flipScreenVertically();
    pinMode(ino::BTN_1, ino::INPUT);
    pinMode(ino::BTN_2, ino::INPUT);
    pinMode(ino::BTN_3, ino::INPUT);
    pinMode(ino::BTN_4, ino::INPUT);
    pinMode(ino::BTN_5, ino::INPUT);
    pinMode(ino::BUZZER, ino::OUTPUT);
}

function move()
{
    if (digitalRead(ino::BTN_1) == ino::HIGH)
    {
        print("BTN1\n");
        if (digitalRead(ino::BTN_2) == ino::HIGH)
        {
            print("BTN2\n");
            if(digitalRead(ino::BTN_4) == ino::HIGH)
            {
                print("BTN4\n");
                cursor.y = cursor.y - 1;
                redraw = true;
            }
            else if(digitalRead(ino::BTN_5) == ino::HIGH)
            {
                print("BTN5\n");
                cursor.y = cursor.y + 1;
                redraw = true;
            }
        }
        else if(digitalRead(ino::BTN_4) == ino::HIGH)
        {
            print("BTN4\n");
            cursor.x = cursor.x - 1;
            redraw = true;
        }
        else if(digitalRead(ino::BTN_5) == ino::HIGH)
        {
            print("BTN5\n");
            cursor.x = cursor.x + 1;
            redraw = true;
        }
    }
}

function loop() 
{
    move();
    if (redraw == true)
    {
        clear();
        setColor(ino::WHITE);
        drawLine(0, 51, 127, 51);
        drawBoard();
        display();
        redraw = false;
    }
};