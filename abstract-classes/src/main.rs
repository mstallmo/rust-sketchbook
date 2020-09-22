use crate::logger::IsLogger;
use std::os::raw::{c_void, c_char};
use std::ffi::CStr;
use crate::multiplier::IntegerMulitplier;
use std::ops::Mul;

mod logger;
mod bindings;
mod engine;
mod multiplier;

pub struct RustLogger {}

impl IsLogger for RustLogger {
    fn say_hi(&self) {
        println!("Rust Logger!");
        println!("Mason's first abstract binding");
    }

    fn log_value(&self, message: *const c_char) {
        println!("{}", unsafe { CStr::from_ptr(message) }.to_str().unwrap());
    }
}

pub struct Double {}

impl IntegerMulitplier for Double {
    fn mult_int(&self, other: &mut i32) {
        *other *= 2;
    }
}

pub struct Square {}

impl IntegerMulitplier for Square {
    fn mult_int(&self, other: &mut i32) {
        *other *= *other;
    }
}

fn main() {
    println!("Hello, world!");

    let mut engine = engine::Engine::new(1);
    let logger = Box::new(RustLogger {});
    engine.register_logger(logger);
    for _ in 0..10 {
        engine.add(1);
    }

    let double = Box::new(Double {});
    let double_again = Box::new(Double {});
    let square = Box::new(Square {});
    engine.register_multiplier(double);
    engine.register_multiplier(double_again);
    engine.register_multiplier(square);
    engine.multiply();
}
