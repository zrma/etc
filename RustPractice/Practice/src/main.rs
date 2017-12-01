fn test(x: &i32, y: i32) {
    *x = y;
}


fn main() {
    let mut a = Box::new(20);

    println!("{}", a);

    test(&a, 30);

    println!("{}", a);
}
