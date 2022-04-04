#include "graphics.h"
#include "gui.h"
#include "leaf.h"
#include "time.h"
#include "player.h"

void GameOrigin(void)
{
    initgraph(1200, 400);
    setcaption("风叶穿行 C语言版");
    PasteImage((char*)".\\Textures\\origin.png", 0, 0, NULL);

    music_over.OpenFile((char*)".\\Musics\\gameover.mp3");
    music_bgm.OpenFile((char*)".\\Musics\\windy_day.mp3");
    music_bgm.SetVolume(0.4);
    music_bgm.Play(0);

    mouse_msg msg;
    int mouse_x, mouse_y;
    for(; is_run(); delay_fps(100))
    {
        while (mousemsg()) msg = getmouse();
        mousepos(&mouse_x, &mouse_y);

        if(msg.is_down() && mouse_x >= 510 && mouse_x <= 675 && mouse_y >= 215 && mouse_y <= 330) break;
        if(msg.is_down() && mouse_x >= 0 && mouse_x <= 195 && mouse_y >= 340 && mouse_y <= 400)
            ShellExecute(NULL,"open","tutorial.exe",NULL,NULL,SW_SHOWNORMAL);
    }
}

void GameInit(void)
{
    srand(time(NULL));
    GuiInit();
    PlayerInit();
    LeafInit();
    for(int i = 3; i >= 1; i--)
    {
        GuiDraw();
        PasteImage(Link( Link( (char*)".\\Textures\\Digit\\", Myitoa(i)), (char*)".png"), 500, 20, NULL, TRANSPARENT, BLACK);
        delay_ms(1000);
    }
}

void GameLoop(void)
{
    for(; is_run(); delay_fps(40))
    {
        PlayerLoop();
        LeafLoop();

        //参考系移动
        player->x -= 4.8;
        for(int i = 0; i <= leaf_array->len - 1; i++) leaf_array->buf[i].x -= 4.8;

        GuiDraw();

        //判定游戏结束
        if(player->x < -24 || player->y > 460) return;

        //计算游戏时间
        if(++player->run_timer >= 40)
        {
            player->run_timer = 0;
            player->seconds++;
        }
    }
}

void GameOver(void)
{
    GuiOver();

    mouse_msg msg;
    int mouse_x, mouse_y;
    for(; is_run(); delay_fps(100))
    {
        while (mousemsg()) msg = getmouse();
        mousepos(&mouse_x, &mouse_y);

        if(msg.is_down() && mouse_x >= 760 && mouse_x <= 980 && mouse_y >= 32 && mouse_y <= 112) break;
        if(msg.is_down() && mouse_x >= 760 && mouse_x <= 980 && mouse_y >= 116 && mouse_y <= 196)
            ShellExecute(NULL,"open","https://www.bilibili.com/video/BV1bq4y1e7CD/", NULL, NULL, SW_SHOWNORMAL);
        if(msg.is_down() && mouse_x >= 760 && mouse_x <= 980 && mouse_y >= 204 && mouse_y <= 284)
            ShellExecute(NULL, "open","tutorial.exe", NULL, NULL, SW_SHOWNORMAL);
        if(msg.is_down() && mouse_x >= 760 && mouse_x <= 980 && mouse_y >= 292 && mouse_y <= 372) exit(0);
    }

}

int main()
{
    GameOrigin();
    do
    {
        GameInit();
        GameLoop();
        GameOver();
    }while(1);
}
