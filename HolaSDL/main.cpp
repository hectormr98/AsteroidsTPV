#include <math.h>
#include "ExampleGame.h"

#include<ctime>

using namespace std;

int main(int ac, char** av) {
	srand(time(NULL));
	ExampleGame g;
	g.start();
	return 0;
}
