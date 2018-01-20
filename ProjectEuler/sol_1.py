# !python3
# Project Euler
# by Jonathan Lin
""" Solution 1  """

def main():
    """ Solution code """
    add=0
    for i in range(0, 1000):
        if (i % 5 == 0 or i % 3 == 0):
            add += i
    print(add)


if __name__ == '__main__':
    main()