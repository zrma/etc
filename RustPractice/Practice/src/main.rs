fn main() {
    let mut vec = Vec::new();
    &vec.push(1);
    &vec.push(2);

    assert_eq!(vec.len(), 2);
    assert_eq!(vec[0], 1);

    println!("Hello, world!");

    for x in &vec {
        println!("{}", x);
    }
}
