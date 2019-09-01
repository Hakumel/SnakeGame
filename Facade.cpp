
void Facade::initial_game()
{
	wall* wl = wall::getdata();
	wl->drawwall();
	snake sk(wl);
	sk.initial();
	Food* fd = Food::getdata();
	fd->setFood();
	bool gametag = true;
	bool gamerestart = true;
	char prekey = '\0';
	while (true)
	{
		while (gametag)
		{
			char key = _getch();
			if ((key != 'w' && key != 's' && key != 'd' && key != 'a') || ((key == 'a' && prekey == 'd') || (key == 'w' && prekey == 's') || (key == 's' && prekey == 'w') || (key == 'd' && prekey == 'a')))
			{
				key = prekey;
			}
			if ((prekey == '\0' && key == 'a') || key == '\0')
			{
				continue;
			}
			while (!_kbhit())//无打入返回0
			{
				if (sk.move(key))
				{
					/*system("cls");
					wl->drawwall();*/
					Sleep(snake::getFlushT());
				}
				else
				{
					gametag = false;
					break;
				}
			}
		}
		std::cout << "输入y 再次开始， 其他结束。" << std::endl;
		if (_getch() == 'y')
		{
			system("cls");
			wl->clanwall();
			wl->drawwall();
			sk.initial();
			fd->setFood();
			gametag = true;
		}
		else
		{
			break;
		}
	}

}
