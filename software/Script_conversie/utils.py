import sys

# set of all supported counter block types
counter_blocks = {
    'CTU', 'CTD', 'CTUD',
    'CTU_DINT', 'CTD_DINT', 'CTUD_DINT',
    'CTU_LINT', 'CTD_LINT', 'CTUD_LINT',
    'CTU_UDINT', 'CTD_UDINT', 'CTUD_UDINT',
    'CTU_ULINT', 'CTD_ULINT', 'CTUD_ULINT', 
}

# set of all supported comparison block types
comparison_blocks = {
    'EQ', 'NE', 'LT', 'LE', 'GT', 'GE'
}

# set of all supported selection-related block types
selection_blocks = {
    'SEL', 'MUX', 'MAX', 'MIN', 'LIMIT',
}

# set of all supported bitwise operation block types
bitwise_blocks = {
    'AND', 'OR', 'XOR', 'NOT',
}

def print_info(msg):
    """
    Displays an informational message in yellow

    Args:
        msg (str): The message to display
    """
    print(f"\033[93m[INFO]\033[0m {msg}") 

def print_success(msg):
    """Displays a success message in green

    Args:
        msg (str): The message to display
    """
    print(f"\033[92m[SUCCESS]\033[0m {msg}")  

def print_error(msg):
    """
    Displays an error message in red and sends it to stderr
    
    Args:
        msg (str): The message to display
    """
    print(f"\033[91m[ERROR]\033[0m {msg}", file=sys.stderr)