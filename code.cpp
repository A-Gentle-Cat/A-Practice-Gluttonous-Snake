#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <cstring>
#include <windows.h>
#include <algorithm>

using namespace std;

int n = 50;  //nΪ��ͼ��С 
char ori_map[100][100];
int snake_map[100][100];
int now_dr;  //��¼��ǰ���� 
int lenth;  //��¼��ǰ�ߵĳ��� 
int snake_p[300000][2];  //0��x��1��y
int xx, yy;
bool flag = true;
int food_s;  //��¼��û�гԵ�ʳ�� 
int temp_sum;
int score[1000];
int play_time;

void check_cin();
void gotoxy(unsigned char x,unsigned char y);
void move_snake(int dr);
void food_system();

//ת�ƹ�� 
void gotoxy(unsigned char x,unsigned char y){
    //COORD��Windows API�ж����һ�ֽṹ����ʾһ���ַ��ڿ���̨��Ļ�ϵ�����
    COORD cor;
    //��� 
    HANDLE hout;
    //�趨����Ҫ��λ�������� 
    cor.X = x;
    cor.Y = y;
    //GetStdHandle������ȡһ��ָ���ض���׼�豸�ľ����������׼���룬��׼����ͱ�׼����
    //STD_OUTPUT_HANDLE���Ǵ�����׼�����Ҳ������ʾ�����ĺ� 
    hout = GetStdHandle(STD_OUTPUT_HANDLE);
    //SetConsoleCursorPosition�����������ÿ���̨����λ��
    SetConsoleCursorPosition(hout, cor);
}
void temp_test()
{
	gotoxy(0, 45);
	cout << "cycle number = " << temp_sum++;
}

void origin_makemap() //��ʼ����ͼ
{
	for(int i = 0; i < n/2; i++){
		if(i == 0 || i == n/2-1){
			for(int j = 0; j < n; j++){
				ori_map[i][j] = '*';
			for(int j = n+3; j <= n+23; j++)
				ori_map[i][j] = '~';
			}
		}
		else{
			ori_map[i][0] = '*';
			for(int j = 1; j < (n-2); j++)
				ori_map[i][j] = ' ';
			ori_map[i][n-1] = '*';
			ori_map[i][n+3] = '~';
			ori_map[i][n+22] = '~';
		}
	}
}

void put_map()//�������
{
//	bool f = false;
	for(int i = 0; i < n/2; i++){
		for(int j = 0; j < n+23; j++){
			if(i == 2 && j == n+10){
				cout << "���ְ�";
				for(int k = j; k < n+16; k++)
					cout << " ";
				cout << '~';
				break;
//				f = true;
			}
			printf("%c", ori_map[i][j]);	
		}
		cout << endl;
	}
	printf("\n\n");
	for(int i = 0; i < n/4; i++){
		if(i == 0 || i == n/4-1)
			for(int j = 0; j < 40; j++)
				printf("-");
		else{
			if(i == 1){
				cout << "��ǰ���ȣ�" << lenth;;
				for(int j = 12; j < 40; j++)
					cout << " ";
			}
			else{
				for(int j = 1; j < 40; j++)
					cout << " ";
			}
			cout << "-"; 
		}
		cout << endl;
	}
//	for(int i = 0; i < lenth; i++){
//		printf("\nx = %d y = %d\n", snake_p[i][0], snake_p[i][1]);
//	}
}

void rand_num(int x)
{
	srand(time(NULL));
	for(int i = 0; i < 5; i++){
//		Sleep();
		int t = rand();
		x = (x+i)*t+t % 19260817;
	}
}


