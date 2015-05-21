#[allow(dead_code)]
enum Day {
    Monday,
    Tuesday,
    Wednesday,
    Thursday,
    Friday,
    Saturday,
    Sunday,
}

impl Day {
    fn mood(&self) {
        println!("{}", match *self {
            Day::Friday => "it's friday",
            Day::Saturday | Day::Sunday => "weekend :-)",
            _ => "weekday...",
        })
    }
}

#[allow(dead_code)]
enum Color {
    Red = 0xff0000,
    Green = 0x00ff00,
    Blue = 0x0000ff,
}

fn main() {
    let today = Day::Monday;

    today.mood();

    println!("roses are #{:06x}", Color::Red as i32);
    println!("violets are #{:06x}", Color::Blue as i32);
}
