/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 16:55:35 by iassil            #+#    #+#             */
/*   Updated: 2024/03/29 22:12:24 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
*	This function checks and execute the builtins functions
*/
static void	ft_compare_arg(char *cmd, t_cont *cont, t_struct *strp, int *flag)
{
	if (ft_strncmp(cmd, "echo", ft_strlen(cmd)) == 0)
		(1) && (execute_echo(cont, &strp), *flag = 1);
	else if (ft_strncmp(cmd, "cd", ft_strlen(cmd)) == 0)
		(1) && (execute_cd(cont, &strp), *flag = 1);
	else if (ft_strncmp(cmd, "env", ft_strlen(cmd)) == 0)
		(1) && (execute_env(cont, &strp), *flag = 1);
	else if (ft_strncmp(cmd, "export", ft_strlen(cmd)) == 0)
		(1) && (execute_export(cont, &strp), *flag = 1);
	else if (ft_strncmp(cmd, "pwd", ft_strlen(cmd)) == 0)
		(1) && (ft_pwd(strp->env), *flag = 1);
	else if (ft_strncmp(cmd, "unset", ft_strlen(cmd)) == 0)
		(1) && (execute_unset(cont, &strp), *flag = 1);
	else if (ft_strncmp(cmd, "exit", ft_strlen(cmd)) == 0)
		(1) && (ft_exit(), *flag = 1);
}

/*
*	This function checks and dup the files for the right builtin
*/
int	ft_check_commands(t_cont *cont, t_struct *strp, t_info *info, int j)
{
	char	*cmd;
	int		flag;
	int		original_stdout;

	(1) && (cmd = cont->cmd, flag = 0);
	if (cmd == NULL)
		return (strp->status = 0, 1);
	if (j == 1 && info->nbr_cont == 1 && info->fd.outfile != 1)
	{
		original_stdout = dup(STDOUT_FILENO);
		ft_syscall(dup2(info->fd.outfile, STDOUT_FILENO), "msh: dup2");
		ft_syscall(close(info->fd.outfile), "msh: close");
	}
	ft_compare_arg(cmd, cont, strp, &flag);
	if (j == 1 && flag == 1 && info->nbr_cont == 1 && info->fd.outfile != 1)
	{
		ft_syscall(dup2(original_stdout, STDOUT_FILENO), "msh: dup2");
		ft_syscall(close(original_stdout), "msh: close");
		return (1);
	}
	else if (flag == 1)
		return (1);
	return (0);
}
