const std = @import("std");
const chip8 = @import("Chip8_Emulator");

pub fn main() void {
    std.debug.print("{s}\n", .{chip8.greeting()});
}
