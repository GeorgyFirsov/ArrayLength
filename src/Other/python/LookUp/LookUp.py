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
        
python LookUp.py [--suppress_errors] [--dir=<search_dir>] [--mode=<mode>] string1 [string2 [string3 ...]]
        
Searches strings string1, string2, etc. in all files in specified directory search_dir
        
Parameters:
    - suppress_errors - if set, no error messages will be displayed
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

    def __init__(self, operation_code: int = 0, suppress_errors: bool = False):

        op_codes = {
              0: self.__process_with_subdirs
            , 1: self.__process_current_dir
        }

        self.__operation = op_codes[operation_code]
        self.__suppress_errors = suppress_errors

    def run(self, *args):
        directory, strings = LookupOperation.__process_args(*args)
        return self.__operation(directory, strings)

    def __process_with_subdirs(self, directory: str, strings: set):
        try:
            for name in listdir(directory):
                full_name = directory + '/' + name
                if isfile(full_name):
                    self.__search_for_strings(full_name, strings)
                elif isdir(full_name):
                    self.__process_with_subdirs(full_name, strings)

        except FileNotFoundError:
            if not self.__suppress_errors:
                readable_name = directory.replace('\\/', '\\').replace('/', '\\')
                print(f'\n[ Error ] Directory {readable_name} is inaccessible: no such directory\n')
        except PermissionError:
            if not self.__suppress_errors:
                readable_name = directory.replace('\\/', '\\').replace('/', '\\')
                print(f'\n[ Error ] Directory {readable_name} is inaccessible: access denied\n')

    def __process_current_dir(self, directory: str, strings: set):
        try:
            for name in listdir(directory):
                full_name = directory + '/' + name
                if isfile(full_name):
                    self.__search_for_strings(full_name, strings)

        except FileNotFoundError:
            if not self.__suppress_errors:
                readable_name = directory.replace('\\/', '\\').replace('/', '\\')
                print(f'\n[ Error ] Directory {readable_name} is inaccessible: no such directory\n')
        except PermissionError:
            if not self.__suppress_errors:
                readable_name = directory.replace('\\/', '\\').replace('/', '\\')
                print(f'\n[ Error ] Directory {readable_name} is inaccessible: access denied\n')

    def __search_for_strings(self, file: str, strings: set):
        try:
            with open(file, 'r') as f:
                lineno = 1
                for line in f:
                    for string in strings:
                        if string in line:
                            readable_name = file.replace('\\/', '\\').replace('/', '\\')
                            print(f'[ Found ] {readable_name} contains line "{line[:-1].strip()}" at {lineno}')
                    lineno += 1

        # In case of some errors just skip non-readable files
        except UnicodeDecodeError:
            pass
        except PermissionError:
            if not self.__suppress_errors:
                readable_name = file.replace('\\/', '\\').replace('/', '\\')
                print(f'\n[ Error ] {readable_name} can not be opened: access denied. Skipping...\n')

    @staticmethod
    def __process_args(*args) -> tuple:
        directory = '.'
        strings = set()

        for arg in args:
            if arg.startswith('--dir='):
                directory = arg[6:]
            else:
                strings.add(arg)

        return directory, strings


def main():
    """Runs lookup operation.
    """
    if not validate_args():
        return

    operation, suppress_errors, args = parse_args()
    lookup = LookupOperation(operation, suppress_errors)
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
    suppress_errors = False

    for arg in argv[1:]:
        if arg.startswith('--mode='):
            operation = int(arg[7:])
        elif arg == '--suppress_errors':
            suppress_errors = True
        else:
            if arg.startswith('"'):
                arg = arg[1:]
            if arg.endswith('"'):
                arg = arg[:-1]

            args.append(arg)

    return operation, suppress_errors, args


if __name__ == '__main__':
    try:
        main()
    except KeyboardInterrupt:
        print('\nUser interrupted an execution by Ctrl+C combination.\n')
