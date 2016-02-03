import sys


def main():
    if len(sys.argv) < 2:
        sys.exit("You forgot to pass an argument!")
    argument = sys.argv[1]
    result = do_something(argument)
    if not result:
        sys.exit(1)
    return 0


def do_something(arg):
    print ("The second argument is {}".format(arg))


if __name__ == '__main__':
    sys.exit(main())
