load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

# Load rules_cc for C/C++ build rules
http_archive(
    name = "rules_cc",
    urls = ["https://github.com/bazelbuild/rules_cc/archive/refs/tags/0.0.8.tar.gz"],
    strip_prefix = "rules_cc-0.0.8",
)

# set up C++ toolchain
load("@rules_cc//cc:repositories.bzl", "rules_cc_dependencies")
rules_cc_dependencies()
