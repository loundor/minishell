/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stissera <stissera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 19:58:06 by stissera          #+#    #+#             */
/*   Updated: 2022/09/27 08:48:53 by stissera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

static int	ft_instr(char *str, char set)
{
	if (!str || !set)
		return (0);
	while (*str)
	{
		if (*str == set)
			return (1);
		str++;
	}
	return (0);
}

static char	*add_to_str(char *str, int fd)
{
	ssize_t	nbr;
	char	*buff;
	char	*temp;

	buff = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buff)
		return (NULL);
	nbr = 1;
	while (!ft_instr(str, '\n') && nbr != 0)
	{
		nbr = read(fd, buff, BUFFER_SIZE);
		if (nbr == -1)
		{
			free(buff);
			return (NULL);
		}
		buff[nbr] = '\0';
		temp = str;
		str = ft_strjoin(temp, buff);
		if (temp)
			free(temp);
	}
	free(buff);
	return (str);
}

static char	*ft_get_line(char *str)
{
	char	*ret;
	size_t	i;

	if (!str[0])
		return (NULL);
	i = 0;
	while (str[i] != '\n' && str[i])
		i++;
	ret = (char *)malloc(sizeof(char) * i + 2);
	if (!ret)
		return (NULL);
	i = 0;
	while (str[i] != '\n' && str[i])
	{
		ret[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
		ret[i++] = '\n';
	ret[i] = '\0';
	return (ret);
}

static char	*ft_remove_send(size_t start, char *str)
{
	char	*ret;
	size_t	i;

	if (ft_strlen(str) - start >= ft_strlen(str))
	{
		free(str);
		return (NULL);
	}
	ret = (char *)malloc(sizeof(char) * (ft_strlen(str) - start) + 1);
	if (!ret)
		return (NULL);
	i = 0;
	while (str[start])
		ret[i++] = str[start++];
	ret[i] = '\0';
	free(str);
	return (ret);
}

char	*get_next_line(int fd)
{
	static char	*str[1024];
	char		*ret;

	if (fd < 0 && BUFFER_SIZE <= 0)
		return (NULL);
	str[fd] = add_to_str(str[fd], fd);
	if (!str[fd])
		return (NULL);
	ret = ft_get_line(str[fd]);
	str[fd] = ft_remove_send(ft_strlen(ret), str[fd]);
	return (ret);
}
