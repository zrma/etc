use crate::store::Description;
use serde::{Deserialize, Serialize};

#[derive(Serialize, Deserialize, Debug)]
pub struct Task {
    pub done: bool,
    pub desc: String,
}

impl Description for Task {
    fn description(&self) -> String {
        serde_json::to_string(&self).unwrap()
    }
}

pub fn build_task(s: &str) -> Task {
    Task {
        done: false,
        desc: String::from(s),
    }
}