//��ʼ���ߵ�λ�� 
void origin_player_place()
{
	srand(time(NULL));
	do{
//		cout << 1;
//		temp_test();
		xx = rand() % 50;
		yy = rand() % 50;
//		printf("xx = %d yy = %d\n", xx, yy);
//		if(xx <= 13 || y >= 40) continue;
	}while(xx <= 10 || xx >= 20 || yy <= 13 || yy >= 42);
	snake_map[xx][yy] = 1;
	ori_map[xx][yy] = 64;
	now_dr = rand() % 4;  //1��2��3��4��
	//��¼��ͷλ�� 
	switch (now_dr){
		case 0:
			for(int i = 1; i <= 4; i++){
				ori_map[xx+i][yy] = 62;
				snake_p[++lenth][0] = xx+i;
				snake_p[lenth][1] = yy;
			}
			break;
		case 1:
			for(int i = 1; i <= 4; i++){
				ori_map[xx-i][yy] = 62;
				snake_p[++lenth][0] = xx-i;
				snake_p[lenth][1] = yy;
			}
			break;
		case 2:
			for(int i = 1; i <= 4; i++){
				ori_map[xx][yy+i] = 62;
				snake_p[++lenth][0] = xx;
				snake_p[lenth][1] = yy+i;
			}
			break;
		case 3:
			for(int i = 1; i <= 4; i++){
				ori_map[xx][yy-i] = 62;
				snake_p[++lenth][0] = xx;
				snake_p[lenth][1] = yy-i;
			}
			break;
	}
	snake_p[0][0] = xx;
	snake_p[0][1] = yy;
	//��¼��ʼ�ߵ�λ�� 
	for(int i = 0; i <= lenth; i++){
		snake_map[snake_p[i][0]][snake_p[i][1]] = 1;
	}
//	gotoxy(snake_p[0][0], snake_p[0][1]);
//	printf("x = %d y = %d\n", xx, yy);
}

//ת�� 
void switch_dr(char dr)
{
	switch (dr){
		case 'w':
		case 'W':
			now_dr = 0;
			break;
		case 's':
		case 'S':
			now_dr = 1;
			break;
		case 'a':
		case 'A':
			now_dr = 2;
			break;
		case 'd':
		case 'D':
			now_dr = 3;
			break;
	}
}

//�����ж� 
bool rule_judge_s(int tx, int ty)
{
	switch (now_dr){
		case 0:
			if(snake_map[tx-1][ty] == 1)
				return false;
			break;
		case 1:
			if(snake_map[tx+1][ty] == 1)
				return false;
			break;
		case 2:
			if(snake_map[tx][ty-1] == 1)
				return false;
			break;
		case 3:
			if(snake_map[tx][ty+1] == 1)
				return false;
			break;
	}
	return true;
}

bool rule_judge()
{
	int tx = snake_p[0][0];
	int ty = snake_p[0][1];
	if(ori_map[tx][ty] == '*'){
		gotoxy(0, 28);
		cout << "GAME OVER! ";
		cout << "����ǽ��\n";
		return false;
	}
	else if(!rule_judge_s(tx, ty)){
		gotoxy(0, 28);
		cout << "GAME OVER! ";
		cout << "�� �� �� �� ��\n";
	}
	else return true;
}

//�ƶ� 
void move_snake(int dr)
{
	//������� 
	for(int i = 0; i <= lenth; i++){
		int tx = snake_p[i][0];
		int ty = snake_p[i][1];
		snake_map[tx][ty] = 0;
	}
//	printf("lenth = %d\n", lenth);
	int temp_x;
	int temp_y;
//	int ex, ey;
	switch (dr){
		case 0:
			temp_x = snake_p[0][0]-1;
			temp_y = snake_p[0][1];
			for(int i = 0; i <= lenth; i++){
				swap(temp_x, snake_p[i][0]);
				swap(temp_y, snake_p[i][1]);
			}
			break;
		case 1:
			temp_x = snake_p[0][0]+1;
			temp_y = snake_p[0][1];
			for(int i = 0; i <= lenth; i++){
				swap(temp_x, snake_p[i][0]);
				swap(temp_y, snake_p[i][1]);
			}
			break;
		case 2:
			temp_x = snake_p[0][0];
			temp_y = snake_p[0][1]-1;
			for(int i = 0; i <= lenth; i++){
				swap(temp_x, snake_p[i][0]);
				swap(temp_y, snake_p[i][1]);
			}
			break;
		case 3:
			temp_x = snake_p[0][0];
			temp_y = snake_p[0][1]+1;
			for(int i = 0; i <= lenth; i++){
				swap(temp_x, snake_p[i][0]);
				swap(temp_y, snake_p[i][1]);
			}
			break;
	}
//	if(food_s){
//		ex = snake_p[lenth][0];
//		ey = snake_p[lenth][1];
//	}
//	printf("\nx = %d y = %d\n", snake_p[0][0], snake_p[0][1]);
//	Sleep(100);
	//��¼���� 
	for(int i = 0; i <= lenth; i++){
		int tx = snake_p[i][0];
		int ty = snake_p[i][1];
		snake_map[tx][ty] = 1;
	}
//	Sleep(25);
//	check_cin();
//	Sleep(25);
	gotoxy(snake_p[0][1], snake_p[0][0]);
	putchar('@');
	gotoxy(snake_p[1][1], snake_p[1][0]);
	putchar('>');
//	Sleep(25);
	gotoxy(snake_p[lenth][1], snake_p[lenth][0]);
	putchar(' ');
//	Sleep(25);
	food_system();
	check_cin();
}

