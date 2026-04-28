use std::fs::File;
use std::io::prelude::*;

use crate::task::{Task, build_task};
use serde::{Deserialize, Serialize};

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

    pub fn list(&self) -> &[Task] {
        &self.tasks
    }

    pub fn done(&mut self, idx: usize) {
        {
            let task: &mut Task = &mut self.tasks[idx];
            task.done = true;
        }

        self.save();
    }

    fn save(&mut self) {
        if self.file.is_empty() {
            return;
        }

        let mut file = File::create(self.file.as_str()).unwrap();
        file.write_all(self.tasks.description().as_bytes()).unwrap();
    }
}

impl Description for [Task] {
    fn description(&self) -> String {
        serde_json::to_string(&self).unwrap()
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

    Store {
        file: name.to_string(),
        tasks: v,
    }
}
