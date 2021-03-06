CC=g++  -std=c++11
CFLAGS=-c -Wpedantic #-Ofast
LDFLAGS=
SOURCES=diseaseMonitor.cpp record.cpp record_HT.cpp utils.cpp cdHashTable.cpp bbst.cpp topk.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=diseaseMonitor



#syspro
#kuriws
all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

run:
	./$(EXECUTABLE) -p ../inputs/ass1_medium.txt -h1 20 -h2 20 -b 128

clean:
	rm -f $(OBJECTS) $(EXECUTABLE) $(TESTEXEC)

#./diseaseMonitor -p /home/demetres/Documents/sxoli/SYSPRO/FINAL_20/inputs/ass1_records.txt -h1 40 -h2 41 -b 20
