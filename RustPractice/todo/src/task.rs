pub trait Descript {
    fn description(&self) -> String;
}

pub struct Task {
    pub done: bool,
    pub desc: String,
}

impl Descript for Task {
    fn description(&self) -> String {
        format!("{}", self.desc)
    }
}

pub fn build_task(s: &str) -> Task {
    return Task {
        done: false,
        desc: String::from(s),
    };
}
