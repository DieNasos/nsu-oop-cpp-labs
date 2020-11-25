// OOOP LABA #0.B

#include "WordCounter.h"

void word_count(const char* in_filename, const char* out_filename)
{
	WordCounter counter;
	counter.read(in_filename);
	counter.write(out_filename);
}

int main(int argc, char* argv[])
{
	char* in_filename = argv[1];
	char* out_filename = argv[2];
	word_count(in_filename, out_filename);
	return 0;
}

//int main()
//{
//	word_count("in.txt", "out.txt");
//	return 0;
//}