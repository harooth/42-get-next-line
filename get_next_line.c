/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hagevorg <hagevorg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 18:49:27 by hagevorg          #+#    #+#             */
/*   Updated: 2022/05/03 18:49:27 by hagevorg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_line(char *str)
{
	int		i;
	char	*s;

	i = 0;
	if (!str[i])
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	s = (char *)malloc(i + 2);
	if (!s)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		s[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
	{
		s[i] = str[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}

char	*ft_save(char *result)
{
	char	*newresult;
	int		i;
	int		mallocindex;

	i = 0;
	while (result[i] && result[i] != '\n')
		i++;
	if (!result[i])
	{
		free(result);
		return (NULL);
	}
	newresult = (char *)malloc(sizeof(char *) * (ft_strlen(result) - i + 1));
	if (!newresult)
		return (NULL);
	i++;
	mallocindex = 0;
	while (result[i])
		newresult[mallocindex++] = result[i++];
	newresult[mallocindex] = '\0';
	free (result);
	return (newresult);
}

char	*ft_read_and_save(int fd, char *result)
{
	char	*buff;
	int		read_bytes;

	buff = malloc(sizeof(char) * (BUF_SIZE + 1));
	if (!buff)
		return (NULL);
	read_bytes = 1;
	while (!ft_strchr(result, '\n') && read_bytes != 0)
	{
		read_bytes = read(fd, buff, BUF_SIZE);
		if (read_bytes == -1)
		{
			free(buff);
			return (NULL);
		}
		buff[read_bytes] = '\0';
		result = ft_strjoin(result, buff);
	}
	free(buff);
	return (result);
}

char	*get_next_line(int fd)
{
	static char	*result;
	char		*line;

	if (fd < 0 || BUF_SIZE <= 0)
		return (0);
	result = ft_read_and_save(fd, result);
	if (!result)
		return (NULL);
	line = ft_line(result);
	result = ft_save(result);
	return (line);
}

// int main()
// {
// 	int fd = open("test.txt", O_RDONLY);
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	//get_next_line(fd);
// 	return(0);
// }
