use crate::logger::IsLogger;
use crate::multiplier::IntegerMulitplier;

use std::ffi::c_void;
use std::os::raw::c_char;

#[repr(C)]
pub struct AbstractLoggerBinding<T>
    where T: IsLogger {
    pub say_hi: unsafe extern fn(*mut T),
    pub log_value: unsafe extern fn(*mut T, *const c_char),
    pub context: *mut T,
}


#[repr(C)]
pub struct IMultiplierBinding<T>
    where T: IntegerMulitplier {
    pub mult_int: unsafe extern fn(*mut T, &mut i32),
    pub context: *mut T,
}

#[link(name = "logger", kind = "static")]
extern "C" {
    pub fn say_something(logger: *mut c_void);
    pub fn engine_factory(initial_value: i32) -> *mut c_void;
    pub fn register_logger(engine: *mut c_void, logger: *mut c_void);
    pub fn register_multiplier(engine: *mut c_void, multiplier: *mut c_void);
    pub fn add(engine: *mut c_void, other: i32);
    pub fn multiply(engine: *mut c_void);
}
