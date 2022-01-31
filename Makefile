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
DIR		= map set
DIRS	= $(addprefix $(BUILD)/, $(DIR))

INC		= -I./includes

MAIN	= main.cpp
OBJ_MAIN:= $(MAIN:%.cpp=$(BUILD)/%.o)

# MAP
MAP		= bounds.cpp copy_construct.cpp erase2.cpp find_count.cpp insert.cpp map.cpp op_sqbr.cpp rev_ite_construct.cpp rite.cpp tricky_construct.cpp comp.cpp empty.cpp erase.cpp insert2.cpp ite_arrow.cpp more.cpp relational_ope.cpp rite_arrow.cpp swap.cpp tricky_erase.cpp
SRC_MAP	= $(addprefix map/, $(MAP))
OBJ_MAP	:= $(SRC_MAP:%.cpp=$(BUILD)/%.o)

# SET
SET		= bounds.cpp erase2.cpp insert.cpp relational_ope.cpp swap.cpp comp.cpp erase.cpp ite_arrow.cpp rev_ite_construct.cpp tricky_construct.cpp copy_construct.cpp find_count.cpp set.cpp rite_arrow.cpp tricky_erase.cpp empty.cpp insert2.cpp  more.cpp rite.cpp
SRC_SET	= $(addprefix set/, $(SET))
OBJ_SET	:= $(SRC_SET:%.cpp=$(BUILD)/%.o)

# ALL
SRC		= $(SRC_MAP) $(SR)
NAME	= FT
DEP		:= $(SRC:%.cpp=$(BUILD)/%.d)
OBJ = $(OBJ_MAP) $(OBJ_SET) $(OBJ_MAIN)

# COMPILATION
CC		= clang++
CFLAGS	= -Wall -Werror -Wextra -std=c++98
DFLAGS  = -MP -MMD

$(NAME): $(OBJ)
	@$(CC) $(OBJ) -o $(NAME) -D USING_FT=1
	@$(CC) $(OBJ) -o STD -D USING_FT=0
	@echo "MAP COMPILED"

all: $(NAME)

set: $(NAME_SET)

clean:
	@rm -rf $(BUILD)
	@echo "\033[1;34mExecute:\t\033[1;33mCleaning build\t\033[0;32m[OK]\033[0m"

fclean: clean
	@rm -f $(NAME)
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
