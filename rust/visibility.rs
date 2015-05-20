mod my {
    pub struct WhiteBox<T> {
        pub contents: T,
    }

    pub struct BlackBox<T> {
        contents: T,
    }

    impl<T> BlackBox<T> {
        pub fn new(contents: T) -> BlackBox<T> {
            BlackBox {
                contents: contents,
            }
        }
    }
}

fn main() {
    let white_box = my::WhiteBox { contents: "public information" };

    println!("The white box contains: {}", white_box.contents);

    //let black_box = my::BlackBox { contents: "classified information" };

    let _black_box = my::BlackBox::new("classified information");

    //println!("The black box contains: {}", _black_box.contents);
}
