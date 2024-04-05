##
## EPITECH PROJECT, 2024
## Arcade | Pacman
## File description:
## This is the Makefile for the Arcade project
## (more specifically the Pacman game)
## It job is to compile, clean and tests the project
##

# All the source files
CXX_SOURCES		= 	src/Pacman.cpp								\
					src/entities/Wall.cpp						\
					src/entities/APacManEntity.cpp				\
					src/entities/Pac.cpp						\
					src/entities/AGhost.cpp						\
					src/entities/PacDot.cpp						\
					src/entities/PacManText.cpp					\
					src/entities/LevelCounter.cpp				\
					src/entities/LiveCounter.cpp				\
					src/entities/ghosts/Pinky.cpp				\
					src/entities/ghosts/Blinky.cpp				\
					src/entities/ghosts/Inky.cpp				\
					src/entities/ghosts/Clyde.cpp				\
					src/utils/Move.cpp							\
					src/utils/GridCoordinate.cpp				\

CXX_TESTS		=

# Compiler and linker settings
NAME 			= 	arcade_pacman.so
COMMON_LIB      = 	../../libs/common
CXX				= 	g++
CXXFLAGS		= 	-W -Wall -Wextra -std=c++20 --coverage -I../../include \
					-fPIC
COMMON_OBJS 	= 	$(COMMON_LIB)/AGame.o									\
					$(COMMON_LIB)/utils/RGBAColor.o							\
					$(COMMON_LIB)/utils/Coord2D.o							\
					$(COMMON_LIB)/utils/Picture.o							\
					$(COMMON_LIB)/events/Event.o							\
					$(COMMON_LIB)/displayable/ADisplayable.o				\
					$(COMMON_LIB)/displayable/entities/SimpleSprite.o		\
					$(COMMON_LIB)/displayable/entities/AnimatedSprite.o		\
					$(COMMON_LIB)/displayable/entities/AEntity.o			\
					$(COMMON_LIB)/displayable/entities/SimpleEntity.o		\
					$(COMMON_LIB)/displayable/primitives/APrimitive.o		\
					$(COMMON_LIB)/displayable/primitives/Circle.o			\
					$(COMMON_LIB)/displayable/primitives/Square.o			\
					$(COMMON_LIB)/displayable/primitives/Text.o				\
					$(COMMON_LIB)/displayable/primitives/Line.o				\

CXX_OBJS		= 	$(CXX_SOURCES:.cpp=.o)
CXX_TESTS_OBJS	= 	$(CXX_TESTS:.cpp=.o)
LOG				= 	./build.log

.PHONY: $(NAME) all clean fclean re tests_run clean_test \
	common $(COMMON_LIB) clean_common fclean_common

