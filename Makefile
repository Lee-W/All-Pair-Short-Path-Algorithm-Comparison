CC = g++-4.8
CFLAG = -std=c++11

BIN_DIR := bin
BUILD_DIR := build
SRC_DIR := src

$(BIN_DIR)/SPSPComparison.out: $(SRC_DIR)/APSPComparison.cpp \
							   $(BUILD_DIR)/APSPAlgorithms.o \
							   $(BUILD_DIR)/SSSPAlgorithms.o $(BUILD_DIR)/NodeComparator.o \
							   $(BUILD_DIR)/SpFileReader.o
	@mkdir -p $(BIN_DIR)
	$(CC) -o $@ $< $(SRC_DIR)/APSPAlgorithms.cpp\
				   $(SRC_DIR)/SSSPAlgorithms.cpp\
				   $(SRC_DIR)/SpFileReader.cpp $(SRC_DIR)/NodeComparator.cpp\
				   $(CFLAG)

$(BUILD_DIR)/APSPAlgorithms.o: $(SRC_DIR)/APSPComparison.cpp
	@mkdir -p $(BUILD_DIR)
	$(CC) -c -o $@ $< $(CFLAG)

$(BUILD_DIR)/SSSPAlgorithms.o: $(SRC_DIR)/SSSPAlgorithms.cpp
	@mkdir -p $(BUILD_DIR)
	$(CC) -c -o $@ $< $(CFLAG)

$(BUILD_DIR)/NodeComparator.o: $(SRC_DIR)/NodeComparator.cpp
	@mkdir -p $(BUILD_DIR)
	$(CC) -c -o $@ $< $(CFLAG)

$(BUILD_DIR)/SpFileReader.o: $(SRC_DIR)/SpFileReader.cpp $(SRC_DIR)/SpFileReader.h
	@mkdir -p $(BUILD_DIR)
	$(CC) -c -o $@ $< $(CFLAG)

gen: input/spflower.out
	@echo "Start generating test case"
	./input/generate_test_cases.sh input/test_case
	@echo "Finish generating test case"

input/spflower.out:
	gcc-4.8 -o $@ input/spflower.c

run_all_test_case:
	./input/run_all_case.sh bin input/test_case

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)

clean_test_case:
	rm -rf input/spflower.out input/test_case/

clean_output:
	rm -rf output
