/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartel <jmartel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 11:41:02 by jmartel           #+#    #+#             */
/*   Updated: 2018/12/01 20:52:03 by jmartel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"

void		ft_realloc(char **line, t_file *file)
{
	char	*new;

	if (!(new = malloc(sizeof(**line) * (file->l_s + BUFF_SIZE))))
		return ;
	ft_memcpy(new, *line, file->l_s);
	free(*line);
	file->l_s += BUFF_SIZE;
	*line = new;
}

void		check_lst(t_file **lst, int fd)
{
	t_file		*new;

	if (!(new = (t_file*)malloc(sizeof(t_file))))
		return ;
	new->fd = fd;
	if (!(new->b_s = (char*)malloc(sizeof(char) * BUFF_SIZE)))
		return ;
	new->b = new->b_s;
	new->size = read(new->fd, new->b_s, BUFF_SIZE);
	new->l_s = new->size;
	new->i = 0;
	new->next = NULL;
	if (lst == NULL || *lst == NULL)
		(*lst) = new;
	else
		(*lst)->next = new;
	return ;
}

int			ft_read(t_file *file, char **line)
{
	if (file->b == file->b_s + file->size)
	{
		file->size = read(file->fd, file->b_s, BUFF_SIZE);
		file->b = file->b_s;
		file->l_s += file->size;
	}
	if (file->size == 0 && file->i != 0)
	{
		(*line)[file->i] = 0;
		return (1);
	}
	if (file->size == 0)
		return (0);
	while (*file->b != '\n' && file->b < file->b_s + file->size)
		(*line)[file->i++] = *(file->b++);
	if (*(file->b) == '\n')
	{
		(file->b)++;
		(*line)[file->i] = 0;
		file->i = 0;
		return (1);
	}
	return (ft_read2(file, line));
}

int			ft_read2(t_file *file, char **line)
{
	int		res;

	if (file->b >= file->b_s + file->size)
	{
		ft_realloc(line, file);
		res = ft_read(file, line);
		file->i = 0;
		return (res);
	}
	file->fd = -1;
	return (0);
}

int			get_next_line(const int fd, char **line)
{
	static t_file	*lst = NULL;
	t_file			*file;

	if (fd < 0 || line == NULL)
		return (-1);
	if (lst == NULL)
		check_lst(&lst, fd);
	file = lst;
	while (file != NULL)
	{
		if (file->fd == fd)
			break ;
		if (file->next == NULL)
			check_lst(&file, fd);
		file = file->next;
	}
	if (!(*line = malloc(sizeof(**line) * file->l_s)))
		return (-1);
	return (ft_read(file, line));
}
