#include <iostream>

#include "Application\Application.h"

int main()
{
	Application App;

	while (App.IsOpen())
	{
		App.Run();
	}

	return 0;
}