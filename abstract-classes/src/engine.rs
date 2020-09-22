use crate::bindings::{AbstractLoggerBinding, engine_factory, add, register_logger, IMultiplierBinding, register_multiplier, multiply};
use crate::logger::IsLogger;
use std::os::raw::{c_void, c_char};
use std::fmt::Pointer;
use crate::multiplier::IntegerMulitplier;

pub struct Engine {
    ptr: *mut c_void,
}

impl Engine {
    pub fn new(initial_value: i32) -> Engine {
        unsafe {
            Engine {
                ptr: engine_factory(initial_value)
            }
        }
    }

    pub fn add(&self, other: i32) {
        unsafe {
            add(self.ptr, other);
        }
    }

    pub fn register_logger<T>(&mut self, logger: Box<T>)
        where T: IsLogger {
        unsafe extern "C" fn say_hi<T>(context: *mut T)
            where T: IsLogger {
            let logger_ref: &mut T = &mut *context;
            logger_ref.say_hi();
        }

        unsafe extern "C" fn log_value<T>(context: *mut T, message: *const c_char)
            where T: IsLogger {
            let logger_ref: &mut T = &mut *context;
            logger_ref.log_value(message);
        }

        let context: *mut T = Box::into_raw(logger);

        let logger_internal: Box<AbstractLoggerBinding<T>> = Box::new(AbstractLoggerBinding {
            say_hi,
            log_value,
            context,
        });

        let logger_ptr = Box::into_raw(logger_internal) as *mut c_void;

        unsafe { register_logger(self.ptr as *mut c_void, logger_ptr); }
    }

    pub fn register_multiplier<T>(&mut self, multiplier: Box<T>)
    where T: IntegerMulitplier {
        unsafe extern "C" fn mult_int<T>(context: *mut T, other: &mut i32)
            where T: IntegerMulitplier {
            let multiplier_ref: &mut T = &mut *context;
            multiplier_ref.mult_int(other);
        }

        let context: *mut T = Box::into_raw(multiplier);

        let multiplier_internal: Box<IMultiplierBinding<T>> = Box::new(IMultiplierBinding{
            mult_int,
            context,
        });

        let multiplier_ptr = Box::into_raw(multiplier_internal) as *mut c_void;

        unsafe { register_multiplier(self.ptr, multiplier_ptr); }
    }

    pub fn multiply(&mut self) {
        unsafe {
            multiply(self.ptr);
        }
    }
}

