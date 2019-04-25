/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkettani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 11:27:18 by jkettani          #+#    #+#             */
/*   Updated: 2019/04/25 16:13:58 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <string.h>
# include <stdint.h>

/*
** Macros
*/

# define BIGINT_SIZE       515
# define BIGINT_BLOCK_SIZE 32

/*
** Typedefs
*/

# ifndef __MY_TYPEDEFS__
#  define __MY_TYPEDEFS__

typedef char				t_char;
typedef	short				t_short;
typedef int					t_int;
typedef long int			t_lint;
typedef long long			t_llint;
typedef	unsigned char		t_uchar;
typedef unsigned short		t_ushort;
typedef unsigned int		t_uint;
typedef unsigned long		t_ulint;
typedef unsigned long long	t_ullint;
typedef float				t_float;
typedef double				t_dbl;
typedef long double			t_ldbl;

# endif

# ifndef __BASE__
#  define __BASE__

#  define DEC_BASE "0123456789"
#  define OCT_BASE "01234567"
#  define BIN_BASE "01"

# endif

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

typedef struct		s_bigint{
	size_t			length;
	t_uint			blocks[BIGINT_SIZE];
}					t_bigint;

/*
** Array
*/

void				ft_arraymergesort(int *array, size_t array_size);
void				ft_strarraymergesort(char **array, size_t array_size);

/*
** Bigint
*/

int					ft_bigint_comp(const t_bigint *bigint1,
						const t_bigint *bigint2);
t_bigint			*ft_bigint_add(const t_bigint *bigint1,
						const t_bigint *bigint2, t_bigint *result);
t_bigint			*ft_bigint_subst(const t_bigint *bigint1,
						const t_bigint *bigint2, t_bigint *result);
void				ft_bigint_order(const t_bigint *bigint1,
						const t_bigint *bigint2, const t_bigint **small_nb,
						const t_bigint **large_nb);
size_t				ft_bigint_size(const t_bigint *bigint);
t_bigint			*ft_uimax_to_bigint(uintmax_t nb, t_bigint *result);
t_bigint			*ft_bigint_shiftleft(t_bigint *result, t_uint shift);
t_bigint			*ft_bigint_cpy(t_bigint *dest, const t_bigint *src);
t_bigint			*ft_bigint_multiply_uint(t_bigint *result, t_uint nb);
t_bigint			*ft_bigint_multiply(const t_bigint *bigint1,
						const t_bigint *bigint2, t_bigint *result);
void				ft_bigint_pow10(t_bigint *result, t_uint exponent);
int					ft_bigint_divide(const t_bigint *dividend,
						const t_bigint *divisor);
char				*ft_strupper(char *str);
char				*ft_strtrim_spec(char const *s, char *spec);
char				*ft_strdel_ret_null(char **as);

/*
** Char
*/

int					ft_isalnum(int c);
int					ft_isalpha(int c);
int					ft_isascii(int c);
int					ft_isblank(int c);
int					ft_iscntrl(int c);
int					ft_isdigit(int c);
int					ft_isgraph(int c);
int					ft_islower(int c);
int					ft_isprint(int c);
int					ft_issign(int c);
int					ft_isspace(int c);
int					ft_isupper(int c);
int					ft_isxdigit(int c);
int					ft_tolower(int c);
int					ft_toupper(int c);

/*
** Convert
*/

char				*ft_imaxtoa_base(intmax_t nb, const char *base);
char				*ft_itoa(int n);
char				*ft_itoa_base(int n, int base_size);
char				*ft_uimaxtoa_base(uintmax_t nb, const char *base);
int					ft_atoi(const char *str);
int					ft_atois(const char *str, int *nb);
int					ft_check_int_overflow_add(int nb1, int nb2);
int					ft_check_int_overflow_multi(int nb1, int nb2);
int					ft_digits_base(intmax_t n, int radix);
int					ft_is_valid_base(const char *base);
int					ft_udigits_base(uintmax_t n, int radix);

/*
** List
*/

t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem),
						void (*del)(void *, size_t));
