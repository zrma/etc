use clap::{Arg, Command};
use store::{Description, store};

mod store;
mod task;

fn main() {
    let matches = Command::new("todo")
        .version("1.0")
        .author("zrma <bulbitain@gmail.com>")
        .about("todo rust programming practice")
        .subcommand(
            Command::new("add").about("add task").arg(
                Arg::new("INPUT")
                    .help("add <task>")
                    .num_args(1..)
                    .required(true),
            ),
        )
        .subcommand(Command::new("list").about("get a list of tasks"))
        .subcommand(
            Command::new("done")
                .about("done task")
                .arg(Arg::new("INPUT").help("done <task>").required(true)),
        )
        .get_matches();

    let mut s = store("todo.json");

    if let Some(matches) = matches.subcommand_matches("add") {
        let input = matches.get_many::<String>("INPUT").unwrap();
        let desc = input.map(|s| s.as_str()).collect::<Vec<&str>>().join(" ");
        println!("add task {}", desc);
        s.add(&desc);
    } else if let Some(_matches) = matches.subcommand_matches("list") {
        let list = s.list();
        for t in list {
            println!("{}", t.description());
        }
    } else if let Some(matches) = matches.subcommand_matches("done") {
        let input = matches
            .get_one::<String>("INPUT")
            .unwrap()
            .parse::<usize>()
            .unwrap();
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
    assert!(list[0].done);
}
