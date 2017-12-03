#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

int main()
{
	int fd = open("pipe", O_WRONLY);
	char* s = "my text";
	write(fd, s, strlen(s));
	return 0;
}
