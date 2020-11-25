#include "Workflow/Workflow.h"

int main()
{
	string schemeFilename("scheme.txt");

	Executor executor;
	executor.execute(schemeFilename);

	return 0;
}