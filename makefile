CC       := gcc
CFLAGS   := -Wall -Wextra -O2
LDFLAGS  :=
LDLIBS   := -lm

TARGET   := ai-gpt.out
BUILD    := build

SRCS_C   := $(shell find . -name '*.c' 2>/dev/null)
OBJS     := $(patsubst %.c,$(BUILD)/%.o,$(SRCS_C))
DEPS     := $(OBJS:.o=.d)

# ============ 构建规则 ============
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS) $(LDLIBS)

$(BUILD)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

-include $(DEPS)

.PHONY: all clean rebuild run

clean:
	rm -rf $(BUILD) $(TARGET)

rebuild:
	$(MAKE) clean
	$(MAKE) all

run: all
	./$(TARGET)