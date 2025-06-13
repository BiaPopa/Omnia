def generate_setup(inputs_digital, outputs_digital, standard_block_calls):
    """
    Generates the Arduino setup() function code

    Args:
        inputs_digital (dict): Dictionary of digital input variables
        outputs_digital (dict): Dictionary of digital output variables
        standard_block_calls (list): List of functional block calls with parameters

    Returns:
        str: Formatted setup() function code
    """
    lines = []
    lines.append('void setup() {')

    # configure input pins with pull-up resistors
    for var in inputs_digital:
        lines.append(f'  pinMode({var.upper()}_GPIO, INPUT_PULLUP);')
    
    # configure output pins
    for var in outputs_digital:
        lines.append(f'  pinMode({var.upper()}_GPIO, OUTPUT);')
    
    lines.append('')

    # initialize standard function block parameters
    for block in standard_block_calls:
        instanta = block['instanta']
        tip = block['tip']
        param = block['parametri']

        if tip == 'TON' or tip == 'TOF' or tip == 'TP':
            if 'ms' in param["PT"]:
                pt_ms = param["PT"].replace("T#", "").replace("ms", "") 
            elif 's' in param["PT"]:
                pt_s = param["PT"].replace("T#", "").replace("s", "")  
                pt_ms = int(pt_s) * 1000
            else:
                pt_ms = 0
            
            lines.append(f'  {instanta}.PT = {pt_ms};')
        elif tip.startswith('CTU') or tip.startswith('CTD') or tip.startswith('CTUD'):
            lines.append(f'  {instanta}.PV = {param["PV"]};')

    lines.append('}')
    return '\n'.join(lines)
