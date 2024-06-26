﻿#include"all.h"



#include"all.h"
#include"Atlas.h"

#pragma once
#include<iostream>
#include<fstream>
#include<easyx.h>
#include<graphics.h>
#include<deque>
#include<vector>
#include<string>

void run(ExMessage& msg, int& cur, Atlas* container)
{
	int delt = (msg.vkcode) - (VK_LEFT + VK_RIGHT) / 2;//正负绝对左右移动
	cur = (cur + 1 * delt + static_cast<Atlas*>(container)->get_size()) % static_cast<Atlas*>(container)->get_size();
}
Atlas::Atlas(const char* rootdir, const char* name, int n, int w, int h)
{
	role_add_image(rootdir, name, n, w, h, ".png");
}
int Start::process_command(ExMessage& msg)
{
	int com = -1;
	for (int i = 0; i < buttons.size(); i++)
	{
		if (buttons[i]->in_area(msg))
		{
			com = buttons[i]->react(msg) ? i : -1;
			enter_scene();
			return com;
		}
	}
	return com;
}
void Start::enter_scene()
{
	cleardevice();
	draw_pic();
	return;
}

void Start::ChooseMap(ExMessage& msg)
{
	/*Button left;
	Button right;
	left.init("left");
	left.init("right");*/
	cleardevice();
	Anime::draw_back_img(this);
	//putimage(0, 0, back_ground->get_image(cur_back));
	while (1)
	{
		while (peekmessage(&msg, EX_KEY | EX_MOUSE))
		{
			if ((msg.vkcode == VK_LEFT || msg.vkcode == VK_RIGHT) && msg.message == WM_KEYUP)
			{
				int delt = (msg.vkcode) - (VK_LEFT + VK_RIGHT) / 2;//正负绝对左右移动
				cur_back = (cur_back + 1 * delt + back_ground.size()) % back_ground.size();
				//run(msg, cur_back, back_ground);
			}
			else if (msg.vkcode == VK_RETURN)
			{
				enter_scene();
				return;
			}
			cleardevice();
		}
		BeginBatchDraw();

		Anime::draw_back_img(this);
		settextstyle(50, 0, "consola");
		outtextxy(WORDX, (MAINH - 100), "就决定是你了");
 		EndBatchDraw();
		Sleep(15);
	}

}


Button::Button(const char* filename, const char* text_)
{
	this->images->add_image(BTDIR, filename, BTW, BTH, 1, ".ico");
	this->images->add_image(BTDIR, filename, BTW, BTH, 1, ".ico", MASK);
	text = string(text_);
}
int Button::react(ExMessage& msg)
{
	draw_words(HANGON);
	draw_lucency(x + wordsw + gap * 1.5, y, arrow, arrow + 1);
	while (in_area(msg))
	{
		peekmessage(&msg, EX_MOUSE);
		if (msg.lbutton)
		{
			draw_words(HANGON);
			draw_lucency(msg.x - 20, msg.y - 20, cursor, cursor + 1);
			while (msg.message != WM_LBUTTONUP)
			{
				peekmessage(&msg, EX_MOUSE);
			}
			if (in_area(msg))
			{
				draw_words(CLICKED);
				return true;
			}
			else
			{
				draw_words(UNIN);
				continue;
			}
		}
	}
}
entertain Start::setmode(ExMessage& msg)
{
	if (shot == NULL)
	{
		shot = new Atlas();
		shot->add_image("shot", "", MAINW, MAINH, 4);
	}
	setbkmode(OPAQUE);
	setfillcolor(RED);
	settextstyle(50, 20, "consola");
	cleardevice();
	putimage(0, 0, shot->get_image(cur_mode));
	outtextxy(MAINW / 2, MAINH / 20, &mode_explain[cur_mode][0]);
	while (1)
	{
		while (peekmessage(&msg, EX_KEY))
		{
			if ((msg.vkcode == VK_LEFT || msg.vkcode == VK_RIGHT) && msg.message == WM_KEYUP)
			{
				run(msg, cur_mode, shot);
			}
			else if (msg.vkcode == VK_RETURN)
			{
				enter_scene();
				return entertain(cur_mode);
			}
			else
			{
				continue;
			}
			cleardevice();
			putimage(0, 0, shot->get_image(cur_mode));
			outtextxy(MAINW / 2, MAINH / 20, &(mode_explain[cur_mode])[0]);
			outtextxy(0, 0, "按enter键选择模式");
		}
	}

}
#include"Anime.h"
void Anime::draw_back_img(Start* se)
{
	if ((se->back_frame)[(se->cur_back)] / 3 >= (se->back_ground)[(se->cur_back)].get_size() - 1)
	{
		(se->back_frame)[se->cur_back] = 0;
	}
	else
	{
		++(se->back_frame)[se->cur_back];
	}
	putimage(0, 0, se->back_ground[se->cur_back].get_image(se->back_frame[se->cur_back] / 3));
}

