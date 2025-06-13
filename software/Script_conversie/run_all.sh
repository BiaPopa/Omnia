#!/bin/bash

# Usage: ./run_all.sh

RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m'

ALL_PASSED=true

for st_file in tests/program_*.st; do
    # extract test name (e.g. ASSIGN)
    filename=$(basename -- "$st_file")
    TEST_NAME="${filename#program_}"
    TEST_NAME="${TEST_NAME%.st}"

    TESTS_DIR="tests"
    RESULTS_DIR="$TESTS_DIR/results"
    OUTPUT_FILE="program/program.ino"

    INPUT_FILE="${TESTS_DIR}/program_${TEST_NAME}.st"
    EXPECTED_FILE="${RESULTS_DIR}/result_${TEST_NAME}.ino"

    if [ ! -f "$EXPECTED_FILE" ]; then
        echo -e "${RED}[ERROR]${NC} Expected result file not found: $EXPECTED_FILE"
        echo -e "${RED} ❌ FAILED: $TEST_NAME${NC}"
        ALL_PASSED=false
        continue
    fi

    rm -f "$OUTPUT_FILE"

    echo "Running test: $TEST_NAME..."
    SKIP_EXTRA=1 python3 convert.py "$INPUT_FILE"

    if [ ! -f "$OUTPUT_FILE" ]; then
        echo -e "${RED}FAILED: $TEST_NAME${NC} (output file not generated)"
        echo -e "${RED} ❌ FAILED: $TEST_NAME${NC}"
        All_PASSED=false
        continue
    fi

    if diff -Bb "$OUTPUT_FILE" "$EXPECTED_FILE" > /dev/null; then
        echo -e "${GREEN} ✅ PASSED: $TEST_NAME${NC}"
    else
        echo -e "${RED} ❌ FAILED: $TEST_NAME${NC}"
        echo "Differences:"
        diff -Bb "$OUTPUT_FILE" "$EXPECTED_FILE"
        ALL_PASSED=false
    fi
done

if $ALL_PASSED; then
    echo -e "\n${GREEN}All tests passed successfully!${NC}"
else
    echo -e "\n${RED}Some tests failed.${NC}"
fi