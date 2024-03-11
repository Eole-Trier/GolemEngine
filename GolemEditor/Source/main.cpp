#include "editor.h"
#include <iostream>

int main()
{
	Editor* editor = new Editor();
	editor->Run();
	delete editor;
	std::cout << "Project Closed" << std::endl;
	return 0;
}