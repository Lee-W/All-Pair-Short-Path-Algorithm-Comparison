CC = g++-4.8
CFLAG = -std=c++11

BIN_DIR := bin
BUILD_DIR := build
SRC_DIR := src


gen: input/spflower.out
	@echo "Start generating test case"
	./input/generate_test_cases.sh input/test_case
	@echo "Finish generating test case"

input/spflower.out:
	gcc-4.8 -o $@ input/spflower.c

$(BUILD_DIR)/SpFileReader.o: $(SRC_DIR)/SpFileReader.cpp $(SRC_DIR)/SpFileReader.h
	@mkdir -p $(BUILD_DIR)
	$(CC) -c -o $@ $< $(CFLAG)

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR) input/spflower.out input/test*
