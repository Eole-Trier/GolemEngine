#include "editor.h"
#include <iostream>
#include "mathslib.h"

int main()
{
	Editor* editor = new Editor();
	Matrix4 a(1);
	Matrix4 b(2);
	std::cout << a + b<< std::endl;
	editor->Run();
	return 0;
}