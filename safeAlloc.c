/*
	safeAlloc.c
	Safe Memory Allocation
	Created By Omer Yumusak
	06.25.2023
	https://www.linkedin.com/in/hiqermod/
*/

#include "safeAlloc.h"

static size_t	my_strlen(char *str)
{
	size_t	counter;

	counter = 0;
	while (str[counter])
	{
		counter++;
	}
	return (counter);
}

static char	*my_strdup(char *str)
{
	char	*retVal;
	size_t	counter;

	retVal = (char *)malloc(sizeof(char) * my_strlen(str) + 1);
	if (!retVal)
	{
		fprintf(stderr ,"SafeAlloc: Strdup Alloc Error!\n");
		safeExit(-1);
	}

	counter = 0;
	while (*(str + counter))
	{
		*(retVal + counter) = *(str + counter);
		counter++;
	}
	*(retVal + counter) = 0;

	return (retVal);
}

t_safeList	*createList(char *fileDir, int line, void *alloc, int size)
{
	t_safeList	*retVal;

	retVal = (t_safeList *)malloc(sizeof(t_safeList));
	if (!retVal)
	{
		fprintf(stderr ,"SafeAlloc: CreateList Malloc Err!\n");
		safeExit(-1);
	}

	retVal->fileDir = my_strdup(fileDir);
	retVal->alloc = alloc;
	retVal->next = 0;
	retVal->line = line;
	retVal->size = size;

	return (retVal);
}

t_safeList	*addList(t_safeList *lst, char *fileDir, int line, void *alloc, int size)
{
	t_safeList	*tmp;

	tmp = lst;
	while (tmp->next)
		tmp = tmp->next;

	tmp->next = (t_safeList *)malloc(sizeof(t_safeList));
	if (!tmp->next)
	{
		fprintf(stderr, "SafeAlloc: AddList Alloc Err\n");
		safeExit(-1);
	}

	tmp->next->next = 0;
	tmp->next->alloc = alloc;
	tmp->next->fileDir = my_strdup(fileDir);
	tmp->next->line = line;
	tmp->next->size = size;

	return (lst);
}

t_safeList	*pushList(t_safeList *lst, char *fileDir, int line, void *alloc, int size)
{
	if (lst == 0)
		lst = createList(fileDir, line, alloc, size);
	else
		lst = addList(lst, fileDir, line, alloc, size);
	return (lst);
}


void	OMERYUMUSAK_exit(int nb)
{
	t_safeList	*lst;
	t_safeList	*before;

	lst = OMERYUMUSAK_safeAlloc(0, "garbage!", 0, 1);
	before = 0;
	while (lst)
	{
		before = lst;
		lst = lst->next;
		free(before->alloc);
		free(before->fileDir);
		free(before);
	}
	exit(nb);
}

void	*OMERYUMUSAK_safeAlloc(int size, char *file, int line, int mode)
{
	void				*ret_val;
	FILE				*filee;
	static t_safeList	*lst = 0;
	static int			check = 0;

	// get Ptr mode
	if (mode == 1)
		return (lst);
	// set Ptr mode
	else if (mode == 2)
	{
		lst = 0;
		return (NULL);
	}

	if (size <= 0)
	{
		fprintf(stderr ,"SafeAlloc: Negative Size! Folder: %s, Line: %d\n", file, line);
		safeExit (-1);
	}
		

	ret_val = malloc(size);
	if (!ret_val)
	{
		fprintf(stderr, "SafeAlloc: Allocate Err! Folder: %s, Line: %d\n", file, line);
		safeExit(-1);
	}
		

	if (access("safeAlloc", F_OK))
	{
		filee = fopen("./safeAlloc", "w");
	}
	else
		filee = fopen("./safeAlloc", "a");
	if (filee == NULL)
	{
		fprintf(stderr, "SafeAlloc: Open Err! Folder: %s, Line: %d\n", file, line);
		free(ret_val);
		safeExit(-1);
	}

	if (check == 0)
	{
		fprintf(filee, "SafeAlloc By Omer Yumusak\n");
		check = 1;
	}


	lst = pushList(lst, file, line, ret_val, size);

	fprintf(filee, "File: %s, Line: %d, Size: %d\n", file, line, size);

	fclose(filee);
	return (ret_val);
}

void	OMERYUMUSAK_free(void *dest, char *file, int line)
{
	t_safeList	*lst;
	t_safeList	*tmp;
	int			check;
	FILE		*filee;

	check = 0;
	lst = OMERYUMUSAK_safeAlloc(0, "garbage!", 0, 1);

	tmp = lst;
	while (tmp)
	{
		if (tmp->alloc == dest)
		{
			check = 1;
			break;
		}
		tmp = tmp->next;
	}

	if (check == 0)
	{
		fprintf(stderr, "Not Allocated Free!\n");
		return ;
	}

	filee = fopen("./safeAlloc", "w");
	if (filee == NULL)
	{
		fprintf(stderr, "SafeAlloc: Open Err! Folder: %s, Line: %d\n", file, line);
		safeExit(-1);
	}

	fprintf(filee, "SafeAlloc By OMER YUMUSAK\n");

	tmp = lst;
	lst = 0;

	while (tmp)
	{
		if (tmp->alloc != dest)
			fprintf(filee, "File: %s, Line: %d, Size: %ld\n", tmp->fileDir, tmp->line, tmp->size);
		else
		{
			if (lst && tmp->next)
			{
				lst->next = tmp->next;

				free(tmp->alloc);
				free(tmp->fileDir);
				free(tmp);
				tmp = lst;
			}
			else if (lst && !tmp->next)
			{
				free(tmp->alloc);
				free(tmp->fileDir);
				free(tmp);
				lst->next = 0;
				break;
			}
			else if (!lst && tmp->next)
			{
				lst = tmp;

				tmp = tmp->next;

				free(lst->alloc);
				free(lst->fileDir);
				free(lst);
				lst = 0;
				continue;
			}
			else if (!lst && !tmp->next)
			{
				free(tmp->alloc);
				free(tmp->fileDir);
				free(tmp);
				OMERYUMUSAK_safeAlloc(0, "garbage!", 0, 2);
				break;
			}
		}
		lst = tmp;
		tmp = tmp->next;
	}
	fclose(filee);
}