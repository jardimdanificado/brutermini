

local redraw = true;
local cursor = {x = 1, y = 1};
local canvas = 
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
local x = 1;
local y = 1;


function buttonDown(button)
    return digitalRead(button) == HIGH;
end


function drawBoard()
    for x = 0, 15 do
        for y = 0, 5 do
            if (cursor.x == x+1 and cursor.y == y+1) then
                oled_setColor(WHITE);
                oled_fillRect(x * 8, y * 8, 8, 8);
                oled_setColor(BLACK);
            end
            oled_drawString(x * 8, y * 8, string.char(canvas[x+1][y+1]));
            oled_setColor(WHITE);
        end
    end
end

function move()
    if buttonDown(BTN_1) then
        if buttonDown(BTN_2) then
            if buttonDown(BTN_4) then
                if cursor.y > 1 then
                    cursor.y = cursor.y - 1
                else
                    cursor.y = 6
                end
                redraw = true
            elseif buttonDown(BTN_5) then
                if cursor.y < 6 then
                    cursor.y = cursor.y + 1
                else
                    cursor.y = 1
                end
                redraw = true
            end
        elseif buttonDown(BTN_4) then
            if cursor.x > 1 then
                cursor.x = cursor.x - 1
            else
                if cursor.y > 1 then
                    cursor.y = cursor.y - 1
                    cursor.x = 16
                else
                    cursor.y = 6
                    cursor.x = 16
                end
            end
            redraw = true
        elseif buttonDown(BTN_5) then
            if cursor.x < 16 then
                cursor.x = cursor.x + 1
            else
                if cursor.y < 6 then
                    cursor.y = cursor.y + 1
                    cursor.x = 1
                else
                    cursor.y = 1
                    cursor.x = 1
                end
            end
            redraw = true
        end
    elseif buttonDown(BTN_5) then
        if canvas[cursor.x][cursor.y] < 255 then
            canvas[cursor.x][cursor.y] = canvas[cursor.x][cursor.y] + 1
        else
            canvas[cursor.x][cursor.y] = 0
        end
        redraw = true
    elseif buttonDown(BTN_4) then
        if canvas[cursor.x][cursor.y] > 0 then
            canvas[cursor.x][cursor.y] = canvas[cursor.x][cursor.y] - 1
        else
            canvas[cursor.x][cursor.y] = 255
        end
        redraw = true
    end
end

oled_init();

function loop()
    move();
    if redraw == true then
        oled_clear();
        oled_setColor(WHITE);
        oled_drawString(0, 56, canvas[cursor.x][cursor.y] .. "");
        oled_drawLine(0, 54, 127, 54);
        drawBoard();
        oled_display();
        redraw = false;
    end
    delay(10);
end

