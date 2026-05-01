import numpy as np


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
    input, _expected = build_dataset(f)
    predicted = np.array([sin(i) for i in range(25, len(input) + 25)])
    future_result = np.array([sin(i) for i in range(len(f), len(f) + 400)])

    print("baseline sample:", predicted[:5].round(4).tolist())
    print("future sample:", future_result[:5].round(4).tolist())


if __name__ == "__main__":
    predict()
