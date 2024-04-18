import gleam/io
import gleam/string

pub fn main() {
  io.println("Hello from hello_world!")

  io.println(string.reverse("Hello from hello_world!"))
}
