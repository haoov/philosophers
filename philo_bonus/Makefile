#************PROGRESS*************#

ifndef PROGRESS
T := $(shell $(MAKE) $(MAKECMDGOALS) --no-print-directory \
      -nrRf $(firstword $(MAKEFILE_LIST)) \
      PROGRESS="COUNTTHIS" | grep -c "COUNTTHIS")
N := x
C = $(words $N)$(eval N := x $N)
PROGRESS = @printf "[%s/%s]\t\033[0K" $C $T
endif

#*************PROJECT*************#

PROJDIR			= $(realpath $(CURDIR))
NAME			= philo_bonus
SRCDIR			= $(PROJDIR)/srcs
HDDIR			= $(PROJDIR)/inc
OBJDIR			= $(PROJDIR)/objs
DEPDIR			= $(PROJDIR)/dep

#*************COMPILE*************#

CC				= cc
CFLAGS			= -Wall -Wextra -Werror
DEBUG			= -g -fsanitize=address
INC				= -I $(HDDIR)

#**************FILES**************#

SRCS			= $(SRCDIR)/main.c\
				  $(SRCDIR)/init.c\
				  $(SRCDIR)/cleanup.c\
				  $(SRCDIR)/utils/ft_atoi.c\
				  $(SRCDIR)/utils/ft_strcmp.c\
				  $(SRCDIR)/utils/only_digit.c\
				  $(SRCDIR)/utils/ft_strlen.c\
				  $(SRCDIR)/utils/ft_calloc.c\
				  $(SRCDIR)/utils/ft_max.c\
				  $(SRCDIR)/utils/ft_min.c\
				  $(SRCDIR)/print/print_log.c\
				  $(SRCDIR)/print/print_error.c\
				  $(SRCDIR)/print/print_helper.c\
				  $(SRCDIR)/process/process.c\
				  $(SRCDIR)/process/philo_life.c\
				  $(SRCDIR)/time/timestamp.c\
				  $(SRCDIR)/time/process_pause.c
HD				= $(HDDIR)/philo.h
OBJS			= $(patsubst $(SRCDIR)/%,$(OBJDIR)/%,$(SRCS:.c=.o))
DEPS			= $(patsubst $(SRCDIR)/%,$(DEPDIR)/%,$(SRCS:.c=.d))
#Only for implicit building rule
DEP_FILE		= $(patsubst $(OBJDIR)/%,$(DEPDIR)/%,$(@:.o=.d))

#**************COLORS*************#

GREEN			= \033[0;32m
BLUE			= \033[0;34m
NC				= \033[0m

#***************PRINT*************#

DONE_PRINT		= @printf "$(GREEN)Done !$(NC)\n"

#***************RULES*************#

all : $(NAME)

$(NAME) : $(OBJS)
	$(PROGRESS)
	@printf "$(NC)Linking $@...$(NC)\033[0K\n"
	@$(CC) $(CFLAGS) $(OBJS) -o $@
	$(DONE_PRINT)

$(OBJDIR)/%.o : $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	@mkdir -p $(patsubst $(OBJDIR)/%,$(DEPDIR)/%,$(dir $@))
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@ -MMD -MF $(DEP_FILE)
	$(PROGRESS)
	@printf "$(GREEN)Building $(notdir $@)$(NC)\n"

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