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
	int sfd = shm_open("test", O_CREAT | O_RDWR, S_IRWXU);
	if(sfd < 0)
	{
		perror("sfd");
		return sfd;
	}
	int res = ftruncate(sfd, SIZE_N);
	if(res < 0)
	{
		perror("ftruncate:");
		return -1;
	}

	struct buffer_t* shared = mmap(NULL, sizeof(struct buffer_t), PROT_READ | PROT_WRITE, MAP_SHARED, sfd, 0);

	if(shared == -1)
	{
		return 1;
	}

	shared->pos = 0;
	for(int i=0; i<4; i++)
	{
		if(shared->pos == SIZE_N-1) shared->pos = 0; 
		shared->data[shared->pos] = i;
		shared->pos++;
	}	

	close(sfd);
	return 0;
}
