def value_receive(value):
    print("I'm Python...receive {0}".format(value))
    return value * 10


def list_receive(list):
    print("I'm Python...receive {0}".format(list))
    return sum(list)


class Sample(object):
    def __init__(self):
        print("  on python: __init__()")
        self.message = "Hello "

    def arrange(self, name):
        print("  on python: arrange()")
        return self.message + name.decode("utf-8")