t_list				*ft_lstnew(void const *content, size_t content_size);
void				ft_lstadd(t_list **alst, t_list *new);
void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void				ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list				*ft_lstmergesort(t_list **lst, int (*cmp)());
t_list				*ft_lstrev(t_list **lst);
void				ft_lstsplithalf(t_list *lst, t_list **front, t_list **back);
int					ft_lstissorted(t_list *lst, int (*f)());
int					ft_lstcountif(t_list *lst, void *data_ref, int (*cmp)());
void				ft_lstget(t_list *lst, void *ret, void (*f)(void *, void*));
t_list				*ft_lstfindfirst(t_list *lst, void *data_ref, int (*cmp)());
t_list				*ft_lstfindlast(t_list *lst, void *data_ref, int (*cmp)());
int					ft_lstsize(t_list *lst);
int					ft_lsttointarray(t_list *lst, int **array, int (*f)());
int					ft_lsttostrarray(t_list *lst, char ***array, char *(*f)());
int					ft_lsthasdup(t_list **lst, int (*cmp)(),
						void (*del)(void *, size_t));
int					ft_lstmedian(t_list *lst, int (*f)(), int *median);

/*
** Math
*/

int					ft_exponent(long double value);
int					ft_power(int nb, int power);
intmax_t			ft_max(intmax_t n1, intmax_t n2);
intmax_t			ft_min(intmax_t n1, intmax_t n2);
unsigned int		ft_abs(int nb);

/*
** Mem
*/

int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				ft_bzero(void *s, size_t n);
void				ft_memdel(void **ap);
void				*ft_memalloc(size_t size);
void				*ft_memcat(void *s1, size_t n1, const void *s2, size_t n2);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memset(void *b, int c, size_t len);
void				*ft_memjoin(const void *s1, size_t n1, const void *s2,
						size_t n2);
void				*ft_memdup(const void *src, size_t size);
void				*ft_memcdup(const void *src, int c, size_t size,
						size_t *dst_size);

/*
** Print
*/

void				ft_print_bytes(void *ptr, size_t size);
void				ft_putchar(char c);
void				ft_putchar_fd(char c, int fd);
void				ft_putendl(char const *s);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putnbr(int n);
void				ft_putnbr_base(int nbr, int base_size);
void				ft_putnbr_fd(int n, int fd);
void				ft_putstr(char const *s);
void				ft_putstr_fd(char const *s, int fd);

/*
** Str
*/

char				**ft_strsplit(char const *s, char c);
char				*ft_strappend(char **str, const char *append);
char				*ft_strcat(char *s, const char *append);
char				*ft_strcdup(char const *s, char c);
char				*ft_strchr(const char *s, int c);
char				*ft_strcnew(size_t size, int c);
char				*ft_strcpy(char *dst, const char *src);
char				*ft_strcut(char **str, size_t len);
char				*ft_strdup(const char *s1);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char				*ft_strncat(char *s, const char *append, size_t count);
char				*ft_strncpy(char *dst, const char *src, size_t len);
char				*ft_strndup(const char *s1, size_t len);
char				*ft_strnew(size_t size);
char				*ft_strnstr(const char *s1, const char *s2, size_t len);
char				*ft_strpad_left(char **str, int c, size_t len);
char				*ft_strpad_right(char **str, int c, size_t len);
char				*ft_strprepend(const char *prepend, char **str);
char				*ft_strrchr(const char *s, int c);
char				*ft_strskip(const char *str, int (*f)(int));
char				*ft_strstr(const char *s1, const char *s2);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strtrim(char const *s);
int					ft_get_next_line(const int fd, char **line);
int					ft_instr(const char c, const char *str);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strdel_ret(char **as, int ret);
int					ft_strequ(char const *s1, char const *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t len);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
size_t				ft_count_words_c(char const *s, char c);
size_t				ft_strclcat(char *dst, size_t dst_size, char c,
						size_t size);
size_t				ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t				ft_strlen(const char *s);
void				ft_strclr(char *s);
void				ft_strdel(char **as);
void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));

#endif
