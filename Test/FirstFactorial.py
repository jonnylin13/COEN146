def FirstFactorial(num):
    
    return Factorial(num)

def Factorial(num):
    if num == 1:
        return num
    else:
        return num * Factorial(num - 1)

print(FirstFactorial(int(input())))