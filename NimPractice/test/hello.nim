import strformat

type
    Person = object
        name*: string
        age: Natural

var people = [
    Person(name: "Tester01", age:20),
    Person(name: "Abdula", age:15)
]

for person in people:
    echo fmt"{person.name} is {person.age} years old"
