##
## EPITECH PROJECT, 2024
## Arcade
## File description:
## This is the Makefile for the Arcade project
## It compiles each games, drivers and the core
##

# All the source files
CXX_SOURCES		= src/main.cpp		\

GAMES			= games/Pacman/ 	\
				  games/Snake/		\

DRIVERS			= drivers/ncurses/	\
				  drivers/sdl2/		\

CXX_TESTS		=

# Compiler and linker settings
NAME 			= arcade
XX				= g++
XXFLAGS			= -W -Wall -Wextra -std=c++20 --coverage -I./include
CXX_OBJS		= $(CXX_SOURCES:.cpp=.o)
CXX_TESTS_OBJS	= $(CXX_TESTS:.cpp=.o)
LOG				= ./build.log

.PHONY: $(NAME) all clean fclean re tests_run clean_test \
	$(CXX_OBJS) $(CXX_TESTS_OBJS) games $(GAMES) graphicals $(DRIVERS) \
	tests_games tests_drivers

# Colors and formatting
GREEN =		\033[1;32m
YELLOW =	\033[1;33m
RED =		\033[1;31m
BLUE =		\033[1;36m
GOLD =		\033[1;33m
RESET =		\033[0m

RUNNING = [$(YELLOW)~$(RESET)]
SUCCESS = [$(GREEN)✔$(RESET)]
FAILURE = [$(RED)✘$(RESET)]

all:		$(GAMES) $(DRIVERS) $(NAME)

games:		$(GAMES)
graphicals:	$(DRIVERS)

$(GAMES):
		@mkdir -p lib
		@printf "$(RUNNING) $(BLUE) 🔨  Building $@$(RESET)"
		@make -C $@ >> $(LOG) 2>&1 \
		&& (printf "\r$(SUCCESS)\n" && cp $@/*.so lib/) \
		|| printf "\r$(FAILURE)\n"

$(DRIVERS):
		@mkdir -p lib
		@printf "$(RUNNING) $(BLUE) 🔨  Building $@$(RESET)"
		@make -C $@ >> $(LOG) 2>&1 \
		&& (printf "\r$(SUCCESS)\n" && cp $@/*.so lib/) \
		|| printf "\r$(FAILURE)\n"

$(NAME):	$(CXX_OBJS)
# Link the object files
		@printf "$(RUNNING) $(BLUE) 🔗  Linking$(RESET)"
		@$(XX) -o $(NAME) $(CXX_OBJS) $(XXFLAGS) >> $(LOG) 2>&1 \
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
		@$(XX) -o $@ -c $< $(XXFLAGS) >> $(LOG) 2>&1 \
		&& printf "\r$(SUCCESS)\n" || printf "\r$(FAILURE)\n"

clean:
# Delete all the object files
		@for file in $(CXX_OBJS); do \
			printf "$(RUNNING) $(RED) 🗑️   Deleting $$file$(RESET)"; \
			rm -f $$file >> $(LOG) 2>&1 \
			&& printf "\r$(SUCCESS)\n" || printf "\r$(FAILURE)\n"; \
		done
		@for game in $(GAMES); do \
			printf "$(RUNNING) $(RED) 🗑️   Clean $$game$(RESET)"; \
			make -C $$game clean >> $(LOG) 2>&1 \
			&& printf "\r$(SUCCESS)\n" || printf "\r$(FAILURE)\n"; \
		done
		@for driver in $(DRIVERS); do \
			printf "$(RUNNING) $(RED) 🗑️   Clean $$driver$(RESET)"; \
			make -C $$driver clean >> $(LOG) 2>&1 \
			&& printf "\r$(SUCCESS)\n" || printf "\r$(FAILURE)\n"; \
		done

fclean: clean clean_test
# Delete the binary
		@printf "$(RUNNING) $(RED) 🗑️   Deleting $(NAME)$(RESET)"
		@rm -f $(NAME) >> $(LOG) 2>&1 \
		&& printf "\r$(SUCCESS)\n" || printf "\r$(FAILURE)\n"
		@for game in $(GAMES); do \
			printf "$(RUNNING) $(RED) 🗑️   Fclean $$game$(RESET)"; \
			make -C $$game fclean >> $(LOG) 2>&1 \
			&& printf "\r$(SUCCESS)\n" || printf "\r$(FAILURE)\n"; \
		done
		@for driver in $(DRIVERS); do \
			printf "$(RUNNING) $(RED) 🗑️   Fclean $$driver$(RESET)"; \
			make -C $$driver fclean >> $(LOG) 2>&1 \
			&& printf "\r$(SUCCESS)\n" || printf "\r$(FAILURE)\n"; \
		done
		@printf "$(RUNNING) $(RED) 🗑️   Deleting lib/$(RESET)"
		@rm -rf lib >> $(LOG) 2>&1 \
		&& printf "\r$(SUCCESS)\n" || printf "\r$(FAILURE)\n"
# Delete the log file
		@printf "$(RUNNING) $(RED) 🗑️   Deleting $(LOG)$(RESET)"
		@rm -f $(LOG) >> $(LOG) 2>&1 \
		&& printf "\r$(SUCCESS)\n" || printf "\r$(FAILURE)\n"

re:			fclean all

$(CXX_TESTS_OBJS):	%.o: %.cpp
		@printf "$(RUNNING) $(BLUE) 🔨  $$(basename $<)$(RESET)"
		@$(XX) -o $@ -c $< $(XXFLAGS) >> $(LOG) 2>&1 \
		&& printf "\r$(SUCCESS)\n" || printf "\r$(FAILURE)\n"

tests_games:
		@for game in $(GAMES); do \
			printf "$(RUNNING) $(BLUE) 🔨  Tests $$game$(RESET)"; \
			make -C $$game tests_run >> $(LOG) 2>&1 \
			&& printf "\r$(SUCCESS)\n" || printf "\r$(FAILURE)\n"; \
		done

tests_drivers:
		@for driver in $(DRIVERS); do \
			printf "$(RUNNING) $(BLUE) 🔨  Tests $$driver$(RESET)"; \
			make -C $$driver tests_run >> $(LOG) 2>&1 \
			&& printf "\r$(SUCCESS)\n" || printf "\r$(FAILURE)\n"; \
		done

tests_run: fclean $(CXX_OBJS) $(CXX_TESTS_OBJS)  tests_games tests_drivers
	@printf "$(RUNNING) $(BLUE) 🔗  Linking$(RESET)"
	@$(XX) -o tests.out $(filter-out src/main.o, $(CXX_OBJS)) \
	$(CXX_TESTS_OBJS) $(XXFLAGS) --coverage >> $(LOG) 2>&1 \
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
