/*
	safeAlloc.h
	Safe Memory Allocation
	Created By Omer Yumusak
	06.25.2023
	https://www.linkedin.com/in/hiqermod/
*/
#ifndef SAFEALLOC_H
# define SAFEALLOC_H

#define safeAlloc(nbr) OMERYUMUSAK_safeAlloc(nbr, __FILE__, __LINE__, 0)
#define safeFree(ptr) OMERYUMUSAK_free(ptr, __FILE__, __LINE__)
#define safeExit(nb) OMERYUMUSAK_exit(nb)

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>

typedef struct s_safeList
{
	char	*fileDir;
	int		line;
	void	*alloc;
	size_t		size;
	struct	s_safeList *next;
} t_safeList;

void	OMERYUMUSAK_free(void *dest, char *file, int line);
void	*OMERYUMUSAK_safeAlloc(int size, char *file, int line, int mode);
void	OMERYUMUSAK_exit(int nb);


#endif