/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarzouk <mmarzouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 19:29:37 by mmarzouk          #+#    #+#             */
/*   Updated: 2021/03/09 21:04:20 by mmarzouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

char    **split_it(char *s)
{
    char **sp;
    int i;
    short flag;

    flag = 0;
    sp = 0;
    while (s[i] && *s == ' ')
        s++;
    while (s[i])
    {
        

    }  
}
// if (s[i] == '\\' && !(flag^2))
//     flag = (flag | 2);
// else if (s[i] == '\\' && (flag^2))
//     flag = (flag^2);