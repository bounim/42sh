/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/17 17:20:43 by emartine          #+#    #+#             */
/*   Updated: 2018/01/17 17:20:45 by emartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stddef.h>
# include "hashmap.h"
# include "printer.h"

int		ft_isspace(int c);
int		ft_isspace_n(int c);
void	*ft_memcat(size_t *rn, const void *a, size_t an,
		const void *b, size_t bn);
void	*ft_memcpy(void *dst, const void *src, size_t n);
int		ft_memcmp(void *a, const void *b, size_t len);
void	*ft_memmove(void *dst, const void *src, size_t len);
void	*ft_memset(void *b, int c, size_t len);
char	*ft_stpncpy(char *dest, const char *src, size_t n);
char	*ft_stpncpyz(char *dest, const char *src, size_t n);
char	*ft_strchr(const char *s, int c);
int		ft_strcmp(const char *s1, const char *s2);
size_t	ft_strlen(const char *str);
char	*ft_strncpy(char *dest, const char *src, size_t n);
char	*ft_strncpyz(char *dest, const char *src, size_t n);
size_t	ft_strnlen(const char *str, size_t size);

#endif
