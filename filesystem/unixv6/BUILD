# load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library")

# static library
cc_library(
    name = "v6slib",
    srcs = [
        "diskimg.c",
        "inode.c",
        "unixfilesystem.c",
        "directory.c",
        "pathname.c",
        "chksumfile.c",
        "file.c",
    ],
    hdrs = glob(["*.h"]),
    includes = ["."],
    visibility = ["//visibility:public"]
)

# Main binary
cc_binary(
    name = "diskimageaccess",
    srcs = ["diskimageaccess.c"],
    deps = [":v6slib"],
    linkopts = ["-lssl", "-lcrypto"],
)
