#include <stdio.h>
#include <omp.h>
#include <iostream>
#include <climits>
#include <vector>
#include <string>
#include <sstream>

#ifdef _WIN32
#define _OPENMP _OMP_H
#endif

void client(omp_lock_t& read_lock, omp_lock_t& write_lock, std::string& task) {
	std::vector<std::string> tasks = {
		"5+3",
		"res/2",
		"24/res",
		"res*res",
		"res-2",
		""
	};
	for (int i = 0; i < tasks.size(); i++) {
		omp_set_lock(&write_lock);
		task = tasks[i];
		omp_unset_lock(&read_lock);
	}
}

void server(omp_lock_t& read_lock, omp_lock_t& write_lock, std::string& task) {
	std::string number1, number2, oper;
	int pointer = 0, res = 0, num1, num2;
	while (true) {
		omp_set_lock(&read_lock);
		if (task.size() == 0) {
			std::cout << res << std::endl;
			return;
		}
		pointer = 0;
		number1 = "";
		while ((task[pointer] != '+') && (task[pointer] != '-') && (task[pointer] != '*') && (task[pointer] != '/')) {
			number1 += task[pointer];
			pointer++;
		}
		oper = task[pointer];
		number2 = "";
		for (int i = pointer + 1; i < task.size(); i++) {
		number2 += task[i];
		}
		if (number1 == "res") {
		num1 = res;
		}
		else {
		num1 = std::atoi(number1.c_str());
		}
		if (number2 == "res") {
		num2 = res;
		}
		else {
		num2 = std::atoi(number2.c_str());
		}
		if (oper == "+") {
		res = num1 + num2;
		}
		else if (oper == "-") {
		res = num1 - num2;
		}
		else if (oper == "/") {
		res = num1 / num2;
		}
		else if (oper == "*") {
		res = num1 * num2;
		}
		omp_unset_lock(&write_lock);
	}
}

int main(int argc, char* argv[]) {
	omp_lock_t read_lock, write_lock;
	omp_init_lock(&read_lock);
	omp_set_lock(&read_lock);
	omp_init_lock(&write_lock);
	std::string task;
#pragma omp parallel
	{
#pragma omp sections
		{
#pragma omp section
			{
				server(read_lock, write_lock, task);
			}
#pragma omp section
			{
				client(read_lock, write_lock, task);
			}
		}
	}
	return 0;
}