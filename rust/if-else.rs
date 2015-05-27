fn main() {
    let n = 5;

    if n < 0 {
        println!("{} is negtive", n);
    } else if n > 0 {
        println!("{} is positive", n);
    } else {
        println!("{} is zero", n);
    }

    let big_n =
        if n < 10 && n > -10 {
            println!(", and is a small number, increase ten-fold");
            10 * n
        } else {
            println!(", and is a big number, reduce by two");
            n / 2
        };

    println!("{} -> {}", n, big_n);
}
