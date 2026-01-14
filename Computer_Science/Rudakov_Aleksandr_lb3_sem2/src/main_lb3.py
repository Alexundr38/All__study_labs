from sklearn import datasets
from sklearn.model_selection import train_test_split
from sklearn.neighbors import KNeighborsClassifier
from sklearn.metrics import accuracy_score
from sklearn import preprocessing
import numpy as np

def load_data(train_size = 0.8):
    wine = datasets.load_wine()
    x = wine.data[:, [0, 1]]
    y = wine.target
    X_train, X_test, y_train, y_test = train_test_split(x, y, train_size = train_size, random_state = 42)
    return X_train, X_test, y_train, y_test

def train_model(X_train, y_train, n_neighbors = 15, weights = 'uniform'):
    clf = KNeighborsClassifier(n_neighbors = n_neighbors, weights = weights)
    clf.fit(X_train, y_train)
    return clf

def predict(clf, X_test):
    res = clf.predict(X_test)
    return res

def estimate(res, y_test):
    accuracy = accuracy_score(res, y_test)
    accuracy = np.round(accuracy, 3)
    return accuracy

def scale(data, mode = 'standard'):
    if mode == 'standard':
        scaler = preprocessing.StandardScaler()
    elif mode == 'maxabs':
        scaler = preprocessing.MaxAbsScaler()
    elif mode == 'minmax':
        scaler = preprocessing.MinMaxScaler()
    else:
        return None
    sc_data = scaler.fit_transform(data)
    return sc_data
