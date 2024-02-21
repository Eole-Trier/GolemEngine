#include "editor.h"
#include <iostream>
//#include "mathslib.h"

int main()
{
	Editor* editor = new Editor();
	editor->Run();
	delete editor;
	return 0;
}