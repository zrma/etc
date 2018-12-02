#[macro_use]
extern crate clap;

use clap::App;

mod task;

use task::build_task;

mod todo;

use todo::todo;
use todo::Description;

fn main() {
    let yaml = load_yaml!("cli.yml");
    let matches = App::from_yaml(yaml).get_matches();

    let mut t = todo();

    if let Some(matches) = matches.subcommand_matches("add") {
        let input = matches.values_of("INPUT").unwrap();
        let desc = input.map(|s| &*s).collect::<Vec<&str>>().join(" ");
        println!("add task {}", desc);
        t.add(&desc)
    } else if let Some(matches) = matches.subcommand_matches("list") {
        let list = t.list();
        println!("total \n {}", list.description());
    } else if let Some(matches) = matches.subcommand_matches("done") {
        let input = matches.value_of("INPUT").unwrap().parse::<usize>().unwrap();
        println!("done task {}", input);
        t.done(input)
    }
}

#[test]
fn test_main() {
    let mut t = todo();

    let msg = "buy a car";
    t.add(msg);
    {
        let list = t.list();
        assert_eq!(list.description(), msg);
    }

    t.done(0);
    {
        let list = t.list();
        assert_eq!(list[0].done, true);
    }
}
