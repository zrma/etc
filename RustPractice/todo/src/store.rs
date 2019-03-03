extern crate serde;
extern crate serde_json;

use std::fs::File;
use std::io::prelude::*;

use task::build_task;
use task::Task;

pub trait Description {
    fn description(&self) -> String;
}

#[derive(Serialize, Deserialize, Debug)]
pub struct Store {
    file: String,
    tasks: Vec<Task>,
}

impl Store {
    pub fn add(&mut self, s: &str) {
        let task = build_task(s);
        self.tasks.push(task);

        self.save();
    }

    pub fn list(&self) -> &Vec<Task> {
        return &self.tasks;
    }

    pub fn done(&mut self, idx: usize) {
        {
            let task: &mut Task = &mut self.tasks[idx];
            task.done = true;
        }

        self.save();
    }

    fn save(&mut self) {
        if self.file == "" {
            return;
        } else {
            let mut file = File::create(self.file.as_str()).unwrap();
            file.write_all(self.tasks.description().as_bytes()).unwrap();
        }
    }
}

impl Description for Vec<Task> {
    fn description(&self) -> String {
        return serde_json::to_string(&self).unwrap();
    }
}

pub fn store(name: &str) -> Store {
    let v: Vec<Task> = match name {
        "" => vec![],
        _ => {
            let mut file = File::open(name).unwrap();
            let mut contents = String::new();
            file.read_to_string(&mut contents).unwrap();

            serde_json::from_str(&contents).unwrap()
        }
    };

    return Store {
        file: name.to_string(),
        tasks: v,
    };
}
