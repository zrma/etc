#[macro_use]
extern crate const_cstr;
extern crate dlopen;

use dlopen::symbor::Library;

fn main() {
    let file_name = if cfg!(windows) {
        "./embed.dll"
    } else if cfg!(macos) {
        "./libembed.dylib"
    } else {
        "./libembed.so"
    };

    let lib = Library::open(file_name).expect("Failed to load library");

    let func = match unsafe { lib.symbol_cstr::<fn()>(const_cstr!("process").as_cstr()) } {
        Ok(x) => x,
        Err(_) => panic!(),
    };

    func();
    println!("done!");
}

#[test]
fn test_main() {
    let mut total = 0;

    for i in 1..10 {
        total += i
    }

    println!("{}", total)
}
