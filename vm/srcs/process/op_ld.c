/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_ld.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/16 18:11:21 by bopopovi          #+#    #+#             */
/*   Updated: 2019/07/18 17:41:52 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "proc.h"

__attribute__((unused))static bool l_dbg = 1;

void	op_ld(__attribute__((unused))t_vm *vm, t_proc *process,
	t_param *params, __attribute__((unused))t_op op)
{
	unsigned int reg_dest;
	unsigned int load;

	local_dbg(l_dbg, "{magenta}EXECUTING OP_LD{eoc}\n");
	load = 0;
	if (params[0].type == DIR_CODE)
		load = params[0].val;
	else if (params[0].type == IND_CODE)
		load = read_from_vm(vm, process->pc + (params[0].val % IDX_MOD), REG_SIZE);
	reg_dest = params[1].val;
	local_dbg(l_dbg, "Destination register : %d\n", reg_dest);
	write_to_register(process, reg_dest, load);
	process_set_carry(process, op, load);
	local_dbg(l_dbg, "{magenta}OP_LD END{eoc}\n\n");
}

/*
** Unsure if address restriction has to be applied to param 1 if its type is IND
*/

void	op_ldi(__attribute__((unused))t_vm *vm, t_proc *process,
	t_param *params, __attribute__((unused))t_op op)
{
	unsigned int reg_dest;
	unsigned int load_addr;
	unsigned int write;
	unsigned int src_1;
	unsigned int src_2;

	local_dbg(l_dbg, "{magenta}EXECUTING OP_LDI{eoc}\n");
	src_1 = 0;
	src_2 = 0;
	if (params[0].type == REG_CODE)
		src_1 = read_from_register(process, params[0].val);
	else if (params[0].type == IND_CODE)
		src_1 = read_from_vm(vm, process->pc + (params[0].val % IDX_MOD), op.dir_type == 0 ? 4 : 2);
	else if (params[0].type == DIR_CODE)
		src_1 = params[0].val;
	if (params[1].type == REG_CODE)
		src_2 = read_from_register(process, params[1].val);
	else if (params[1].type == DIR_CODE)
		src_2 = params[1].val;
	reg_dest = params[2].val;
	local_dbg(l_dbg, "Destination register : %d\n", reg_dest);
	local_dbg(l_dbg, "Value to be written :\n");
	load_addr = process->pc + ((src_1 + src_2) % IDX_MOD);
	write = read_from_vm(vm, load_addr, sizeof(int));
	write_to_register(process, reg_dest, write);
	process_set_carry(process, op, write);
	local_dbg(l_dbg, "{magenta}OP_LDI END{eoc}\n\n");
}
