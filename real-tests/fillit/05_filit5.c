/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05_filit5.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/02 17:04:02 by jmartel           #+#    #+#             */
/*   Updated: 2018/12/02 18:38:32 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit_test.h"
#include "libunit.h"
#include <string.h>

int			fillit5(void)
{
	pid_t	pid;
	int		pipefd[2];
	int		wait_res;
	char	buf[FILLIT5_LEN + 1];
	char	**params;

	if (pipe(pipefd) == -1)
		exit(-1);
	if ((pid = fork()) == -1)
		exit(FAILURE);
	if (pid == 0)
	{
		params = malloc(sizeof(char *) * 3);
		params[0] = strdup("fillit");
		params[1] = strdup(FILLIT5_SAMPLE);
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
		read(pipefd[0], buf, FILLIT5_LEN);
		close(pipefd[0]);
		buf[FILLIT5_LEN] = 0;
		if (strcmp(buf, FILLIT5_RES) == 0)
			exit(SUCCESS);
		else
			exit(FAILURE);
	}
	return (FAILURE);
}
