const foo = "foo";
const bar: "foo" = "foo";
let baz = "foo";
const qux = "foo" as const;

const Foo = {
    type: foo
}

const Bar = {
    type: bar
}

const Baz = {
    type: baz
}

const Qux = {
    type: qux
}

type FooType = typeof qux;

function funcFoo(foo: FooType) {
    console.log(foo);
}

function funcString(foo: string) {
    console.log(foo);
}


funcFoo(foo);
funcFoo(Foo.type); // Error
funcFoo(bar);
funcFoo(Bar.type);
funcFoo(baz); // Error
funcFoo(Baz.type); // Error
funcFoo(qux);
funcFoo(Qux.type);

funcString(foo);
funcString(Foo.type);
funcString(bar);
funcString(Bar.type);
funcString(baz);
funcString(Baz.type);
funcString(qux);
funcString(Qux.type);
