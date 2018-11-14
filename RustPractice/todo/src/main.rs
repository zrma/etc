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

    if let Some(matches) = matches.subcommand_matches("add") {
        let input = matches.values_of("INPUT").unwrap();
        let desc = input.map(|s| &*s).collect::<Vec<&str>>().join(" ");
        println!("add task {}", desc);

        let t = build_task(&*desc);
        let text = t.description();

        println!("{}", text)
    } else if let Some(matches) = matches.subcommand_matches("list") {
        println!("tasks \n{}", "Hello World");
    } else if let Some(matches) = matches.subcommand_matches("done") {
        let input = matches.value_of("INPUT").unwrap();
        println!("done task {}", input);
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