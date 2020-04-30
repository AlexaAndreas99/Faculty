import random
import numpy as np
import matplotlib
import copy


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
    split_point = int(train_size_set * len(values))
    train = values[:split_point]
    test = values[split_point:]
    return train, test


def split_values(values):
    random.shuffle(values)
    x = []
    y = []
    for i in values:
        x_aux = [1]
        for j in i[0:5]:
            x_aux.append(j)
        x.append(x_aux)
        y.append(i[5])
    return x, y


# the activation function:
def liniar(x):
    return x


# the derivate of te activation function
def liniar_derivative(x):
    return 1


class NeuralNetwork:

    # constructor for this VERY particular network with 2 layers (plus one for input)

    def __init__(self, x, y, hidden):
        self.input = x
        self.weights1 = np.random.rand(self.input.shape[1], hidden)
        self.weights2 = np.random.rand(hidden, 1)
        self.y = y
        self.output = np.zeros(self.y.shape)
        self.loss = []

    # the function that computs the output of the network for some input
    def feedforward(self):
        self.layer1 = liniar(np.dot(self.input, self.weights1))
        self.output = liniar(np.dot(self.layer1, self.weights2))

    # the backpropagation algorithm
    def backprop(self, l_rate):
        # application of the chain rule to find derivative of the
        # loss function with respect to weights2 and weights1
        d_weights2 = np.dot(np.transpose(self.layer1), (2 * (self.y - self.output) *
                                                        liniar_derivative(self.output)))

        d_weights1 = np.dot(np.transpose(self.input), (np.dot(2 * (self.y -
                                                                   self.output) * liniar_derivative(self.output),
                                                              self.weights2.T) *
                                                       liniar_derivative(self.layer1)))
        # update the weights with the derivative (slope) of the loss function
        self.weights1 += l_rate * d_weights1
        self.weights2 += l_rate * d_weights2
        self.loss.append(sum((self.y - self.output) ** 2))


def run(x, y):
    nn = NeuralNetwork(np.array(x), np.transpose([y]), 7)
    nn.loss = []
    for i in range(150):
        nn.feedforward()
        nn.backprop(0.0000001)
    return nn


if __name__ == "__main__":

    totalError = []
    for i in range(10):
        data = loadData()
        train, test = split_train_test(0.8, data)
        x_train, y_train = split_values(train)
        x_test, y_test = split_values(test)
        nn = run(x_train, y_train)
        k = 0
        error = 0
        nn.input = x_test
        nn.feedforward()
        for j in nn.output:
            error = error + (j[0] - y_test[k]) ** 2
            k += 1
        totalError.append([copy.deepcopy(error), copy.deepcopy(error / len(nn.output))])

    k = 1
    for i in totalError:
        print("Iteration {}: total error {} mean error {}".format(f'{k}'.rjust(2), f'{round(i[0], 2)}'.rjust(6),
                                                                  f'{round(i[1], 2)}'.rjust(6)))
        k += 1
