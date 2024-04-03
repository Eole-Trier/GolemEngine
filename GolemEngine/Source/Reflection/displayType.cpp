#include "Reflection/displayType.h"
#include "Reflection/classesManager.h"

void DisplayType::DisplayWithHashCode(size_t _hashCode, void* _object)
{
	ClassesManager::Display(_hashCode, _object);
}
