# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkettani <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/08 14:15:50 by jkettani          #+#    #+#              #
#    Updated: 2019/04/25 14:25:05 by jkettani         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ----- VARIABLES -----

NC =            \x1b[0m
OK_COLOR =      \x1b[32;01m
ERR_COLOR =     \x1b[31;01m
WARN_COLOR =    \x1b[34;01m
QUIET :=        @
ECHO :=         @echo
ifneq ($(QUIET),@)
ECHO :=         @true
endif
SHELL =         /bin/sh
MAKEFLAGS +=    --warn-undefined-variables
NAME =          libft.a
SRC_PATH =      srcs
INCLUDE_PATH =  includes
OBJ_PATH =      .obj
RM =            rm -f
RMDIR =         rmdir
AR =            ar
ARFLAGS =       -rcs
CC =            gcc
CFLAGS =        -g3 -Werror -Wall -Wextra
CPPFLAGS =      -I$(INCLUDE_PATH)
DEPFLAGS =      -MT $@ -MMD -MP -MF $(OBJ_PATH)/$*.d
COMPILE.c =     $(CC) $(CFLAGS) $(CPPFLAGS) $(DEPFLAGS) -c
POSTCOMPILE =   touch $@
SRC_ARRAY =     ft_arraymergesort
SRC_BIGINT =    ft_bigint_comp ft_bigint_add ft_bigint_subst ft_bigint_order \
				ft_bigint_size ft_uimax_to_bigint ft_bigint_shiftleft \
				ft_bigint_multiply_uint ft_bigint_cpy ft_bigint_multiply \
				ft_bigint_divide ft_bigint_pow10
SRC_CHAR =      ft_isalnum ft_isalpha ft_isascii ft_isblank ft_iscntrl \
			    ft_isdigit ft_isgraph ft_islower ft_isprint ft_isspace \
			    ft_isupper ft_isxdigit ft_tolower ft_toupper ft_issign
SRC_CONVERT =   ft_atoi ft_itoa ft_itoa_base ft_digits_base \
				ft_udigits_base ft_imaxtoa_base ft_uimaxtoa_base \
				ft_is_valid_base ft_atois ft_check_int_overflow_add \
				ft_check_int_overflow_multi
SRC_LIST =      ft_lstadd ft_lstdel ft_lstdelone ft_lstiter ft_lstmap \
				ft_lstnew ft_lstrev ft_lstsplithalf ft_lstmergesort \
				ft_lsthasdup ft_lstissorted ft_lstcountif ft_lstget \
				ft_lstfindfirst ft_lstfindlast ft_lstsize \
				ft_lsttointarray ft_lstmedian
SRC_MATH =      ft_power ft_min ft_max ft_exponent ft_abs
SRC_MEM =       ft_bzero ft_memalloc ft_memchr ft_memcmp ft_memcpy \
				ft_memccpy ft_memdel ft_memmove ft_memset ft_memcat \
				ft_memjoin ft_memdup ft_memcdup
SRC_PRINT =     ft_print_bytes ft_putchar ft_putchar_fd ft_putendl \
			    ft_putendl_fd ft_putnbr ft_putnbr_base ft_putnbr_fd \
			    ft_putstr ft_putstr_fd
SRC_STR =       ft_count_words_c ft_strcat ft_strchr ft_strclr ft_strcmp \
		        ft_strcpy ft_strdel ft_strdup ft_strcdup ft_strequ \
		        ft_striter ft_striteri ft_strjoin ft_strlcat ft_strlen \
		        ft_strmap ft_strmapi ft_strncat ft_strncmp ft_strncpy \
		        ft_strnequ ft_strnew ft_strnstr ft_strrchr ft_strsplit \
		        ft_strstr ft_strsub ft_strtrim ft_instr \
				ft_strappend ft_strprepend ft_strcnew ft_strpad_left \
				ft_strpad_right ft_strcut ft_strndup ft_strclcat ft_strdel_ret \
				ft_strupper ft_strtrim_spec ft_strdel_ret_null ft_strskip
SRC_NAME =      $(addprefix array/, $(SRC_ARRAY)) \
				$(addprefix bigint/, $(SRC_BIGINT)) \
				$(addprefix char/, $(SRC_CHAR)) \
				$(addprefix convert/, $(SRC_CONVERT)) \
				$(addprefix list/, $(SRC_LIST)) \
				$(addprefix math/, $(SRC_MATH)) \
				$(addprefix mem/, $(SRC_MEM)) \
				$(addprefix print/, $(SRC_PRINT)) \
				$(addprefix str/, $(SRC_STR))
SRC =           $(addprefix $(SRC_PATH)/, $(addsuffix .c, $(SRC_NAME)))
OBJ =           $(addprefix $(OBJ_PATH)/, $(SRC:.c=.o))
DEP =           $(addprefix $(OBJ_PATH)/, $(SRC:.c=.d))
OBJ_TREE =      $(shell find $(OBJ_PATH) -type d -print | sort -r \
				2> /dev/null)

.SUFFIXES:
.SUFFIXES: .c .o .h

# ----- RULES -----

.PHONY: all
all: $(NAME)

.PRECIOUS: $(OBJ_PATH)%/. $(OBJ_PATH)/. 
$(OBJ_PATH)/. $(OBJ_PATH)%/.: 
	$(ECHO) "Making directory $(WARN_COLOR)$@$(NC)..."
	$(QUIET) mkdir -p $@

$(OBJ_PATH)/%.d: ;

.SECONDEXPANSION:

$(OBJ): $(OBJ_PATH)/%.o: %.c $(OBJ_PATH)/%.d | $$(@D)/.
	$(ECHO) "Compiling $(WARN_COLOR)$<$(NC)..."
	$(QUIET) $(COMPILE.c) $< -o $@
	$(QUIET) $(POSTCOMPILE)

$(NAME): $(OBJ)
	$(ECHO) "Building archive file $(WARN_COLOR)$(NAME)$(NC)..."
	$(QUIET) $(AR) $(ARFLAGS) $@ $?

.PHONY: norminette
norminette:
	$(ECHO) "$(WARN_COLOR)Checking norminette on .h files...$(NC)"
	$(QUIET) norminette $(INCLUDE_PATH)
	$(ECHO) "$(WARN_COLOR)Checking norminette on .c files...$(NC)"
	$(QUIET) norminette $(SRC_PATH)

.PHONY: clean
clean:
	$(ECHO) "Cleaning object files..."
	$(QUIET) $(RM) $(OBJ)
	$(ECHO) "Cleaning dependency files..."
	$(QUIET) $(RM) $(DEP)
	$(ECHO) "Cleaning obj tree..."
	$(QUIET) echo $(OBJ_TREE) | xargs $(RMDIR) 2> /dev/null || true
	@if [ -d $(OBJ_PATH) ]; \
		then echo "$(ERR_COLOR)-> Could not clean obj directory.$(NC)"; \
		else echo "$(OK_COLOR)-> Obj directory succesfully cleaned.$(NC)"; fi

.PHONY: fclean
fclean: clean
	$(ECHO) "Cleaning $(NAME)..."
	$(QUIET) $(RM) $(NAME)
	@if [ -f $(NAME) ]; \
		then echo "$(ERR_COLOR)-> Could not clean $(NAME).$(NC)"; \
		else echo "$(OK_COLOR)-> $(NAME) succesfully cleaned.$(NC)"; fi

.PHONY: re
re: fclean all

# ----- INCLUDES -----

-include $(DEP)
