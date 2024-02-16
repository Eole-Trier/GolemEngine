#include "editor.h"

#include <iostream>
#include "vector3.h"

int main()
{
	Editor* editor = new Editor();
	Vector3 vec3(2, 2, 2);
	std::cout << vec3 << std::endl;
	editor->Run();
	return 0;
}