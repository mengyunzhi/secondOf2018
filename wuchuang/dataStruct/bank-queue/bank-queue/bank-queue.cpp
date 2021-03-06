#include "pch.h"
#include "银行排队.h"
#include <iomanip>
#include <iostream>

using namespace std;

int main()
{
	// 窗口数组			// 等待时间
	int window_num[10], wait_time = 0, time[3];

	// 最长等待时间		// 开放窗口数
	int max_wait_time = 0, windows, temp = 0;

	float num;				//人数
	Road queue;				
	Serve window[10];

	for (int i = 0; i < 10; i++)
	{
		window_num[i] = 0;
		time[i] = 0;
	}

	cin >> num;
	for (int i = 0; i < num; i++)
	{
		int x, y;
		cin >> x >> y;
		if (y > 60)
			y = 60;
		queue.queueIn(x, y);
	}

	cin >> windows;

	// queue.isEmpty返回队列长度
	while (queue.isEmpty()) {
		int i;
		for (i = 0; i < windows; i++)
		{
			if (queue.getQueuereach_time() >= window[i].getReach_time() + window[i].getServe_time()) {
				window[i].setTime(queue.getQueuereach_time(), queue.getQueueserve_time(), 0);
				queue.queueOut();
				window_num[i]++;		//i窗口服务人数+1
				break;
			}
		}
		if (i == windows) {
			int k, m, n;

			// 寻找等待时间最小的窗口
			for (int j = 0; j < windows; j++)
			{
				time[j] = window[j].getReach_time() + window[j].getServe_time();

				if (j == 0) {
					n = 0;
					k = time[0];
				}
				if (j > 0) {
					if (k > time[j]) {
						n = j;
						k = time[j];
					}

				}
			}

			// m为此窗口所需的等待时间，n为此窗口的位置
			m = window[n].getReach_time() + window[n].getServe_time() - queue.getQueuereach_time();
			window[n].setTime(queue.getQueuereach_time() + m, queue.getQueueserve_time(), m);
			queue.queueOut();
			window_num[n]++;
			wait_time = wait_time + m;		// 记录等待时间

			if (m > max_wait_time) {
				max_wait_time = m;
			}
		}
	}

	// 寻找最后服务结束的窗口
	for (int j = 0; j < windows; j++)
	{
		time[j] = window[j].getReach_time() + window[j].getServe_time();
		if (j == 0) {
			temp = time[0];
		}
		if (j > 0) {
			if (temp < time[j])
				temp = time[j];
		}
	}

	// 输出结果
	cout << setprecision(2) << wait_time / num << " "; cout << max_wait_time << " "; cout << temp << endl;
	for (int i = 0; i < windows; i++)
	{
		if (i < windows - 1) {
			cout << window_num[i] << " ";
		}
		else {
			cout << window_num[i];
		}
	}
	return 0;
}

