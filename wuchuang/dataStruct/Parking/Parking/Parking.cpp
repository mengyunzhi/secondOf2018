#include "pch.h"
#include"Parking.h"
#include <iostream>
using namespace std;

int main()
{
	cout << "停车场一小时收费4元" << endl;
	char a;												//a判断车辆到达还是离开
	int num, n = 0, q;
	Car car[3];											//建立Car类的对象数组，分别对应停车场中存入的车
	Parking park;										//创建Parking类对象park
	Stack1 y;											//创建中间栈的对象y
	Road road;											//创建便道类对象road
	for (;;) {											//循环执行操作
		q = 0;
		cout << "进站输入A，出站输入D，输入E终止本次操作，请输入你的操作:";
		cin >> a;
		if (a == 'E') {									//若输出E，终止程序运行
			q = 1;
			break;
		}
		if (a == 'A') {									//输入A，进行进站操作
			q = 1;
			cout << "请输入车牌号:";
			cin >> num;
			car[n].carNum(num);							//将车牌号传给对应的Car对象

			if (park.getTop() == 2) {					//若停车场满 则车进入便道
				road.queueIn(car[n].getNumber());
				cout << "车位于便道上,位置为:" << road.isEmpty() << endl;
			}
			else {										//车进入停车场
				if (park.getTop() < 2 && !road.isEmpty()) {
					park.push(car[n].getNumber());
					cout << "车停入停车场中,位置为:" << park.getTop() + 1 << endl;
					int i;
					cout << "请输入进站时间:";
					cin >> i;
					car[n].cinTimein(i);
				}
			}
			n++;
			cout << endl;
		}

		if (a == 'D') {
			q = 1;
			cout << "车辆出站，请输入车牌号:";
			cin >> num; int i, j, k, l, m;
			j = park.searchOrder(num);					//寻找车牌号对应的车辆在停车场中的位置，若搜索不到返回-1
			if (j >= 0) {
				for (i = 0; i < park.getTop() - j; i++) {
					k = park.pop();						//出站车辆之后的车依次出站，并存入暂时存放车辆的中间栈中
					y.push(k);
				}

				l = park.pop();							//出站车辆出站

				for (; y.getTop() > -1;) {				//中间栈中的车重新入站
					k = y.pop();
					park.push(k);
				}

				for (i = 0; i < 3; i++) {				//利用车牌号找出出站车辆对应的Car对象，并输入出站时间，展示消费情况
					if (car[i].getNumber() == num) {
						cout << "请输入出站时间:";
						cin >> j; car[i].cinTimeout(j);
						Cost a;
						cout << "本次停车费用为:";
						cout << a.showCost(car[i].getTimeout(), car[i].getTimein());
						cout << endl;

						if (road.isEmpty()) {			//若便道上有车，则第一辆车在车出站的同时进入停车场
							m = road.queueOut();
							cout << "车牌号为" << m << "的车已进入停车场" << endl;
							car[2].carNum(m); park.push(m);
							cout << "进站时间为:" << j << endl;
							car[2].cinTimein(j);
							cout << endl;
						}
					}
				}
			}
			else {
				cout << "车牌号输入错误,请重新操作" << endl;
			}
		}
		if (!q) {
			cout << "输入错误，请重新输入" << endl;
			cout << endl;
		}
	}
	return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
