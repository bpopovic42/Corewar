/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayguillo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 12:14:08 by ayguillo          #+#    #+#             */
/*   Updated: 2019/06/26 16:45:02 by ayguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/op.h"
#include "../includes/asm.h"
#include "../libft/libft.h"

void		ft_paramd(char **split, t_op *op, int size)
{
	char			**dirsplit;
	t_op			*tmp;
	unsigned int	param;

	tmp = op;
	dirsplit = NULL;
	if (split[0])
		ft_fillinstop(split[0], op);
	if (split[1] && split[1][0] != DIRECT_CHAR)
	{
		ft_printf("%s is not a direct, did you mean %c%s ?\n", split[1],
				DIRECT_CHAR, split[1]);
		return ;
	}
	param = ft_filllabel(op, split);
	ft_fillparam1(op, size, DIR_CODE, param);
	ft_free_tab2d(&dirsplit);
}

void		ft_paramrg(char **split, t_op *op)
{
	t_op			*tmp;
	char			**reg;
	int				param;


	tmp = op;
	param = 0;
	reg = NULL;
	if (split[0])
		ft_fillinstop(split[0], op);
	if (split[1] && split[1][0] != 'r')
	{
		ft_printf("%s is not a register, did you mean %c%s ?\n", split[1], 'r',
				split[1]);
		return ;
	}
	if (!(reg = ft_strsplit(split[1], 'r')))
		return;
	if (reg[0])
	{
		if ((param = ft_atoi(reg[0])) <= 0 || param > REG_NUMBER)
		{
			ft_strdel(reg);
			ft_printf("Min register = 1 or Max registers = %i\n", REG_NUMBER);
			return ;
		}
	}
	ft_fillparam1(op, 1, REG_CODE, param);
	ft_free_tab2d(&reg);
}

void		ft_paramld(char **split, t_op *op)
{
	t_op	*tmp;

	tmp = op;
	if (split[0])
		ft_fillinstop(split[0], op);
	if (split[1] && split[1][0] == DIRECT_CHAR)
		ft_filld(split, 1, op, DIR_SIZE);
	else if (split[1] && (split[1][0] >= '0' && split[1][0] <= '9'))
		ft_filli(split, 1, op);
	else
	{
		ft_printf("Syntax %s invalid.", split[1]);
		return ;
	}
	if (split[2])
	{
		if (split[2][0] != 'r')
		{
			ft_printf("%s is not a register, did you mean %c%s ?\n", split[2], 'r',
					split[2]);
			return ;
		}
		else
			ft_fillrg(split, 2, op);
	}
}
