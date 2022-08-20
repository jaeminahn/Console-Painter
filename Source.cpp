#include <iostream>
#include <string>
#include <windows.h>
using namespace std;
using std::cout;

void setcolor(int ForgC, int BackC) // 색깔 지정
{
	WORD wColor = ((BackC & 0x0F) << 4) + (ForgC & 0x0F);;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), wColor);
}

void mc(int *x, int *y) //마우스 클릭 좌표 가져오기
{
	HANDLE hIn, hOut;
	DWORD dwNOER;
	INPUT_RECORD rec;

	hIn = GetStdHandle(STD_INPUT_HANDLE);
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleMode(hIn, ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT);

	while (TRUE) {
		ReadConsoleInput(hIn, &rec, 1, &dwNOER);

		if (rec.EventType == MOUSE_EVENT)
		{
			if (rec.Event.MouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED)
			{
				*x = rec.Event.MouseEvent.dwMousePosition.X;
				*y = rec.Event.MouseEvent.dwMousePosition.Y;
				return;
			}
		}
	}
}

void gotoxy(int x, int y) //좌표 이동
{
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void hidecursor(void) //커서 숨기기
{
	CONSOLE_CURSOR_INFO curInfo;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
	curInfo.bVisible = 0;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
}

void showcursor(void) //커서 보이기
{
	CONSOLE_CURSOR_INFO curInfo;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
	curInfo.bVisible = 1;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
}

void modeup(int i, int j) //메뉴 안보이기
{
	for (i = 0; i <= j; i++)
	{
		gotoxy(i, 1);
		cout << " ";
	}
}

int main()
{
	system("title Painter 1.3"); //타이틀

	hidecursor();
	system(" mode con lines=45 cols=80"); //창 크기

start:

	int x, y;
	int f = 7;
	char a = '*';
	string str;

	//----------------------------------------------------
	//-------------------------------------------상단 메뉴

	gotoxy(0, 0);

	cout << ' ';

	setcolor(0, 7);
	cout << " Eraser ";
	setcolor(7, 0);

	cout << ' ';

	setcolor(0, 7);
	cout << " Pencil ";
	setcolor(7, 0);

	cout << ' ';

	setcolor(0, 7);
	cout << " Reset ";
	setcolor(7, 0);


	gotoxy(56, 0);
	setcolor(15, 8);
	cout << " Pencil Mode ";
	setcolor(7, 0);

	gotoxy(70, 0);
	setcolor(15, 8);
	cout << " Palette ";
	setcolor(7, 0);

	gotoxy(0, 2);
	cout << "--------------------------------------------------------------------------------";


	while (1)
	{
		mc(&x, &y);

		if (y == 0 && x >= 1 && x <= 8) //eraser 버튼
		{
			a = ' ';
		}

		else if (y == 0 && x >= 10 && x <= 17) //pencil 버튼
		{
			if (a != '@' && a != '#' && a != '$' && a != '+' && a != '=' && a != '.' && a != '&') a = '*';
		}

		else if (y == 0 && x >= 19 && x <= 25) //reset 버튼
		{
			system("cls"); //화면 삭제
			setcolor(7, 0); //색상 초기화
			goto start; //처음으로
		}

		//----------------------------------------------------
		//--------------------------연필 모드 목록 출력 & 버튼

		else if (y == 0 && x >= 56 && x <= 68)
		{
			setcolor(7, 0);
			gotoxy(0, 1);
			cout << "[@] ";
			cout << "[#] ";
			cout << "[$] ";
			cout << "[*] ";
			cout << "[+] ";
			cout << "[=] ";
			cout << "[.] ";
			cout << "[&] ";
			cout << "[?] ";
			cout << "[!] ";
			setcolor(f, 0); //원래 색 복원

			while (1)
			{
				mc(&x, &y);

				if (y == 0 && x >= 56 && x <= 68) //연필 모드 재클릭
				{
					modeup(0, 50);
					break;
				}

				else if (y == 1 && x >= 0 && x <= 2) //@
				{
					a = '@';
					modeup(0, 50);
					break;
				}

				else if (y == 1 && x >= 4 && x <= 6) //#
				{
					a = '#';
					modeup(0, 50);
					break;
				}

				else if (y == 1 && x >= 8 && x <= 10) //$
				{
					a = '$';
					modeup(0, 50);
					break;
				}

				else if (y == 1 && x >= 12 && x <= 14) //*
				{
					a = '*';
					modeup(0, 50);
					break;
				}

				else if (y == 1 && x >= 16 && x <= 18) //+
				{
					a = '+';
					modeup(0, 50);
					break;
				}

				else if (y == 1 && x >= 20 && x <= 22) //=
				{
					a = '=';
					modeup(0, 50);
					break;
				}

				else if (y == 1 && x >= 24 && x <= 26) //.
				{
					a = '.';
					modeup(0, 50);
					break;
				}

				else if (y == 1 && x >= 28 && x <= 30) //&
				{
					a = '&';
					modeup(0, 50);
					break;
				}

				else if (y == 1 && x >= 32 && x <= 34) //?
				{
					a = '?';
					modeup(0, 50);
					break;
				}

				else if (y == 1 && x >= 36 && x <= 38) //!
				{
					a = '!';
					modeup(0, 50);
					break;
				}
			}
		}

		//----------------------------------------------------
		//--------------------------색상 모드 목록 출력 & 버튼

		else if (y == 0 && x >= 70 && x <= 78)
		{
			gotoxy(0, 1);
			setcolor(0, 12); //12 빨강
			cout << ' ';
			setcolor(7, 0);

			cout << " ";

			setcolor(0, 9); //9 파랑
			cout << ' ';
			setcolor(7, 0);

			cout << " ";

			setcolor(0, 10); //10 초록
			cout << ' ';
			setcolor(7, 0);

			cout << " ";

			setcolor(0, 14); //14 노랑
			cout << ' ';
			setcolor(7, 0);

			cout << " ";

			setcolor(0, 11); //11 민트
			cout << ' ';
			setcolor(7, 0);

			cout << " ";

			setcolor(0, 13); //13 보라
			cout << ' ';
			setcolor(7, 0);

			cout << " ";

			setcolor(0, 7); //7 하양
			cout << ' ';
			setcolor(7, 0);

			setcolor(f, 0); //원래 색 복원

			while (1)
			{
				mc(&x, &y);

				if (y == 0 && x >= 70 && x <= 78) //색상 모드 재클릭
				{
					modeup(0, 50);
					break;
				}

				else if (y == 1 && x == 0) //빨강
				{
					f = 12;
					setcolor(f, 0);
					modeup(0, 50);
					break;
				}

				else if (y == 1 && x == 2) //파랑
				{
					f = 9;
					setcolor(f, 0);
					modeup(0, 50);
					break;
				}

				else if (y == 1 && x == 4) //초록
				{
					f = 10;
					setcolor(f, 0);
					modeup(0, 50);
					break;
				}

				else if (y == 1 && x == 6) //노랑
				{
					f = 14;
					setcolor(f, 0);
					modeup(0, 50);
					break;
				}

				else if (y == 1 && x == 8) //민트
				{
					f = 11;
					setcolor(f, 0);
					modeup(0, 50);
					break;
				}

				else if (y == 1 && x == 10) //보라
				{
					f = 13;
					setcolor(f, 0);
					modeup(0, 50);
					break;
				}

				else if (y == 1 && x == 12) //하양
				{
					f = 7;
					setcolor(f, 0);
					modeup(0, 50);
					break;
				}
			}
		}

		gotoxy(x, y);

		if (y > 2)
		{
			cout << a;
		}
	}

	return 0;
}
