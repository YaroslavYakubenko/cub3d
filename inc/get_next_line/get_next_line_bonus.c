/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyakuben <yyakuben@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 17:44:49 by yyakuben          #+#    #+#             */
/*   Updated: 2024/11/24 20:14:23 by yyakuben         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_get_new_static_buff(char *static_buff)
{
	char	*new_buff;
	int		count1;
	int		count2;

	count1 = 0;
	while (static_buff[count1] && static_buff[count1] != '\n')
		count1++;
	if (!static_buff[count1])
	{
		free(static_buff);
		return (NULL);
	}
	new_buff = (char *)malloc((ft_strlen_v2(static_buff) - count1 + 1));
	if (!new_buff)
	{
		free(new_buff);
		return (NULL);
	}
	count1 ++;
	count2 = 0;
	while (static_buff[count1])
		new_buff[count2++] = static_buff[count1++];
	new_buff[count2] = '\0';
	free(static_buff);
	return (new_buff);
}

char	*ft_get_line(char *static_buff)
{
	int		i;
	char	*line;

	i = 0;
	if (!static_buff[i])
		return (NULL);
	while (static_buff[i] && static_buff[i] != '\n')
		i++;
	line = (char *)malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (static_buff[i] && static_buff[i] != '\n')
	{
		line[i] = static_buff[i];
		i++;
	}
	if (static_buff[i] == '\n')
	{
		line[i] = static_buff[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*ft_read_data(int fd, char *static_buff)
{
	char	*buff;
	int		bytes_read;

	bytes_read = 1;
	buff = malloc((BUFFER_SIZE + 1) * (sizeof(char)));
	if (!buff)
		return (NULL);
	while (!ft_strchr_v2 (static_buff, '\n') && bytes_read != 0)
	{
		bytes_read = read(fd, buff, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free (buff);
			return (NULL);
		}
		buff[bytes_read] = '\0';
		static_buff = ft_strjoin_v2(static_buff, buff);
	}
	free(buff);
	return (static_buff);
}

char	*get_next_line(int fd)
{
	static char	*static_buff[4096];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, NULL, 0) < 0)
	{
		free(static_buff[fd]);
		static_buff[fd] = NULL;
		return (NULL);
	}
	static_buff[fd] = ft_read_data(fd, static_buff[fd]);
	if (!static_buff[fd])
	{
		free(static_buff[fd]);
		return (NULL);
	}
	line = ft_get_line(static_buff[fd]);
	static_buff[fd] = ft_get_new_static_buff(static_buff[fd]);
	if (!static_buff[fd])
		free(static_buff[fd]);
	return (line);
}

// int main()
// {
// 	int fd1, fd2;
// 	if ((fd1 = open("text.txt", O_RDONLY))==-1 
// 	|| (fd2 = open("text1.txt", O_RDONLY))==-1 )
// 	{
// 		perror("open failed on file file.dat");
// 		exit(1);
// 	}
// 	for(int i = 0; i < 10; i++)
// 	{
// 		printf("fd1 [%d] = %s\n", i + 1, get_next_line(fd1));
// 		printf("fd2 [%d] = %s\n", i + 1, get_next_line(fd2));
// 	}
// 	close(fd1);
// 	close(fd2);
// }
