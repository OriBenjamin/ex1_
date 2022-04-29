COMPILER = gcc
OBJS = RLEList.o AsciiArtTool.o main.o
EXEC = AsciiArtTool
DEBUG_FLAG = -g
COMP_FLAG = -std=c99 -Wall -Werror

$(EXEC) : $(OBJS)
	$(COMPILER) $(DEBUG_FLAG) $(OBJS) -o $@
RLEList.o: RLEList.c RLEList.h
	$(COMPILER ) -c RLEList.c
AsciiArtTool.o: AsciiArtTool.c AsciiArtTool.h RLEList.h
	$(COMPILER ) -c AsciiArtTool.c
main.o: main.c AsciiArtTool.h RLEList.h
	$(COMPILER ) -c main.c
clean:
	rm -f $(OBJS) $(EXEC)
	