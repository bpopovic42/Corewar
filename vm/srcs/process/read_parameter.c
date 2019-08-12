/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_parameter.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlambert <vlambert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/20 17:15:43 by bopopovi          #+#    #+#             */
/*   Updated: 2019/08/12 16:50:51 by vlambert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "proc.h"

unsigned int	read_parameter(t_vm *vm, t_proc *proc, t_op op, t_param *param)
{
	unsigned int	read;
	unsigned int	read_addr;
	unsigned short	dir_size;

	read = 0;
	read_addr = 0;
	dir_size = op.dir_type == 0 ? 4 : 2;
	if (param->type == REG_CODE)
		read = read_from_register(proc, param->val, vm);
	else if (param->type == IND_CODE)
	{
		if (op.addr_restrict)
			read_addr = (proc->pc + (short)((short)param->val % IDX_MOD))
				% MEM_SIZE;
		else
			read_addr = (proc->pc + param->val) % MEM_SIZE;
		read = read_from_vm(vm, read_addr, dir_size);
		dbg_print_ind_load(vm->options & OPTD, "IND_READ", read_addr, read);
	}
	else if (param->type == DIR_CODE)
	{
		read = param->val;
		dbg_print_dir_load(vm->options & OPTD, "DIR_READ", read);
	}
	return (read);
}
