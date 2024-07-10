
function strsplit(string, separator)
{
    var result = {};
    var i = 0;
    
    while (string != "")
    {
        var index = str::chr(string, separator);
        if (index == -1)
        {
            result[i] = string;
            break;
        }
        else
        {
            result[i] = str::substr(string, 0, index);
            string = str::substr(string, index + 1);
        }
        i++;
    }
    return result;
}

var a = {};
a.b = {};
a.b.c = 99;
print(a.b.c);



strsplit("hello world", ' ');