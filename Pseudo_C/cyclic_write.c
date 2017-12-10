#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include "cyclic_buffer.h"
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

#define SIZE_N 4096

int main()
{
	int sfd = shm_open("test", O_CREAT | O_WRONLY, S_IRWXU);
	if(sfd < 0)
	{
		perror("sfd");
		return sfd;
	}
	int res = ftruncate(sfd, 4096);
	if(res < 0)
	{
		perror("ftruncate:");
		return -1;
	}

	struct buffer* shared = mmap(NULL, 4096, PROT_WRITE, MAP_SHARED, sfd, 0);

	bool flip = true;
	while(1)
	{
		if(flip)
		{
			shared -> first = 1;
			shared -> last = 1;
		}
		else
		{
			shared -> first = 0;
			shared -> last = 0;
		}
		flip = !flip;
	}
		
	close(sfd);
	return 0;
}
