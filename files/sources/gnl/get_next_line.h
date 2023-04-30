/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 12:24:52 by wruet-su          #+#    #+#             */
/*   Updated: 2023/01/29 02:33:49 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <limits.h> /* for OPENMAX value */
# include <stdio.h> /* for NULL value */
/* # include <fcntl.h> for OPEN function when tests */
# include <stdlib.h> /* for MALLOC */
# include <sys/types.h> /* READ's INCLUDES */
# include <sys/uio.h> /* READ's INCLUDES */
# include <unistd.h> /* READ's INCLUDES */
# include <stdint.h>

char	*get_next_line(int fd);
char	*give_to_line_what_is_stashed(char *stash);
char	*ft_split_and_free(char *line, char *stash, char *free1, char *free2);
char	*ft_customized_strjoin_with_free(char const *s1, char const *s2);
int		ft_return_n_position_in_string(const char *s, int c);
char	*ft_strdup(const char *s);
void	*ft_calloc(size_t nmemb, size_t size);
void	ft_bzero(void *s, size_t n);
size_t	ft_strlen(const char *str);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);

/* If BUFFER_SIZE is undefined,
 * this macro defines it to 100 */

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

/* If the value of BUFFER_SIZE exceeds 10 millions,
 * this macro changes it to !) millions flat */

# ifdef BUFFER_SIZE
#  if BUFFER_SIZE > 10000000
#   undef BUFFER_SIZE
#   define BUFFER_SIZE 10000000
#  endif
# endif

/* If the value of BUFFER_SIZE is < 0
 * or negative, this macro changes it to 0 */

# ifdef BUFFER_SIZE
#  if BUFFER_SIZE < 1
#   undef BUFFER_SIZE
#   define BUFFER_SIZE 0
#  endif
# endif
#endif
