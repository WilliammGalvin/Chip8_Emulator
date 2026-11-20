const std = @import("std");

pub fn greeting() []const u8 {
    return "Hello, world!";
}

test "greeting" {
    try std.testing.expectEqualStrings("Hello, world!", greeting());
}
