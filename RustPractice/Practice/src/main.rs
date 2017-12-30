fn test(x: &mut i32, y: i32) {
    *x = y;
}


fn main() {
    let mut a : i32 = 20;

    println!("{}", a);

    test(&mut a, 30);

    println!("{}", a);
}
