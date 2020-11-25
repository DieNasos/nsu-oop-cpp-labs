#include "TritSet.h"

int main()
{
	TritSet trit1(3);

	trit1.setTrit(0, False);
	trit1.setTrit(1, True);
	trit1.setTrit(2, False);

	TritSet trit2(3);

	trit2.setTrit(0, True);
	trit2.setTrit(1, False);
	trit2.setTrit(2, True);

	trit2[1] = trit1[1];

	TritVal val = trit1[0];

	trit2.printInfo();

	return 0;
}