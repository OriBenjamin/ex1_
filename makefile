COMPILER = gcc
OBJS = RLEList.o AsciiArtTool.o main.o
EXEC = AsciiArtTool
DEBUG_FLAG = -g
COMP_FLAG = -std=c99 -Wall -Werror

$(EXEC) : $(OBJS)
	$(COMPILER) $(DEBUG_FLAG) $(OBJS) -o $@
RLEList.o: RLEList.c RLEList.h
	$(COMPILER) -c $(DEBUG_FLAG) $(COMP_FLAG) RLEList.c
AsciiArtTool.o: AsciiArtTool.c AsciiArtTool.h RLEList.h
	$(COMPILER) -c $(DEBUG_FLAG) $(COMP_FLAG) AsciiArtTool.c
main.o: main.c AsciiArtTool.h RLEList.h
	$(COMPILER) -c $(DEBUG_FLAG) $(COMP_FLAG) main.c
clean:
	rm -f $(OBJS) $(EXEC)
	