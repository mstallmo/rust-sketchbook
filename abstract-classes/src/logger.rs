use std::os::raw::c_char;


pub trait IsLogger {
    fn say_hi(&self);

    fn log_value(&self, message: *const c_char);
}