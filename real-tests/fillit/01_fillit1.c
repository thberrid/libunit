/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_fillit1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/02 14:57:25 by jmartel           #+#    #+#             */
/*   Updated: 2018/12/02 18:37:21 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit_test.h"
#include "libunit.h"
#include <string.h>

int			fillit1(void)
{
	pid_t	pid;
	int		pipefd[2];
	int		wait_res;
	char	buf[FILLIT1_LEN + 1];
	char	**params;

	if (pipe(pipefd) == -1)
		exit(-1);
	if ((pid = fork()) == -1)
		exit(FAILURE);
	if (pid == 0)
	{
		params = malloc(sizeof(char *) * 3);
		params[0] = strdup(FILLIT_PATH);
		params[1] = strdup(FILLIT1_SAMPLE);
		params[2] = NULL;
		if (dup2(pipefd[1], 1) == -1)
			exit(-1);
		close(pipefd[0]);
		execve(FILLIT_PATH, params, NULL);
	}
	else
	{
		wait(&wait_res);
		close(pipefd[1]);
		if (wait_res == SIGBUS || wait_res == SIGSEGV)
		{
			close(pipefd[0]);
			close(pipefd[1]);
			exit(wait_res);
		}
		read(pipefd[0], buf, FILLIT1_LEN);
		close(pipefd[0]);
		buf[FILLIT1_LEN] = 0;
		if (strcmp(buf, FILLIT1_RES) == 0)
			exit(SUCCESS);
		else
			exit(FAILURE);
	}
	return (FAILURE);
}
