/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_arena.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlambert <vlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 15:19:47 by vlambert          #+#    #+#             */
/*   Updated: 2019/07/02 13:02:27 by vlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../includes/vm.h"
#include "../libft/color.h"

void	print_arena(t_vm *vm)
{
	int i;
	t_proc *tmp;

	i = 0;
	while (i < MEM_SIZE)
	{
		if (!(i % 64) && i != 0)
			ft_printf("\n");
		tmp = vm->proc;
		while (tmp)
		{
			if (i == tmp->pc && tmp->player == 0)
			{
				ft_printf("%02x", vm->mem[i]);
				break;
			}
			if (i == tmp->pc && tmp->player == 1)
			{
				ft_printf("%02x", vm->mem[i]);
					break;
			}
			if (i == tmp->pc && tmp->player == 2)
			{
				ft_printf("%02x", vm->mem[i]);
					break;
			}
			if (i == tmp->pc && tmp->player == 3)
			{
				ft_printf("%02x", vm->mem[i]);
					break;
			}
			tmp = tmp->next;
		}	
		if (!tmp )
			ft_printf("%02x", vm->mem[i]);
		i++;
	}
	ft_printf("\n;\n\n");
}

int		create_arena(t_vm *vm)
{
	int i;
	int start;

	i = 0;
	while(i < vm->players_nbr)
	{
		start = i * MEM_SIZE / vm->players_nbr;
		ft_strcpyfast((char *)vm->mem + start, (char*)vm->players[i].code,
			vm->players[i].size);
		if (add_process(vm, i, start, NULL) == ERR_MALLOC)
		{
			while (i--)
				kill_unactive_processes(vm, 1);
			return (ERR_MALLOC);
		}
		++i;
	}
	print_arena(vm);
	return (0);
}