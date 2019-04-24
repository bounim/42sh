/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/17 17:20:43 by emartine          #+#    #+#             */
/*   Updated: 2019/03/22 19:50:39 by khsadira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stddef.h>
# include <sys/types.h>
# include "hashmap.h"
# include "printer.h"

void	ft_putnbr_fd(int n, int fd);
void	ft_free_arr(char **arr);
int		ft_nblen(int nb);
int		ft_isdigit(int c);
int		ft_strnequ(char const *s1, char const *s2, size_t n);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char const *s, int fd);
void	ft_strdel(char **as);
int		ft_strichr(char *str, char c);
void	ft_memdel(void **ap);
int		ft_strequ(char const *s1, char const *s2);
int		ft_isspace(int c);
int		ft_isspace_n(int c);
int		ft_isdigit(int c);
int		ft_memtoi(const uint8_t *s, size_t size);
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
void	ft_arrdel(char **arr);
char	**ft_arrdup(char **arr);
char	*ft_strdup(const char *s1);
size_t	ft_arrlen(char **arr);
int		ft_atoi(const char *s);
char	*ft_itoa(int n);
char	*ft_strsub(char const *s, unsigned int start, size_t n);
char	*ft_strstr(const char *h, const char *n);
void	*ft_memalloc(size_t size);
char	*ft_strfjoin(char *s1, char *s2, int opt);
char	**ft_strsplit(char const *s, char c);
size_t	ft_wslen(char *str);
int		ft_isnotprint(int c);
int		ft_first_char_unicode(int c);
int		ft_u8_strequ(uint8_t const *s1, uint8_t const *s2);
uint8_t	*ft_u8_strfjoin(uint8_t *s1, uint8_t *s2, int opt);
int		ft_strisdigit(char *str);
uint8_t	*ft_u8_strjoin(uint8_t const *s1, uint8_t const *s2);
size_t	ft_u8_strlen(const uint8_t *s);
uint8_t	*ft_u8_strnew(size_t n);
uint8_t	**ft_u8_strsplit(uint8_t const *s, uint8_t c);
int		ft_u8_is_alnum(uint8_t c);
int		ft_isalpha(int c);
int		ft_isalnum(int c);
void	*ft_memchr(const void *s, int c, size_t n);
ssize_t	ft_carac_size(uint8_t *buf, size_t ulen);
ssize_t	ft_carac_nb(uint8_t *str, size_t ulen);
size_t	ft_count_bn(char *str);
size_t	ft_wchar_len(unsigned char *str);
size_t	ft_ustrlen(const uint8_t *ustr);
uint8_t	*ft_u8_strdup(const uint8_t *s);
int		ft_get_nb_len(int nb);

#endif
