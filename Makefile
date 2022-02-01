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
DIR		=
DIRS	= $(addprefix $(BUILD)/, $(DIR))

INC		= -I./includes

# FILES
NAME	= ft
NAME1	= stl

SRC		= main.cpp \
		  test_vector.cpp \
		  test_stack.cpp \
		  test_map.cpp \
		  test_set.cpp


DEP		:= $(SRC:%.cpp=$(BUILD)/%.d)
OBJ		:= $(SRC:%.cpp=$(BUILD)/%.o)

# COMPILATION
CC		= clang++
CFLAGS	= -Wall -Werror -Wextra -std=c++98
DFLAGS  = -MP -MMD

$(NAME): $(OBJ)
	@$(CC) $(OBJ) -o $(NAME) -D TEST_FT=1
	@$(CC) $(OBJ) -o $(NAME1) -D TEST_FT=0


all: $(NAME)

clean:
	@rm -rf $(BUILD)
	@rm -rf test/root
	@echo "\033[1;34mExecute:\t\033[1;33mCleaning build\t\033[0;32m[OK]\033[0m"

fclean: clean
	@rm -f $(NAME) $(NAME1)
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
