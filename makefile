CC = gcc
OBJS = RLEList.o AsciiArtTool.o main.o
EXEC = AsciiArtTool
TOOL_DIR = tool/
DEBUG_FLAG = -g
COMP_FLAG = -std=c99 -Wall -Werror 
$(EXEC) : $(OBJS)
	$(CC) $(DEBUG_FLAG) $(OBJS) -o $@
RLEList.o : RLEList.c RLEList.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) RLEList.c
AsciiArtTool.o: $(TOOL_DIR)AsciiArtTool.c $(TOOL_DIR)AsciiArtTool.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) AsciiArtTool.c
main.o: $(TOOL_DIR)main.c  $(TOOL_DIR)AsciiArtTool.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) main.c
clean:
	rm -f $(OBJS) $(EXEC)