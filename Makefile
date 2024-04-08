##
## EPITECH PROJECT, 2024
## Arcade
## File description:
## This is the Makefile for the Arcade project
## It compiles each games, drivers and the core
##

# All the source files
CXX_SOURCES		= 	src/main.cpp							\
					src/Arcade.cpp							\
					src/Player.cpp							\
					src/menu/Menu.cpp						\
					src/errors/NoSuchDriverException.cpp	\
					src/errors/LibraryFormatException.cpp	\

GAMES			= 	games/Pacman 			\
				  	games/Snake				\
				  	games/Cookie_Clicker	\

DRIVERS			= 	drivers/ncurses		\
				  	drivers/sdl2		\
				  	drivers/sfml		\

CXX_TESTS		=

# Compiler and linker settings
NAME 			= 	arcade
CXX				= 	g++
CXXFLAGS		= 	-W -Wall -Wextra -std=c++20 --coverage -I./include
CXX_OBJS		= 	$(CXX_SOURCES:.cpp=.o)
CXX_TESTS_OBJS	= 	$(CXX_TESTS:.cpp=.o)
JSON_LIB		= 	./libs/json
COMMON_LIB		= 	./libs/common
JSON_OBJS 		= 	$(JSON_LIB)/JsonObject.o	\
					$(JSON_LIB)/JsonArray.o		\
					$(JSON_LIB)/JsonString.o	\
					$(JSON_LIB)/JsonInt.o		\
					$(JSON_LIB)/JsonBoolean.o	\

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

LOG				= ./build.log

.PHONY: $(NAME) all clean fclean re tests_run clean_test \
	games $(GAMES) graphicals $(DRIVERS) \
	tests_games tests_drivers tests_libs shared $(JSON_LIB) clean_json \
	fclean_json $(COMMON_LIB) clean_common fclean_common

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

all:		$(GAMES) $(DRIVERS) $(NAME)

core:		$(NAME)
games:		$(GAMES)
graphicals:	$(DRIVERS)

shared:
		@printf "$(RUNNING) $(YELLOW) 📥  Init submodules$(RESET)"
		@git submodule init >> $(LOG) 2>&1 \
		&& printf "\r$(SUCCESS)\n" || (printf "\r$(FAILURE)\n" \
		&& cat $(LOG) && exit 1)
		@printf "$(RUNNING) $(YELLOW) 📥  Update submodules$(RESET)"
		@git submodule update --remote >> $(LOG) 2>&1 \
		&& printf "\r$(SUCCESS)\n" || (printf "\r$(FAILURE)\n" \
		&& cat $(LOG) && exit 1)

$(GAMES): shared
		@mkdir -p lib
		@printf "$(RUNNING) $(BLUE) 🔨  Building $@$(RESET)\n"
		@LOWERCASE_DIR=$$(echo $@ | sed 's:.*/::' \
		| tr '[:upper:]' '[:lower:]') ; \
		SO_NAME=arcade_$${LOWERCASE_DIR}.so ; \
		make -C $@ --silent && \
		printf "$(RUNNING) $(BLUE) 📦  Copying $${SO_NAME}$(RESET)" && \
		cp $@/$$SO_NAME lib/ && \
		printf "\r$(SUCCESS)\n" || printf "\r$(FAILURE)\n"

$(DRIVERS): shared
		@mkdir -p lib
		@printf "$(RUNNING) $(BLUE) 🔨  Building $@$(RESET)\n"
		@LOWERCASE_DIR=$$(echo $@ | sed 's:.*/::' \
		| tr '[:upper:]' '[:lower:]') ; \
		SO_NAME=arcade_$${LOWERCASE_DIR}.so ; \
		make -C $@ --silent && \
		printf "$(RUNNING) $(BLUE) 📦  Copying $${SO_NAME}$(RESET)" && \
		cp $@/$$SO_NAME lib/ && \
		printf "\r$(SUCCESS)\n" || printf "\r$(FAILURE)\n"

$(JSON_LIB):
		@printf "$(RUNNING) $(BLUE) 📚  Building json library$(RESET)"
		@if [ -f './libs/json/JsonObject.o' ]; then \
			printf "\r$(SKIPPED) $(RESET) 📚  Building json \
library (already built)\n"; \
		else \
			make -C $(JSON_LIB) >> $(LOG) 2>&1 \
			&& printf "\r$(SUCCESS)\n" || printf "\r$(FAILURE)\n"; \
		fi