//ʳ��ϵͳ 
void food_system()
{
	srand(time(NULL));
	int fx, fy;
	if(!food_s){
		do{
			Sleep(50); 
			fx = (rand() % 24) + 1;
			fy = (rand() % 48) + 1;
			gotoxy(0, 35);
			printf("ʳ������x = %d y = %d\n", fx, fy);
		}while(ori_map[fx][fy] == '@' || ori_map[fx][fy] == '*' || snake_map[fx][fy] == 1);
		ori_map[fx][fy] = '$';
		gotoxy(fy, fx);
		putchar('$');
//		Sleep(20000);
//		gotoxy(snake_p[0][1], snake_p[0][0]);
		food_s = 1;
	}
	int tx = snake_p[0][0];
	int ty = snake_p[0][1];
	//�Ե���ʳ��
	if(ori_map[tx][ty] == '$'){
		gotoxy(snake_p[lenth][1], snake_p[lenth][0]);
		putchar('>');
		food_s = 0;
		ori_map[tx][ty] = ' ';
		gotoxy(snake_p[0][1], snake_p[0][1]);
		int tail_dr_x = snake_p[lenth][0] - snake_p[lenth-1][0];
		int tail_dr_y = snake_p[lenth][1] - snake_p[lenth-1][1];
		if(tail_dr_x > 0 && tail_dr_y == 0){
			lenth++;
			snake_p[lenth][0] = snake_p[lenth-1][0] + 1;
			snake_p[lenth][1] = snake_p[lenth-1][1];
		}
		else if(tail_dr_x < 0 && tail_dr_y == 0){
			lenth++;
			snake_p[lenth][0] = snake_p[lenth-1][0] - 1;
			snake_p[lenth][1] = snake_p[lenth-1][1];
		}
		else if(tail_dr_x == 0 && tail_dr_y > 0){
			lenth++;
			snake_p[lenth][0] = snake_p[lenth-1][0];
			snake_p[lenth][1] = snake_p[lenth-1][1] + 1;
		}
		else{
			lenth++;
			snake_p[lenth][0] = snake_p[lenth-1][0];
			snake_p[lenth][1] = snake_p[lenth-1][1] - 1;
		}
	}
}

void putout_waiting()
{
	gotoxy(0, 30);
	cout << "---Waiting---" << endl;
	Sleep(1000);
	cout << "[";
	gotoxy(8, 31);
	cout << "]";
	gotoxy(1, 31);
	for(int i = 0; i < 4; i++){
		Sleep(500);
		cout << "->";
	}
}


void putout_wait()
{
	for(int i = 0; i < 6; i++){
		Sleep(100);
		cout << ">";
	}
	cout << endl;
} 

void restart()
{
	memset(snake_map, 0, sizeof(snake_map));
	memset(snake_p, 0, sizeof(snake_p));
	lenth = 0;
	food_s = 0;
	gotoxy(0, 30);
	cout << endl;
	cout << "���ڳ�ʼ�����״̬";
	putout_wait();
	gotoxy(0, 0);
	origin_player_place();
	Sleep(200);
	gotoxy(0, 32);
	cout << "�������»��Ƶ�ͼ";
	putout_wait();
	Sleep(200);
	gotoxy(0, 0);
	origin_makemap();
	put_map();
}

bool judge_legal(char d)
{
	switch (d){
		case 'W':
		case 'w':
			if(now_dr == 1) {
//				cout << 1;
				return false;
			}
			break;
		case 's':
		case 'S':
			if(now_dr == 0){
//				cout << 0;
				return false;
			}
			break;
		case 'a':
		case 'A':
			if(now_dr == 3) {
//				cout << 3;
				return false;
			}
			break;
		case 'd':
		case 'D':
			if(now_dr == 2){
//				cout << 2;
				return false;
			}
			break;
		default :
			return false;
			break;
	}
//	cout << "dafs";
	return true;
}

