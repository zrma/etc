#[macro_use]
extern crate serde_derive;

#[macro_use]
extern crate clap;

use clap::App;
use store::store;
use store::Description;

mod store;
mod task;

fn main() {
    let yaml = load_yaml!("cli.yml");
    let matches = App::from_yaml(yaml).get_matches();

    let mut s = store("todo.json");

    if let Some(matches) = matches.subcommand_matches("add") {
        let input = matches.values_of("INPUT").unwrap();
        let desc = input.map(|s| &*s).collect::<Vec<&str>>().join(" ");
        println!("add task {}", desc);
        s.add(&desc);
    } else if let Some(_matches) = matches.subcommand_matches("list") {
        let list = s.list();
        for t in list {
            println!("{}", t.description());
        }
    } else if let Some(matches) = matches.subcommand_matches("done") {
        let input = matches.value_of("INPUT").unwrap().parse::<usize>().unwrap();
        println!("done task {}", input);
        s.done(input)
    }
}

#[test]
fn test_main() {
    let mut t = store("");

    let msg = "buy a car";
    t.add(msg);

    let list = t.list();
    assert_eq!(
        list.description(),
        "[{\"done\":false,\"desc\":\"buy a car\"}]"
    );

    t.done(0);
    let list = t.list();
    assert_eq!(list[0].done, true);
}
