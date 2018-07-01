import numpy as np
from keras.models import Sequential
from keras.layers import Dense, Activation
from keras.layers.recurrent import LSTM
from keras.optimizers import Adam
import matplotlib.pyplot as plt


def sin(x, T=100):
    return np.sin(2.0 * np.pi * x / T)


def noisy_sin(T=100, ampl=0.05):
    x = np.arange(0, 2 * T + 1)
    noise = ampl * np.random.uniform(low=- 1.0, high=1.0, size=len(x))
    return sin(x) + noise


def build_dataset(inputs):
    input = []
    expected = []
    maxlen = 25
    for i in range(len(inputs) - maxlen):
        input.append(inputs[i: i + maxlen])
        expected.append(inputs[i + maxlen])
    re_input = np.array(input).reshape(len(input), maxlen, 1)
    re_expected = np.array(expected).reshape(len(input), 1)
    return re_input, re_expected


def predict():
    f = noisy_sin()
    input, expected = build_dataset(f)

    length_of_sequence = input.shape[1]
    in_out_neurons = 1
    n_hidden = 300
    model = Sequential()
    model.add(LSTM(n_hidden, batch_input_shape=
    (None, length_of_sequence, in_out_neurons), return_sequences=False))
    model.add(Dense(in_out_neurons))
    model.add(Activation("linear"))
    optimizer = Adam(lr=0.001)
    model.compile(loss="mean_squared_error", optimizer=optimizer)

    model.fit(input, expected,
              batch_size=500,
              epochs=80,
              validation_split=0.1
              )

    future_test = input[175].T
    time_length = future_test.shape[1]
    future_result = np.empty((0))

    for step2 in range(400):
        test_data = np.reshape(future_test, (1, time_length, 1))
        batch_predict = model.predict(test_data)
        future_test = np.delete(future_test, 0)
        future_test = np.append(future_test, batch_predict)
        future_result = np.append(future_result, batch_predict)

    predicted = model.predict(input)

    plt.figure()
    plt.plot(range(0, len(f)), f, color="b", label="sin")
    plt.plot(range(25, len(predicted) + 25), predicted, color="r", label="predict")
    plt.plot(range(0 + len(f), len(future_result) + len(f)), future_result, color="g", label="future")
    plt.legend()
    plt.show()


if __name__ == "__main__":
    predict()
