/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lifetime.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaudez <tblaudez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 18:01:58 by tblaudez          #+#    #+#             */
/*   Updated: 2018/12/15 20:52:04 by tblaudez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_lt	*get_lifetime(t_lt *new_ptr)
{
	static t_lt	*lifetime = NULL;

	if (new_ptr != NULL)
		lifetime = new_ptr;
	return (lifetime);
}

void	*lt_push(void *ptr)
{
	t_lt	*lifetime;

	if (!(lifetime = (t_lt*)malloc(sizeof(t_lt))))
	{
		lt_destroy();
		exit(EXIT_FAILURE);
	}
	lifetime->ptr = ptr;
	lifetime->next = get_lifetime(NULL);
	get_lifetime(lifetime);
	return (ptr);
}

void	lt_release(void *ptr)
{
	t_lt	*lifetime;
	t_lt	*tmp;

	lifetime = get_lifetime(NULL);
	if (lifetime->ptr == ptr)
	{
		get_lifetime(lifetime->next);
		if (lifetime->ptr)
			ft_memdel((void**)&lifetime->ptr);
		ft_memdel((void**)&lifetime);
		return ;
	}
	while (lifetime && lifetime->ptr != ptr)
		lifetime = lifetime->next;
	if (!lifetime)
		return ;
	tmp = get_lifetime(NULL);
	while (tmp->next != lifetime)
		tmp = tmp->next;
	tmp->next = lifetime->next;
	if (lifetime->ptr)
		ft_memdel((void**)&lifetime->ptr);
	ft_memdel((void**)&lifetime);
}

void	lt_destroy(void)
{
	t_lt	*lifetime;
	t_lt	*tmp;

	lifetime = get_lifetime(NULL);
	while (lifetime)
	{
		tmp = lifetime;
		lifetime = lifetime->next;
		ft_memdel((void**)&tmp->ptr);
		ft_memdel((void**)&tmp);
	}
}
