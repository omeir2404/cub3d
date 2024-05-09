/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dontTouchFuncts.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oharoon <oharoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 19:33:42 by oharoon           #+#    #+#             */
/*   Updated: 2024/05/09 15:38:05 by oharoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_mlx.h"

/**
 * @brief Get the Ticks object(for frame rate)
 * 
 * @return double 
 */
double	get_ticks(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000.0 + tv.tv_usec / 1000.0);
}
