#
# This file contains a python script that looks for 
# specified string in all files in specified location
# 
# Author: Firsov Georgy
# Contact: gfirsov007@gmail.com
# Date: 15.09.2019
# Copyright © 2019 Firsov Georgy. All rights reserved.
#

from sys import argv
from os import listdir
from os.path import isfile, isdir


usage = """Usage:
        
python LookUp.py [dir=<search_dir>] [mode=<mode>] string1 [string2 [string3 ...]]
        
Searches strings string1, string2, etc. in all files in specified directory search_dir
        
Parameters:
    - dir - directory with files (by default - directory with script)
    - mode - type of search:
        0 - search in subdirectories too (default)
        1 - search only in current directory
"""


class LookupOperation(object):
    """Class provides lookup for strings in files from
    specified directory.
    Initialize it with mode (listed in usage) and call run method
    with strings you want to search.
    """

    def __init__(self, operation_code: int = 0):

        op_codes = {
              0: LookupOperation.__process_with_subdirs
            , 1: LookupOperation.__process_current_dir
        }

        self.__operation = op_codes[operation_code]

    def run(self, *args):
        directory, strings = LookupOperation.__process_args(*args)
        return self.__operation(directory, strings)

    @staticmethod
    def __process_with_subdirs(directory: str, strings: set):
        for name in listdir(directory):
            full_name = directory + '/' + name
            if isfile(full_name):
                LookupOperation.__search_for_strings(full_name, strings)
            elif isdir(full_name):
                LookupOperation.__process_with_subdirs(full_name, strings)

    @staticmethod
    def __process_current_dir(directory: str, strings: set):
        for name in listdir(directory):
            full_name = directory + '/' + name
            if isfile(full_name):
                LookupOperation.__search_for_strings(full_name, strings)

    @staticmethod
    def __search_for_strings(file: str, strings: set):
        try:
            with open(file, 'r') as f:
                lineno = 1
                for line in f:
                    for string in strings:
                        if string in line:
                            print(f'{file} contains line "{line[:-1].strip()}" at {lineno}')
                    lineno += 1
        except UnicodeDecodeError:
            pass  # Just skip non-readable file

    @staticmethod
    def __process_args(*args) -> tuple:
        directory = '.'
        strings = set()

        for arg in args:
            if arg.startswith('dir='):
                directory = arg[4:]
            else:
                strings.add(arg)

        return directory, strings


def main():
    """Runs lookup operation.
    """
    if not validate_args():
        return

    operation, args = parse_args()
    lookup = LookupOperation(operation)
    lookup.run(*args)


def validate_args() -> bool:
    """Checks arguments for validity and prints usage, if they
    are not valid.

    :return: True if arguments are valid, False otherwise.
    """
    if len(argv) == 1 or \
       '--help' in argv:
        print(usage)
        return False
    return True


def parse_args() -> tuple:
    """Extracts operation type (mode) from args.
    If none provided, sets it to default (0).

    :return: mode and list of strings.
    """
    operation = 0
    args = list()

    for arg in argv[1:]:
        if arg.startswith('mode='):
            operation = int(arg[5:])
        else:
            if arg.startswith('"'):
                arg = arg[1:]
            if arg.endswith('"'):
                arg = arg[:-1]

            args.append(arg)

    return operation, args


if __name__ == '__main__':
    main()
