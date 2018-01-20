

def series_sum(n):
    sum = 0.0
    for i in range(0, n):
        sum += 1.0 / (1.0 + (i * 3.0))

    answer = format(sum, '.2f')
    return answer

if __name__ == '__main__':
    print(series_sum(3))