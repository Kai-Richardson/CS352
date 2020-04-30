/*1*/ fn main() {
/*2*/     let outer;
/*3*/     {
/*4*/         let inner = String::from("hello!");
/*5*/         outer = inner;
/*6*/     }
/*7*/     println!("{}", outer);
/*8*/ }