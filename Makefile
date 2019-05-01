# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: apion <apion@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/29 11:28:44 by apion             #+#    #+#              #
#    Updated: 2019/05/01 10:07:48 by apion            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SHELL		:= /bin/sh
RM			:= /bin/rm
CC			:= gcc
ifndef NOERR
CFLAGS		:= -Wall -Wextra -Werror
endif
ifdef LLDB
CC			+= -g
endif
CINCLUDES	= $(addprefix -I, $(H_DIR))
CPPFLAGS	= -MMD -MP -MF $(O_DIR)/$*.d

LIBFT_PATH		:= libft
LIBFT			:= $(LIBFT_PATH)/libft.a
FT_PRINTF_PATH	:= ft_printf
FT_PRINTF		:= $(FT_PRINTF_PATH)/libftprintf.a

NAME		:= lem-in
C_DIR		:= srcs
H_DIR		:= incs $(LIBFT_PATH)/includes $(FT_PRINTF_PATH)
O_DIR		:= .obj
C_FILES		:= \
	srcs/atoi_pos.c \
	srcs/bakery.c \
	srcs/cleaner.c \
	srcs/dijkstra.c \
	srcs/error.c \
	srcs/get_next_line.c \
	srcs/list_line.c \
	srcs/main.c \
	srcs/map.c \
	srcs/merge_sort.c \
	srcs/parser.c \
	srcs/parser_room.c \
	srcs/parser_tube.c \
	srcs/room.c \
	srcs/customlibft/ft_bsearch_id.c \
	srcs/customlibft/ft_nchar.c \
	srcs/customlibft/ft_queue.c \
	srcs/output/print_matrix.c \
	srcs/output/output.c
O_FILES		:= $(C_FILES:%.c=%.o)
D_FILES		:= $(C_FILES:%.c=%.d)
O_TREE		= $(shell find $(O_DIR) -type d -print 2> /dev/null | tail -r)

.SECONDEXPANSION:

.PHONY: all
all: $(NAME)

$(LIBFT): .FORCE
	@echo "Compiling lib $@..."
	@$(MAKE) -C $(@D)

$(FT_PRINTF): .FORCE
	@echo "Compiling lib $@..."
	@$(MAKE) -C $(@D)

$(NAME): $(addprefix $(O_DIR)/, $(O_FILES)) $(LIBFT) $(FT_PRINTF)
	@echo "Compiling executable $@..."
	@$(CC) $(CFLAGS) $(CINCLUDES) -o $@ $^
	@echo "Done."

$(O_DIR)/%.o: %.c
$(O_DIR)/%.o: %.c $(O_DIR)/%.d | $$(@D)/.
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) $(CPPFLAGS) $(CINCLUDES) -o $@ -c $<

.PRECIOUS: $(O_DIR)/. $(O_DIR)%/.
$(O_DIR)/.:
	@echo "Creating directory $@..."
	@mkdir -p $@
$(O_DIR)%/.:
	@echo "Creating directory $@..."
	@mkdir -p $@

.PRECIOUS: %.d
%.d: ;

.PHONY: clean
clean:
	@echo "Cleaning object files..."
	@-$(RM) $(addprefix $(O_DIR)/, $(O_FILES)) 2> /dev/null
	@echo "Cleaning dependencies files..."
	@-$(RM) $(addprefix $(O_DIR)/, $(D_FILES)) 2> /dev/null
	@echo "Removing $(O_DIR) tree..."
	@-echo $(O_TREE) | xargs rmdir 2> /dev/null
	@[ -d $(O_DIR) ] \
		&& echo "Could not remove $(O_DIR) tree." \
		|| echo "Successfully clean."

.PHONY: fclean
fclean: clean
	@echo "Removing file $(NAME)..."
	@-$(RM) $(NAME) 2> /dev/null
	@[ -f $(NAME) ] \
		&& echo "Could not remove $(NAME) file." \
		|| echo "Successfully clean."

.PHONY: re
re: fclean all

.FORCE:

-include $(addprefix $(O_DIR)/, $(D_FILES))
