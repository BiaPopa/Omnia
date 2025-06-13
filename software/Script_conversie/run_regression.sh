#!/bin/bash

# Usage: ./run_regression.sh ASSIGN

RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m'

TEST_NAME="$1"
TESTS_DIR="tests"
RESULTS_DIR="$TESTS_DIR/results"
OUTPUT_FILE="program/program.ino"

INPUT_FILE="${TESTS_DIR}/program_${TEST_NAME}.st"
EXPECTED_FILE="${RESULTS_DIR}/result_${TEST_NAME}.ino"

if [ -z "$TEST_NAME" ]; then
  echo -e "${RED}[ERROR]${NC} You must provide a test name. Example: ./run_regression.sh ASSIGN"
  exit 1
fi

if [ ! -f "$INPUT_FILE" ]; then
    echo -e "${RED}[ERROR]${NC} Test input file not found: $INPUT_FILE"
    exit 1
fi

if [ ! -f "$EXPECTED_FILE" ]; then
    echo -e "${RED}[ERROR]${NC} Expected result file not found: $EXPECTED_FILE"
    exit 1
fi

rm -f "$OUTPUT_FILE"

echo "Running test: $TEST_NAME..."
SKIP_EXTRA=1 python3 convert.py "$INPUT_FILE"

if [ ! -f "$OUTPUT_FILE" ]; then
  echo -e "${RED}[ERROR]${NC} Output file $OUTPUT_FILE was not generated"
  exit 1
fi

if diff -Bb "$OUTPUT_FILE" "$EXPECTED_FILE" > /dev/null; then
    echo -e "${GREEN} ✅ PASSED: $TEST_NAME${NC}"
    exit 0
else
    echo -e "${RED} ❌ FAILED: $TEST_NAME${NC}"
    echo "Differences:"
    diff -Bb "$OUTPUT_FILE" "$EXPECTED_FILE"
    exit 1
fi
