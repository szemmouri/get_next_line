#include "get_next_line_bonus.h"
#include <stdio.h>
 
int	main(void)
{
	int fd = open("file.txt", O_RDWR);
	int fd2 = open("file2.txt", O_RDWR);
	char *str = "";

	while (str)
	{
		str = get_next_line(fd);
		printf("%s", str);
	}
	printf("===================================");
	while (str)
	{
		str = get_next_line(fd2);
		printf("%s", str);
	}

	// printf("\nBUFFER_SIZE: %d\n", BUFFER_SIZE);
}