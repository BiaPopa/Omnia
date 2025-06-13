import os
import sys
import stat
import shutil
import merging

from pathlib import Path
from setup import generate_setup
from loop import generate_loop
from address_mapper import AddressMapper as pin
from utils import (
    counter_blocks, 
    comparison_blocks, 
    selection_blocks, 
    bitwise_blocks
)
from utils import (
    print_info, 
    print_success, 
    print_error
)

def remove_folder(folder_path):
    """
    Recursively remove a folder and all its contents

    Args:
        folder_path (str): Path to the folder to be removed
    """
    folder = Path(folder_path)
    if folder.exists() and folder.is_dir():
        for item in folder.rglob('*'):
            if item.is_file() or item.is_symlink():
                item.chmod(stat.S_IWRITE)
                item.unlink()
            elif item.is_dir():
                remove_folder(item)
        folder.rmdir()

def handle_include_and_copy(functional_standard_blocks, destination_folder="program"):
    """
    Check which include files are needed based on the functional standard blocks
    and copy them to the destination folder if they do not already exist

    Args:
        functional_standard_blocks (dict): Mapping of block instance names to block types
        destination_folder (str): Folder where the include files should be copied
    
    Returns:
        str: A string containing the necessary include statements
    """
    includes = []

    needs_timer_include = any(
        bloc_type in ['TON', 'TOF', 'TP'] for bloc_type in functional_standard_blocks.values()
    )

    needs_counter_include = any(
        bloc_type in counter_blocks for bloc_type in functional_standard_blocks.values()
    )

    needs_trigger_include = any(
        bloc_type in ['R_TRIG', 'F_TRIG', 'SR', 'RS', 'SEMA'] for bloc_type in functional_standard_blocks.values()
    )

    needs_comparison_include = any(
        bloc_type.startswith(prefix) for prefix in comparison_blocks for bloc_type in functional_standard_blocks.values()
    )

    needs_selection_include = any(
        bloc_type.startswith(prefix) for prefix in selection_blocks for bloc_type in functional_standard_blocks.values()
    )

    needs_bitwise_include = any(
        bloc_type in bitwise_blocks for bloc_type in functional_standard_blocks.values()
    )

    if needs_timer_include:
        source_path = os.path.join("include", "timers.h")
        destination_path = os.path.join(destination_folder, "timers.h")

        if not os.path.exists(source_path):
            print_error(f"Missing required include file: {source_path}")
            sys.exit(1)

        if not os.path.exists(destination_path):
            shutil.copy(source_path, destination_path)

        includes.append('#include <timers.h>\n')

    if needs_counter_include:
        source_path = os.path.join("include", "counters.h")
        destination_path = os.path.join(destination_folder, "counters.h")

        if not os.path.exists(source_path):
            print_error(f"Missing required include file: {source_path}")
            sys.exit(1)

        if not os.path.exists(destination_path):
            shutil.copy(source_path, destination_path)

        includes.append('#include <counters.h>\n')

    if needs_trigger_include:
        source_path = os.path.join("include", "triggers.h")
        destination_path = os.path.join(destination_folder, "triggers.h")

        if not os.path.exists(source_path):
            print_error(f"Missing required include file: {source_path}")
            sys.exit(1)

        if not os.path.exists(destination_path):
            shutil.copy(source_path, destination_path)

        includes.append('#include <triggers.h>\n')

    if needs_comparison_include:
        source_path = os.path.join("include", "comparison.h")
        destination_path = os.path.join(destination_folder, "comparison.h")

        if not os.path.exists(source_path):
            print_error(f"Missing required include file: {source_path}")
            sys.exit(1)

        if not os.path.exists(destination_path):
            shutil.copy(source_path, destination_path)

        includes.append('#include <comparison.h>\n')

    if needs_selection_include:
        source_path = os.path.join("include", "selection.h")
        destination_path = os.path.join(destination_folder, "selection.h")

        if not os.path.exists(source_path):
            print_error(f"Missing required include file: {source_path}")
            sys.exit(1)

        if not os.path.exists(destination_path):
            shutil.copy(source_path, destination_path)

        includes.append('#include <selection.h>\n')

    if needs_bitwise_include:
        source_path = os.path.join("include", "bitwise.h")
        destination_path = os.path.join(destination_folder, "bitwise.h")

        if not os.path.exists(source_path):
            print_error(f"Missing required include file: {source_path}")
            sys.exit(1)

        if not os.path.exists(destination_path):
            shutil.copy(source_path, destination_path)

        includes.append('#include <bitwise.h>\n')

    return ''.join(includes)

def between(text, start_char, end_char):
    """
    Returns substring found between the first occurrences of start_char and end_char

    Args:
        text (str): The input string
        start_char (str): Starting delimiter
        end_char (str): Ending delimiter

    Returns:
        str or None: Substring between the delimiters, or None if not found
    """
    start = text.find(start_char)
    end = text.find(end_char, start + 1)

    if start != -1 and end != -1:
        return text[start + 1:end]
    
    return None

