CXXFLAGS=-g -W -Wall -O2

all: producer consumer

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

producer: shm_double_buffer.o producer.o
	$(CXX) $(LDFLAGS) -o $@ $^ -pthread

consumer: shm_double_buffer.o consumer.o
	$(CXX) $(LDFLAGS) -o $@ $^ -pthread

