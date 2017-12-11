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

	struct buffer_t* shared = mmap(NULL, sizeof(struct buffer_t), PROT_READ, MAP_SHARED, sfd, 0);
	if(shared == NULL)
	{
		perror("shared");
		return -1;
	}
	//sleep(6); //6 secs to write
	uint64_t pos = (shared->pos+1)%4096;
	while(1)
	{
		if(shared->pos == pos)
		{
			sleep(1);
			continue;
		}
		printf("%d\n", shared->data[pos]);
		pos++;
		pos %= 4096;
	}
	munmap(shared, sizeof(struct buffer_t));
	close(sfd);
	return 0;
}
