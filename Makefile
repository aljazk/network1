TARGET=release/netc
CFLAGS=-Wall -Wextra -DSFML_STATIC
LFLAGS=-static \
	-lsfml-graphics-s -lsfml-window-s -lsfml-network-s -lsfml-system-s \
	-ljpeg -lglew32 -lfreetype \
	-lgdi32 -lopengl32 -lwinmm -lws2_32
FILES=main.cpp

OBJS=$(patsubst %,build/%.o,$(basename $(FILES)))
.PHONY: all clean
all: $(TARGET)
$(TARGET): $(OBJS)
	@echo "Linking..."
	@mkdir -p $(@D)
	@g++ $(OBJS) $(LFLAGS) -o $(TARGET)
	@echo "Done."
build/%.o: src/%.cpp
	@echo "Compiling $<"
	@mkdir -p $(@D)
	@g++ -c $< $(CFLAGS) -o $@
build/%.o: src/%.c
	@echo "Compiling $<"
	@mkdir -p $(@D)
	@g++ -c $< $(CFLAGS) -o $@
src/%.cpp : src/%.hpp
src/%.c : src/%.h
clean:
	@rm -rf *.o $(TARGET) $(TARGET).exe build/
	@echo "Cleaned."
