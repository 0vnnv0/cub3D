# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lhagemos <lhagemos@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/26 12:43:46 by anschmit          #+#    #+#              #
#    Updated: 2025/06/18 12:48:47 by lhagemos         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC_DIR =	srcs
HDR_DIR =	includes
OBJ_DIR =	objs
LIBFT_DIR =	$(SRC_DIR)/libft
GNL_DIR =	$(SRC_DIR)/gnl

SRC_FLS =	$(LIBFT_FLS)\
					$(GNL_FLS)\

LIBFT_FLS =  ft_isalpha.c \
				 ft_isdigit.c \
				 ft_isalnum.c \
				 ft_isascii.c \
				 ft_isprint.c \
				 ft_strlen.c \
				 ft_memset.c \
				 ft_bzero.c \
				 ft_memcpy.c \
				 ft_memmove.c \
				 ft_strlcpy.c \
				 ft_strlcat.c \
				 ft_toupper.c \
				 ft_tolower.c \
				 ft_strchr.c \
				 ft_strrchr.c \
				 ft_strncmp.c \
				 ft_memchr.c \
				 ft_memcmp.c \
				 ft_strnstr.c \
				 ft_atoi.c \
				 ft_calloc.c \
				 ft_strdup.c \
				 ft_strjoin.c \
				 ft_strtrim.c \
				 ft_strmapi.c \
				 ft_striteri.c \
				 ft_striteri.c \
				 ft_putchar_fd.c \
				 ft_putstr_fd.c \
				 ft_putendl_fd.c \
				 ft_putnbr_fd.c \
				 ft_itoa.c \
				 ft_putchar.c \
				 ft_puthex.c \
				 ft_putnbr.c \
				 ft_putpointer.c \
				 ft_putstr.c \
				 ft_putui.c \
				 ft_lstnew.c \
				 ft_lstsize.c \
				 ft_lstlast.c \
				 ft_lstadd_front.c \
				 ft_lstadd_back.c \
				 ft_lstdelone.c \
				 ft_lstclear.c \
				 ft_lstiter.c \
				 ft_split.c 

GNL_FLS = get_next_line.c get_next_line_utils.c
	
SRCS =	$(addprefix $(LIBFT_DIR)/, $(LIBFT_FLS)) \
		$(addprefix $(GNL_DIR)/, $(GNL_FLS))
		
OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o, $(SRCS))
DEPS = $(OBJS:.o=.d)

CC =	cc
CFLGS = -Wall -Werror -Wextra
IFLGS =	-I $(HDR_DIR)

.PHONY: all clean fclean re

all: $(NAME)
	
-include $(DEPS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@mkdir -p $(@D)
	$(CC) $(CFLGS) $(IFLGS) -c -o $@ $<

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)/$(LIBFT_DIR)
	mkdir -p $(OBJ_DIR)/$(GNL_DIR)

$(NAME): $(OBJS)
		ar rc $(NAME) $(OBJS)
		ranlib $(NAME)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all 
