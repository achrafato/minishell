/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 10:36:20 by iassil            #+#    #+#             */
/*   Updated: 2024/03/05 17:02:10 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_check_if_chars_digit(int c)
{
	if ((c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9'))
		return (1);
	return (0);
}

char	*ft_arg_is_exist(t_env *env, char *var)
{
	char	*ptr;
	int		i;

	while (env != NULL)
	{
		i = 0;
		while (var[i] == env->value[i])
			i++;
		if (env->value[i] == '=' && !ft_check_if_chars_digit(var[i]))
			break ;
		env = env->next;
	}
	if (env->value)
	{
		env->value += (i + 1);
		ptr = ft_strdup(env->value);
		if (!ptr)
			return (NULL);
		env->value -= (i + 1);
		return (ptr);
	}
	return (NULL);
}

int	ft_surpass_chars(char *var)
{
	int	i;

	i = 0;
	while (var[i] && ft_check_if_chars_digit(var[i]))
		i++;
	return (i + 1);
}

void	ft_append_char(char **str, int c)
{
	int		len;
	char	*s;
	int		i;

	i = 0;
	len = ft_strlen(*str);
	s = *str;
	*str = malloc(sizeof(char) * (len + 2));
	if (!(*str))
		return ;
	while (s && s[i])
	{
		(*str)[i] = s[i];
		i++;
	}
	(*str)[i++] = c;
	(*str)[i] = '\0';
	free(s);
}

char	*ft_handle_expand(t_env *env, char *arg)
{
	int		i;
	int		quote;
	char	*expa;
	char	*new_str;
	char	*s;

	(1) && (new_str = NULL, i = 0);
	if (arg[i] == '\'' || arg[i] == '\"')
		quote = arg[i++];
	while (arg[i])
	{
		if (arg[i] == quote)
			i++;
		if (!arg[i])
			break ;
		if (arg[i] == '$' && quote == '\"')
		{
			(1) && (expa = ft_arg_is_exist(env, arg + (i + 1))), (s = new_str);
			(1) && (new_str = ft_strjoin(new_str, expa)), free(s), free(expa);
			i += ft_surpass_chars(arg + (i + 1));
		}
		else
			ft_append_char(&new_str, arg[i++]);
	}
	return (new_str);
}

void	ft_expand_argument(t_env *env, t_token **linked_list)
{
	t_token	*head;

	head = *linked_list;
	while (head != NULL)
	{
		head->token = ft_handle_expand(env, head->token);
		head = head->next;
	}
}
