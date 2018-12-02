use task::build_task;
use task::Task;

pub trait Description {
    fn description(&self) -> String;
}

pub struct Store {
    tasks: Vec<Task>,
}

impl Store {
    pub fn add(&mut self, s: &str) {
        let task = build_task(s);
        self.tasks.push(task)
    }

    pub fn list(&self) -> &Vec<Task> {
        return &self.tasks;
    }

    pub fn done(&mut self, idx: usize) {
        let task: &mut Task = &mut self.tasks[idx];
        task.done = true;
    }
}

impl Description for Vec<Task> {
    fn description(&self) -> String {
        let mut s = String::new();
        for mut t in self {
            s += &t.desc;
        }

        return s;
    }
}

pub fn todo() -> Store {
    let v = vec![];

    return Store { tasks: v };
}
