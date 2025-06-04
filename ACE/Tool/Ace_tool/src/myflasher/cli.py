# cli.py
import argparse
from myflasher.flasher import flash_hex
from myflasher.debugger import debugger


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--flash", help="HEX file to flash")
    parser.add_argument("--debug", help="Debugger file out")

    args = parser.parse_args()

    if args.flash:
        flash_hex(args.flash)
    if args.debug:
        debugger(args.debug)

