// XXX: error: duplicate definition of value `test`
fn test(i:i32) -> String {
    "a i32"
}

fn test(f:f64) -> String {
    "a double"
}

fn main() {
    println!("{}", test(1));
    println!("{}", test(1.0));
}
