NAME := ft_shmup

CC := cc
CFLAGS := -Wall -Werror -Wextra -MMD -MP

LIBRARY := -lncurses

INCLUDES := -I .

C_FILES := \
	main.c \
	init.c \
	creation.c \
	display.c \
	update.c \
	collision.c \
	frames.c \
	free_everything.c \

OBJ_DIR := .obj/
OBJ_FILES := $(addprefix $(OBJ_DIR), $(C_FILES:.c=.o))
D_FILES := $(OBJ_FILES:.o=.d)

.PHONY : all clean fclean re

all: $(NAME)

$(NAME): $(OBJ_FILES)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBRARY)

-include $(D_FILES)

$(OBJ_DIR)%.o : %.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $@

clean:
	rm -rf $(OBJ_DIR)

fclean:
	$(MAKE) clean
	rm -f $(NAME)

re:
	$(MAKE) fclean
	$(MAKE) all
