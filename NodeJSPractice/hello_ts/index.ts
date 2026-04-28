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
// @ts-expect-error string으로 widen된 값은 "foo" 리터럴 타입에 넣을 수 없다.
funcFoo(Foo.type);
funcFoo(bar);
funcFoo(Bar.type);
// @ts-expect-error let으로 선언된 baz는 string으로 widen된다.
funcFoo(baz);
// @ts-expect-error 객체 속성의 string 값은 리터럴 타입으로 보존되지 않는다.
funcFoo(Baz.type);
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
