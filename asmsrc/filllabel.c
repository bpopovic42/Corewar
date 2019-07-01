/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filllabel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayguillo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 15:04:56 by ayguillo          #+#    #+#             */
/*   Updated: 2019/06/26 15:10:46 by ayguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"
#include "../libft/libft.h"

static int		ft_paramlabel(t_op *op, char *label)
{
	t_op	*tmp;
	int		addr;
	int		filladdr;

	tmp = op;
	addr = -1;
	filladdr = 0;
	while (tmp->next)
	{
		filladdr += tmp->size + 1;
		if (tmp->label)
			if (!ft_strcmp(tmp->label, label))
				addr = tmp->addr;
		tmp = tmp->next;
	}
	tmp->addr = filladdr;
	if (addr >= 0)
		return ((addr - filladdr + MEM_SIZE) % MEM_SIZE);
	return (0);
}

unsigned int	ft_filllabel(t_op *op, char **split)
{
	unsigned int param;
	char		**label;
	char		**dirsplit;

	label = NULL;
	dirsplit = NULL;
	if (split[1] && split[1][1] == LABEL_CHAR)
	{
		if (!(label = ft_strsplit(split[1], LABEL_CHAR)))
			return (0) ;
		param = ft_paramlabel(op, label[1]);
	}
	else
	{
		if (!(dirsplit = ft_strsplit(split[1], DIRECT_CHAR)))
		{
			ft_free_tab2d(&label);
			return (0) ;
		}
		param = ft_atui(dirsplit[0]);
	}
	ft_free_tab2d(&dirsplit);
	ft_free_tab2d(&label);
	return (param);
}