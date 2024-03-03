#include "editor.h"
#include <iostream>
//#include "mathslib.h"

int main()
{
	Editor* editor = new Editor();
	editor->Run();
	delete editor;
	std::cout << "Project Closed" << std::endl;
	return 0;
}