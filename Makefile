TARGET = amigeconv

CC     = gcc
CFLAGS = -Wall -Werror -O3
LIBS   = -lm

SRCDIR = src
OBJDIR = obj
BINDIR = bin

SOURCES  := $(wildcard $(SRCDIR)/*.c) $(wildcard $(SRCDIR)/formats/*.c)
INCLUDES := $(wildcard $(SRCDIR)/*.h) $(wildcard $(SRCDIR)/formats/*.h)
OBJECTS  := $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

all: $(BINDIR)/$(TARGET)

$(BINDIR)/$(TARGET): $(OBJECTS)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(OBJECTS) $(LIBS) -o $@ 

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(INCLUDES)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean

clean:
	@rm -rf $(OBJDIR) $(BINDIR)
