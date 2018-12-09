extern crate serde;
extern crate serde_json;

use store::Description;

#[derive(Serialize, Deserialize, Debug)]
pub struct Task {
    pub done: bool,
    pub desc: String,
}

impl Description for Task {
    fn description(&self) -> String {
        return serde_json::to_string(&self).unwrap();
    }
}

pub fn build_task(s: &str) -> Task {
    return Task {
        done: false,
        desc: String::from(s),
    };
}
