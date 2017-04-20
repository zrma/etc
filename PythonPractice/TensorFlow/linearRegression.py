# -*- coding: utf-8 -*-

# 경사하강법을 이용한 선형회귀분석


from numpy import random
from collections import namedtuple


numPoints = 1000
vectors = list()

Vector = namedtuple('Vector', 'x, y')

for i in range(numPoints):
    x1 = random.normal(0.0, 0.55)
    y1 = x1 * 0.1 + 0.3 + random.normal(0.0, 0.03)
    v = Vector(x = x1, y = y1)
    vectors.append(v)

xDatas = [v.x for v in vectors]
yDatas = [v.y for v in vectors]

from matplotlib import pyplot


pyplot.plot(xDatas, yDatas, 'ro')
pyplot.legend()
pyplot.xlabel('x')
pyplot.ylabel('y')
pyplot.show()

import tensorflow as tf


W = tf.Variable(tf.random_uniform([1], -1.0, 1.0))
b = tf.Variable(tf.zeros([1]))

y = W * xDatas + b

# 비용 함수(= 오차)
loss = tf.reduce_mean(tf.square(y - yDatas))

# 학습 속도 설정
optimizer = tf.train.GradientDescentOptimizer(0.5)
train = optimizer.minimize(loss)

# 변수 초기화
init = tf.global_variables_initializer()

# 세션 생성
session = tf.Session()
session.run(init)

# 반복 학습
for step in range(20):
    session.run(train)
    print('{}, {}, {}'.format(step, session.run(W), session.run(b)))

    pyplot.plot(xDatas, yDatas, 'ro')
    pyplot.plot(xDatas, session.run(W) * xDatas + session.run(b))
    pyplot.legend()
    pyplot.xlabel('x')
    pyplot.ylabel('y')
    pyplot.show()
