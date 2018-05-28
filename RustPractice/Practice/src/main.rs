#[macro_use]
extern crate const_cstr;
extern crate dlopen;

use dlopen::symbor::Library;

fn main() {
    let lib = Library::open("./libembed.dylib").expect("Failed to load library");

    let func = unsafe { lib.symbol_cstr::<fn()>(const_cstr!("process").as_cstr()) }.unwrap();

    func();
    println!("done!");
}
