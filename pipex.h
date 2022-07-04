/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchennak <jchennak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 21:02:52 by jchennak          #+#    #+#             */
/*   Updated: 2022/07/04 16:35:30 by jchennak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef PIPEX_H
#define PIPEX_H
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>



typedef struct s_data
{
	int fileds[2]; 
	pid_t	pid;
	pid_t	pid_2;
	int		infile;
	int		outfile;
	
}	t_data;

void	err(char *str);

# endif