void check_cin()
{
	if(kbhit() && flag){
		char derection = getch();
		if(judge_legal(derection)){
			switch_dr(derection);
//			Sleep(50); 
//			move_snake(now_dr);
		}
//		food_system();
	}
}

void start_waiting()
{
	gotoxy(0, 30);
	cout << "��Ϸ����ʱ"; 
	for(int i = 5; i >= 1; i--){
		Sleep(400);
		cout << i;
		gotoxy(10, 30);
	}
	gotoxy(0, 30);
	for(int i = 0; i <= 10; i++){
		cout << " ";
	}
}

void delet_line(int x, int ti)
{
	putchar('\r');
	for(int i = 0; i < x; i++){
		Sleep(ti);
		cout << " ";
	}
	putchar('\r');
}

void start_tip()
{
	gotoxy(0, 30);
	cout << "̰������������汾V1.1" << endl;
	Sleep(1000);
	cout << "����������׶� �����Ҳ�����������������" << endl;
	Sleep(1000);
	cout << "����bug";
	Sleep(1000);
	delet_line(8, 20);
	cout << "��������";
	Sleep(1000);
	delet_line(14, 20);
	cout << "��֭��ʾ�����";
	Sleep(1000);
	delet_line(14, 60);
	cout << "V1.1�汾 �޸�����bug";
	Sleep(1000);
	delet_line(20, 60);
	cout << "�����˿����ļ���";
	Sleep(1000);
	delet_line(20, 60); 
	cout << "��� ���ĸ�л���ܲ�����Ա�����" << endl;
	Sleep(1000);
	delet_line(14, 60);
	cout << "���ڣ���Ϸ������ʼ";
	Sleep(1000);
//	delet_line(14, 60);
	gotoxy(0, 30);
	for(int i = 0; i < 4; i++){
		delet_line(39, 7);
//		Sleep(300);
		cout << endl;
	}
}

bool cmp(int a, int b){
	return a > b;
}

//����ͳ��ϵͳ 
void rank_score()
{
	score[play_time] = lenth;
	sort(score, score + 1 + play_time, cmp);
	gotoxy(n+9, 4);
	for(int i = 0; i < play_time; i++){
		printf("No.%d:  %d\n", i+1, score[i]);
		gotoxy(n+9, 4+i+1);
	}
}

int main()
{
	origin_player_place();
	origin_makemap();
	put_map();
//	Sleep(8000);
//	printf("xx = %d yy = %d\n", xx, yy);
//	gotoxy(snake_p[0][0], snake_p[0][1]);
//	gotoxy(yy, xx);
//	cout << 1;
//	Sleep(200000);
	start_tip(); 
	start_waiting();
//	fflush(stdin);
	while(1){
		int start = clock();
		int ti = 1;
//		fflush(stdin);
		while(flag){
		int snake_speed = 110; 
//			temp_test();
			check_cin();
			while(!kbhit()){
				if(ti % 200 == 0) snake_speed -= 20;
//				temp_test();
				gotoxy(0, 36);
				if(clock() - start >= 1000) {
					delet_line(20, 0);
					printf("Your total Steps = %d\n", ti++);
					printf("speed = %d\n", snake_speed);
//					cout << "Your total Steps = " << ++ti << " " << "speed = " << speed;
				}
				check_cin();   //������
				Sleep(snake_speed);  //�����ߵ�����
				check_cin();
				move_snake(now_dr);  //�ƶ���
				food_system();
				if(!rule_judge()){
					flag = false;
					break;
				}
				gotoxy(10, 28);
				cout << lenth;
//				gotoxy(snake_p[0][1], snake_p[0][0]);
			}
			check_cin();
		}
		play_time++;
		rank_score();
		gotoxy(0, 30);
		cout << "����������Y/y �뿪������N/n" << endl;
		char next_step;
		do{
			next_step = getch();
		}while(next_step != 'n' && next_step != 'N' && next_step != 'Y' && next_step != 'y');
//		char next_step = getch();
		if(next_step == 'n' || next_step == 'N'){
			cout << "Thank you for playing my game!" << endl;
			return 0;
		}
		else if(next_step == 'Y' || next_step == 'y'){
			flag = true;
			putout_waiting();
			restart();
			start_waiting();
			rank_score();
		}
	}
	return 0;
}
