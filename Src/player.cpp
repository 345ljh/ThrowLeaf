#include "player.h"

PLAYER* player;

void PlayerInit(void)
{
    player = (PLAYER*)malloc(sizeof(PLAYER));
    player->direct = 0;
    player->speed_y = 0;
    player->state = HANG;
    player->x = 600;
    player->y = 340;
    player->grab_timer = 0;
    player->support = 2;
    player->run_timer = 0;
    player->seconds = 0;
}

void PlayerLoop(void)
{
    if(player->state != FLY)
    {
        char key_message = 0;
        //同时检测4个按键
        if (kbmsg())
        {
            for(int i = 0; i <= 3; i++)
            {
                if(GetKeyState('J') < 0 || GetKeyState('W') < 0 || GetKeyState(38) < 0 || GetKeyState(' ') < 0) key_message |= 1;
                if(GetKeyState('A') < 0 || GetKeyState(37) < 0) key_message |= 2;
                if(GetKeyState('D') < 0 || GetKeyState(39) < 0) key_message |= 4;
                if(GetKeyState('K') < 0 || GetKeyState('Z') < 0) key_message |= 8;
            }
        }

        //当抓取判定大于5时可进行抓取判定,否则为冷却时间
        if(player->grab_timer > 0) player->grab_timer--;
        if(player->state != HANG)
        {
            if(player->grab_timer >= 4) player->state = GRAB;
            //根据y方向速度改变三种状态
            else player->state = player->speed_y > 0 ? FALL : (player->speed_y < 0 ? JUMP : RUN);
        }

        //抓取判定
        if(player->state == GRAB || player->state == HANG)
        {
            int isgrab = 0;  //确定是否抓取成功,考虑深色叶断裂后的情形
            for(int i = 0; i <= leaf_array->len - 1; i++)
            {
                if(fabs(player->x + ( (player->state != HANG) * (20 - 40 * player->direct) ) - leaf_array->buf[i].x) <= (5 + 20 * (player->state == HANG)) &&
                        player->y - (20 + 40 * (player->state == HANG)) <= leaf_array->buf[i].y + leaf_property[leaf_array->buf[i].style].height &&
                        player->y - (20 + 40 * (player->state == HANG)) >= leaf_array->buf[i].y + leaf_property[leaf_array->buf[i].style].height - leaf_property[leaf_array->buf[i].style].stem_len)
                    //根据状态调整手的判定点与范围
                {
                    if(leaf_array->buf[i].style != 5)
                    {
                        player->speed_y = 0;
                        player->support = 2;
                        if(player->state == GRAB)
                        {
                            player->state = HANG;
                            player->y += 40;
                        }
                        player->grab_timer = 0;
                        player->x = leaf_array->buf[i].x;
                        if(leaf_array->buf[i].style == 4 && !leaf_array->buf[i].destroy_time) leaf_array->buf[i].destroy_time++;
                        isgrab = 1;
                    }
                    else
                    {
                        array_delete(leaf_array, i);
                        player->state = FLY;
                        player->x -= 21;
                        player->y = leaf_array->buf[i].y + 26;
                        player->fly_timer = 400;
                    }
                    break;
                }
            }
            if(!isgrab)
            {
                if(player->state == HANG) player->state = FALL;
                player->support = 0;
            }
        }

        //支撑状态
        if(player->speed_y >= 0 && player->support != 2)
        {
            player->support = 0;
            //依次检测是否在叶片上
            for(int i = 0; i <= leaf_array->len - 1; i++)
            {
                if(fabs(player->x - leaf_array->buf[i].x) <= leaf_property[leaf_array->buf[i].style].width / 2 &&
                        fabs(player->y - leaf_array->buf[i].y - 24) < 10)
                {
                    if(leaf_array->buf[i].style != 5)
                    {
                        player->speed_y = 0;
                        player->support = 1;
                        player->y = leaf_array->buf[i].y + 26;
                        player->state = RUN;
                        if(leaf_array->buf[i].style == 4 && !leaf_array->buf[i].destroy_time) leaf_array->buf[i].destroy_time++;
                    }
                    else
                    {
                        array_delete(leaf_array, i);
                        player->state = FLY;
                        player->x -= 21;
                        player->fly_timer = 400;
                    }
                    break;
                }
            }
        }

        //根据按键更新人物状态
        //跳跃
        if( (key_message & 1) && player->support)
        {
            player->speed_y = -12;
            player->state = JUMP;
            player->grab_timer = 0;  //刷新抓取冷却
            player->support = 0;
        }
        //向左右移动
        if( (key_message & 2) && player->support != 2)
        {
            player->x -= 5.6;
            player->direct = 1;
        }
        if( (key_message & 4) && player->support != 2)
        {
            player->x += 5.6;
            player->direct = 0;
        }
        //伸手
        if( (key_message & 8) && !player->grab_timer && player->support != 2)
        {
            player->grab_timer = 20;
        }

        //y方向运动
        player->y += player->speed_y;
        if(player->state != HANG) player->speed_y += 0.6;
    }
    //飞行状态
    else
    {
        double flyspeed;
        if(player->x > 800) flyspeed = 4.8;
        else flyspeed = 6.6 * pow(2.71828, log(4.8 / 6.6) / 800.0 * player->x);
        player->x += flyspeed;  //若x坐标小于800则相对参考系前进
        player->fly_timer--;
        player->grab_timer = 0;
        char key_message = GetKeyState('J') < 0;
        if(key_message) //跳跃解除飞行状态
        {
            player->speed_y = -12;
            player->state = JUMP;
            player->fly_timer = 0;
            player->support = 0;
        }
        if(player->fly_timer <= 0)
        {
            player->state = RUN;
            player->direct = 0;

        }
        if(player->state != FLY) LeafInsert(player->x, player->y - 26);
    }
}