# Colors and formatting
GREEN =		\033[1;32m
YELLOW =	\033[1;33m
RED =		\033[1;31m
BLUE =		\033[1;36m
GOLD =		\033[1;33m
MAGENTA =	\033[1;35m
RESET =		\033[0m

RUNNING = [$(YELLOW)~$(RESET)]
SUCCESS = [$(GREEN)✔$(RESET)]
FAILURE = [$(RED)✘$(RESET)]
SKIPPED = [$(MAGENTA)@$(RESET)]

all:		$(NAME)

$(NAME):	common $(CXX_OBJS)
# Link the object files
		@printf "$(RUNNING) $(BLUE) 🔗  Linking$(RESET)"
		@$(CXX) -shared -o $(NAME) $(CXX_OBJS) $(CXXFLAGS) $(COMMON_OBJS) \
		>> $(LOG) 2>&1 \
		&& printf "\r$(SUCCESS)\n" || printf "\r$(FAILURE)\n"
# Check if the binary was created
		@if [ -f $(NAME) ]; then \
			printf \
			"$(SUCCESS)$(GREEN)  🎉  $(NAME) built successfully$(RESET)\n";\
		else \
			printf "$(FAILURE)$(RED)  🚨  $(NAME) build failed$(RESET)\n"; \
			cat $(LOG); \
		fi

$(CXX_OBJS):	%.o: %.cpp
# Compile the source file
		@printf "$(RUNNING) $(BLUE) 🔨  $$(basename $<)$(RESET)"
		@$(CXX) -o $@ -c $< $(CXXFLAGS) >> $(LOG) 2>&1 \
		&& printf "\r$(SUCCESS)\n" || printf "\r$(FAILURE)\n"

common: $(COMMON_LIB)

$(COMMON_LIB):
		@printf "$(RUNNING) $(BLUE) 📚  Building common library$(RESET)"
		@if [ -f '../../libs/common/AGame.o' ]; then \
			printf "\r$(SKIPPED) $(RESET) 📚  Building common \
library (already built)\n"; \
		else \
			make -C ../../libs/common >> $(LOG) 2>&1 \
			&& printf "\r$(SUCCESS)\n" || printf "\r$(FAILURE)\n"; \
		fi

clean_common:
		@printf "$(RUNNING) $(RED) 🗑️   Cleaning common library$(RESET)"
		@make -C ../../libs/common clean >> $(LOG) 2>&1 \
		&& printf "\r$(SUCCESS)\n" || printf "\r$(FAILURE)\n"

fclean_common:
		@printf "$(RUNNING) $(RED) 🗑️   Deleting common library$(RESET)"
		@make -C ../../libs/common fclean >> $(LOG) 2>&1 \
		&& printf "\r$(SUCCESS)\n" || printf "\r$(FAILURE)\n"

clean: clean_common
# Delete all the object files
		@for file in $(CXX_OBJS); do \
			printf "$(RUNNING) $(RED) 🗑️   Deleting $$file$(RESET)"; \
			rm -f $$file >> $(LOG) 2>&1 \
			&& printf "\r$(SUCCESS)\n" || printf "\r$(FAILURE)\n"; \
		done

fclean: clean clean_test fclean_common
# Delete the binary
		@printf "$(RUNNING) $(RED) 🗑️   Deleting $(NAME)$(RESET)"
		@rm -f $(NAME) >> $(LOG) 2>&1 \
		&& printf "\r$(SUCCESS)\n" || printf "\r$(FAILURE)\n"
# Delete the log file
		@printf "$(RUNNING) $(RED) 🗑️   Deleting $(LOG)$(RESET)"
		@rm -f $(LOG) >> $(LOG) 2>&1 \
		&& printf "\r$(SUCCESS)\n" || printf "\r$(FAILURE)\n"

re:			fclean all

$(CXX_TESTS_OBJS):	%.o: %.cpp
		@printf "$(RUNNING) $(BLUE) 🔨  $$(basename $<)$(RESET)"
		@$(CXX) -o $@ -c $< $(CXXFLAGS) >> $(LOG) 2>&1 \
		&& printf "\r$(SUCCESS)\n" || printf "\r$(FAILURE)\n"

tests_run: fclean $(CXX_OBJS) $(CXX_TESTS_OBJS)
	@printf "$(RUNNING) $(BLUE) 🔗  Linking$(RESET)"
	@$(CXX) -o tests.out $(filter-out src/main.o, $(CXX_OBJS)) \
	$(CXX_TESTS_OBJS) $(CXXFLAGS) --coverage >> $(LOG) 2>&1 \
	-lcriterion >> $(LOG) 2>&1 \
	&& printf "\r$(SUCCESS)\n" || printf "\r$(FAILURE)\n";
	@printf "$(RUNNING)$(BLUE)  🧪  Running tests$(RESET)" \
	&& ./tests.out --xml=criterion.xml --ignore-warnings >> tests.log 2>&1 \
	&& printf "\r$(SUCCESS)\n" \
	|| printf "\r$(FAILURE)\n";
	@cat tests.log;
	@printf "$(RUNNING)$(YELLOW)  📊  Generating coverage$(RESET)" \
	&& gcovr --exclude tests/ >> coverage.log 2>&1 \
	&& printf "\r$(SUCCESS)\n" \
	|| printf "\r$(FAILURE)\n";
	@cat coverage.log;

clean_test:
	@printf "$(RUNNING) $(RED) 🗑️   Deleting tests.out$(RESET)"
	@rm -f tests.out >> $(LOG) 2>&1 \
	&& printf "\r$(SUCCESS)\n" || printf "\r$(FAILURE)\n"
	@printf "$(RUNNING) $(RED) 🗑️   Deleting coverage$(RESET)"
	@rm -f coverage* >> $(LOG) 2>&1 \
	&& printf "\r$(SUCCESS)\n" || printf "\r$(FAILURE)\n"
	@printf "$(RUNNING) $(RED) 🗑️   Deleting tests/*.o$(RESET)"
	@rm -f $(CXX_TESTS_OBJS) >> $(LOG) 2>&1 \
	&& printf "\r$(SUCCESS)\n" || printf "\r$(FAILURE)\n"
	@printf "$(RUNNING) $(RED) 🗑️   Deleting *.gcda$(RESET)"
	@find ./ -name "*.gcda" -delete >> $(LOG) 2>&1 \
	&& printf "\r$(SUCCESS)\n" || printf "\r$(FAILURE)\n"
	@printf "$(RUNNING) $(RED) 🗑️   Deleting *.gcno$(RESET)"
	@find ./ -name "*.gcno" -delete >> $(LOG) 2>&1 \
	&& printf "\r$(SUCCESS)\n" || printf "\r$(FAILURE)\n"
	@printf "$(RUNNING) $(RED) 🗑️   Deleting criterion.xml$(RESET)"
	@rm -f criterion.xml >> $(LOG) 2>&1 \
	&& printf "\r$(SUCCESS)\n" || printf "\r$(FAILURE)\n"
	@printf "$(RUNNING) $(RED) 🗑️   Deleting tests.log$(RESET)"
	@rm -f tests.log >> $(LOG) 2>&1 \
	&& printf "\r$(SUCCESS)\n" || printf "\r$(FAILURE)\n"
	@printf "$(RUNNING) $(RED) 🗑️   Deleting coverage.log$(RESET)"
	@rm -f coverage.log >> $(LOG) 2>&1 \
	&& printf "\r$(SUCCESS)\n" || printf "\r$(FAILURE)\n"
	@if [ -d .cache/ ]; then \
		printf "$(RUNNING) $(RED) 🗑️   Deleting .cache/$(RESET)"; \
		rm -rf .cache >> $(LOG) 2>&1 \
		&& printf "\r$(SUCCESS)\n" || printf "\r$(FAILURE)\n"; \
	fi
	@if [ -d .local/ ]; then \
		printf "$(RUNNING) $(RED) 🗑️   Deleting .local/$(RESET)"; \
		rm -rf .local >> $(LOG) 2>&1 \
		&& printf "\r$(SUCCESS)\n" || printf "\r$(FAILURE)\n"; \
	fi
