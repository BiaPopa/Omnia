# Structured Text to Arduino Converter

This project provides a Python-based tool that converts Structured Text (ST) source code (in accordance with IEC 61131-3) into an equivalent Arduino-compatible .ino file, ready to be compiled and deployed on microcontrollers like ESP32 or Arduino boards.

## Features

- Parses standard **ST blocks** (assignments, timers, counters, comparisons, bitwise logic, selections, triggers)
- Maps ST memory addresses (`%IX`, `%QX`, `%IW`, `%QW`) to real GPIO pins using `address_mapper.py`
- Generates corresponding `setup()` and `loop()` functions based on the ST logic
- Adds correct `#define` statements and `pinMode()` configurations
- Integrates support for all major standard blocks defined in separate `.h` headers
- Supports optional **merging** of additional user-written `.ino` code (e.g., logging or display logic)
- Provides colored terminal output for better feedback (`INFO`, `SUCCESS`, `ERROR`)

---

## File Structure

```
project/
│
├── convert.py                # main script for converting ST to Arduino code
├── utils.py                  # colored logging and block definitions
├── address_mapper.py         # maps %IX, %QX, etc. to GPIOs
├── setup.py                  # generates setup() function content
├── loop.py                   # generates loop() function logic
├── merging.py                # optional merging with extra .ino file
│
├── include/                  # header files for standard function blocks
│   ├── bitwise.h
│   ├── comparison.h
│   ├── counters.h
│   ├── selection.h
│   ├── timers.h
│   └── triggers.h
│
├── tests/                    # regression tests
│   ├── program_*             # input test ST file
│   ├── results/
│       └── result_*          # expected .ino file after conversion
├── run_test.sh               # runs single test
└── run_all.sh                # runs all regression tests
```

---

## Usage

### Basic Conversion

To convert a ST program:

```bash
python3 convert.py program_name
```

If no file is provided, it defaults to program.st:

```bash
python3 convert.py
```

This generates program/program.ino.

### Optional: Merge With Extra Arduino Code

After conversion, you will be prompted:

```
Do you want to merge with another Arduino file? [y/N]:
```

If you reply with y or yes, the script will ask for a file path. The provided .ino file will be parsed and its components (#include, #define, setup(), loop(), other functions) will be inserted into the correct locations of the generated program.ino. Duplicates are removed automatically.

---

## GPIO Mapping

The script uses predefined mappings in `address_mapper.py` for:

- `%IX` – Digital Inputs  
- `%QX` – Digital Outputs  
- `%IW` – Analog Inputs  
- `%QW` – Analog Outputs  

Each is mapped to a specific GPIO pin using a lookup table. If a given address is not found, the script will return `"UNKNOWN"`.

Example:
```python
AddressMapper.get_gpio('%IX0.0')  # returns 17
```

---

## Regression Testing Framework

To validate script correctness, a **test framework** is included under `tests/`.

### Run a single test

```bash
chmod +x run_test.sh
./run_test.sh ASSIGN
```

- Converts `tests/program_ASSIGN` into `program/program.ino`
- Compares it against `tests/results/result_ASSIGN`
- Reports `PASSED` (green) or `FAILED` (red) along with a diff

### Run all tests

```bash
chmod +x run_all.sh
./run_all.sh
```

- Iterates through all files starting with `program_` inside `tests/`
- Runs each test individually and summarizes the results

---

## Requirements

- Python 3.7+
- POSIX shell (for test scripts)

---