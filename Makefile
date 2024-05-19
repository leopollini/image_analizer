NAME		= test

OBJDIR		= .objFiles
SRCDIR		= src

API1_FILES	= Pixel_counter
API2_FILES	= Cropper
API3_FILES	= Log_transformer

FILES		= main

API1		= Pixel_counter
API2		= Cropper
API3		= Log_transformer
APIS		= $(API1) $(API2) $(API3) #$(API4) $(API5) $(API6)
APISDIR		= apis

CXX			= g++
CXXFLAGS	= -Wall -Wextra
AR			= ar rc


HEADER		= libs/CImg.h


#Colors:
GREEN		=	\e[92;5;118m
YELLOW		=	\e[93;5;226m
GRAY		=	\e[33;2;37m
RESET		=	\e[0m
CURSIVE		=	\e[33;3m


all: $(NAME) $(HEADER)

$(NAME): $(APIS) $(OBJDIR)/$(FILES).o
	@$(CXX) $(CXXFLAGS) $(OBJDIR)/*.o -o $(NAME)
	@printf "$(_SUCCESS) $(GREEN)- Executable ready!\n$(RESET)"


$(API1): $(OBJDIR)/$(API1)/$(API1_FILES).o
	@mkdir -p $(APISDIR)
	@$(CXX) $(CXXFLAGS) $(OBJDIR)/$@/*.o -o $(APISDIR)/$@
	@printf "$(_SUCCESS) $(GREEN)- $@ maked!\n$(RESET)"

$(API2): $(OBJDIR)/$(API2)/$(API2_FILES).o
	@mkdir -p $(APISDIR)
	@$(CXX) $(CXXFLAGS) $(OBJDIR)/$@/*.o -o $(APISDIR)/$@
	@printf "$(_SUCCESS) $(GREEN)- $@ maked!\n$(RESET)"

$(API3): $(OBJDIR)/$(API3)/$(API3_FILES).o
	@mkdir -p $(APISDIR)
	@$(CXX) $(CXXFLAGS) $(OBJDIR)/$@/*.o -o $(APISDIR)/$@
	@printf "$(_SUCCESS) $(GREEN)- $@ maked!\n$(RESET)"


$(OBJDIR)/%.o : $(SRCDIR)/%.cpp $(HEADER)
	@mkdir -p $(dir $@)
	@echo compiling $@ ...
	@$(CXX) $(CXXFLAGS) -c $< -o $@
	

clean:
	@rm -rf $(OBJDIR) $(OBJ)
	@printf "$(YELLOW)    - Object files removed!$(RESET)\n"

fclean: clean
	@rm -rf $(NAME)
	@rm -rf $(APISDIR)
	@printf "$(YELLOW)    - Executable removed!$(RESET)\n"

re: fclean all

.PHONY:	clean fclean re all
