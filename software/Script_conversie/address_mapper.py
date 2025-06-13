class AddressMapper:
    """
    Maps PLC I/O addresses to corresponding Arduino GPIO pins
    """
    map_table = {
        # digital inputs
        'IX': {
            '0.0': 17, '0.1': 0, '0.2': 21, '0.3': 22,
            '0.4': 23, '0.5': 2, '0.6': 1, '0.7': 8,
            '1.0': 11
        },
        # digital outputs
        'QX': {
            '0.0': 10, '0.1': 15, '0.2': 20, '0.3': 19,
            '0.4': 18, '0.5': 9, '0.6': 14, '0.7': 16
        },
        # analog inputs
        'IW': {
            '0': 5, '1': 35, '2': 36, '3': 39
        },
        # analog outputs
        'QW': {
            '0': 25, '1': 26
        }
    }

    @classmethod
    def get_gpio(cls, address: str) -> int | str:
        """
        Returns the GPIO pin mapped to a PLC-style address

        Args:
            address (str): The address in format like "%IX0.0" or "%QW1"

        Returns:
            int | str: The corresponding GPIO pin number or 'UNKNOWN'
        """
        if not address.startswith('%'):
            return 'UNKNOWN'
        
        prefix = address[1:3]
        suffix = address[3:]
        return cls.map_table.get(prefix, {}).get(suffix, 'UNKNOWN')
