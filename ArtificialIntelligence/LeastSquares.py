import random
import numpy


def loadData():
    f = open("data.txt", 'r')
    line = f.readline()
    values = []
    while line:
        data = line.split(' ')
        data = [float(elem) for elem in data[0:6]]
        values.append(data)
        line = f.readline()
        if line == '\n':
            line = f.readline()
    return values


def split_train_test(train_size_set, values):
    random.shuffle(values)
    split_point = int(train_size_set * len(values))
    train = values[:split_point]
    test = values[split_point:]
    return train, test


def split_values(values):
    x = []
    y = []
    for i in values:
        x_aux = [1]
        for j in i[0:5]:
            x_aux.append(j)
        x.append(x_aux)
        y.append(i[5])
    return x, y


def get_b(x, y):
    # (x^t*x)^-1*x^t*y
    x_t = numpy.transpose(x)
    x_prod = numpy.matmul(x_t, x)
    x_inv = numpy.linalg.inv(x_prod)
    prod = numpy.matmul(x_inv, x_t)
    final = numpy.matmul(prod, y)
    return final


def prediction(row, b):
    f_x = 0
    j = 0
    for i in row:
        f_x += (i * b[j])
        j += 1
    return f_x


def main():
    train, test = split_train_test(0.8, loadData())
    x_train, y_train = split_values(train)
    b = get_b(x_train, y_train)
    print(b)
    x_test, y_test = split_values(test)
    j = 0
    error = []
    for i in x_test:
        pred = prediction(i, b)
        error.append((y_test[j] - pred) ** 2)
        j += 1

    print(numpy.sum(error))
    print("Error is smaller than 0.4: ", numpy.mean(error) < 0.4)


main()
