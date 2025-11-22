RED			= \033[1;31m
GREEN		= \033[1;32m
BLUE		= \033[1;34m
CYAN		= \033[1;36m
WHITE		= \033[0;37m

NAME		= claptrap
CC			= c++
CFLAGS	= -Wall -Wextra -Werror -std=c++98
INC			= -I inc/
SRCPATH = src/
SRC			= main.cpp ClapTrap.cpp
RM			= rm -rf

OBJDIR	= .config/obj/
OBJ			= $(addprefix $(OBJDIR), $(SRC:.cpp=.o))

DEPDIR	= .config/dep/
DEP			= $(addprefix $(DEPDIR), $(SRC:.cpp=.d))

all : $(NAME)

$(OBJDIR)%.o: $(SRCPATH)%.cpp
	@mkdir -p $(@D) $(DEPDIR)
	@echo "$(BLUE)Compiling$(WHITE) $<..."
	@$(CC) $(CFLAGS) $(INC) -MMD -MP -MF $(DEPDIR)$*.d -c $< -o $@

$(NAME): $(OBJ)
	@echo "$(CYAN)Linking$(WHITE) $(NAME)..." 
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@echo "$(GREEN)Done$(WHITE)"

-include $(DEP)

clean :
	@echo "$(RED)Cleaning$(WHITE) $(NAME)..."
	@$(RM) .config
	@echo "$(GREEN)Done$(WHITE)"

fclean : clean
	@$(RM) $(NAME)

re : fclean all

.PHONY : all clean fclean re