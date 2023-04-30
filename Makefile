
### COMPILATION ###
CC      = gcc
FLAGS  = -Wall -Wextra -Werror

### EXECUTABLE ###
NAME   = pipex
NAME_BONUS = pipex_bonus

### INCLUDES ###
OBJ_PATH  = files/sources/objs
HEADER = files/includes
SRC_PATH  = files/sources
OBJ_PATH_BONUS  = files_bonus/sources/objs
HEADER_BONUS = files_bonus/includes
SRC_PATH_BONUS  = files_bonus/sources

### SOURCE FILES ###
SOURCES =     		main.c \
					utils.c \
					ft_split.c \
					libft_functs.c \
					free.c \
					forking.c \
					error.c \
					fds.c \
					gnl/get_next_line.c \
					gnl/get_next_line_utils.c \

SOURCES_BONUS =		main.c \
					utils.c \
					ft_split.c \
					libft_functs.c \
					free.c \
					forking.c \
					error.c \
					fds.c \
					heredoc.c \
					gnl/get_next_line.c \
					gnl/get_next_line_utils.c \

### OBJECTS ###

SRCS = $(addprefix $(SRC_PATH)/,$(SOURCES))
OBJS = $(addprefix $(OBJ_PATH)/,$(SOURCES:.c=.o))
SRCS_BONUS = $(addprefix $(SRC_PATH_BONUS)/,$(SOURCES_BONUS))
OBJS_BONUS = $(addprefix $(OBJ_PATH_BONUS)/,$(SOURCES_BONUS:.c=.o))


### COLORS ###
NOC         = \033[0m
BOLD        = \033[1m
UNDERLINE   = \033[4m
BLACK       = \033[1;30m
RED         = \033[1;31m
GREEN       = \033[1;32m
YELLOW      = \033[1;33m
BLUE        = \033[1;34m
VIOLET      = \033[1;35m
CYAN        = \033[1;36m
WHITE       = \033[1;37m

### RULES ###

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) -o $@ $^
	@echo "$(GREEN)Project successfully compiled"

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c $(HEADER)/$(NAME).h
	@$(CC) $(FLAGS) -c -o $@ $<
	@echo "$(BLUE)Creating object file -> $(WHITE)$(notdir $@)... $(RED)[Done]$(NOC)"

clean:
	@echo "$(GREEN)Supressing libraries files$(CYAN)"
	@rm -f $(OBJ_PATH)/*.o
	@rm -f $(OBJ_PATH)/*/*.o
	@rm -f $(OBJ_PATH_BONUS)/*.o
	@rm -f $(OBJ_PATH_BONUS)/*/*.o

fclean:
	@echo "$(GREEN)Supressing libraries files$(CYAN)"
	@rm -f $(OBJ_PATH)/*.o
	@rm -f $(OBJ_PATH)/*/*.o
	@rm -f $(OBJ_PATH_BONUS)/*.o
	@rm -f $(OBJ_PATH_BONUS)/*/*.o
	@rm -f $(NAME)
	@rm -f $(NAME_BONUS)

bonus: $(NAME_BONUS)
	
$(NAME_BONUS): $(OBJS_BONUS)
	$(CC) $(FLAGS) -o $@ $^
	@echo "$(GREEN)Project successfully compiled"

$(OBJ_PATH_BONUS)/%.o: $(SRC_PATH_BONUS)/%.c $(HEADER_BONUS)/pipex.h
	@$(CC) $(FLAGS) -c -o $@ $<
	@echo "$(BLUE)Creating object file -> $(WHITE)$(notdir $@)... $(RED)[Done]$(NOC)"

norminette:
	@norminette files/includes/*
	@norminette files/sources/*
	@norminette files_bonus/includes/* files_bonus/sources/*

re: fclean
	@$(MAKE) all

.PHONY: re fclean clean norminette bonus
