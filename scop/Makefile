# ---- NAME ---- #

NAME = obj_compile

CXX = c++ -std=c++11
# CXXFLAGS = -Wall -Wextra -Werror
DB = -g3
FA = -fsanitize=address
AR = ar
ARFLAG = ruc
RM = rm -f
INCLUDE = -I./include
GLUT = -L/System/Library/Frameworks -framework OpenGL -framework GLUT
GLFW = -lglfw3 -L./library -framework CoreVideo -framework OpenGL -framework IOKit -framework Cocoa -framework Carbon
GLEW = -lGLEW -L./library
LIB = $(GLFW) $(GLEW)

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

sources1 += src/main.cpp

sources1 += src/App.cpp

sources1 += src/ObjFile.cpp
sources1 += src/MtlFile.cpp
sources1 += src/Newmtl.cpp

sources1 += src/Camera.cpp
sources1 += src/Object.cpp

sources1 += src/Program.cpp
sources1 += src/texture.cpp

# ---- Bonus ---- #

sources2 :=

sources2 +=

# ---- Elements ---- #

all_sources = $(sources1) $(sources2)

objects1 = $(sources1:.cpp=.o)
objects2 = $(sources2:.cpp=.o)
all_objects = $(objects1) $(objects2)

define objects_goal
$(addprefix $(object_dir)/, $(call $(if $(filter bonus, $(MAKECMDGOALS)), all_objects, objects1)))
endef

define react
$(if $(filter bonus, $(MAKECMDGOALS)), bonus, all)
endef

# ---- Command ---- #

.PHONY : clean fclean re all bonus

all : $(NAME)

$(NAME) : $(objects_goal)
	@$(CXX) $(INCLUDE) $(DB) $(CXXFLAGS) $(LIB) -o $@ $(objects_goal)
	@echo "$(DELINE) $(MAGENTA)$@ $(RESET) is compiled $(GREEN)$(BOLD) OK ✅ $(RESET)"

bonus : $(NAME)

$(object_dir)/%.o : %.cpp
	@mkdir -p $(object_dir)
	@mkdir -p $(object_dir)/$(dir $^)
	@$(CXX) $(INCLUDE) $(DB) $(CXXFLAGS) -c $^ -o $@
	@echo " $(MAGENTA)$(NAME) $(RESET)objects file compiling... $(DELINE)$(GREEN) $^ $(RESET)$(CURSUP)"

clean :
	@$(RM) $(all_objects)
	@rm -rf $(object_dir)
	@echo "$(RED) Delete$(BOLD) objects $(RESTINT)file $(RESET)"

fclean : clean
	@$(RM) $(NAME)
	@echo "$(RED) Delete$(BOLD) $(NAME) $(RESTINT)file $(RESET)"

re : fclean
	@make $(react)
