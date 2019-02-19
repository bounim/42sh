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
void	*ft_memcpy(void *dst, const void *src, size_t n);
int		ft_memcmp(void *a, const void *b, size_t len);
void	*ft_memmove(void *dst, const void *src, size_t len);
void	*ft_memset(void *b, int c, size_t len);
char	*ft_stpncpy(char *dest, const char *src, size_t n);
char	*ft_stpncpyz(char *dest, const char *src, size_t n);
char	*ft_strchr(const char *s, int c);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *str);
char	*ft_strncpy(char *dest, const char *src, size_t n);
char	*ft_strncpyz(char *dest, const char *src, size_t n);
size_t	ft_strnlen(const char *str, size_t size);

//FIXME

void	ft_arrdel(char **arr);
char	**ft_arrdup(char **arr);
char	*ft_strdup(const char *s1);
size_t	ft_arrlen(char **arr);
int		ft_atoi(const char *s);
char	*ft_itoa(int n);
char	*ft_strsub(char const *s, unsigned int start, size_t n);
void	*ft_memalloc(size_t size);
char	*ft_strfjoin(char *s1, char *s2, int opt);
char	**ft_strsplit(char const *s, char c);
size_t	ft_wslen(char *str);
int		ft_isnotprint(int c);
int		ft_first_char_unicode(int c);
int		ft_u8_strequ(uint8_t const *s1, uint8_t const *s2);
uint8_t	*ft_u8_strfjoin(uint8_t *s1, uint8_t *s2, int opt);
uint8_t	*ft_u8_strjoin(uint8_t const *s1, uint8_t const *s2);
size_t	ft_u8_strlen(const uint8_t *s);
uint8_t	*ft_u8_strnew(size_t n);
uint8_t	**ft_u8_strsplit(uint8_t const *s, uint8_t c);

#endif
