# This is a minimal set of ANSI/VT100 color codes
Color_Off=\033[0m
_GREEN=\033[1;32m
_CYAN=\033[1;36m
BRed=\033[1;31m         # Red
_Orange=\033[1;96m        # Blue
_Purple=\033[1;35m

# DIRECTORIES

BUILD	= .build

SRC_DIR	= ./src/
DIR		= map
DIRS	= $(addprefix $(BUILD)/, $(DIR))

INC		= -I./includes

# FILES
NAME_MAP= map_FT
MAP_STL	= map_STL
NAMES	= $(NAME_MAP) $(MAP_STL)

MAP		= bounds.cpp copy_construct.cpp erase2.cpp find_count.cpp insert.cpp main.cpp op_sqbr.cpp rev_ite_construct.cpp rite.cpp tricky_construct.cpp comp.cpp empty.cpp erase.cpp insert2.cpp ite_arrow.cpp more.cpp relational_ope.cpp rite_arrow.cpp swap.cpp tricky_erase.cpp

SRC_MAP	= $(addprefix map/, $(MAP))
OBJ_MAP	:= $(SRC_MAP:%.cpp=$(BUILD)/%.o)

SRC		= $(SRC_MAP)

DEP		:= $(SRC:%.cpp=$(BUILD)/%.d)

# COMPILATION
CC		= clang++
CFLAGS	= -Wall -Werror -Wextra -std=c++98
DFLAGS  = -MP -MMD

$(NAME_MAP): $(OBJ_MAP)
	@$(CC) $(OBJ_MAP) -o $(NAME_MAP) -D USING_FT=1
	@$(CC) $(OBJ_MAP) -o $(MAP_STL) -D USING_FT=0
	@echo "MAP COMPILED"

all: $(NAME_MAP) $(MAP_STL)

map: $(NAME_MAP)

clean:
	@rm -rf $(BUILD)
	@echo "\033[1;34mExecute:\t\033[1;33mCleaning build\t\033[0;32m[OK]\033[0m"

fclean: clean
	@rm -f $(NAMES)
	@echo "\033[1;34mExecute:\t\033[1;33mCleaning exec\t\033[0;32m[OK]\033[0m"

re: fclean all

$(BUILD):
	@echo "\033[1;32m\nCreation of .build\033[0m \n"
	@mkdir $@ $(DIRS)

$(BUILD)/%.o: $(SRC_DIR)%.cpp | $(BUILD)
	@printf "\033[1;34mExecute: \t\033[1;33mCompilation of \033[1;36m$(notdir $<) \033[0m \
	%-33.33s\r"
	@$(CC) $(CFLAGS) $(DFLAGS) -c $< -o $@ $(INC)


-include $(DEP)

.PHONY: all clean fclean re
