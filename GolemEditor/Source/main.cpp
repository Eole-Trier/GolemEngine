#include "editor.h"
#include <iostream>
//#include "mathslib.h"

int main()
{
	Editor* editor = new Editor();
	editor->Run();
	std::cout << "Project Closed" << std::endl;
	return 0;
}