#include "gui.h"

GUI gui;
MUSIC music_over;
MUSIC music_bgm;

void GuiInit(void)
{
    cleardevice(gui.msg);
    PasteImage((char*)".\\Textures\\background.png", 0, 0, gui.background);
    music_bgm.SetVolume(0.4);
}

void GuiDraw(void)
{
    cleardevice(gui.animation);
    cleardevice(gui.leaf);
    cleardevice(gui.player);
    cleardevice(gui.text);

    PasteImage((char*)".\\Textures\\background.png", 0, 0, gui.background);
    putimage_transparent(NULL, gui.background, 0, 0, BLACK);

    if(player->seconds == 0) PasteImage((char*)".\\Textures\\go.png", 700, 100, gui.animation, TRANSPARENT, BLACK);
    if(player->seconds / 30 && player->seconds % 30 >= 0 && player->seconds % 30 < 5)
    {
        int pos = 1200 - 300 * (player->seconds % 30) - 7.5 * player->run_timer;
        PasteImage((char*)".\\Textures\\magpie.png", pos, 70, gui.animation, TRANSPARENT, BLACK);
        setbkmode(TRANSPARENT);
        setcolor(EGERGB(195, 132, 19), gui.animation);
        setfont(35, 0, "宋体", gui.animation);
        outtextxy(pos + 50, 125, Myitoa(player->seconds / 30 * 30), gui.animation);
    }
    putimage_transparent(NULL, gui.animation, 0, 0, BLACK);

    for(int i = 0; i <= leaf_array->len - 1; i++)
        PasteImage( Link( Link( (char*)".\\Textures\\Leaf\\leaf_", Myitoa(leaf_array->buf[i].style) ), (char*)".png"),
                    leaf_array->buf[i].x - leaf_property[leaf_array->buf[i].style].width / 2, leaf_array->buf[i].y,
                    gui.leaf, TRANSPARENT, BLACK);
    putimage_transparent(NULL, gui.leaf, 0, 0, BLACK);

    char str[121] = ".\\Textures\\State\\";
    switch(player->state)
    {
    case RUN:
    {
        strcat(str, "run_");
        if(player->direct == 0) strcat(str, "right.png");
        else strcat(str, "left.png");
        break;
    }
    case JUMP:
    {
        strcat(str, "jump_");
        if(player->direct == 0) strcat(str, "right.png");
        else strcat(str, "left.png");
        break;
    }
    case FALL:
    {
        strcat(str, "fall_");
        if(player->direct == 0) strcat(str, "right.png");
        else strcat(str, "left.png");
        break;
    }
    case GRAB:
    {
        strcat(str, "grab_");
        if(player->direct == 0) strcat(str, "right.png");
        else strcat(str, "left.png");
        break;
    }
    case HANG:
    {
        strcat(str, "hang.png");
        break;
    }
    case FLY:
    {
        strcat(str, "fly.png");
        break;
    }
    }
    PasteImage(str, player->x - 24, player->y - 60, gui.player, TRANSPARENT, BLACK);
    putimage_transparent(NULL, gui.player, 0, 0, BLACK);

    int digits = player->seconds ? (int)(log(player->seconds) / log(10)) : 0;
    for(int i = 0; i <= digits; i++)
        PasteImage(Link( Link( (char*)".\\Textures\\Digit\\", Myitoa(player->seconds / (int)pow(10, i) % 10)), (char*)".png"),
                   1140 - 48 * i, 60, gui.player, TRANSPARENT, BLACK);

    putimage_transparent(NULL, gui.text, 0, 0, BLACK);

    if(music_bgm.GetPlayStatus() == MUSIC_MODE_STOP) music_bgm.Play(0);
}

