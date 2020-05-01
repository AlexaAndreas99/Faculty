#include <iostream>
#include <Windows.h>
#include "UI.h"
#include "Controller.h"
using namespace std;
int main()
{
	Controller ctrl;
	UI ui{ ctrl };
	ui.run();
	system("pause");
	return 0;
}