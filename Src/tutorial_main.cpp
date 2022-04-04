#include "graphics.h"
#include "app.h"

int main()
{
    initgraph(800, 400);
    setcaption("风叶穿行教程");
    int page = 0;
    mouse_msg msg;
    int mouse_x, mouse_y;
    for(; is_run(); delay_fps(10))
    {
        while (mousemsg()) msg = getmouse();
        mousepos(&mouse_x, &mouse_y);
        PasteImage((char*)".\\Textures\\Tutorial\\background.png", 0, 0, NULL);
        PasteImage( Link( Link((char*)".\\Textures\\Tutorial\\tutorial_", Myitoa(page)), (char*)".png"), 0, 0, NULL, TRANSPARENT, BLACK);
        if(msg.is_down() && mouse_x >= 560 && mouse_x <= 780 && mouse_y >= 180 && mouse_y <= 256)
        {
            if(page < 10) page++;
            else return 0;
        }
        if(msg.is_down() && mouse_x >= 560 && mouse_x <= 780 && mouse_y >= 264 && mouse_y <= 340 && page > 0) page--;
        if(msg.is_down() && mouse_x >= 510 && mouse_x <= 570 && mouse_y >= 50 && mouse_y <= 110) return 0;
    }
}