$(COMMON_LIB):
		@printf "$(RUNNING) $(BLUE) 📚  Building common library$(RESET)"
		@if [ -f './libs/common/AGame.o' ]; then \
			printf "\r$(SKIPPED) $(RESET) 📚  Building common \
library (already built)\n"; \
		else \
			make -C $(COMMON_LIB) >> $(LOG) 2>&1 \
			&& printf "\r$(SUCCESS)\n" || printf "\r$(FAILURE)\n"; \
		fi

$(NAME):	shared $(JSON_LIB) $(COMMON_LIB) $(CXX_OBJS)
# Link the object files
		@printf "$(RUNNING) $(BLUE) 🔗  Linking$(RESET)"
		@$(CXX) -o $(NAME) $(CXX_OBJS) $(CXXFLAGS) $(JSON_OBJS) $(COMMON_OBJS)\
		$(shell [ `uname` != "Darwin" ] && echo "-fno-gnu-unique") \
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

clean_json:
		@printf "$(RUNNING) $(RED) 🗑️   Cleaning json library$(RESET)"
		@make -C $(JSON_LIB) clean >> $(LOG) 2>&1 \
		&& printf "\r$(SUCCESS)\n" || printf "\r$(FAILURE)\n"

clean_common:
		@printf "$(RUNNING) $(RED) 🗑️   Cleaning common library$(RESET)"
		@make -C $(COMMON_LIB) clean >> $(LOG) 2>&1 \
		&& printf "\r$(SUCCESS)\n" || printf "\r$(FAILURE)\n"

clean: clean_json clean_common
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

fclean_json:
		@printf "$(RUNNING) $(RED) 🗑️   Deleting json library$(RESET)"
		@make -C $(JSON_LIB) fclean >> $(LOG) 2>&1 \
		&& printf "\r$(SUCCESS)\n" || printf "\r$(FAILURE)\n"

fclean_common:
		@printf "$(RUNNING) $(RED) 🗑️   Deleting common library$(RESET)"
		@make -C $(COMMON_LIB) fclean >> $(LOG) 2>&1 \
		&& printf "\r$(SUCCESS)\n" || printf "\r$(FAILURE)\n"

fclean: clean clean_test fclean_json fclean_common
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
		@$(CXX) -o $@ -c $< $(CXXFLAGS) >> $(LOG) 2>&1 \
		&& printf "\r$(SUCCESS)\n" || printf "\r$(FAILURE)\n"

tests_games:
		@for game in $(GAMES); do \
			printf "$(RUNNING) $(BLUE) 🧪  Tests $$game$(RESET)"; \
			make -C $$game tests_run >> $(LOG) 2>&1 \
			&& printf "\r$(SUCCESS)\n" || printf "\r$(FAILURE)\n"; \
		done

tests_drivers:
		@for driver in $(DRIVERS); do \
			printf "$(RUNNING) $(BLUE) 🧪  Tests $$driver$(RESET)"; \
			make -C $$driver tests_run >> $(LOG) 2>&1 \
			&& printf "\r$(SUCCESS)\n" || printf "\r$(FAILURE)\n"; \
		done

tests_libs:
	@printf "$(RUNNING) $(BLUE) 🧪  Tests common$(RESET)"
	@make -C libs/common tests_run >> $(LOG) 2>&1 \
	&& printf "\r$(SUCCESS)\n" || printf "\r$(FAILURE)\n"
	@printf "$(RUNNING) $(BLUE) 🧪  Tests json$(RESET)"
	@make -C libs/json tests_run >> $(LOG) 2>&1 \
	&& printf "\r$(SUCCESS)\n" || printf "\r$(FAILURE)\n"

tests_run: fclean $(JSON_LIB) $(COMMON_LIB) $(CXX_OBJS) $(CXX_TESTS_OBJS) \
 	tests_games tests_drivers tests_libs
	@printf "$(RUNNING) $(BLUE) 🔗  Linking$(RESET)"
	@$(CXX) -o tests.out $(filter-out src/main.o, $(CXX_OBJS)) \
	$(CXX_TESTS_OBJS) $(CXXFLAGS) $(JSON_OBJS) $(COMMON_OBJS) --coverage \
	>> $(LOG) 2>&1 \
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
