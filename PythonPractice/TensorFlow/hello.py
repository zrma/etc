# -*- coding: utf-8 -*-

import tensorflow as tf


a = tf.placeholder('float')
b = tf.placeholder('float')

y = tf.mul(a, b)

session = tf.Session()

print(session.run(y, feed_dict = {a: 3, b: 3}))
