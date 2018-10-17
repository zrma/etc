# coding=utf-8
from flask import Flask
import uuid


app = Flask(__name__)


@app.route('/')
def root():
        return 'Flask Dockerized {}'.format( uuid.getnode() )


if __name__ == '__main__':
        app.run(debug=True, host='0.0.0.0', port=8888)