void GuiOver(void)
{
    music_bgm.SetVolume(0.1);
    music_over.Play(0);

    setcolor(BLACK, gui.msg);
    setfillcolor(BLACK, gui.msg);
    for(int r = 500; r >= 100; r -= 10)
    {
        circle(player->x, player->y, r, gui.msg);
        //填充圆外部分,由于r较大时区域不连续,故每1°进行填充1次,实测不影响运行速度
        for(int deg = -90; deg <= 180; deg += 1)
            floodfill(player->x + (r + 2) * cos(deg * 3.1415 / 180), player->y - (r + 2) * sin(deg * 3.1415 / 180), BLACK, gui.msg);
        putimage(0, 0, gui.msg);
        delay_ms(10);
    }

    delay_ms(100);
    PasteImage((char*)".\\Textures\\background.png", 0, 0, gui.background);
    putimage_transparent(NULL, gui.background, 0, 0, BLACK);

    PasteImage((char*)".\\Textures\\gameover.png", 200, 0, gui.msg, TRANSPARENT, BLACK);
    setbkmode(TRANSPARENT);

    setcolor(EGERGB(146, 192, 24), gui.msg);
    setfont(70, 0, "宋体", gui.msg);
    outtextxy(310, 185, Myitoa(player->seconds), gui.msg);
    putimage_transparent(NULL, gui.msg, 0, 0, BLACK);

    int rate;
    if(player->seconds <= 3) rate = 10;
    else if(player->seconds >= 4 && player->seconds <= 7) rate = 25;
    else if(player->seconds >= 8 && player->seconds <= 12) rate = 50;
    else if(player->seconds >= 13 && player->seconds <= 25) rate = 70;
    else if(player->seconds >= 26 && player->seconds <= 39) rate = 90;
    else if(player->seconds >= 40 && player->seconds <= 95) rate = 95;
    else rate = 99;

    char str1[121] = "", str2[121] = "";
    switch(rate)
    {
    case 10:
    {
        switch(rand() % 2)
        {
        case 0:
        {
            strcpy(str1, "是什么糊住了22");
            strcpy(str2, "眼睛？是风！");
            break;
        }
        case 1:
        {
            strcpy(str1, "落地成盒，虾仁");
            strcpy(str2, "猪心 (ノへ￣、");
            break;
        }
        }
        break;
    }
    case 25:
    {
        switch(rand() % 2)
        {
        case 0:
        {
            strcpy(str1, "身残志坚，答应22");
            strcpy(str2, "不要放弃治疗！");
            break;
        }
        case 1:
        {
            strcpy(str1, "这河狸吗？");
            strcpy(str2, "o(一︿一+)o");
            break;
        }
        }
        break;
    }
    case 50:
    {
        switch(rand() % 2)
        {
        case 0:
        {
            strcpy(str1, "就这，绝对不是");
            strcpy(str2, "我 (°ー°〃)");
            break;
        }
        case 1:
        {
            strcpy(str1, "是意外啦，22绝");
            strcpy(str2, "不会轻易狗带！");
            break;
        }
        }
        break;
    }
    case 70:
    {
        switch(rand() % 3)
        {
        case 0:
        {
            strcpy(str1, "再接再厉，");
            strcpy(str2, "芜湖起飞！");
            break;
        }
        case 1:
        {
            strcpy(str1, "22必不能");
            strcpy(str2, "轻易认输！");
            break;
        }
        case 2:
        {
            strcpy(str1, "是时候展现");
            strcpy(str2, "真正的技术了！");
            break;
        }
        }
        break;
    }
    case 90:
    case 95:
    {
        switch(rand() % 2)
        {
        case 0:
        {
            strcpy(str1, "平平无奇小天才");
            strcpy(str2, "ㄟ( ▔, ▔ )ㄏ");
            break;
        }
        case 1:
        {
            strcpy(str1, "不愧是你，");
            strcpy(str2, "22拯救者！");
            break;
        }
        }
        break;
    }
    case 99:
    {
        switch(rand() % 2)
        {
        case 0:
        {
            strcpy(str1, "天赋异禀·疾风征服");
            strcpy(str2, "者·被22选中的人！");
            break;
        }
        case 1:
        {
            strcpy(str1, "成就达成，");
            strcpy(str2, "进击的22！");
            break;
        }
        }
        break;
    }
    }

    setfont(25, 0, "宋体", gui.msg);
    setcolor(EGERGB(105, 159, 160), gui.msg);
    outtextxy(540, 120, "你超过了", gui.msg);
    outtextxy(540, 150, "的玩家！", gui.msg);
    outtextxy(540, 210, str1, gui.msg);
    outtextxy(540, 240, str2, gui.msg);

    setcolor(EGERGB(146, 192, 24), gui.msg);
    outtextxy(640, 120, Link(Myitoa(rate), (char*)"%"), gui.msg);
}
