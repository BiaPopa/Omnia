from utils import comparison_blocks, selection_blocks, bitwise_blocks

def convert_expression(expression):
    """
    Converts a logic expression from ST to C-style syntax

    Args:
        expression (str): Expression using ST logic operators

    Returns:
        str: Converted expression using C-style operators
    """
    expression = expression.replace('NOT', '!')
    expression = expression.replace('AND', '&')
    expression = expression.replace('OR', '|')
    expression = expression.replace('XOR', '^')
    return expression

def generate_loop(instructions, inputs_digital, inputs_analog, outputs_digital, outputs_analog, functional_standard_blocks, standard_block_calls):
    """
    Generates the Arduino loop() function code based on parsed ST program

    Args:
        instructions (list): List of assignment instructions from ST code
        inputs_digital (dict): Mapping of digital input variable names to addresses
        inputs_analog (dict): Mapping of analog input variable names to addresses
        outputs_digital (dict): Mapping of digital output variable names to addresses
        outputs_analog (dict): Mapping of analog output variable names to addresses
        functional_standard_blocks (dict): Mapping of block instances to types
        standard_block_calls (list): List of block instance calls with parameters

    Returns:
        str: The complete loop() function as a string
    """
    lines = []
    lines.append('void loop() {')

    for var in inputs_digital:
        lines.append(f'  bool {var} = (digitalRead({var.upper()}_GPIO) == LOW);')

    for var in inputs_analog:
        lines.append(f'  int {var} = analogRead({var.upper()}_GPIO);')

    lines.append('')

    for block in standard_block_calls:
        instanta = block['instanta']
        tip = block['tip']
        param = block['parametri']

        for p, v in param.items():
            if 'NOT(' in v or 'AND(' in v or 'OR(' in v or 'XOR(' in v:
                param[p] = convert_expression(v)

        if tip == 'R_TRIG' or tip == 'F_TRIG':
            lines.append(f'  {instanta}.CLK = {param["CLK"]};')
            lines.append(f'  {instanta}.update();')
            lines.append('')
        elif tip == 'TON' or tip == 'TOF' or tip == 'TP':
            lines.append(f'  {instanta}.IN = {param["IN"]};')
            lines.append(f'  {instanta}.update();')
            lines.append('')
        elif tip.startswith('CTU') or tip.startswith('CTD') or tip.startswith('CTUD'):
            for param, val in param.items():
                if param != 'PV':
                    lines.append(f'  {instanta}.{param} = {val};')
            lines.append(f'  {instanta}.update();')
            lines.append('')
        elif tip == 'SR' or tip == 'RS' or tip == 'SEMA':
            for param, val in param.items():
                lines.append(f'  {instanta}.{param} = {val};')
            lines.append(f'  {instanta}.update();')
            lines.append('')
        elif any(tip.startswith(prefix) for prefix in comparison_blocks) or any(tip.startswith(prefix) for prefix in selection_blocks) or tip in bitwise_blocks:
            for param, val in param.items():
                lines.append(f'  {instanta}.{param} = {val};')
            lines.append(f'  {instanta}.update();')
            lines.append('')

    for assignment in instructions:
        assignment = assignment.replace(' ', '')
        if ':=' in assignment:
            dest, src = assignment.split(':=', 1)
            src = src.replace(';', '')

            if src in functional_standard_blocks and any(functional_standard_blocks[src].startswith(prefix) for prefix in comparison_blocks):
                src += '.OUT'
            elif src in functional_standard_blocks and any(functional_standard_blocks[src].startswith(prefix) for prefix in selection_blocks):
                src += '.OUT'
            elif src in functional_standard_blocks and functional_standard_blocks[src] in bitwise_blocks:
                src += '.OUT'

            if dest in outputs_digital:
                lines.append(f'  digitalWrite({dest.upper()}_GPIO, {src} ? HIGH : LOW);')
            elif dest in outputs_analog:
                lines.append(f'  analogWrite({dest.upper()}_GPIO, ({src}) / 4);')
    lines.append('')

    lines.append('  delay(100);')
    lines.append('}')
    return '\n'.join(lines)
