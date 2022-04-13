CPP = gcc
SOURCES = tlv_pull.c main.c
OBJS = $(SOURCES:.c=.o)
LDFLAGS = -lmxml
all: xml_to_tlv
xml_to_tlv: $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)
clean:
	rm -rf  *.o xml_to_tlv
