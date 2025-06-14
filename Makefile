CC = cc
CFLAGS = -Wall -Wextra -Werror -g

NAME = philo
OBJDIR = obj

PFLAGS = -pthread

SRCS = main.c init.c validation.c utils.c threads.c monitor.c actions.c forks.c

OBJS = $(SRCS:%.c=$(OBJDIR)/%.o)

all: $(NAME)

$(NAME): $(OBJDIR) $(OBJS)
	@$(CC) $(CFLAGS) $(PFLAGS) $(OBJS) -o $(NAME)
	@clear
	@echo "\n\033[1;36mprogram ready\033[0m\n"

$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: %.c philo.h
	@$(CC) -c $(CFLAGS) $< -o $@

clean:
	@rm -rf $(OBJDIR)
	@clear
	@echo "\n\033[32mdone\n\033[0m"

fclean: clean
	@rm -f $(NAME)
	@clear
	@echo "\n\033[32mdone\n\033[0m"
	
re: fclean all

.PHONY: all clean fclean re