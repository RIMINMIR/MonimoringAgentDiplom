from conans import ConanFile, CMake


class HelloConan(ConanFile):
    name = "main"
    version = "1.0"
    settings = "os", "compiler", "arch"
    options = {"shared": [True, False]}
    default_options = "shared=False"
    generators = "cmake"
    exports_sources = "src/*"
    requires = (
        "boost/1.72.0",
        "fmt/6.1.2",
        "rapidjson/1.1.0"
    )

    def build(self):
        cmake = CMake(self)
        cmake.configure(source_folder = ".")
        cmake.build()