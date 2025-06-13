import sys
from utils import print_error, print_info

def extract_sections_from_extra(file_path):
    """
    Extracts include, define, setup, loop and other code sections from an extra .ino file

    Args:
        file_path (str): Path to the extra Arduino .ino file

    Returns:
        tuple: (includes, defines, setup_body, loop_body, other_code)
    """
    includes = []
    defines = []
    setup_body = []
    loop_body = []
    other_code = []

    current_section = None
    inside_function = False
    brace_depth = 0

    try:
        with open(file_path, 'r') as f:
            lines = f.readlines()
                
    except FileNotFoundError:
        print_error(f"Extra file not found: {file_path}")
        sys.exit(1)
    except Exception as e:
        print_error(f"Failed to read extra file: {file_path}")
        sys.exit(1)

    i = 0
    while i < len(lines):
        line = lines[i].rstrip()

        if line.startswith("#include"):
            includes.append(line)
        elif line.startswith("#define"):
            defines.append(line)
        elif line.strip().startswith("void setup"):
            current_section = "setup"
            inside_function = True
            brace_depth = 0
        elif line.strip().startswith("void loop"):
            current_section = "loop"
            inside_function = True
            brace_depth = 0
        elif inside_function:
            if '{' in line:
                brace_depth += line.count('{')
            if '}' in line:
                brace_depth -= line.count('}')
                if brace_depth <= 0:
                    inside_function = False
                    current_section = None
                    i += 1
                    continue

            if current_section == "setup":
                setup_body.append(line)
            elif current_section == "loop":
                loop_body.append(line)
        elif line.strip() != "":
            other_code.append(line)

        i += 1

    return includes, defines, setup_body, loop_body, other_code

def merging_files(ino_filename, extra_filename):
    """
    Merges sections from an extra Arduino file into the generated Arduino file

    Args:
        ino_filename (str): Path to the generated Arduino .ino file
        extra_filename (str): Path to the extra Arduino .ino file
    """
    try:
        includes_extra, defines_extra, setup_extra, loop_extra, other_extra = extract_sections_from_extra(extra_filename)
        print_info(f"Extracted sections from {extra_filename}")

        with open(ino_filename, 'r') as ino_file:
            original_lines = ino_file.readlines()

        # extract includes and defines from the original .ino file
        includes_original = [line for line in original_lines if line.strip().startswith("#include")]
        defines_original = [line for line in original_lines if line.strip().startswith("#define")]
        body_original = [
            line for line in original_lines
            if not line.strip().startswith("#include")
            and not line.strip().startswith("#define")
            and not line.strip().startswith("// Arduino code generated from .st file")
        ]
        
        # append first comment line
        new_lines = ["// Arduino code generated from .st file\n\n"]

        # append include (without duplicates)
        seen_includes = set()

        for line in includes_original + includes_extra:
            if line.strip() not in seen_includes:
                new_lines.append(line.strip() + '\n')
                seen_includes.add(line.strip())

        new_lines.append('\n')

        # append defines (without duplicates)
        seen_defines = set()

        for line in defines_original + defines_extra:
            if line.strip() not in seen_defines:
                new_lines.append(line.strip() + '\n')
                seen_defines.add(line.strip())

        # append setup and loop bodies
        in_setup = False
        in_loop = False
        inserted_setup = False
        inserted_loop = False
        brace_depth = 0

        for line in body_original:
            stripped = line.strip()

            if stripped.startswith("void setup"):
                in_setup = True
                brace_depth = 1
                new_lines.append('\n')
                new_lines.append(line)
                continue
            elif stripped.startswith("void loop"):
                in_loop = True
                brace_depth = 1
                new_lines.append('\n')
                new_lines.append(line)
                continue

            if in_setup or in_loop:
                brace_depth += line.count('{') - line.count('}')

                if brace_depth == 1:
                    if in_setup and not inserted_setup:
                        for extra_line in setup_extra:
                            new_lines.append("  " + extra_line.strip() + '\n')
                        inserted_setup = True
                        new_lines.append('\n')  

                    if in_loop and not inserted_loop:
                        for extra_line in loop_extra:
                            new_lines.append("  " + extra_line.strip() + '\n')
                        inserted_loop = True
                        new_lines.append('\n')

                new_lines.append(line)
                
                if brace_depth == 0:
                    in_setup = False
                    in_loop = False

                continue

            if not line.strip().startswith("#include") and not line.strip().startswith("#define") and not line.strip() == "":
                new_lines.append(line)

        # append other code 
        if other_extra:
            new_lines.append('\n\n')
            for line in other_extra:
                new_lines.append(line + '\n')
                if line.strip() == "}":
                    new_lines.append('\n')

        with open(ino_filename, 'w') as f_output:
            print_info(f"Writing merged content to {ino_filename}")
            f_output.writelines(new_lines)

    except Exception as e:
        print_error(f"Failed to merge Arduino files: {e}")
        print_error(f"Error: {e}")
        sys.exit(1)
