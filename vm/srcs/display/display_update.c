/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_update.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/29 17:00:00 by bopopovi          #+#    #+#             */
/*   Updated: 2019/08/23 18:57:36 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "display.h"

void	display_handle_key(t_vm *vm, char key)
{
	if (key == ' ' || key == 'n')
		vm->display.status.paused ^= 1;
	else if (key == 'q')
	{
		endwin();
		exit(0);
	}
	else if (key == 'l' && vm->display.speed < NC_MIN_SPEED)
		vm->display.speed = (vm->display.speed + 10);
	else if (key == 'k' && vm->display.speed < NC_MIN_SPEED)
		vm->display.speed += 1;
	else if (key == 'h' && vm->display.speed > 0)
		vm->display.speed = (vm->display.speed - 10);
	else if (key == 'j' && (vm->display.speed - 1) > 0)
		vm->display.speed -= 1;
	if (vm->display.speed <= 0)
		vm->display.speed = 1;
	else if (vm->display.speed > NC_MIN_SPEED)
		vm->display.speed = NC_MIN_SPEED;
	display_info(vm);
}

void	display_update(t_vm *vm)
{
	char c;

	c = 0;
	if (vm->options & OPTZ)
	{
		display_info(vm);
		display_memory(vm);
		c = getch();
		if (ft_strchr(NC_KEYS, c))
			display_handle_key(vm, c);
		while (vm->display.status.paused)
		{
			c = getch();
			if (ft_strchr(NC_KEYS, c))
				display_handle_key(vm, c);
		}
		if (c == 'n')
			vm->display.status.paused = 1;
		else
			usleep(1000000 / vm->display.speed);
	}
}