def params_type(param, var_types, functional_standard_blocks):
    """
    Determines the type of a parameter based on its value and context
    
    Args:
        param (str): The parameter name
        var_types (dict): Dictionary mapping variable names to their types
        functional_standard_blocks (dict):  Mapping of instance names to their block definitions
    
    Returns:
        str: A template-style type string, like '<int>' or '<bool>'
    """
    comp_type = '<'
    
    if param in var_types:
        comp_type += var_types[param].lower()
    elif param.isdigit():
        comp_type += 'int'
    elif param.lower() == 'true' or param.lower() == 'false':
        comp_type += 'bool'
    elif '.' in param and 'CV' in param:
        comp_type += 'int'
    elif param in functional_standard_blocks:
        block = functional_standard_blocks[param].split('<')[0].strip()

        if block in selection_blocks or block in bitwise_blocks:
            comp_type += between(functional_standard_blocks[param], '<', '>')
    else:
        comp_type += 'bool'

    comp_type += '>'
    return comp_type

def parse_st_file(filename):
    """
    Parses a structured text (.st) file to extract digital and analog inputs/outputs,
    variable types, functional standard blocks, instructions and standard block calls
    
    Args:
        filename (str): Path to the .st file to be parsed
    
    Returns:
        tuple: Contains dictionaries for inputs and outputs (digital and analog),
            variable types, functional standard blocks, instructions and standard block calls
    """
    inputs_digital = {}
    inputs_analog = {}
    outputs_digital = {}
    outputs_analog = {}
    var_types = {}
    functional_standard_blocks = {}

    instructions = []
    standard_block_calls = []

    try:
        with open(filename, 'r') as file:
            lines = file.readlines()
            print_info(f"Loaded {len(lines)} lines from {st_filename}")
    except Exception as e:
        print_error(f"Failed to read file {st_filename}")
        sys.exit(1)

    if not any("PROGRAM" in line for line in lines) or not any("END_PROGRAM" in line for line in lines):
        print_error("Input file does not contain a valid PROGRAM block.")
        sys.exit(1)

    inside_var = False
    inside_program = False

    for line in lines:
        line = line.strip()

        if line.startswith('PROGRAM'):
            inside_program = True
            continue

        if line.startswith('END_PROGRAM'):
            inside_program = False
            break

        if inside_program:
            if line.startswith('VAR'):
                inside_var = True
                continue

            if line.startswith('END_VAR'):
                inside_var = False
                continue

            if inside_var:
                # handle address-based declarations
                if 'AT' in line:
                    parts = line.split('AT')
                    if len(parts) == 2:
                        var_name = parts[0].strip()
                        address = parts[1].strip().split()[0] 
                        type = parts[1].strip().split()[2].replace(';', '') if len(parts[1].strip().split()) > 2 else None
                        
                        if address.startswith('%IX'):
                            inputs_digital[var_name] = address
                        elif address.startswith('%IW'):
                            inputs_analog[var_name] = address
                        elif address.startswith('%QX'):
                            outputs_digital[var_name] = address
                        elif address.startswith('%QW'):
                            outputs_analog[var_name] = address
                        var_types[var_name] = type
                elif ':' in line and ';' in line:
                    name, block_type = line.replace(';', '').split(':')[0], line.replace(';', '').split(':')[1]
                    functional_standard_blocks[name.strip()] = block_type.strip()
            else:
                # handle functional standard blocks and instructions
                if '(' in line and ')' in line and ';' in line:
                    name, rest = line.split('(', 1)
                    params_raw = rest.split(');')[0]
                    params_list = params_raw.split(',')
                    tip = None

                    if ':=' in name:
                        name, tip = name.split(':=')
                        
                        if tip.strip() == 'SEL' or tip.strip() == 'MUX':
                            functional_standard_blocks[name.strip()] = tip.strip() + params_type(params_list[1].strip(), var_types, functional_standard_blocks)
                        elif tip.strip() in bitwise_blocks:
                            functional_standard_blocks[name.strip()] = tip.strip()
                        else:
                            functional_standard_blocks[name.strip()] = tip.strip() + params_type(params_list[0].strip(), var_types, functional_standard_blocks)
                    
                    if name.strip() in functional_standard_blocks:
                        parametri = {}

                        for i in range(len(params_list)):
                            p = params_list[i]

                            if p.strip() in functional_standard_blocks:
                                p += '.OUT'

                            if ':=' in p:
                                k, v = p.split(':=')
                                parametri[k.strip()] = v.strip()
                            elif tip != None and tip.strip().startswith('SEL'):
                                if i == 0:
                                    parametri['G'] = p.strip()
                                else:
                                    k = 'IN' + str(i - 1)
                                    parametri[k] = p.strip()
                            elif tip != None and tip.strip().startswith('LIMIT'):
                                if i == 0:
                                    parametri['MN'] = p.strip()
                                elif i == 1:
                                    parametri['IN'] = p.strip()
                                elif i == 2:
                                    parametri['MX'] = p.strip()
                            elif tip != None and tip.strip().startswith('MUX'):
                                if i == 0:
                                    parametri['K'] = p.strip()
                                else:
                                    k = 'IN' + str(i - 1)
                                    parametri[k] = p.strip()
                            elif tip != None and tip.strip().startswith('NOT'):
                                if i == 0:
                                    parametri['IN'] = p.strip()
                            else:
                                k = 'IN' + str(i + 1)
                                parametri[k] = p.strip()

                        standard_block_calls.append({
                            "instanta": name.strip(),
                            "tip": functional_standard_blocks[name.strip()],
                            "parametri": parametri
                        }) 
                elif ':=' in line and ';' in line:
                    instructions.append(line.strip())

    return inputs_digital, inputs_analog, outputs_digital, outputs_analog, var_types, functional_standard_blocks, instructions, standard_block_calls


