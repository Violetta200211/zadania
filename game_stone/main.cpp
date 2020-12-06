# include <iostream>
# include <iomanip>
# include <random>
# include <ctime>
# include <sstream>

int main() {
	int min = 10, max = 20;
	std::minstd_rand gen(time(nullptr));
	int valueStone = min + (gen() % (max - min + 1));

	int valUser = 0;
	int valComputer = 0;

	int step = 1;
	while (valueStone != 0) {
		std::cout << "���������� ������   " << valueStone << std::endl;
		std:: cout << "step " << step << std::endl;
		int choice;
		switch(valueStone) {
		case 4: choice = 3; break;
		case 3: choice = 2; break;
		case 2: choice = 1; break;
		case 1: choice = 1; break;
		default: choice = 1 + gen() % 3;

		}

		valComputer += choice;
		step = 1;
		valueStone -= choice;
		std::cout << "���������� ������   " << valueStone << std::endl;
		std:: cout << "step " << step << std::endl;


		if (valueStone != 0) {
			std:: cout << "������� ���-�� ������ �� 1 �� 3" << std::endl;
			std:: string n;
			std:: getline(std::cin, n);
			std::stringstream ss(n);
			ss >> choice;

			while (choice > 3 or choice < 1 or valueStone - choice < 0 or ss.fail()) {
				std::cout << "������� ���-�� ������" << std::endl;
				std::cout << "������� ���-�� ������ �� 1 �� 3" << std::endl;
				std:: getline(std::cin,n);
				std::stringstream ss(n);
				ss >> choice;
			}
			valUser += choice;
			valueStone -= choice;
			step = 0;
		}
		std::cout << "����� ����������" << valComputer << std::endl;
		std::cout << "����� ����" << valUser << std::endl;

	}
	if (step == 0) {
		std::cout << "������� ���������";
	} else {
		std::cout << "�������� ��";
	}
	return 0;
}
