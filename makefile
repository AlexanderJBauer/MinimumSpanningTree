#OBJS specifies which files to compile as part of the project
OBJS = main.cpp

#CC specifies which compiler we're using
CC = g++

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
COMPILER_FLAGS = -Wall

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = prog2

#This is the target that compiles our executable
all :
	$(CC) $(OBJS) $(COMPILER_FLAGS) -o $(OBJ_NAME)

#This is the target that will clean our build directory (delete files)
clean :
	rm prog2