if __name__ == "__main__":
    if len(sys.argv) > 1 and sys.argv[1] in ['--help', '-h']:
        print_info("Usage: python convert.py [input_file.st]")
        print_info("If no file is given, defaults to program.st")
        sys.exit(0)

    if len(sys.argv) > 1:
        st_filename = sys.argv[1]
        print_info(f"Using provided file: {st_filename}")
    else:
        st_filename = "program.st"
        print_info(f"No filename provided. Using default: {st_filename}")

    # validate the input file
    if not os.path.exists(st_filename):
        print_error(f"File not found: {st_filename}")
        sys.exit(1)

    if os.path.getsize(st_filename) == 0:
        print_error(f"Input file is empty: {st_filename}")
        sys.exit(1)

    remove_folder("program")

    try:
        Path("program").mkdir(exist_ok=True)
    except Exception as e:
        print_error(f"Cannot create output folder 'program'")
        sys.exit(1)

    ino_filename = os.path.join("program", "program.ino")

    # parse the .st file
    inputs_digital, inputs_analog, outputs_digital, outputs_analog, var_types, functional_standard_blocks, instructions, standard_block_calls = parse_st_file(st_filename)
    print_info("Parsing input file and generating code...")

    try:
        with open(ino_filename, 'w') as output:
            output.write('// Arduino code generated from .st file\n\n')

            include_lines = handle_include_and_copy(functional_standard_blocks)
            if include_lines:
                output.write(include_lines + '\n')
                print_info("Included headers")

            # generate #define statements for GPIO pins
            for var, addr in inputs_digital.items():
                pin_number = pin.get_gpio(addr)

                if pin_number == 'UNKNOWN':
                    output.write(f'#define {var.upper()}_GPIO // Add gpio pin (digital input)\n')
                    print_info(f"Pin mapping missing for address {addr} (var: {var})")
                else:
                    output.write(f'#define {var.upper()}_GPIO {pin_number}\n')

            for var, addr in inputs_analog.items():
                pin_number = pin.get_gpio(addr)

                if pin_number == 'UNKNOWN':
                    output.write(f'#define {var.upper()}_GPIO // Add gpio pin (analog input)\n')
                    print_info(f"Pin mapping missing for address {addr} (var: {var})")
                else:
                    output.write(f'#define {var.upper()}_GPIO {pin_number}\n')

            for var, addr in outputs_digital.items():
                pin_number = pin.get_gpio(addr)

                if pin_number == 'UNKNOWN':
                    output.write(f'#define {var.upper()}_GPIO // Add gpio pin (digital output)\n')
                    print_info(f"Pin mapping missing for address {addr} (var: {var})")
                else:
                    output.write(f'#define {var.upper()}_GPIO {pin_number}\n')

            for var, addr in outputs_analog.items():
                pin_number = pin.get_gpio(addr)

                if pin_number == 'UNKNOWN':
                    output.write(f'#define {var.upper()}_GPIO // Add gpio pin (analog output)\n')
                    print_info(f"Pin mapping missing for address {addr} (var: {var})")
                else:
                    output.write(f'#define {var.upper()}_GPIO {pin_number}\n')

            # declare functional standard blocks
            for instance, bloc_type in functional_standard_blocks.items():
                output.write(f"\n{bloc_type} {instance};")
                
            output.write('\n\n')

            # generate setup()
            output.write(generate_setup(inputs_digital, outputs_digital, standard_block_calls))
            output.write('\n\n')
            print_info("setup() code written")

            # generate loop()
            output.write(generate_loop(instructions, inputs_digital, inputs_analog, outputs_digital, outputs_analog, functional_standard_blocks, standard_block_calls))
            print_info("loop() code written")

            print_success(f"Arduino file generated: {ino_filename}")
    except Exception as e:
        print_error(f"Failed to write to output file: {ino_filename}")
        sys.exit(1)

    # check if the user wants to append an extra Arduino file
    if not os.getenv("SKIP_EXTRA"):
        response = input("\nDo you want to append an extra Arduino file (e.g. utilities, libraries)? [y/N]: ").strip().lower()
        if response in ['y', 'yes']:
            extra_file = input("Enter the filename of the extra .ino file to append: ").strip()
            
            if not os.path.exists(extra_file):
                print_error(f"Extra file not found: {extra_file}")
                sys.exit(1)

            print_info(f"Merging code from '{extra_file}' to {ino_filename}...")
            merging.merging_files(ino_filename, extra_file)
            print_success("Merging completed successfully.")
    else:
        print_info("No extra file appended.")
