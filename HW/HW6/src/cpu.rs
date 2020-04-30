/// Rust's default clock doesn't use the per-process tick counter that C++ does.
/// This module wraps the libc clock functions for equivalent timing, with
/// an API loosely based on the std::time module.
///
/// author: Aaron Moss
/// Based on "malbarbo" answer from https://stackoverflow.com/questions/36716567/is-there-a-rust-equivalent-to-the-clock-function-in-c

use libc::{c_long, time_t, timespec};
use std::io;
use std::mem;
pub use std::time::Duration;

pub struct Instant(timespec);

impl Instant {
    pub fn now() -> Self {
        unsafe {
            let mut time_point = mem::uninitialized();
            let result = libc::clock_gettime(
                libc::CLOCK_PROCESS_CPUTIME_ID, 
                &mut time_point as *mut timespec);
            if result != 0 {
                panic!("cpu::Instant::now(): {}", io::Error::last_os_error());
            }
            Instant(time_point)
        }
    }

    pub fn duration_since(&self, earlier: Instant) -> Duration {
        let mut secs = self.0.tv_sec - earlier.0.tv_sec;
        let mut nanos = self.0.tv_nsec - earlier.0.tv_nsec;
        if nanos < 0 {
            secs -= 1 as time_t;
            nanos += 1000000000 as c_long;
        }
        if secs < 0 { return Duration::from_secs(0); }
        Duration::new(secs as u64, nanos as u32)
    }
}