def main():
    add = 0
    a = b = 1
    switch = False
    while a < 4000000 and b < 4000000:
        if switch:
            a += b
            if a < 4000000 and a % 2 == 0:
                add += a
        else:
            b += a
            if b < 4000000 and b % 2 == 0:
                add += b
        switch = not switch 
    print(add)


if __name__ == '__main__':
    main()