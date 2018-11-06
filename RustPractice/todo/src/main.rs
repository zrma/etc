#[macro_use]
extern crate clap;


use clap::App;


fn main() {
    let yaml = load_yaml!("cli.yml");
    let matches = App::from_yaml(yaml).get_matches();

    if let Some(matches) = matches.subcommand_matches("add") {
        let input = matches.values_of("INPUT").unwrap();
        let str = input.map(|s| &*s).collect::<Vec<&str>>().join(" ");
        println!("add task {}", str);
    } else if let Some(matches) = matches.subcommand_matches("done") {
        let input = matches.value_of("INPUT").unwrap();
        println!("done task {}", input);
    } else {
        println!("oops!");
    }
}
