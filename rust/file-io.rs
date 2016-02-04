// from b4284: https://gist.github.com/b4284/2a456b60ffad6963a432
use std::{env, fs, io};
use std::io::Read;

fn format_02x_8u8(data: &[u8], missing_value: String) -> String {
    if data.len() >= 8 {
        return format!("{:02x} {:02x} {:02x} {:02x} {:02x} {:02x} {:02x} {:02x}",
                        data[0], data[1], data[2], data[3],
                        data[4], data[5], data[6], data[7]);
    } else {
        let mut q = data.iter().map(|b| format!("{:02x}", b)).collect::<Vec<_>>();

        while q.len() < 8 {
            q.push(missing_value.clone());
        }

        return q.join(" ");
    }
}

fn dump_bin(data: &Vec<u8>) {
    let mut i = 0;

    let mut c1 = data.chunks(16);

    while c1.len() > 0 {
        let mut c2 = c1.next().unwrap().chunks(8);

        let s1 = format_02x_8u8(c2.next().unwrap(), String::from("__"));

        let s2 = format_02x_8u8(match c2.next() {
            None => &[],
            Some(a) => a
        }, String::from("__"));

        println!("{:08x}h: {} {}", i * 16, s1, s2);

        i += 1;
    }

    return ();
}

fn main() {
    if env::args().len() > 1 {
        let fname = &*env::args().nth(1).unwrap();

        let stdin = io::stdin();

        let mut f: Box<Read> = match fname {
            "_" => Box::new(stdin.lock()),
            _ => Box::new(fs::File::open("test.txt").unwrap())
        };

        // let mut f = fs::File::open("test.txt").unwrap();
        let mut buf = Vec::new();

        let _ = f.read_to_end(&mut buf);

        dump_bin(&buf)
    }
}
