#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include "cyclic_buffer.h"
#include <unistd.h>

int main()
{
	int sfd = shm_open("test", O_RDONLY, S_IRWXU);
	if(sfd == -1)
	{
		perror("sfd");
		return sfd;
	}

	struct buffer* shared = mmap(NULL, sizeof(struct buffer), PROT_READ, MAP_SHARED, sfd, 0);
	if(shared == NULL)
	{
		perror("shared");
		return -1;
	}
	sleep(5);

	while(1)
	{
		if(shared->first != shared->last) return 0;
	}

	close(sfd);
	return 0;
}
