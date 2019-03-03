#[macro_use]
extern crate const_cstr;
extern crate dlopen;

use dlopen::symbor::Library;

#[cfg(target_os = "windows")]
const FILE_NAME: &str = "./embed.dll";

#[cfg(target_os = "linux")]
const FILE_NAME: &str = "./libembed.so";

#[cfg(target_os = "macos")]
const FILE_NAME: &str = "./libembed.dylib";

fn main() {
    let lib = Library::open(FILE_NAME).expect("Failed to load library");

    let func = match unsafe { lib.symbol_cstr::<fn()>(const_cstr!("process").as_cstr()) } {
        Ok(x) => x,
        Err(_) => panic!(),
    };

    func();
    println!("done!");
}
