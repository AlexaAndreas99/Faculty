import random
import math


class DataSet:
    def __init__(self, filename, train_size):
        self.filename = filename
        self.train_size_set = train_size
        self.values = []

        self._loadData()

    def _loadData(self):
        f = open(self.filename, 'r')
        line = f.readline()

        while line:
            data = line.split(',')
            data = [data[0]] + [int(elem) for elem in data[1:5]]
            self.values.append(data)
            line = f.readline()

    def splitTrainTest(self):
        random.shuffle(self.values)
        split_point = int(self.train_size_set * len(self.values))
        train = self.values[:split_point]
        test = self.values[split_point:]
        return train, test


class Node:
    def __init__(self, index=1, value=1):
        self.index = index
        self.value = value
        self.dataset = None
        self.left = None
        self.right = None


class DT:
    def __init__(self, data_set):
        self.data_set = data_set
        self.tree = None

    def createLeaf(self, dataset):
        classes = [row[0] for row in dataset]
        leaf_value = 'L'
        best_p = 0

        for cls in ['L', 'B', 'R']:
            p = classes.count(cls)
            if p > best_p:
                best_p = p
                leaf_value = cls

        return leaf_value

    def partition(self, index, value, dataset):
        left = []
        right = []
        for data in dataset:
            if data[index] < value:
                left.append(data)
            else:
                right.append(data)
        return left, right

    def entropy(self, dataset):
        classes = [row[0] for row in dataset]
        size = len(dataset)
        e = 0

        for cls in ['L', 'B', 'R']:
            p = int(classes.count(cls) / size * 100) / 100.0
            if p > 0:
                e += - p * math.log2(p)

        return e

    def split(self, node):
        best_index = 1
        best_value = 1
        best_gain = 0

        node_entropy = self.entropy(node.dataset)
        size = len(node.dataset)

        for index in range(1, 5):
            for value in range(1, 6):
                left_set, right_set = self.partition(index, value, node.dataset)

                if len(left_set) == 0 or len(right_set) == 0:
                    continue

                left_entropy = self.entropy(left_set)
                right_entropy = self.entropy(right_set)
                gain = node_entropy - (len(left_set) / size * left_entropy +
                                       len(right_set) / size * right_entropy)
                if gain > best_gain:
                    best_gain = gain
                    best_index = index
                    best_value = value

        left_set, right_set = self.partition(best_index, best_value, node.dataset)

        if best_gain == 0 or not left_set or not right_set:
            node.left = node.right = self.createLeaf(node.dataset)
            return

        node.index = best_index
        node.value = best_value

        left_node = Node()
        left_node.dataset = left_set
        node.left = left_node

        right_node = Node()
        right_node.dataset = right_set
        node.right = right_node

        self.split(node.left)
        self.split(node.right)

    def build(self, train_set):
        root = Node()
        root.dataset = train_set
        self.split(root)
        return root

    def predict(self, node, row):
        if node.value < row[node.index]:
            if isinstance(node.right, Node):
                return self.predict(node.right, row)
            else:
                return node.right
        else:
            if isinstance(node.left, Node):
                return self.predict(node.left, row)
            else:
                return node.left

    def run(self):
        train, test = self.data_set.splitTrainTest()
        self.tree = self.build(train)

        correct = 0
        for index in range(len(test)):
            predicted_class = self.predict(self.tree, test[index])
            if predicted_class == test[index][0]:
                correct += 1

        return int(correct / len(test) * 10000) / 100.00    # .2 precision


def main():

    data_set = DataSet('balance-scale.data', 0.8)
    decision_tree = DT(data_set)
    accuracy = decision_tree.run()
    print("Accuracy: ",accuracy)


main()