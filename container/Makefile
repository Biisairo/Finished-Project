# ---- NAME ---- #

NAME = container

FT = ./libft/libft.a
FTCXX = -L./libft -lft

INCLUDE = -Iinclude/iterator -Iinclude/utils -Iinclude/STL

CXX = c++
CXXFLAGS = -Wall -Wextra -Werror
# CXXFLAGS = -Wall -Wextra -Werror -fsanitize=address -g
# CXXFLAGS = -g3 -fsanitize=address
AR = ar
ARFLAG = ruc
RM = rm -f

object_dir = ./objects

# ---- escape ---- #

DELINE = \033[K
CURSUP = \033[A

RESET = \033[0m
RESTINT = \033[22m

BOLD = \033[1m

MAGENTA = \033[35m
GREEN = \033[32m
RED = \033[31m

# ---- Mandatory ---- #

sources1 :=

sources1 +=

# ---- Bonus ---- #

sources2 :=

sources2 +=

# ---- Elements ---- #

all_sources = $(sources1) $(sources2)

objects1 = $(sources1:.cpp=.o)
objects2 = $(sources2:.cpp=.o)
all_objects = $(objects1) $(objects2)

define objects_goal
$(addprefix $(object_dir)/, $(call $(if $(filter bonus, $(MAKECMDGOALS)), objects2, objects1)))
endef

define react
$(if $(filter bonus, $(MAKECMDGOALS)), bonus, all)
endef

# ---- Command ---- #

.PHONY : clean fclean re all bonus

main :
	@make fclean
	@mkdir -p $(object_dir)
	@$(CXX) $(CXXFLAGS) -c src/main_test.cpp -o $(object_dir)/main_test.o $(INCLUDE)
	@$(CXX) $(CXXFLAGS) -o $(NAME) $(object_dir)/main_test.o $(INCLUDE)

test :
	cp include/*/*.hpp tester

re :
	make end; make test

end :
	make fclean; rm tester/*.hpp; cd tester/test; make fclean; cd ../speedtests; ./speedtests.sh clean; rm -rf tester/mii-tester/deepthought; rm -rf tester/mii-tester/logs

vector :
	@make fclean
	@mkdir -p $(object_dir)
	@$(CXX) $(CXXFLAGS) -c src/vector_test.cpp -o $(object_dir)/vector_test.o $(INCLUDE)
	@$(CXX) $(CXXFLAGS) -o $(NAME) $(object_dir)/vector_test.o $(INCLUDE)
	@./container
	@make fclean

stack :
	@make fclean
	@mkdir -p $(object_dir)
	@$(CXX) $(CXXFLAGS) -c src/stack_test.cpp -o $(object_dir)/stack_test.o $(INCLUDE)
	@$(CXX) $(CXXFLAGS) -o $(NAME) $(object_dir)/stack_test.o $(INCLUDE)
	@./container
	@make fclean

map :
	@make fclean
	@mkdir -p $(object_dir)
	@$(CXX) $(CXXFLAGS) -c src/map_test.cpp -o $(object_dir)/map_test.o $(INCLUDE)
	@$(CXX) $(CXXFLAGS) -o $(NAME) $(object_dir)/map_test.o $(INCLUDE)
	@./container
	@make fclean

set :
	@make fclean
	@mkdir -p $(object_dir)
	@$(CXX) $(CXXFLAGS) -c src/set_test.cpp -o $(object_dir)/set_test.o $(INCLUDE)
	@$(CXX) $(CXXFLAGS) -o $(NAME) $(object_dir)/set_test.o $(INCLUDE)
	@./container
	@make fclean

clean :
	@$(RM) $(all_objects)
	@rm -rf $(object_dir)

fclean : clean
	@$(RM) $(NAME)
	@rm -rf ./build
