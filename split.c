/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarzouk <mmarzouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 19:29:37 by mmarzouk          #+#    #+#             */
/*   Updated: 2021/03/16 12:17:08 by mmarzouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#define ee printf("HII\n");
size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int		doublecount(char **s)
{
	int i;

	i = 0;
	if (s)
	{
		while (s[i])
			i++;
	}
	return (i);
}

void	doublefree(char **ptr)
{
	int i;

	if (ptr != NULL)
	{
		i = doublecount(ptr);
		while (i >= 0)
		{
			free(ptr[i]);
			i--;
		}
		free(ptr);
	}
	ptr = NULL;
}

void    nfree(void *s)
{
    if(s)
    {
        free (s);
        s = NULL;
    }
}

int	gnl_return(char *s, int i)
{
	free(s);
	s = NULL;
	return (i);
}
char	*ft_strchr(const char *s, int c)
{
	while (*s != c)
	{
		if (*s == '\0')
			return (0);
		s++;
	}
	return ((char *)s);
}
char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	char	*s3;

	if (!s1 || !s2)
		return (NULL);
	s3 = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!s3)
		return (NULL);
	i = 0;
	while (*s1)
	{
		s3[i] = *s1++;
		i++;
	}
	while (*s2)
	{
		s3[i] = *s2++;
		i++;
	}
	s3[i] = '\0';
	return (s3);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*s2;

	if (!(s2 = (char *)malloc((len + 1) * sizeof(char))) || !s)
		return (NULL);
	i = 0;
	if (start < strlen(s))
	{
		while (s[start] && i < len)
		{
			s2[i] = s[start];
			start++;
			i++;
		}
	}
	s2[i] = '\0';
	return (s2);
}

int	gnl_put(char **s, char **line)
{
	char	*temp;
	int		i;

	i = 0;
	while ((*s)[i] && (*s)[i] != '\n')
		i++;
	if ((*s)[i] == '\n')
	{
		*line = ft_substr(*s, 0, i);
		temp = ft_substr(*s, i + 1, ft_strlen(*s));
		free(*s);
		*s = temp;
		return (1);
	}
	else
	{
		*line = ft_substr(*s, 0, ft_strlen(*s));
		free(*s);
		*s = NULL;
		return (0);
	}
}

int	gnl_read(int fd, char **s, char **line, int i)
{
	char	*s2;
	char	*temp;

	if (!(s2 = malloc(sizeof(char) * 100 + 1)))
		return (-1);
	while ((i = read(fd, s2, 100)) > 0)
	{
		s2[i] = '\0';
		if (!s[fd])
			s[fd] = ft_substr("", 0, 0);
		temp = ft_strjoin(s[fd], s2);
		free(s[fd]);
		s[fd] = temp;
		if (ft_strchr(s[fd], '\n'))
			return (gnl_return(s2, gnl_put(&s[fd], line)));
	}
	if (i == -1)
		return (gnl_return(s2, i));
	else if (!s[fd] && i == 0)
	{
		*line = ft_substr("", 0, 0);
		return (gnl_return(s2, i));
	}
	else
		return (gnl_return(s2, gnl_put(&s[fd], line)));
}

int	get_next_line(int fd, char **line)
{
	static char	*keep[1];

	if (fd < 0 || fd > 1 || 100 < 1 || !line)
		return (-1);
	if (keep[fd] && ft_strchr(keep[fd], '\n'))
		return (gnl_put(&keep[fd], line));
	else
		return (gnl_read(fd, keep, line, 0));
}

char	*ft_strdup(const char *s1)
{
	size_t	i;
	char	*s2;

	i = 0;
	if (!(s2 = (char *)malloc((strlen(s1) + 1) * sizeof(char))))
		return (NULL);
	while (s1[i])
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}



char **append_line(char **s, char *line)
{
    char **new;
    int i;
    
    i = 0;
    new = malloc(sizeof(char *) * (doublecount(s) + 2));
    while (s && s[i])
    {
        new[i] = ft_strdup(s[i]);
        i++;
    }
    new[i] = ft_strdup(line);
    new[i+1] = 0;
    doublefree (s);
    nfree (line);
    return (new);
}
void single_q(char *s,int *i)
{
	while(s[(*i)++])
	{
		if(s[(*i)] == '\'')
			break;
	}
}
char    **split_it(char *s)
{
    char **sp;
    int i;
    short flag;
    int start;

    flag = 0;
    sp = 0;
    start = 0;
	i = 0;
    while (s[i] && *s == ' ')
        s++;
    while (s[i])
    {
        if(s[i] == '"' && !flag) {
            flag = 1;
        }
        else if (s[i] == '\'' && flag) {
			single_q(s,&i);
		}
        else if (s[i] == '"' && flag) {
            flag = 0;
        }
        else if(s[i] == ' ' && !flag)
        {
            sp = append_line(sp,ft_substr(s,start,(i - start)));
            start = i;
			while (s[i] && s[i + 1] == ' ')
				i++;
		}
        if(s[i] == '\\' && s[i+1]) {
            i += 2;
		}
		else
			i++;
    }
	sp = append_line(sp,ft_substr(s,start,(i - start)));
    return(sp);
}


int main()
{
    char **sp;
    char *s;
while (1)
{
    get_next_line(0,&s);
    sp = split_it(s);
    for (int j = 0; sp[j]; j++)
        printf("|%s|\n", sp[j]);
}

}
// if (s[i] == '\\' && !(flag^2))
//     flag = (flag | 2);
// else if (s[i] == '\\' && (flag^2))
//     flag = (flag^2);