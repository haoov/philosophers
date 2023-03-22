#*************PROJECT*************#

PROJDIR			= $(realpath $(CURDIR))
NAME			= philo
SRCDIR			= $(PROJDIR)/srcs
HDDIR			= $(PROJDIR)/inc
OBJDIR			= $(PROJDIR)/objs
DEPDIR			= $(PROJDIR)/dep

#*************COMPILE*************#

CC				= cc
CFLAGS			= -Wall -Wextra -Werror
DEBUG			= -g -fsanitize=thread
INC				= -I $(HDDIR)

#**************FILES**************#

SRCS			= $(SRCDIR)/main.c\
				  $(SRCDIR)/init.c\
				  $(SRCDIR)/cleanup.c\
				  $(SRCDIR)/timestamp.c\
				  $(SRCDIR)/philosophers.c\
				  $(SRCDIR)/philo/philo_eat.c\
				  $(SRCDIR)/philo/philo_life.c\
				  $(SRCDIR)/philo/philo_log.c\
				  $(SRCDIR)/philo/philo_monitor.c\
				  $(SRCDIR)/philo/philo_put_down_forks.c\
				  $(SRCDIR)/philo/philo_think.c\
				  $(SRCDIR)/philo/philo_wait.c\
				  $(SRCDIR)/utils/ft_atoi.c\
				  $(SRCDIR)/utils/ft_strcmp.c\
				  $(SRCDIR)/utils/only_digit.c\
				  $(SRCDIR)/utils/ft_strlen.c\
				  $(SRCDIR)/utils/ft_calloc.c\
				  $(SRCDIR)/utils/ft_min.c\
				  $(SRCDIR)/utils/ft_max.c\
				  $(SRCDIR)/print/print_error.c\
				  $(SRCDIR)/print/print_helper.c\
				  $(SRCDIR)/print/print_log.c
HD				= $(HDDIR)/philo.h
OBJS			= $(patsubst $(SRCDIR)/%,$(OBJDIR)/%,$(SRCS:.c=.o))
DEPS			= $(patsubst $(SRCDIR)/%,$(DEPDIR)/%,$(SRCS:.c=.d))

#**************COLORS*************#

GREEN			= \033[0;32m
BLUE			= \033[0;34m
NC				= \033[0m

#***************PRINT*************#

DONE_PRINT		= @printf "$(GREEN)Done !$(NC)\n"

#***************RULES*************#

all : $(NAME)

$(NAME) : $(OBJS)
	$(DONE_PRINT)
	@printf "$(NC)Linking $@...$(NC)\033[0K\n"
	@$(CC) $(CFLAGS) $(OBJS) -o $@
	$(DONE_PRINT)

$(OBJDIR)/%.o : $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	@mkdir -p $(patsubst $(OBJDIR)/%,$(DEPDIR)/%,$(dir $@))
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@ \
		-MMD -MF $(patsubst $(OBJDIR)/%,$(DEPDIR)/%,$(@:.o=.d))
	@printf "$(NC)Building $(notdir $@)$(NC)\n"

-include $(DEPS)

clean :
	@printf "$(NC)Cleaning object files...$(NC)\n"
	@rm -rf $(OBJDIR)
	$(DONE_PRINT)
	@printf "$(NC)Cleaning dependency files...$(NC)\n"
	@rm -rf $(DEPDIR)
	$(DONE_PRINT)

fclean : clean
	@printf "$(NC)Cleaning target files...$(NC)\n"
	@rm -f $(NAME)
	$(DONE_PRINT)

re : fclean all

.PHONY : all clean fclean re